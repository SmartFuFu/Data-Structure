#include<iostream>
#include <conio.h>
using namespace std;
const int maxVertices = 50;


template<class T>
class MinSpanTree;

//���ڽӾ���洢ͼ���ඨ��
template<class NameType, class DistType>
class Graphmtx
{
private:
	NameType VerticesList[maxVertices];        //�����б�
	DistType Edge[maxVertices][maxVertices];   //�ڽӾ���
	int numEdge;                               //��ǰ�ߵ�����
	int numVertices;                           //��ǰ��ĸ���
public:
	Graphmtx();                                                 //���캯��
	int getVertexNum() { return numVertices; }                  //��ȡ��ǰ�Ķ������
	int getEdgeNum() { return numEdge; }                        //��ȡ��ǰ�ıߵĸ���
	int getVertexPos(NameType vertex);                          //ȡ����v��ͼ�еĶ���λ��
	NameType getValue(int i);                                   //ȡ����i��ֵ
	DistType getWeight(int v1, int v2);                         //ȡ��v1v2��Ȩֵ
	int getFirstNeighbor(int v);                                //��ȡv�ĵ�һ���ڽӶ���
	int getNextNeighbor(int v, int w);                          //��ȡv���ڽӶ�����w����һ���ڽӶ���
	bool insertVertex(NameType vertex);                         //����һ������
	bool insertEdge(int v1, int v2, DistType cost);             //�������˶���Ϊv1v2��ȨֵΪcost��һ����
	bool removeVertex(int v);                                   //ɾ��v����
	bool removeEdge(int v1, int v2);                            //ɾ��v1v2��

	template<class NameType, class DistType>
	friend void printMST(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B);    //��Ԫ������ӡ��С������
	template<class NameType, class DistType>
	friend void Prim(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B, NameType C);   //��Ԫ����������Prim�㷨������С������

};

//���캯��
template<class NameType, class DistType>
Graphmtx<NameType, DistType>::Graphmtx()
{
	numVertices = 0;
	numEdge = 0;
	for (int i = 0; i < maxVertices; ++i) {
		for (int j = 0; j < maxVertices; ++j) {
			Edge[i][j] = (i == j) ? 0 : INT_MAX;
		}
	}
}

//��ȡ����λ��
template<class NameType, class DistType>
int Graphmtx<NameType, DistType>::getVertexPos(NameType vertex)
{
	for (int i = 0; i < numVertices; i++) {
		if (VerticesList[i] == vertex)
			return i;
	}
	return -1;
}

//��ȡ����ֵ
template<class NameType, class DistType>
NameType Graphmtx<NameType, DistType>::getValue(int i)
{
	return (i >= 0 && i <= numVertices) ? VerticesList[i] : 0;
}

//��ȡ�ߵ�Ȩֵ
template<class NameType, class DistType>
DistType Graphmtx<NameType, DistType>::getWeight(int v1, int v2)
{
	return Edge[v1][v2];
}

//��ȡv�ĵ�һ���ڽӶ���
template<class NameType, class DistType>
int Graphmtx<NameType, DistType>::getFirstNeighbor(int v)
{
	if (v != -1) {
		for (int col = 0; col < numVertices; ++col) {
			if (Edge[v][col] > 0 && col < INT_MAX)
				return col;
		}
	}
	return -1;
}

//��ȡv���ڽӶ�����w����һ���ڽӶ���
template<class NameType, class DistType>
int Graphmtx<NameType, DistType>::getNextNeighbor(int v, int w)
{
	if (v != -1 && w != -1) {
		for (int col = w + 1; col < numVertices; ++col) {
			if (Edge[v][col] > 0 && col < INT_MAX)
				return col;
		}
	}
	return -1;
}

//����һ������
template<class NameType, class DistType>
bool Graphmtx<NameType, DistType>::insertVertex(NameType vertex)
{
	if (numVertices == maxVertices)
		return 0;
	VerticesList[numVertices] = vertex;
	numVertices++;
	return 1;
}

