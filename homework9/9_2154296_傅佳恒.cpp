#include<iostream>
#include <conio.h>
using namespace std;
const int maxVertices = 50;
//���ڽӱ��ͼ
template<class NameType, class DistType>
struct KeyEdgeNode
{
	int tail;
	int head;
	DistType cost;
};

//�ڽӱ��ϱ߽����ඨ��
template<class NameType, class DistType>
struct Edge
{
	int dest;                              //�ߵ�����һ�����㶨��
	DistType cost;                         //���ϵ�Ȩֵ
	Edge<NameType, DistType>* link;        //��һ������ָ��
	Edge() {}                              //���캯��
	Edge(int num, DistType weight) :dest(num), cost(weight), link(NULL) {}//���캯��
};

template<class NameType, class DistType>
struct Vertex
{
	NameType data;                    //��������������
	Edge<NameType, DistType>* adj;    //������ͷָ��
};

template<class NameType, class DistType>
class Graphlnk
{
private:
	Vertex<NameType, DistType> NodeTable[maxVertices];   //�ڽӱ�
	int numEdges;                                        //�ߵ�����
	int numVertices;                                     //��������
	int caculatekey(int v);                              //�ݹ����ؼ������ʱ��

public:
	KeyEdgeNode<NameType, DistType> KeyEdge[maxVertices]; //��¼�ؼ��������
	int numKeyEdgeNode;                                   //�ؼ������

	Graphlnk();                                           //���캯��
	~Graphlnk();                                          //����������ɾ���������ж���
	int getnumEdges() { return numEdges; }                //��ȡͼ�бߵ���Ŀ
	int getnumVertices() { return numVertices; }          //��ȡͼ�ж�����Ŀ
	int getVertexPos(NameType vertex);                    //��ȡ�����λ��
	NameType getValue(int i);                             //��ȡ��Ӧλ�õĶ���ֵ
	DistType getWeight(int v1, int v2);                   //��ȡ��Ӧ�ߵ�Ȩֵ
	bool insertVertex(NameType vertex);                   //����һ������
	bool insertEdge(int v1, int v2, DistType cost);       //����һ����
	int getFirstNeighbor(int v);                          //��ȡ��ǰ����ĵ�һ���ڽӶ���
	int getNextNeighbor(int v, int w);                    //��ȡ��ǰ����ָ���ڽӶ������һ���ڽӶ���
	int caculatekey();                                    //���õݹ麯������ؼ�·����ȡֵ
	template<class NameType, class DistType>
	friend bool CriticalPath(Graphlnk<NameType, DistType>& T);  //��Ԫ��������������ؼ�·��
};

//���캯��
template<class NameType, class DistType>
Graphlnk<NameType, DistType>::Graphlnk()
{
	numVertices = 0;
	numKeyEdgeNode = 0;
	numEdges = 0;
	for (int i = 0; i < maxVertices; ++i) {
		NodeTable[i].adj = NULL;
	}
	for (int i = 0; i < maxVertices; ++i) {
		KeyEdge[i].tail = -1;
		KeyEdge[i].head = -1;
		KeyEdge[i].cost = 0;
	}
}

