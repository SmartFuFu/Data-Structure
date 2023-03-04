#include <conio.h>
#include<ctime>
#include<iostream>
using namespace std;
/*****************************************************************************************************/
template<class T1, class T2>
struct Pair {
	T1 first;
	T2 second;
	//���캯��
	Pair() {};
	Pair(T1 _first, T2 _second) {
		this->first = _first;
		this->second = _second;
	}
	Pair(const Pair<T1, T2>& T) {
		this->first = T.first;
		this->second = T.second;
	}
	//���صȺ������
	Pair& operator=(const Pair<T1, T2>& T) {
		this->first = T.first;
		this->second = T.second;
		return *this;
	}
	//�����ж��������Ƿ����
	bool operator==(const Pair<T1, T2>& T) {
		return this->first == T.first && this->second == T.second;
	}
	//�����ж��������Ƿ񲻵�
	bool operator!=(const Pair<T1, T2>& T) {
		return this->first != T.first || this->second != T.second;
	}

};
//���������������pair��ӣ�����һ��pair
template<class T1, class T2>
Pair<T1, T2> operator+(const Pair<T1, T2>& TONG, const Pair<T1, T2>& JI) {
	return Pair<T1, T2>(TONG.first + JI.first, TONG.second + JI.second);
}

/*****************************************************************************************************/
template<class Type>
class List;

template<class Type>
class ListNode
{
private:
	Type data;
	ListNode<Type>* next;
	ListNode<Type>* pre;
public:
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
	Type getdata_num(int n);     //��ȡ��n���������

