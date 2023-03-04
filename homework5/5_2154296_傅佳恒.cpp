#include<iostream>
#include<conio.h>
using namespace std;
template <class Type>
class Queue;

template <class Type>
class QueueNode {
	friend class Queue<Type>;
private:
	Type data;                    //���н������
	QueueNode<Type>* link;        //�����ָ��
	QueueNode(Type d = 0, QueueNode* l = NULL) : data(d), link(l) { }
};

template <class Type>
class Queue {
private:
	QueueNode<Type>* front, * rear; //����ָ��
public:
	Queue() : rear(NULL), front(NULL) { }       //���캯��
	~Queue();                                   //��������
	void EnQueue(const Type& item);             //����Ԫ��item���뵽���еĶ�β
	Type DeQueue();                             //ɾȥ��ͷ��㣬�����ض�ͷԪ�ص�ֵ
	Type GetFront();                            //���ض���ͷ��ֵ
	void MakeEmpty();                           //�������ÿ�
	int IsEmpty() const
	{
		return front == NULL;
	}
};

//���е���������
template <class Type>
Queue<Type>::~Queue() {
	QueueNode<Type>* p;
	while (front != NULL) { //�������ͷ�
		p = front;
		front = front->link;
		delete p;
	}
}

//����Ԫ��item���뵽���еĶ�β
template <class Type>
void Queue<Type>::EnQueue(const Type& item) {

	if (front == NULL)
		front = rear = new QueueNode<Type>(item, NULL);
	else {
		rear->link = new QueueNode<Type>(item, NULL);
		rear = rear->link;
	}
}

//ɾȥ��ͷ��㣬�����ض�ͷԪ�ص�ֵ
template <class Type>
Type Queue<Type>::DeQueue() {
	QueueNode<Type>* p = front;
	Type retvalue = p->data; //�����ͷ��ֵ
	front = front->link; //�¶�ͷ
	delete p;
	return retvalue;
}

//���ض���ͷ��ֵ
template <class Type>
Type Queue<Type>::GetFront()
{
	return front->data;
}

//�������ÿ�
template <class Type>
void Queue<Type>::MakeEmpty()
{
	QueueNode<Type>* p;
	while (front != NULL) { //�������ͷ�
		p = front;
		front = front->link;
		delete p;
	}
	front = rear = NULL;
}

void wait_for_enter()
{
	cout << endl
		<< "���س�������";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

int main()
{
	int N;
	Queue<int> A;
	Queue<int> B;
	cout << "����ҵ��ϵͳ��ʼ����" << endl;
	while (1) {
		cout << "������˿�����N��";
		cin >> N;
		if (!cin.good())
			cout << "��������������������һ��������" << endl;
		else if (N <= 0)
			cout << "������һ��������" << endl;
		else
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}

	cout << "����������" << N << "��������������Ϊ" << N << "λ�˿͵ı�ţ�";
	for (int i = 0; i < N; ++i) {
		int num;
		cin >> num;
		if (num % 2 == 1) {
			A.EnQueue(num);
		}
		else {
			B.EnQueue(num);
		}
	}

	cout << "�������Ϊ��";
	while (!A.IsEmpty() || !B.IsEmpty()) {
		int data;
		if (!A.IsEmpty()) {
			data = A.DeQueue();
			cout << data << " ";
		}
		if (!A.IsEmpty()) {
			data = A.DeQueue();
			cout << data << " ";
		}
		if (!B.IsEmpty()) {
			data = B.DeQueue();
			cout << data << " ";
		}
	}
	cout << endl;
	wait_for_enter();
	return 0;
}
