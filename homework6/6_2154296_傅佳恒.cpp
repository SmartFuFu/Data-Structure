
//�����������ֵܵķ�ʽ�洢�����
#include<iostream>
#include<conio.h>
#include<string>
using namespace std;


template <class Type>
class Tree;

//���Ľ��
template <class Type>
class TreeNode {
public:
	friend class Tree<Type>;
	friend void print_tree();      //��Ԫ������չʾ��
	friend void print_Mtree(string prefix, TreeNode<string>* p);
private:
	Type data;
	TreeNode<Type>* firstChild;   //���ӽ��
	TreeNode<Type>* nextSibling;  //���ֵܽ��
	TreeNode(Type value = 0, TreeNode<Type>* fc = NULL, TreeNode<Type>* ns = NULL) : data(value), firstChild(fc), nextSibling(ns) { }
};
//��
template <class Type>
class Tree {
public:
	Tree() { root = current = NULL; }      //���캯������������
	Tree(Type rootVal);                    //���캯����������rootValԪ��Ϊ���ڵ����
	~Tree();                               //��������
	bool isEmpty();                        //�Ƿ�Ϊ����
	bool BuildRoot(Type rootVal);          //�ڿ����Ļ����ϣ�������rootValԪ��Ϊ���ڵ����
	bool Root();                           //�����ĸ�����Ϊ��ǰ���
	bool Find(Type target);                //�����Ƿ��н��ֵΪtarget�Ľ��,ʹ֮��Ϊ��ǰ���
	bool FirstChild();                     //������Ѱ�ҵ�ǰ���ĳ���,ʹ֮��Ϊ��ǰ���
	bool NextSibling();                    //������Ѱ�ҵ�ǰ�����ֵ�,ʹ֮��Ϊ��ǰ���
	bool Parent();                         //������Ѱ�ҵ�ǰ����˫��,ʹ֮��Ϊ��ǰ���
	bool insert_child(Type data);                   //����ǰ�����Ӻ���
	Type root_data();                      //�������Ƚ���ȡֵ
	Type current_data();                   //���ص�ǰ����ȡֵ
	bool current_available();              //�жϵ�ǰ����Ƿ��ȡֵ
	void change_current(Type d);           //�ı䵱ǰ���ȡֵ
	bool delete_tree(Type data);             //ɾ����ֵΪdata�Ľ��Ϊ������������
	void delete_tree(TreeNode<Type>* p);     //ɾ���Ե�ǰ���Ϊ������������
	friend void print_tree();      //��Ԫ������չʾ��
	friend void print_Mtree(string prefix, TreeNode<string>* p);
private:
	TreeNode<Type>* root;                                  //�����
	TreeNode<Type>* current;                               //��ǰ���
	bool Find(TreeNode<Type>* p, Type target);              //����ʱ���õݹ�
	bool FindParent(TreeNode<Type>* t, TreeNode<Type>* p);  //��˫��ʱ�ݹ�
};
//���캯����������rootValԪ��Ϊ���ڵ����
template <class Type>
Tree<Type>::Tree(Type rootVal)
{
	root = current = new TreeNode <Type>(rootVal);
}

//��������
template <class Type>
Tree<Type>::~Tree()
{
	delete_tree(root);
}

//�Ƿ�Ϊ����
template <class Type>
bool Tree<Type>::isEmpty()
{
	return root == NULL;
}

//�ڿ����Ļ����ϣ�������rootValԪ��Ϊ���ڵ����
template <class Type>
bool Tree<Type>::BuildRoot(Type rootVal)
{
	if (!isEmpty())
		return 0;
	else {
		root = current = new TreeNode <Type>(rootVal);
		return 1;
	}
}

//�����ĸ�����Ϊ��ǰ���
template <class Type>
bool Tree<Type>::Root()
{
	if (root == NULL) {
		current = NULL;
		return 0;
	}
	else {
		root = current;
		return 1;
	}
}

//�����Ƿ��н��ֵΪtarget�Ľ��,ʹ֮��Ϊ��ǰ���
template <class Type>
bool Tree<Type>::Find(Type target)
{
	if (isEmpty()) {
		return 0;
	}
	else
		return Find(root, target);
}
template<class Type>
bool Tree<Type>::Find(TreeNode<Type>* p, Type target)
{
	bool result = 0;
	if (p->data == target)
	{
		result = 1;
		current = p;
	}
	else {
		TreeNode<Type>* q = p->firstChild;
		while (q != NULL && !(result = Find(q, target)))
			q = q->nextSibling;
	}
	return result;
}

//������Ѱ�ҵ�ǰ���ĳ���,ʹ֮��Ϊ��ǰ���
template<class Type>
bool Tree<Type>::FirstChild()
{
	if (current == NULL)
		return 0;
	else {
		current = current->firstChild;
		if (current == NULL)
			return 0;
		else
			return 1;
	}
}

