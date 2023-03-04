#include<iostream>
#include<conio.h>
using namespace std;

//��С��
template <class Type>
class MinHeap {
public:
	MinHeap(int maxSize = 10);
	MinHeap(Type arr[], int n);
	~MinHeap() { delete[] heap; }
	bool Insert(const Type& x);
	bool RemoveMin();
	bool IsEmpty() const
	{
		return CurrentSize == 0;
	}
	bool IsFull() const
	{
		return CurrentSize == MaxHeapSize;
	}
	void MakeEmpty() { CurrentSize = 0; }
	int size() { return CurrentSize; }
	Type getmin();
private:
	Type* heap;
	int CurrentSize;                      //��ǰ�ѵĴ�С,ֱ��ָ����ǽ�Ҫ����Ԫ��λ��
	int MaxHeapSize;                      //��ǰ�ѵ�����
	void FilterDown(int i, int m);
	void FilterUp(int i);
};

template <class Type>
MinHeap<Type>::MinHeap(int maxSize)
{
	MaxHeapSize = maxSize;
	CurrentSize = 0;
	heap = new Type[maxSize];
}

template <class Type>
MinHeap<Type>::MinHeap(Type arr[], int n)
{
	MaxHeapSize = n;
	CurrentSize = n;
	heap = new Type[n];
	for (int i = 0; i < n; i++) {
		heap[i] = arr[i];
	}
	int currentPos = (CurrentSize - 2) / 2;
	while (currentPos >= 0) {
		FilterDown(currentPos, CurrentSize - 1);
		currentPos--;
	}
}

//��С�ѵ����µ����㷨
template<class Type>
void MinHeap<Type>::FilterDown(int start, int EndOfHeap)
{
	int i = start;
	int j = 2 * i + 1; //jΪi������Ů�Ľ��
	Type temp = heap[start];   //�ʼ��Ԫ��
	while (j <= EndOfHeap) {
		//ѡȡ����Ů�еĽ�С��
		if (j<EndOfHeap && heap[j]>heap[j + 1])
			++j;
		if (temp <= heap[j])
			break;
		else {
			heap[i] = heap[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	heap[i] = temp;
}

template<class Type>
void MinHeap<Type>::FilterUp(int start)
{
	int j = start;
	int i = (j - 1) / 2;     //iΪj��˫��
	Type temp = heap[start];
	while (j > 0) {
		if (heap[i] <= temp)
			break;
		else {
			heap[j] = heap[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	heap[j] = temp;
}

template<class Type>
bool MinHeap<Type>::Insert(const Type& x)
{
	if (CurrentSize == MaxHeapSize)
		return 0;
	heap[CurrentSize] = x;
	FilterUp(CurrentSize);
	++CurrentSize;
	return 1;
}

template<class Type>
bool MinHeap<Type>::RemoveMin()
{
	if (CurrentSize == 0)
		return 0;
	heap[0] = heap[CurrentSize - 1];
	CurrentSize--;
	FilterDown(0, CurrentSize - 1);
	return 1;
}

template<class Type>
Type MinHeap<Type>::getmin()
{
	return heap[0];
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
	int length;
	cout << "������ľͷ��Ҫ�гɵĿ�����";
	cin >> N;
	MinHeap<int> wood(N);

	cout << "������������" << N << "��������������ÿһ��ľ��ĳ��ȣ�" << endl;
	for (int i = 0; i < N; ++i) {
		cin >> length;
		wood.Insert(length);
	}


	int sum = 0;

	while (wood.size() > 1)
	{
		int k1 = wood.getmin();
		wood.RemoveMin();
		int k2 = wood.getmin();
		wood.RemoveMin();
		sum += (k1 + k2);
		wood.Insert(k1 + k2);
	}

	cout << "��ľͷ����С����Ϊ" << sum << endl;

	wait_for_enter();
	return 0;
}