	//���ܺ���
	ListNode<Type>* find(const Type& d);             //�����Ƿ��е�ǰ��Ԫ�أ����Ҳ���ʱ����NULL�����ҵ�����ָ��ý���ָ��
	void remove(ListNode<Type>* node);               //����Ӧ�����������ɾ��
	void remove_number(int n);                       //�������е�n�����ɾ��
	void insert(ListNode<Type>* node, Type da);      //�ڶ�Ӧ���ǰ����Ԫ��Ϊda�Ľ��
	void pushback(Type data);                        //������ĩβ������Ԫ��Ϊdata��Ԫ��

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

//��ȡ��n���������
template<class Type>
Type List<Type>::getdata_num(int n)
{
	if (isEmpty()) {
		cout << "����Ϊ�գ���������" << endl;
		exit(1);
	}
	if (n > size) {
		cout << "����ɾ�����ݳ�������ǰ��С����������" << endl;
		exit(1);
	}
	if (n <= 0) {
		cout << "�������ֵΪ��������������" << endl;
		exit(1);
	}
	ListNode<Type>* p = first;
	for (int i = 0; i < n; ++i) {
		p = p->next;
	}
	return p->data;
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

//�������е�n�����ɾ��
template<class Type>
void List<Type>::remove_number(int n)
{
	if (isEmpty()) {
		cout << "����Ϊ�գ���������" << endl;
		return;
	}
	if (n > size) {
		cout << "����ɾ�����ݳ�������ǰ��С����������" << endl;

	}
	if (n <= 0) {
		cout << "�������ֵΪ��������������" << endl;
		return;
	}
	ListNode<Type>* p = first;
	for (int i = 0; i < n; ++i) {
		p = p->next;
	}
	this->remove(p);
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
	int IsEmpty() const
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

//ö�����ͣ�ǽ���հף�·
enum maze_type
{
	WALL = 0, BLANK, WAY
};

typedef Pair<int, int> position;

//����Թ��Ķ�ά����
int MAX_X;                  //��ͼ��
int MAX_Y;                  //��ͼ��
maze_type** maze_map;       //��ͼ����
Stack<position> PATH;

const position direction[4] = { {0,1},{1,0},{0,-1},{-1,0} };

void wait_for_enter()
{
	cout << endl
		<< "���س�������";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

//�ж�λ��P�Ƿ��ڵ�ͼ��
bool isIN(position P)
{
	return P.first <= MAX_X && P.first > 0 && P.second <= MAX_Y && P.second > 0;
}
//�ж�λ��P�Ƿ�Ϊ�հ�
bool isBLANK(position P)
{
	return isIN(P) && maze_map[P.first][P.second] == BLANK;
}
//�ж�λ��P�Ƿ�Ϊǽ
bool isWALL(position P)
{
	return isIN(P) && maze_map[P.first][P.second] == WALL;
}
//��ʼ����ͼ��ʹ��ͼȫΪ�հ�
void init_BLANK()
{
	for (int i = 1; i <= MAX_X; ++i) {
		for (int j = 1; j <= MAX_Y; ++j) {
			maze_map[i][j] = BLANK;
		}
	}
}
//��ʼ����ͼ��ʹ��ͼȫΪǽ
void init_WALL()
{
	for (int i = 1; i <= MAX_X; ++i) {
		for (int j = 1; j <= MAX_Y; ++j) {
			maze_map[i][j] = WALL;
		}
	}
}
//��ӡ��ͼ
void print_map()
{
	cout << "�Թ���·��ʾ������($��ʾ·����#��ʾǽ��)��" << endl;
	printf("    ");
	for (int i = 0; i <= MAX_Y + 1; ++i) {
		printf(" %2d ", i);
	}
	printf("\n");
	//��0��
	printf("  0 ");
	for (int i = 0; i <= MAX_Y + 1; ++i) {
		printf("  # ");
	}
	printf("\n\n");
	//��ͼ��
	for (int i = 1; i <= MAX_X; i++) {
		printf(" %2d ", i);
		printf("  # ");
		for (int j = 1; j <= MAX_Y; j++) {
			if (maze_map[i][j] == WALL)
				printf("  # ");
			else if (maze_map[i][j] == BLANK)
				printf("    ");
			else if (maze_map[i][j] == WAY)
				printf("  $ ");
		}
		printf("  # \n\n");
	}
	//���һ��
	printf(" %2d ", MAX_X + 1);
	for (int i = 0; i <= MAX_Y + 1; ++i) {
		printf("  # ");
	}
	printf("\n");
}
//��ӡ·��
void print_path() {
	cout << "������·�����£�" << endl;
	position temp;
	int k = 0;
	Stack<position> realPATH;
	realPATH.MakeEmpty();
	while (!PATH.IsEmpty()) {
		realPATH.Push(PATH.Pop());
	}
	while (!realPATH.IsEmpty()) {
		temp = realPATH.Pop();
		if (k == 0) {
			cout << " (" << temp.first << "," << temp.second << ") ";
			k++;
		}
		else
			cout << "---> (" << temp.first << "," << temp.second << ") ";
	}
}
//����Prim�㷨���ͼ
void Prim()
{

	List<position> T;
	//��<1,1>λ�ÿ�ʼ��������
	position A{ 1,1 };
	T.pushback(A);
	init_WALL();//����ͼȫ��Ϊǽ
	while (!T.isEmpty()) {//������Ϊ��ʱֹͣѭ��
		//�����������һ��Ԫ�ؼ�¼��������ɾ��
		int i = rand() % T.getsize() + 1;
		position current = T.getdata_num(i);
		T.remove_number(i);
		//�����λ�����ܿɴﵽ��λ����
		int road = 0;
		for (int i = 0; i < 4; ++i)
		{
			position nextPos = current + direction[i];
			if (isBLANK(nextPos))
				road++;
		}
		//��λ��С��1����ôΪ��һ·������ǽ����
		if (road <= 1) {
			maze_map[current.first][current.second] = BLANK;
			//������λ�����ܣ�����λ������ǽ��������
			for (int i = 0; i < 4; ++i)
			{
				position nextPos = current + direction[i];
				if (isWALL(nextPos))
					T.pushback(nextPos);
			}
		}
	}
}

//���õݹ��㷨����Թ�
int travelmaze(position current, position goal) {
	if (current == goal) {
		maze_map[current.first][current.second] = WAY;
		return 1;
	}
	else {
		for (int i = 0; i < 4; i++) {
			position temp = current + direction[i];
			if (isBLANK(temp)) {
				maze_map[temp.first][temp.second] = WAY;
				PATH.Push(temp);
				if (travelmaze(temp, goal)) {
					return 1;
				}
				maze_map[temp.first][temp.second] = BLANK;
				PATH.Pop();
			}
		}
	}
	return 0;
}

//ʹ�÷ǵݹ��㷨����Թ�
bool dfs(position start, position goal) {
	//����һ����ǵ�����
	bool** mark;
	mark = new bool* [MAX_X + 1];
	for (int i = 1; i <= MAX_X; ++i) {
		mark[i] = new bool[MAX_Y + 1];
	}
	for (int i = 1; i <= MAX_X; ++i) {
		for (int j = 1; j <= MAX_Y; ++j) {
			mark[i][j] = 0;
		}
	}
	PATH.Push(start);
	mark[start.first][start.second] = 1;
	position temp;
	while (!PATH.IsEmpty()) {
		temp = PATH.GetTop();
		if (temp == goal)
			break;
		bool is_next_way = 0;
		for (int i = 0; i < 4; i++) {
			position next = temp + direction[i];
			if (isBLANK(next) && !mark[next.first][next.second]) {
				PATH.Push(next);
				maze_map[next.first][next.second] = WAY;
				mark[next.first][next.second] = 1;
				is_next_way = 1;
				break;
			}
		}
		if (!is_next_way) {
			maze_map[temp.first][temp.second] = BLANK;
			PATH.Pop();
		}
	}
	//�������Ŀռ�
	for (int i = 1; i <= MAX_X; ++i) {
		delete[] mark[i];
	}
	delete[] mark;
	if (PATH.IsEmpty())
		return 0;
	else
		return 1;
}

int main()
{
	srand(time(NULL));     //���������

	//��������
	cout << "�������ʾ��������" << endl;
	cout << "��������Ҫ���ɵ��Թ������У������м��Կո�ָ�" << endl;
	cout << "���У������е�ȡֵ��ΧΪ5��25" << endl;
	while (1) {
		cout << "�����룺";
		cin >> MAX_X >> MAX_Y;
		if (!cin.good())
			cout << "�������������������" << endl;
		else if (MAX_X < 5 || MAX_Y < 5)
			cout << "��������Թ�̫С�����׶�԰С���Ѷ�������" << endl;
		else if (MAX_X > 25 || MAX_Y > 25)
			cout << "��������Թ�̫�������Դ�ѧ�����������߲�������" << endl;
		else
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}
	cout << "��������Թ���СΪ��" << MAX_X << "��" << MAX_Y << "��" << endl;

	//����ռ�
	maze_map = new maze_type * [MAX_X + 1];
	for (int i = 1; i <= MAX_X; ++i) {
		maze_map[i] = new maze_type[MAX_Y + 1];
	}

	//�����Թ�
	cout << "������������ķ�㷨��Prim�㷨���������һ���Թ�" << endl;
	Prim();
	print_map();

	//�����Թ��յ�
	cout << "��ʿ����λ��<1,1>��ʼ�����Թ�����������Ϊ��ʿ�ų�������������ʿȥ����Ŀ�ĵ�" << endl;
	position goal;
	while (1) {
		cout << "���������꣨�������м��ÿո�ֿ�����";
		cin >> goal.first >> goal.second;
		if (!cin.good())
			cout << "��������������Ϳ��ܲ���ȷŶ����ʿ�ų������Ͷ���֪�������Կ���" << endl;
		else if (!isIN(goal))
			cout << "����������겻�ڵ�ͼ��Ŷ,�����ʿ�е㱿������Ϊ�㿪������" << endl;
		else if (isWALL(goal))
			cout << "����ǽ��������Ϊ��ʿ����ɽ��ʿ��?" << endl;
		else if (goal.first == 1 && goal.second == 1)
			cout << "����ʿԭ��תȦȦ����ʿ�ų����Ǻ��ų�" << endl;
		else
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}

	//�����Թ�·��
	int choice = 0;
	cout << "��ѡ���㷨����ʿ�ҵ�·��1.�ݹ��㷨 2.�ǵݹ��㷨��" << endl;
	while (1) {
		cout << "�����룺";
		cin >> choice;
		if (!cin.good())
			cout << "�������˴��������" << endl;
		else if (choice != 1 && choice != 2)
			cout << "������1��2" << endl;
		else
			break;
		cin.clear();
		cin.ignore(1024, '\n');
	}

	position temp{ 1,1 };
	PATH.MakeEmpty();
	maze_map[temp.first][temp.second] = WAY;
	if (choice == 1) {
		cout << "�������õݹ��㷨���·��" << endl;
		PATH.Push(temp);
		travelmaze(temp, goal);
	}
	else {
		cout << "�������÷ǵݹ��㷨���·��" << endl;
		dfs(temp, goal);
	}

	//��ӡ·��
	print_map();
	print_path();

	//�������ռ�
	for (int i = 1; i <= MAX_X; ++i) {
		delete[] maze_map[i];
	}
	delete[] maze_map;
	wait_for_enter();
	return 0;
}