//�������˶���Ϊv1v2��ȨֵΪcost��һ����
template<class NameType, class DistType>
bool Graphmtx<NameType, DistType>::insertEdge(int v1, int v2, DistType cost)
{
	if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices) {
		if (Edge[v1][v2] == 0 || Edge[v1][v2] == INT_MAX)
			numEdge++;
		Edge[v1][v2] = Edge[v2][v1] = cost;
		return 1;
	}
	return 0;
}

//ɾ��һ���㼰����صı�
template<class NameType, class DistType>
bool  Graphmtx<NameType, DistType>::removeVertex(int v)
{
	if (v<0 || v>numVertices)
		return 0;//���ڱ���ɾ��ʧ��
	if (numVertices == 1)
		return 0;//ֻʣһ�����㲻ɾ��
	for (int i = 0; i < numVertices; i++) {
		if (Edge[v][i] > 0 && Edge[v][i] < INT_MAX)
			numEdge--;//�ߵ�������һ
	}
	VerticesList[v] = VerticesList[numVertices - 1];//�����һ���������ɾ�������λ��
	for (int i = 0; i < numVertices; i++) {
		Edge[i][v] = Edge[i][numVertices - 1];
		Edge[i][numVertices - 1] = INT_MAX;
	}//�����һ�������ǰ��
	for (int i = 0; i < numVertices; i++) {
		Edge[v][i] = Edge[numVertices - 1][i];
		Edge[numVertices - 1][i] = INT_MAX;
	}//�����һ�������ǰ��
	Edge[numVertices - 1][numVertices - 1] = 0;
	numVertices--;//��������һ
	return 1;
}


//ɾ����
template<class NameType, class DistType>
bool Graphmtx<NameType, DistType>::removeEdge(int v1, int v2)
{
	if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices) {
		if (Edge[v1][v2] && Edge[v1][v2] < numVertices) {
			Edge[v1][v2] = Edge[v2][v1] = numVertices;
			numEdge--;
			return 1;
		}
		else
			return 0;
	}
	else
		return 0;
}



template<class T>
class MSTEdgeNode {
private:
	int tail, head;//����յ�
	T cost;        //Ȩֵ
public:
	friend class MinSpanTree<T>;
	MSTEdgeNode(int t = -1, int h = -1, T c = -1)
	{
		tail = t;
		head = h;
		cost = c;
	}//���캯��
	template<class NameType, class DistType>
	friend void printMST(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B);
	template<class NameType, class DistType>
	friend void Prim(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B, NameType C);
};

template<class T>
class MinSpanTree
{
private:
	MSTEdgeNode<T> edge[maxVertices];
	int currentsize;
public:
	MinSpanTree() { currentsize = 0; }
	void insert(MSTEdgeNode<T> item)
	{
		edge[currentsize] = item;
		currentsize++;
	}//������С�������ı�
	template<class NameType, class DistType>
	friend void printMST(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B);
	template<class NameType, class DistType>
	friend void Prim(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B, NameType C);
};

//��ӡ��С���������������������δ�ӡ����
template<class NameType, class DistType>
void printMST(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B)
{
	for (int i = 0; i < B.currentsize; ++i)
	{
		cout << A.getValue(B.edge[i].tail) << "-(" << B.edge[i].cost << ")->" << A.getValue(B.edge[i].head) << endl;
	}
}