//��������
template<class NameType, class DistType>
Graphlnk<NameType, DistType>::~Graphlnk()
{
	for (int i = 0; i < numVertices; ++i) {
		Edge<NameType, DistType>* p = NodeTable[i].adj;
		if (p != NULL) {       //����ɾ��ÿ�����
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
}

//��ȡ��Ӧ����λ��
template<class NameType, class DistType>
int Graphlnk<NameType, DistType>::getVertexPos(NameType vertex)
{
	for (int i = 0; i < numVertices; i++) {
		if (NodeTable[i].data == vertex)
			return i;
	}
	return -1;
}

//��ȡ��Ӧλ�ö����ֵ
template<class NameType, class DistType>
NameType Graphlnk<NameType, DistType>::getValue(int i)
{
	return NodeTable[i].data;
}

//��ȡ��Ӧ���ϵ�Ȩֵ
template<class NameType, class DistType>
DistType Graphlnk<NameType, DistType>::getWeight(int v1, int v2)
{
	if (v1 != -1 && v2 != -1) {
		Edge<NameType, DistType>* p = NodeTable[v1].adj;
		while (p != NULL && p->dest != v2) {
			p = p->link;
		}
		if (p != NULL)
			return p->cost;
	}
	return 0;
}

//���붥��
template<class NameType, class DistType>
bool Graphlnk<NameType, DistType>::insertVertex(NameType vertex)
{
	if (numVertices == maxVertices)
		return 0;
	NodeTable[numVertices].data = vertex;
	NodeTable[numVertices].adj = NULL;
	numVertices++;
	return 1;
}

//�����
template<class NameType, class DistType>
bool Graphlnk<NameType, DistType>::insertEdge(int v1, int v2, DistType cost)
{
	if (v1 < 0 || v1 >= numVertices || v2 < 0 || v2 >= numVertices)
		return 0;
	if (this->getWeight(v1, v2) != 0)
		return 0;
	Edge<NameType, DistType>* p = new Edge<NameType, DistType>;
	p->cost = cost;
	p->dest = v2;
	p->link = NodeTable[v1].adj;
	NodeTable[v1].adj = p;
	numEdges++;
	return 1;
}

//��ȡ��ǰ����ĵ�һ���ڽӶ���
template<class NameType, class DistType>
int Graphlnk<NameType, DistType>::getFirstNeighbor(int v)
{
	if (v != -1) {
		Edge<NameType, DistType>* p = NodeTable[v].adj;
		if (p != NULL)
			return p->dest;
	}
	return -1;
}

//��ȡ��ǰ����ָ���ڽӶ������һ���ڽӶ���
template<class NameType, class DistType>
int Graphlnk<NameType, DistType>::getNextNeighbor(int v, int w)
{
	if (v != -1) {
		Edge<NameType, DistType>* p = NodeTable[v].adj;
		while (p != NULL && p->dest != w)
			p = p->link;
		if (p != NULL && p->link != NULL)
			return p->link->dest;
	}
	return -1;
}

//����ؼ�·���ϵ�Ȩֵ��
template<class NameType, class DistType>
int Graphlnk<NameType, DistType>::caculatekey()
{
	return caculatekey(KeyEdge[0].tail);
}

//�ݹ����ؼ�·���ϵ�Ȩֵ��
template<class NameType, class DistType>
int Graphlnk<NameType, DistType>::caculatekey(int v)
{
	for (int i = 0; i < numKeyEdgeNode; ++i) {
		if (KeyEdge[i].tail == v) {
			return caculatekey(KeyEdge[i].head) + KeyEdge[i].cost;
		}
	}
	return 0;
}

//����ؼ�·������
template<class NameType, class DistType>
bool CriticalPath(Graphlnk<NameType, DistType>& T)
{
	int num = T.numVertices;       //������
	int* ind = new int[num];        //�������
	for (int i = 0; i < num; ++i)
		ind[i] = 0;                //����Ԥ��Ϊ0
	 //ͳ�Ƹ��������
	for (int i = 0; i < num; ++i) {
		int j = T.getFirstNeighbor(i);
		while (j != -1) {
			ind[j]++;
			j = T.getNextNeighbor(i, j);
		}
	}

	DistType* Ve = new DistType[num];  //���¼����翪ʼʱ��
	DistType* Vl = new DistType[num];  //���¼�����ʼʱ��
	DistType* Ee = new DistType[T.numEdges + 1];  //������翪ʼʱ��
	DistType* El = new DistType[T.numEdges + 1];  //�������ʼʱ��

	for (int i = 0; i < num; i++) {    //���¼���ʼ�¼�Ԥ��Ϊ0
		Ve[i] = 0;
	}

	int u = -1;       //�ݴ浱ǰλ��
	int top = -1;     //���Ϊ0�Ķ����ջָ��
	int lnk = -1;     //��¼��һ�������λ�ã�������������

	for (int i = 0; i < num; ++i) {//ջ�ĳ�ʼ�������Ϊ0�Ķ����ջ
		if (ind[i] == 0) {
			ind[i] = top;
			top = i;
		}
	}

	//������������ֱ������¼����翪ʼʱ��ļ���
	for (int i = 0; i < num; ++i) {
		if (top == -1) {//ջ���¼���С��ʵ���¼������޷�������������
			delete[] ind;
			delete[] Ve;
			delete[] Vl;
			delete[] Ee;
			delete[] El;
			return 0;
		}
		u = top;          //�浱ǰ
		top = ind[top];   //��ջ
		ind[u] = lnk;
		lnk = u;

		int v = T.getFirstNeighbor(u);
		while (v != -1) {
			DistType w = T.getWeight(u, v);
			if (Ve[u] + w > Ve[v]) { //����Ve
				Ve[v] = Ve[u] + w;
			}
			--ind[v];
			if (ind[v] == 0) {  //��ȼ��ٵ�0ʱ��ջ
				ind[v] = top;
				top = v;
			}
			v = T.getNextNeighbor(u, v);
		}
	}

	for (int i = 0; i < num; ++i) {  //Vl��ʼ��Ϊ���һ���¼������翪ʼʱ��
		Vl[i] = Ve[lnk];
	}

	while (lnk != -1) {            //������˳��������У�������Сֵ
		int v = ind[lnk];
		lnk = v;
		if (lnk == -1)
			break;
		int k = T.getFirstNeighbor(v);
		while (k != -1) {
			DistType w = T.getWeight(v, k);
			if (Vl[k] - w < Vl[v])
				Vl[v] = Vl[k] - w;
			k = T.getNextNeighbor(v, k);
		}
	}

	KeyEdgeNode<NameType, DistType> ed;
	int j = 0;        //��ı��
	for (int i = 0; i < num; i++) {
		int u = T.getFirstNeighbor(i);
		while (u != -1) {
			DistType w = T.getWeight(i, u);
			Ee[j] = Ve[i];                       //����翪ʼʱ��
			El[j] = Vl[u] - w;                   //�����ʼʱ��
			if (Ee[j] == El[j]) {                //��������ʱ����ͬʱΪ�ؼ��
				ed.tail = i;
				ed.head = u;
				ed.cost = w;
				T.KeyEdge[T.numKeyEdgeNode++] = ed;  //�������
			}
			j++;
			u = T.getNextNeighbor(i, u);     //ȡ��һ���ڽӶ���
		}
	}
	delete[] ind;          //��������
	delete[] Ve;
	delete[] Vl;
	delete[] Ee;
	delete[] El;
	return 1;
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
	int M;
	Graphlnk<int, int> map;
	cout << "���������񽻽ӵ�����N������������M���м��Կո���룩:";
	cin >> N >> M;
	//�����񽻽ӵ����ͼ��
	for (int i = 1; i <= N; ++i) {
		map.insertVertex(i);
	}
	cout << "����������" << M << "�����ݣ�ÿ�и�����������" << endl;
	cout << "�ֱ��Ǹ�����ʼ�������ƵĽ��ӵ����Լ���ɸ���������Ҫ��ʱ��" << endl;

	//���ν����л����ͼ��
	for (int i = 1; i <= M; ++i)
	{
		cout << "�������" << i << "�У�";
		int k1;
		int k2;
		int cost;
		cin >> k1 >> k2 >> cost;
		k1 = map.getVertexPos(k1);
		k2 = map.getVertexPos(k2);
		map.insertEdge(k1, k2, cost);
	}

	if (CriticalPath<int, int>(map) == 0) {//����������ֵΪFalseʱ���л�·���޷�����ؼ�·��
		cout << "0" << endl;
		cout << "�����з���" << endl;
	}
	else {
		cout << "��Ŀ����ʱ��Ϊ" << map.caculatekey() << endl;//������Ŀ����ʱ��
		cout << "�ؼ��Ϊ��" << endl;
		for (int i = 0; i < map.numKeyEdgeNode; ++i) {
			cout << map.getValue(map.KeyEdge[i].tail) << "->" << map.getValue(map.KeyEdge[i].head) << endl;
		}    //���ؼ����ӡ����
		cout << "�������" << endl;
	}

	wait_for_enter();
	return 0;
}
/*
�ṩ�����������£�
7 8
1 2 4
1 3 3
2 4 5
3 4 3
4 5 2
4 6 6
5 7 5
6 7 2

�ṩ�����������£�
9 11
1 2 6
1 3 4
1 4 5
2 5 1
3 5 1
4 6 2
5 7 9
5 8 7
6 8 4
7 9 2
8 9 4

�ṩ�����������£�
4 5
1 2 4
2 3 5
3 4 6
4 2 3
4 1 2
*/