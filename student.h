#pragma once
#include<iostream>
#include<string>

using namespace std;

class Databank;

template <class Type> 
class List;

/*****************************************************************************************************/
class Student
{
private:
	int id;
	string name;
	enum { male, female } gender;
	int age;
	string type;
public:
	//���캯��
	Student() :id(0), name("\0"), gender(male), age(0), type("\0") {}
	Student(int i):id(i), name("\0"), gender(male), age(0), type("\0"){}

	//��Ԫ�����������
	friend istream& operator>>(istream& is, Student& stu);
	friend ostream& operator<<(ostream& os, const Student& stu);
	friend void input(istream& is, Student& stu);

	//����ʱֻ���ж�id������==�����
	bool operator==(const Student stu)
	{
		return this->id == stu.id;
	}

	friend class Databank;
};
//���뺯��
istream& operator>>(istream& is, Student& stu)
{
	string _gender;
	//��˳���������뿼�ţ��������Ա����䣬�������
	is >> stu.id;
	is >> stu.name;

	is >> _gender;
	if (_gender == "��")
		stu.gender = stu.male;
	else if (_gender == "Ů")
		stu.gender = stu.female;

	is >> stu.age;
	is >> stu.type;

	return is;
}
//���뺯��
void input(istream& is, Student& stu)
{
	is >> stu.name;
	//��˳�����������������Ա����䣬�������
	string _gender;
	is >> _gender;
	if (_gender == "��")
		stu.gender = stu.male;
	else if (_gender == "Ů")
		stu.gender = stu.female;

	is >> stu.age;
	is >> stu.type;
}
//�������
ostream& operator<<(ostream& os, const Student& stu)
{
	if (stu.gender == stu.male)
		printf("%-8d\t%-8s\t%-8s\t%-8d\t%-8s\t", stu.id, stu.name.c_str(), "��", stu.age, stu.type.c_str());
	else if(stu.gender == stu.female)
		printf("%-8d\t%-8s\t%-8s\t%-8d\t%-8s\t", stu.id, stu.name.c_str(), "Ů", stu.age, stu.type.c_str());
	return os;
}


/*****************************************************************************************************/
template<class Type>
class ListNode
{
private:
	Type data;
	ListNode<Type>* next;
	ListNode<Type>* pre;
public:
	//���캯��
	ListNode() :next(NULL), pre(NULL){}
	ListNode(Type _data, ListNode<Type>* i = NULL, ListNode<Type>* j = NULL):data(_data), next(i), pre(j){}
	//��Ԫ��������
	friend class Databank;
	friend class List<Type>;
};

/*****************************************************************************************************/
template<class Type>
class List
{
private:
	ListNode<Type>* first;      //����ͷָ��
	ListNode<Type>* last;       //����βָ��
	int size;                   //����Ԫ�ش�С
public:
	//���켰��������
	List();
	void makeEmpty();
	~List();

	//�������
	int getsize();              //��������ǰ�������������ͷ����������
	bool isEmpty();             //�ж������Ƿ�Ϊ�գ�Ϊ��ʱ����ֵΪ1�����򷵻�0

	//���ܺ���
	ListNode<Type>* find(const Type& d);             //�����Ƿ��е�ǰ��Ԫ�أ����Ҳ���ʱ����NULL�����ҵ�����ָ��ý���ָ��
	void remove(ListNode<Type>* node);               //����Ӧ�����������ɾ��
	void insert(ListNode<Type>* node, Type da);      //�ڶ�Ӧ���ǰ����Ԫ��Ϊda�Ľ��
	void pushback(Type data);                        //������ĩβ������Ԫ��Ϊdata��Ԫ��
	friend class Databank;
};

template<class Type>
List<Type>::List()
{
	first = new ListNode<Type>;
	last = first;
	size = 0;
}

template<class Type>
void List<Type>::makeEmpty()
{
	size = 0;
	ListNode<Type>* p = first->next;
	ListNode<Type>* q;
	while (p != NULL) {
		q = p;
		p = p->next;
		delete q;
	}
	first->next = NULL;
	last = first;
}

template<class Type>
List<Type>::~List()
{
	makeEmpty();
	delete first;
}

//���ص�ǰ����Ԫ�ص�����
template<class Type>
int List<Type>::getsize()
{
	return size;
}

//�ж������Ƿ�Ϊ��
template<class Type>
bool List<Type>::isEmpty()
{
	return (first == last);
}

//�����Ƿ���ָ��ȡֵ�Ľ��
template<class Type>
ListNode<Type>* List<Type>::find(const Type& d)
{
	ListNode<Type>* p = first->next;
	while (p != NULL) {
		if (p->data == d) {
			return p;
		}
		p = p->next;
	}
	return p;
}

//��ָ�������������ɾ��
template<class Type>
void  List<Type>::remove(ListNode<Type>* node)
{
	--size;
	if (node == last) {
		last = node->pre;
		last->next = NULL;
	}
	else {
		node->next->pre = node->pre;
		node->pre->next = node->next;
	}
	delete node;
	return;
}

//�������ָ��λ�ò���ָ��Ԫ�صĽ��
template<class Type>
void List<Type>::insert(ListNode<Type>* node,Type da)
{
	++size;
	node->pre->next = new ListNode<Type>(da, node, node->pre);
	node->pre = node->pre->next;
}

//�������ĩβ����ָ��Ԫ�صĽ��
template<class Type>
void List<Type>::pushback(Type da)
{
	++size;
	ListNode<Type>* newnode = new ListNode<Type>(da, NULL, last);
	last->next = newnode;
	last = newnode;
}