//Prim�㷨����С������
template<class NameType, class DistType>
void Prim(Graphmtx<NameType, DistType>& A, MinSpanTree<DistType>& B, NameType C)
{
	int NumVertices = A.numVertices;               //��ǰ������Ŀ
	DistType* lowcost = new DistType[NumVertices];    //������������㼯���ڶ��㵽�����������������ĸ����ϵĵ�ǰ��СȨֵ
	int* nearvex = new int[NumVertices];              //��¼���������㼯�������������뼯�����ĸ��������(��Ȩֵ��С)
	int begin = A.getVertexPos(C);            //��ʼ����λ��

	for (int i = 0; i < NumVertices; i++) {    //��ʼ������
		lowcost[i] = A.Edge[begin][i];
		nearvex[i] = begin;
	}
	nearvex[begin] = -1;                 //����ʼ���������
	MSTEdgeNode<DistType> e;             //�����������ڵ�
	for (int i = 1; i < NumVertices; ++i) {
		int min = INT_MAX;
		int v = -1;
		for (int j = 0; j < NumVertices; j++) {//����Ȩֵ��С��
			if (nearvex[j] != -1 && lowcost[j] < min) {
				v = j;
				min = lowcost[j];
			}
		}
		if (v != -1) {
			e.tail = nearvex[v];
			e.head = v;
			e.cost = lowcost[v];
			B.insert(e);
			nearvex[v] = -1;
			for (int j = 0; j < NumVertices; ++j) {//����lowcost���鼴nearvex����
				if (nearvex[j] != -1 && A.Edge[v][j] < lowcost[j]) {
					lowcost[j] = A.Edge[v][j];
					nearvex[j] = v;
				}
			}
		}
	}
	delete[] lowcost;
	delete[] nearvex;
}
Graphmtx<char, int> map;
MinSpanTree<int> MST;
void wait_for_enter()
{
	cout << endl
		<< "���س�������";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

//���붥��
void insertV()
{
	int num;
	while (1) {
		cout << "�����붥��ĸ���:";
		cin >> num;
		if (!cin.good()) {
			cout << "�������˴��������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (num >= 50 || num <= 0) {
			cout << "������С��50��������" << endl;
		}
		else
			break;
	}
	cout << "�������������������ƣ�" << endl;
	char A;
	for (int i = 0; i < num; ++i) {
		cin >> A;
		map.insertVertex(A);
	}

	cout << "�������" << endl;
}

//�����
void insertE()
{
	int num = map.getVertexNum() * (map.getVertexNum() - 1) / 2;
	char a, b;
	int cost;
	int tail, head;
	cout << "������ȫͼ��������" << num << "����" << endl;
	for (int i = 0; i < num; ++i) {
		cout << "�������" << i + 1 << "���ߵ��������㼰�ߣ�";
		cin >> a >> b >> cost;
		tail = map.getVertexPos(a);
		head = map.getVertexPos(b);
		map.insertEdge(tail, head, cost);
	}
	cout << "�������" << endl;
}

//������С������
void buildMST()
{
	cout << "��Prim������С������" << endl;
	cout << "��������ʼ���㣺";
	char C;
	cin >> C;
	Prim(map, MST, C);
	cout << "���ɽ���" << endl;

}

int main()
{
	cout << "=============================================" << endl;
	cout << "**             �������ģ��ϵͳ            **" << endl;
	cout << "=============================================" << endl;
	cout << "**             A-������������              **" << endl;
	cout << "**             B-��ӵ����ı�              **" << endl;
	cout << "**             C-������С������            **" << endl;
	cout << "**             D-��ʾ��С������            **" << endl;
	cout << "**             E-�˳�                      **" << endl;
	cout << "=============================================" << endl;



	while (1) {
		char choice;
		cout << endl;
		cout << "��ѡ�������";
		cin >> choice;
		switch (choice) {
			case 'A'://���붥��
				insertV();
				break;
			case 'B'://�����
				insertE();
				break;
			case'C'://������С������
				buildMST();
				break;
			case'D':
				cout << "��С����������" << endl;
				printMST(map, MST);//��ӡ��С������
				break;
			case 'E':
				wait_for_enter();//��������
				return 0;
		}
	}
	return 0;
}

/*
�ṩ�����������£�
A 4
a b c d

B
a b 8
b c 7
c d 5
d a 11
a c 18
b d 12

C
b

D
*/