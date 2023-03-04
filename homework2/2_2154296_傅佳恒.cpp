#include<iostream>
#include<conio.h>
using namespace std;

template <class Type>
class List;
template <class Type>
class ListNode;


/*****************************************************************************************************/
template<class Type>
class ListNode
{
public:
	Type data;
	ListNode<Type>* next;
	ListNode<Type>* pre;

	//���캯��
	ListNode() :next(NULL), pre(NULL) {}
	ListNode(Type _data, ListNode<Type>* i = NULL, ListNode<Type>* j = NULL) :data(_data), next(i), pre(j) {}
	//��Ԫ����
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
	List(const List<Type>& DA);       //���ƹ��캯������һ������
	void makeEmpty();
	~List();

	//�������
	int getsize();               //��������ǰ�������������ͷ����������
	bool isEmpty();              //�ж������Ƿ�Ϊ�գ�Ϊ��ʱ����ֵΪ1�����򷵻�0
	ListNode<Type>* getfirst();  //��������ı�ͷ���

	//���ܺ���
	ListNode<Type>* find(const Type& d);             //�����Ƿ��е�ǰ��Ԫ�أ����Ҳ���ʱ����NULL�����ҵ�����ָ��ý���ָ��
	void remove(ListNode<Type>* node);               //����Ӧ�����������ɾ��
	void insert(ListNode<Type>* node, Type da);      //�ڶ�Ӧ���ǰ����Ԫ��Ϊda�Ľ��
	void pushback(Type data);                        //������ĩβ������Ԫ��Ϊdata��Ԫ��

	//��Ԫ����
	template <class Type>
	friend List<Type> intersection(const List<Type>& line1, const List<Type>& line2);
};

template<class Type>
List<Type>::List()
{
	first = new ListNode<Type>;
	last = first;
	size = 0;
}

template<class Type>
List<Type>::List(const List<Type>& DA)
{
	first = new ListNode<Type>;
	last = first;
	size = 0;
	ListNode<Type>* p = DA.first->next;
	while (p != NULL) {
		pushback(p->data);
		p = p->next;
	}
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

//���������ͷ���
template<class Type>
ListNode<Type>* List<Type>::getfirst()
{
	return first;
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
void List<Type>::insert(ListNode<Type>* node, Type da)
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

/*****************************************************************************************************/
void wait_for_enter()
{
	cout << endl
		<< "���س�������";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

template<class Type>
List<Type> intersection(const List<Type>& line1, const List<Type>& line2)
{
	List<Type> result;
	ListNode<Type>* p = line1.first->next;
	ListNode<Type>* q = line2.first->next;
	while (p != NULL && q != NULL) {
		if (p->data == q->data) {
			result.pushback(p->data);
			p = p->next;
			q = q->next;
		}
		else if (p->data > q->data) {
			q = q->next;
		}
		else if (p->data < q->data) {
			p = p->next;
		}
	}

	return result;
}


int main()
{

	List<int> line1, line2;
	cout << "�������һ���ǽ�������������(��-1Ϊ���������־)��" << endl;
	int i = 0;
	while (1) {
		cin >> i;
		if (i == -1)
			break;
		line1.pushback(i);
	}
	cout << "������ڶ����ǽ�������������(��-1Ϊ���������־)��" << endl;
	i = 0;
	while (1) {
		cin >> i;
		if (i == -1)
			break;
		line2.pushback(i);
	}

	List<int>line3 = intersection(line1, line2);

	cout << "������ʾ���£�" << endl;
	if (line3.isEmpty()) {
		cout << "NULL" << endl;
	}
	else {
		ListNode<int>* p = line3.getfirst();
		p = p->next;
		while (p != NULL) {
			cout << p->data << " ";
			p = p->next;
		}
		cout << endl;
	}

	wait_for_enter();

	return 0;
}