//������Ѱ�ҵ�ǰ�����ֵ�,ʹ֮��Ϊ��ǰ���
template<class Type>
bool Tree<Type>::NextSibling()
{
	if (current == NULL)
		return 0;
	else {
		current = current->nextSibling;
		if (current == NULL)
			return 0;
		else
			return 1;
	}
}

//������Ѱ�ҵ�ǰ����˫��,ʹ֮��Ϊ��ǰ���
template<class Type>
bool Tree<Type>::Parent()
{
	if (current == NULL || current == root || isEmpty()) {
		current = NULL;
		return 0;
	}
	else {
		TreeNode<Type>* p = current;
		return FindParent(root, p);
	}
}
template<class Type>
bool Tree<Type>::FindParent(TreeNode<Type>* t, TreeNode<Type>* p)
{
	TreeNode<Type>* q = t->firstChild;
	while (q != NULL && q != p) {
		//ѭ���ĳ��ӵ��ֵ���,�ݹ�������������
		bool i;
		if ((i = FindParent(q, p)) != 0)
			return i;
		q = q->nextSibling;
	}
	if (q != NULL && q == p) {
		current = t;
		return 1;
	}
	else
		return 0;
}

//����ǰ�����Ӻ���
template<class Type>
bool Tree<Type>::insert_child(Type data)
{
	if (current == NULL)
		return 0;
	else {
		TreeNode<Type>* p = current->firstChild;
		if (p == NULL)
			current->firstChild = new TreeNode<Type>(data);
		else {
			TreeNode<Type>* q = p->nextSibling;
			while (q != NULL) {
				p = q;
				q = q->nextSibling;
			}
			p->nextSibling = new TreeNode<Type>(data);
		}
		return 1;
	}
}

//�������Ƚ���ȡֵ
template<class Type>
Type Tree<Type>::root_data()
{
	return root->data;
}

//���ص�ǰ����ȡֵ
template<class Type>
Type Tree<Type>::current_data()
{
	return current->data;
}

//�жϵ�ǰ����Ƿ��ȡֵ
template<class Type>
bool Tree<Type>::current_available()
{
	return current != NULL;
}

//���ĵ�ǰ���ȡֵ
template<class Type>
void Tree<Type>::change_current(Type d)
{
	if (current != NULL)
		current->data = d;
}

//ɾ���Ե�ǰ���Ϊ������������
template<class Type>
bool Tree<Type>::delete_tree(Type data)
{
	if (Find(data) == 0) {
		return 0;
	}
	TreeNode<Type>* del = current;
	if (current == root) {
		root = current = NULL;
	}
	else {
		TreeNode<Type>* p = current;
		Parent();
		TreeNode<Type>* q = current->firstChild;
		if (p == q) {
			current->firstChild = current->firstChild->nextSibling;
		}
		else {
			while (q->nextSibling != p && q->nextSibling != NULL) {
				q = q->nextSibling;
			}
			q->nextSibling = p->nextSibling;
		}
		p->nextSibling = NULL;
	}
	delete_tree(del);
	return 1;
}
template<class Type>
void Tree<Type>::delete_tree(TreeNode<Type>* p)
{
	if (p == NULL)
		return;
	else {
		delete_tree(p->firstChild);
		delete_tree(p->nextSibling);
		delete p;
		p = NULL;
	}
}


//�������Ľṹ�洢����
Tree<string> family;

