#include<iostream>
#include<conio.h>
using namespace std;

template <class Type>
class Stack;

template <class Type>
class StackNode {
	friend class Stack<Type>;
private:
	Type data;                   //�������
	StackNode<Type>* link;       //�����ָ��
	StackNode(Type d = 0, StackNode<Type>* l = NULL) : data(d), link(l) { }
};

template <class Type> class Stack {
public:
	Stack() : top(NULL) { }
	~Stack();                        //���������������ÿ�
	void Push(const Type& item);     //������ѹ��ջ��
	Type Pop();                      //��ջ�����ݵ���
	Type GetTop();                   //ȡջ������
	void MakeEmpty();                //��ջ�ÿ�
	bool IsEmpty() const
	{
		return top == NULL;
	}
private:
	StackNode<Type>* top; //ջ��ָ��
};

//���������������ÿ�
template <class Type>
Stack<Type>::~Stack() {
	StackNode<Type>* p;
	while (top != NULL) //�������
	{
		p = top;
		top = top->link;
		delete p;
	}
}
// ������ѹ��ջ��
template <class Type>
void Stack<Type>::Push(const Type& item) {
	top = new StackNode<Type>(item, top);
}

//��ջ�����ݵ���
template <class Type>
Type Stack<Type>::Pop() {
	StackNode<Type>* p = top;
	Type retvalue = p->data;
	top = top->link;
	delete p;
	return retvalue;
}

//��ȡ�������
template <class Type>
Type Stack<Type>::GetTop() {
	return top->data;
}

//���ջ
template <class Type>
void Stack<Type>::MakeEmpty()
{
	StackNode<Type>* p;
	while (top != NULL) //�������
	{
		p = top;
		top = top->link;
		delete p;
	}
}


//���Դ�ű��ʽ������
char expression[100] = { '\0' };

//��ͣ�����س�������
void wait_for_enter()
{
	cout << endl
		<< "���س�������";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

//�����ж���������ȼ�
int find_priority(char A) {
	if (A == '(')
		return 1;
	else if (A == '+' || A == '-')
		return 2;
	else if (A == '*' || A == '/')
		return 3;
	else if (A == ')')
		return 4;
	else
		return 0;//��ʾ�����������֧��
}
//�ж��Ƿ�Ϊ��
bool isnum(int cur) {
	return (expression[cur] >= '0' && expression[cur] <= '9') || expression[cur] == '.';
}

//��ӡ���ݲ��ƶ��α�
void print_num_and_move(int& cur)
{
	char num[20] = { '\0' };
	int i = 0;
	if (isnum(cur)) {
		while (isnum(cur)) {
			num[i] = expression[cur];
			++i;
			++cur;
		}
		--cur;
		cout << num << " ";
	}
}

//�ж�+-�Ƿ�Ϊ������
bool isfront(int cur)
{
	if (cur == 0 && isnum(cur + 1))
		return 1;
	else if (cur > 0 && !isnum(cur - 1) && isnum(cur + 1))
		return 1;
	return 0;
}

//������ʽ�ո�
void delete_blank() {
	int MAX;
	int i = 0;
	for (; expression[i] != '\0'; ++i) {}
	MAX = i - 1;
	for (int j = 0; expression[j] != '\0'; ++j) {
		if (expression[j] == ' ') {
			for (int k = j; k < MAX; ++k) {
				expression[k] = expression[k + 1];
			}
			expression[MAX] = '\0';
			MAX--;
		}
	}
}

int main()
{
	cout << "������һ����׺���ʽ����֧��������Ӽ��˳����������ţ���";
	cin.get(expression, 100);   //������ո�ı��ʽ
	//delete_blank();            //�����ʽ�����пո�ɾ��
	cout << "���ڽ���׺���ʽת��Ϊ��׺" << endl;
	cout << "ת������ʽΪ��";
	Stack<char> sign;
	sign.MakeEmpty();
	for (int cur = 0; expression[cur] != '\0'; ++cur) {
		char c = expression[cur];
		switch (c) {
			case'-':
				if (isfront(cur)) {
					cout << "-";
					print_num_and_move(++cur);
				}
				else {
					if (sign.IsEmpty() || sign.GetTop() == '(') {
						sign.Push('-');
					}
					else {
						while (!sign.IsEmpty() && sign.GetTop() != '(') {
							char d = sign.Pop();
							cout << d << " ";
						}
						sign.Push('-');
					}
				}
				break;
			case'+':
				if (!isfront(cur)) {
					if (sign.IsEmpty() || sign.GetTop() == '(')
						sign.Push('+');
					else {
						while (!sign.IsEmpty() && sign.GetTop() != '(') {
							char d = sign.Pop();
							cout << d << " ";
						}
						sign.Push('+');
					}
				}
				break;
			case'*':
				if (sign.IsEmpty() || find_priority('*') > find_priority(sign.GetTop())) {
					sign.Push(c);
				}
				else {
					//������С��*/���ȼ��������������*��/
					while (!sign.IsEmpty() && (sign.GetTop() == '*' || sign.GetTop() == '/')) {
						char d = sign.Pop();
						cout << d << " ";
					}
					sign.Push(c);
				}
				break;
			case'/':
				if (sign.IsEmpty() || find_priority('/') > find_priority(sign.GetTop())) {
					sign.Push(c);
				}
				else {
					//������С��*/���ȼ��������������*��/
					while (!sign.IsEmpty() && (sign.GetTop() == '*' || sign.GetTop() == '/')) {
						char d = sign.Pop();
						cout << d << " ";
					}
					sign.Push(c);
				}
				break;
			case'(':
				sign.Push('(');
				break;
			case')':
				while (sign.GetTop() != '(') {
					char d = sign.Pop();
					cout << d << " ";
				}
				sign.Pop();
				break;
			default://�������ֵ�����
				print_num_and_move(cur);
				break;
		}
	}
	while (!sign.IsEmpty()) {
		char d = sign.Pop();
		cout << d << " ";
	}
	cout << endl;
	cout << "�������" << endl;
	wait_for_enter();
	return 0;
}