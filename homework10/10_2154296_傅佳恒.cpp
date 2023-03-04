#include<ctime>
#include<iostream>
#include <conio.h>
using namespace std;
void swap(int& x, int& y);
void bubbleSort(int* p, int n);
void selectSort(int* p, int n);
void insertSort(int* p, int n);
void  ShellSort(int* p, int n);
void QuickSort(int* p, int n);
void QuickSort(int* p, int n, int left, int right, long long int& move, long long int& compare);
int Partition(int* p, int n, int low, int high, long long int& move, long long int& compare);
void FilterDown(int* p, int EndofHeap, int i, long long int& move, long long int& compare);
void HeapSort(int* p, int n);
void merge(int* p, int* tempp, int n, int l, int a, int b, long long int& move, long long int& compare);
void Mergepass(int* p, int* tempp, int n, int len, long long int& move, long long int& compare);
void MergeSort(int* p, int n);
int getBaseTen(int x, int d);
void RadixSort(int* p, int n);

void wait_for_enter()
{
	cout << endl
		<< "���س�������";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

int* Array = NULL;    //������ɵ������
int num = 0;       //���������


int main()
{
	srand(time(NULL));       //���������
	cout << "**             �����㷨�Ƚ�             **" << endl;
	cout << "==========================================" << endl;
	cout << "**          1 --- ð������              **" << endl;
	cout << "**          2 --- ѡ������              **" << endl;
	cout << "**          3 --- ֱ�Ӳ�������          **" << endl;
	cout << "**          4 --- ϣ������              **" << endl;
	cout << "**          5 --- ��������              **" << endl;
	cout << "**          6 --- ������                **" << endl;
	cout << "**          7 --- �鲢����              **" << endl;
	cout << "**          8 --- ��������              **" << endl;
	cout << "**          9 --- �˳�����              **" << endl;
	cout << "==========================================" << endl;


	cout << "������Ҫ�����������������";
	cin >> num;

	//��ʼ�������
	Array = new int[num];
	for (int i = 0; i < num; ++i)
		Array[i] = rand() % num;

	cout << "===============================================================\n";
	cout << "�㷨                    ʱ��           �Ƚϴ���        �ƶ�����\n";
	cout << "===============================================================\n";

	bubbleSort(Array, num);
	selectSort(Array, num);
	insertSort(Array, num);
	ShellSort(Array, num);
	QuickSort(Array, num);
	HeapSort(Array, num);
	MergeSort(Array, num);
	RadixSort(Array, num);


	cout << "===============================================================\n";

	wait_for_enter();
	delete[]Array;
	return 0;
}

//����������λ��
void swap(int& x, int& y)
{
	int temp;
	temp = x;
	x = y;
	y = temp;
}

//ð������
void bubbleSort(int* p, int n)
{
	int* copy = new int[n];
	for (int i = 0; i < n; i++)
		copy[i] = p[i];         //���ݿ���
	long long int move = 0;               //�ƶ�����
	long long int compare = 0;            //�Ƚϴ���
	clock_t start = clock();    //��ʼʱ��

	//����������
	bool exchange = true;
	for (int i = n - 1; i >= 0 && exchange; --i)
	{
		exchange = false;
		for (int j = 0; j < i; ++j)
		{
			if (copy[j] > copy[j + 1])
			{
				swap(copy[j], copy[j + 1]);
				move += 3;
				exchange = true;
			}
			++compare;
		}
	}

	//��ӡ���
	printf("%-15s", "ð������");
	printf("\t%10gms", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("\t%15lld", compare);
	printf("\t%15lld\n", move);
	delete[] copy;
}

//ѡ������
void selectSort(int* p, int n)
{
	int* copy = new int[n];
	for (int i = 0; i < n; i++)
		copy[i] = p[i];         //���ݿ���
	long long int move = 0;               //�ƶ�����
	long long int compare = 0;            //�Ƚϴ���
	clock_t start = clock();    //��ʼʱ��

	//����������
	for (int i = 0; i < n; ++i)
	{
		int min = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (copy[j] < copy[min])
				min = j;
			++compare;
		}
		if (min != i)
		{
			swap(copy[i], copy[min]);
			move += 3;
		}
	}


	//��ӡ���
	printf("%-15s", "ѡ������");
	printf("\t%10gms", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("\t%15lld", compare);
	printf("\t%15lld\n", move);
	delete[] copy;
}

//ֱ�Ӳ�������
void insertSort(int* p, int n)
{
	int* copy = new int[n];
	for (int i = 0; i < n; i++)
		copy[i] = p[i];         //���ݿ���
	long long int move = 0;               //�ƶ�����
	long long int compare = 0;            //�Ƚϴ���
	clock_t start = clock();    //��ʼʱ��

	//����������
	for (int i = 1; i < n; ++i) {
		int temp = copy[i];
		++move;
		int j = i;
		while (j > 0 && temp < copy[j - 1]) {
			++compare;
			copy[j] = copy[j - 1];
			++move;
			--j;
		}
		++compare;
		copy[j] = temp;
		++move;
	}

	//��ӡ���
	printf("%-15s", "ֱ�Ӳ�������");
	printf("\t%10gms", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("\t%15lld", compare);
	printf("\t%15lld\n", move);
	delete[] copy;
}

//ϣ������
void  ShellSort(int* p, int n)
{
	int* copy = new int[n];
	for (int i = 0; i < n; i++)
		copy[i] = p[i];         //���ݿ���
	long long int move = 0;               //�ƶ�����
	long long int compare = 0;            //�Ƚϴ���
	clock_t start = clock();    //��ʼʱ��

	//����������
	int gap = n / 2;
	while (gap)
	{
		for (int i = gap; i < n; i++)
		{
			int temp = copy[i];
			++move;
			int j = i;
			while (j >= gap && temp < copy[j - gap])
			{
				++compare;
				copy[j] = copy[j - gap];
				++move;
				j -= gap;
			}
			++compare;
			copy[j] = temp;
			++move;
		}
		gap /= 2;
	}

	//��ӡ���
	printf("%-15s", "ϣ������");
	printf("\t%10gms", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("\t%15lld", compare);
	printf("\t%15lld\n", move);
	delete[] copy;
}

//��������
void QuickSort(int* p, int n)
{
	int* copy = new int[n];
	for (int i = 0; i < n; i++)
		copy[i] = p[i];         //���ݿ���
	long long int move = 0;               //�ƶ�����
	long long int compare = 0;            //�Ƚϴ���
	clock_t start = clock();    //��ʼʱ��

	//����������
	QuickSort(copy, n, 0, n - 1, move, compare);

	//��ӡ���
	printf("%-15s", "��������");
	printf("\t%10gms", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("\t%15lld", compare);
	printf("\t%15lld\n", move);
	delete[] copy;
}
void QuickSort(int* p, int n, int left, int right, long long int& move, long long int& compare)
{
	if (left < right) {
		int pivotpos = Partition(p, n, left, right, move, compare);
		QuickSort(p, n, left, pivotpos - 1, move, compare);
		QuickSort(p, n, pivotpos + 1, right, move, compare);
	}
}
int Partition(int* p, int n, int low, int high, long long int& move, long long int& compare)
{
	int pivotpos = low;
	int pivot = p[low];
	++move;
	for (int i = low + 1; i <= high; i++) {
		if (p[i] < pivot && ++pivotpos != i) {
			swap(p[pivotpos], p[i]);
			move += 3;
		}
		++compare;
	}
	swap(p[pivotpos], p[low]);
	move += 3;
	return pivotpos;
}

//������
void FilterDown(int* p, int EndofHeap, int i, long long int& move, long long int& compare)
{
	int current = i;
	int child = 2 * i + 1;
	int temp = p[i];
	++move;
	while (child <= EndofHeap) {
		if (child + 1 <= EndofHeap && p[child] < p[child + 1]) {
			++child;//ȡ���ߵĽϴ�ֵ
			++compare;
		}
		if (temp > p[child]) {
			++compare;
			break;
		}
		else {
			++compare;
			p[current] = p[child];
			current = child;
			child = 2 * child + 1;
			move += 2;
		}
	}
	p[current] = temp;
	++move;
}
void HeapSort(int* p, int n)
{
	int* copy = new int[n];
	for (int i = 0; i < n; i++)
		copy[i] = p[i];         //���ݿ���
	long long int move = 0;               //�ƶ�����
	long long int compare = 0;            //�Ƚϴ���
	clock_t start = clock();    //��ʼʱ��

	//����������
	for (int i = (n - 2) / 2; i >= 0; --i)
		FilterDown(copy, n - 1, i, move, compare);
	for (int i = n - 1; i >= 1; --i) {
		swap(copy[0], copy[i]);
		move += 3;
		FilterDown(copy, i - 1, 0, move, compare);
	}

	//��ӡ���
	printf("%-15s", "������");
	printf("\t%10gms", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("\t%15lld", compare);
	printf("\t%15lld\n", move);
	delete[] copy;
}

//�鲢����
void merge(int* p, int* tempp, int n, int l, int a, int b, long long int& move, long long int& compare)
{
	int i = l, j = a + 1, k = l;
	while (i <= a && j <= b) {
		if (p[i] <= p[j]) {
			tempp[k] = p[i];
			++compare;
			++move;
			i++;
			k++;
		}
		else {
			tempp[k] = p[j];
			++compare;
			++move;
			j++;
			k++;
		}
	}
	if (i <= a) {
		for (int n1 = k, n2 = i; n1 <= b && n2 <= a; n1++, n2++) {
			tempp[n1] = p[n2];
			++move;
		}
	}
	else {
		for (int n1 = k, n2 = j; n1 <= b && n2 <= b; n1++, n2++) {
			tempp[n1] = p[n2];
			++move;
		}
	}
}
void Mergepass(int* p, int* tempp, int n, int len, long long int& move, long long int& compare)
{
	int i = 0;
	while (i + 2 * len <= n - 1) {
		merge(p, tempp, n, i, i + len - 1, i + 2 * len - 1, move, compare);
		i += 2 * len;
	}
	if (i + len <= n - 1)
		merge(p, tempp, n, i, i + len - 1, n - 1, move, compare);
	else {
		for (int j = i; j <= n - 1; ++j) {
			tempp[j] = p[j];
			++move;
		}
	}
}
void MergeSort(int* p, int n)
{
	int* copy = new int[n];
	for (int i = 0; i < n; i++)
		copy[i] = p[i];         //���ݿ���
	long long int move = 0;               //�ƶ�����
	long long int compare = 0;            //�Ƚϴ���
	clock_t start = clock();    //��ʼʱ��

	//����������
	int* temp = new int[n];

	int len = 1;
	while (len < n) {
		Mergepass(copy, temp, n, len, move, compare);
		len *= 2;
		Mergepass(temp, copy, n, len, move, compare);
		len *= 2;
	}
	delete[] temp;

	//��ӡ���
	printf("%-15s", "�鲢����");
	printf("\t%10gms", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("\t%15lld", compare);
	printf("\t%15lld\n", move);
	delete[] copy;

}

//��������
int getBaseTen(int x, int d)  // unused
{
	while (d--)
		x /= 10;
	return x % 10;
}
void RadixSort(int* p, int n)
{
	int* copy = new int[n];
	for (int i = 0; i < n; i++)
		copy[i] = p[i];         //���ݿ���
	long long int move = 0;               //�ƶ�����
	long long int compare = 0;           //�Ƚϴ���
	clock_t start = clock();    //��ʼʱ��

	//����������
	const int radix = 10;
	int d = 0;
	int m = n;
	while (m / 10) {
		++d;
		m /= 10;
	}
	++d;//��dλ
	int rear[radix], front[radix];//��ǰָ�룬�Ӻ�ָ��

	int* link = new int[n + 1];
	for (int i = 1; i < n; i++)
		link[i] = i + 1;
	link[n] = 0;

	int current = 1;
	for (int i = 0; i < d; i++)//��d������
	{
		for (int j = 0; j < radix; j++) {
			front[j] = 0;
		}
		while (current != 0) {
			int k = getBaseTen(p[current - 1], i);
			if (front[k] == 0)
				front[k] = current;
			else
				link[rear[k]] = current;
			rear[k] = current;
			current = link[current];
		}
		int j = 0;
		while (front[j] == 0)
			j++;
		current = front[j];
		link[0] = current;
		int last = rear[j];
		for (int k = j + 1; k < radix; k++) {
			if (front[k]) {
				link[last] = front[k];
				last = rear[k];
			}
		}
		link[last] = 0;
	}

	delete[]link;
	//��ӡ���
	printf("%-15s", "��������");
	printf("\t%10gms", ((double)clock() - start) * 1000 / CLOCKS_PER_SEC);
	printf("\t%15lld", compare);
	printf("\t%15lld\n", move);
	delete[] copy;
}