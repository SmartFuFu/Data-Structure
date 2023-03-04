#include "student.h"
#include <conio.h>
#include <fstream>
using namespace std;
/*
�ṩ�����������£�
10001 ���Ѻ� �� 18 �������ʦ
10023 ��ĳ�� �� 29 ������ʦ
10022 ��ĳ�� Ů 16 ����ܹ�ʦ
10011 ��ĳ�� Ů 31 �������ʦ
10098 ��ĳ�� �� 34 ����ܹ�ʦ
10002 ţ�ӱ� �� 10 �������ʦ
10388 ���߱� Ů 45 �������ʦ
10222 ����   Ů 22 ������ʦ
10009 С���� ��  9 �������ʦ
*/
void wait_for_enter()
{
	cout << endl
		<< "���س�������";
	while (_getch() != '\r')
		;
	cout << endl
		<< endl;
}

class Databank
{
private:
	List<Student> table;
public:
	Databank() {}
	~Databank(){}

	void buildup();                       //���ݿ��ʼ��
	void show();                          //չʾ��������
	void search();                        //���ҿ�����Ϣ
	void insertRightPostion(Student& da); //�ں���λ�ò��뿼����Ϣ
	void insert();                        //���뿼����Ϣ
	void remove();                        //ɾ��������Ϣ
	void update();                        //���Ŀ�����Ϣ
	void statistics();                    //ͳ�ƿ�����Ϣ
};

void Databank::buildup()
{
	cout << "�����뽨��������Ϣϵͳ��" << endl;
	int studentnumber = 0;
	cout << "�����뿼��������" << endl;
	while (true)
	{
		cin >> studentnumber;
		if (cin.fail() || studentnumber < 0)
		{
			cout << "������һ����������" << endl;
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else
			break;
	}
	if (studentnumber == 0) {
		cout << "��������Ϊ0���������ݿ�ʱû�п���" << endl;
		return;
	}
	cout << "���������뿼���Ŀ��ţ��������Ա����估�������" << endl;
	Student da;
	for (int i = 0; i < studentnumber; i++) {
		cin >> da;
		if (table.find(da) != NULL) {
			cout << "����Ϊ" << da.id << "��Ӧ��ѧ���Ѿ�����" << endl;
		}
		else {
			this->insertRightPostion(da);
		}
	}
	this->show();
}

void Databank::show()
{
	if (table.isEmpty()) {
		cout << "�ÿ���ϵͳ����������,����Ӻ�����" << endl;
		return;
	}

	for (int i = 0; i < 40; ++i)
		cout << "��";
	cout << endl;

	cout << "����            ����            �Ա�            ����            �������" << endl;

	for (int i = 0; i < 40; ++i)
		cout << "��";
	cout << endl;

	ListNode<Student>* p = table.first->next;
	while (p!=NULL) {
		cout << p->data << endl;
		p = p->next;
	}

	for (int i = 0; i < 40; ++i)
		cout << "��";
	cout << endl;
	cout << "��ǰ����ϵͳ�й���" << table.size << "������" << endl;
	for (int i = 0; i < 40; ++i)
		cout << "��";
	cout << endl;
}

void Databank::search()
{
	cout << "������Ҫ���ҵĿ����ţ�";
	int sid;
	cin >> sid;
	Student N(sid);
	ListNode<Student>* p = table.find(sid);
	if (p == NULL) {
		cout << "�����ڿ���Ϊ" << sid << "�Ŀ�����" << endl;
	}
	else {
		cout << "�����ҵ��Ŀ�����ϢΪ��" << endl;
		cout << p->data << endl;
	}
	cout << "�������" << endl;
}

void Databank::insertRightPostion(Student& da)
{
	if (table.isEmpty()) {
		table.pushback(da);
	}
	else {
		ListNode<Student>* p = table.first->next;
		while (p != NULL) {
			if (da.id < p->data.id) {
				table.insert(p, da);
				return;
			}
			p = p->next;
		}
		table.pushback(da);
	}
}

void Databank::insert()
{
	cout << "������Ҫ����Ŀ����Ŀ��ţ�";
	int sid;
	cin >> sid;
	Student N(sid);
	ListNode<Student>* p = table.find(sid);
	if (p == NULL) {
		cout << "�밴˳������ÿ������������Ա����估�������" << endl;
		input(cin, N);
		cout << "����Ҫ����Ŀ�����ϢΪ��" << endl;
		cout << N << endl;
		insertRightPostion(N);
		cout << "�������" << endl;
	}
	else {
		cout << "����Ϊ" << sid << "��ѧ���Ѿ�����" << endl;
	}
}

void Databank::remove()
{
	cout << "������Ҫɾ���Ŀ����Ŀ��ţ�";
	int sid;
	cin >> sid;
	Student N(sid);
	ListNode<Student>* p = table.find(sid);
	if (p == NULL) {
		cout << "�����ڿ���Ϊ" << sid << "�Ŀ�����" << endl;
	}
	else {
		cout << "��ɾ���Ŀ�����ϢΪ��" << endl;
		cout << p->data << endl;
		table.remove(p);
		cout << "ɾ�����" << endl;
	}
}

void Databank::update()
{
	cout << "�������㽫Ҫ�޸ĵĿ������ţ�";
	int sid;
	cin >> sid;
	Student N(sid);
	ListNode<Student>* p = table.find(sid);
	if (p == NULL) {
		cout << "�����ڿ���Ϊ" << sid << "�Ŀ�����" << endl;
	}
	else {
		cout << "���޸ĵĿ�����ϢΪ��" << endl;
		cout << p->data << endl;
		cout << "�밴˳������ÿ������ĺ���������Ա����估�������" << endl;
		input(cin, N);
		p->data = N;
		cout << "�޸����" << endl;
	}
}

void Databank::statistics()
{
	ListNode<Student>* p = table.first->next;
	int _gender[2] = {0};
	int _age[20] = {0};
	while (p != NULL) {
		++_gender[p->data.gender];
		++_age[p->data.age / 10];
		p = p->next;
	}
	cout << "��Ů�����£�" << endl;
	cout << "������" << _gender[0] << "��" << endl;
	cout << "Ů����" << _gender[1] << "��" << endl << endl;
	cout << "����������£�" << endl;
	for (int i = 0; i < 20; i++) {
		if (_age[i] != 0) {
			cout << "����Ϊ" << i * 10 << "~~" << (i + 1) * 10 - 1 << "����" << _age[i] << "��" << endl;
		}
	}
	cout << "ͳ�����" << endl << endl;
}

int main()
{
	Databank Db;
	Db.buildup();
	char p = '\0';
	while (1) {
		cout << endl;
		cout << "��ѡ����Ҫ���еĲ�����1Ϊ���룬2Ϊɾ����3Ϊ���ң�4Ϊ�޸ģ�5Ϊͳ�����ݣ�0Ϊ�˳�ϵͳ����";
		cin >> p;
		switch (p) 
		{
			case '1':
				Db.insert();
				break;
			case'2':
				Db.remove();
				break;
			case'3':
				Db.search();
				break;
			case'4':
				Db.update();
				break;
			case'5':
				Db.statistics();
				break;
			case'0':
				cout << "����ϵͳ�ر�" << endl;
				return 0;
				break;
			default:
				cout << "�����ָ��Ϸ�������������" << endl;
		}
		cout << "��ǰ����ϵͳ����������" << endl;
		Db.show();
		wait_for_enter();
	}
	return 0;
}