void wait_for_enter()
{
	cout << endl
		<< "���س�������";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

//��ʼ��һ������
void init()
{
	cout << "*****************************************" << endl;
	cout << "**            ���׹���ϵͳ             **" << endl;
	cout << "*****************************************" << endl;
	cout << "**  ��ѡ��Ҫִ�еĲ�����               **" << endl;
	cout << "**            A---���Ƽ���             **" << endl;
	cout << "**            B---��Ӽ�ͥ��Ա         **" << endl;
	cout << "**            C---��ɢ�ֲ���ͥ         **" << endl;
	cout << "**            D---���ļ�ͥ��Ա��Ϣ     **" << endl;
	cout << "**            E---չʾ��ͥ��Աֱϵ���� **" << endl;
	cout << "**            F---�����ӡ����         **" << endl;
	cout << "**            G---�˳�����             **" << endl;
	cout << "*****************************************" << endl;
	cout << endl;

	string name;
	cout << "�����뽨��һ������" << endl;
	cout << "���������ȵ�������";
	cin >> name;
	family.BuildRoot(name);
	cout << "�˼��׵�������" << family.root_data() << endl;
}
//����
void print_tree()
{
	if (family.isEmpty()) {
		cout << "�����б�Ϊ��" << endl;
		return;
	}
	print_Mtree(" ", family.root);
}
void print_Mtree(string prefix, TreeNode<string>* p)
{
	if (p != NULL) {
		cout << prefix;
		if (p->nextSibling == NULL)
			cout << "������";
		else
			cout << "������";
		cout << " " << p->data << endl;
		TreeNode<string>* q = p->firstChild;
		for (; q != NULL; q = q->nextSibling) {
			if (p->nextSibling == NULL)
				print_Mtree(prefix + "    ", q);
			else
				print_Mtree(prefix + "��   ", q);
		}
	}
}
//����ǰ���ĵ�һ����Ů��ӡ����
void print_first_generation()
{
	cout << family.current_data() << "�ĵ�һ�������ǣ�";
	if (family.FirstChild()) {
		cout << family.current_data() << " ";
		while (family.NextSibling())
			cout << family.current_data() << " ";
		cout << endl;
	}
	else {
		cout << "��" << endl;
	}

}

//���Ƽ���
void improve_tree()
{
	string name;
	cout << "������Ҫ������ͥ���˵�������";
	cin >> name;
	if (!family.Find(name)) {
		cout << "û���ڼ����в��ҵ��ó�Ա" << endl;
		return;
	}

	int num;
	while (1) {
		cout << "������" << name << "�Ķ�Ů������";
		cin >> num;
		if (!cin.good()) {
			cout << "��������һ���������������" << endl;
		}
		else if (num <= 0) {
			cout << "������һ��������" << endl;
		}
		else
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}

	string name1;
	for (int i = 0; i < num; i++) {
		cout << "�������" << i + 1 << "����Ů�����֣�" << endl;
		cin >> name1;
		family.insert_child(name1);
	}

	print_first_generation();
	print_tree();
}

//��Ӽ�ͥ��Ա
void append_child()
{
	string parent, child;
	cout << "������Ҫ��Ӷ��ӣ���Ů�������˵�������";
	cin >> parent;
	if (!family.Find(parent)) {
		cout << "û���ڼ����в��ҵ��ó�Ա" << endl;
		return;
	}

	cout << "������" << parent << "����Ӷ��ӣ���Ů������������";
	cin >> child;
	family.insert_child(child);

	print_first_generation();
	print_tree();
}

//ɾ���ֲ���ͥ
void delete_family()
{
	string name;
	cout << "������Ҫ��ɢ��ͥ���˵�������";
	cin >> name;
	if (!family.Find(name)) {
		cout << "û���ڼ����в��ҵ��ó�Ա" << endl;
		return;
	}
	cout << "Ҫ��ɢ��ͥ�����ǣ�" << name << endl;
	family.delete_tree(name);
	cout << "�ѽ�ɢ" << endl;
	print_tree();
}

//���ļ�ͥ��Ա����
void change_name()
{
	string first_name, sec_name;
	cout << "���������������Ŀǰ��������";
	cin >> first_name;
	if (!family.Find(first_name)) {
		cout << "û���ڼ����в��ҵ��ó�Ա" << endl;
		return;
	}
	cout << "��������ĺ��������";
	cin >> sec_name;
	family.change_current(sec_name);
	cout << first_name << "�Ѹ���Ϊ" << family.current_data() << endl;
	print_tree();
}

//չʾ��ͥ��Աֱϵ����
void print_data()
{
	string name;
	cout << "��ѡ����Ҫ��ѯֱϵ������������";
	cin >> name;
	if (!family.Find(name)) {
		cout << "û���ڼ����в��ҵ��ó�Ա" << endl;
		return;
	}
	if (family.Parent())
		cout << "�ý���˫��Ϊ��" << family.current_data() << endl;
	else
		cout << "�ý����˫��" << endl;

	family.Find(name);
	print_first_generation();
}




int main()
{
	init();
	char choice;
	while (1) {
		cout << endl;
		cout << "��ѡ����Ҫִ�еĲ�����";
		cin >> choice;

		switch (choice)
		{
			case 'A':
				improve_tree();

				break;
			case'B':
				append_child();
				break;
			case'C':
				delete_family();
				break;
			case'D':
				change_name();
				break;
			case'E':
				print_data();
				break;
			case'F':
				print_tree();
				break;
			case'G':
				cout << "�������н���" << endl;
				wait_for_enter();
				return 0;
				break;
			default:
				cout << "�������˲��Ϸ���ѡ��" << endl;
				break;

		}
		if (family.isEmpty())
		{
			cout << endl;
			cout << "����Ϊ�գ��޷����в���" << endl;
			string name;
			cout << "�����뽨��һ������" << endl;
			cout << "���������ȵ�������";
			cin >> name;
			family.BuildRoot(name);
			cout << "�˼��׵�������" << family.root_data() << endl;
		}

	}

	return 0;
}