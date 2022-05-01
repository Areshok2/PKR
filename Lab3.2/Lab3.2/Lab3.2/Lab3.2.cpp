

#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> 

using namespace std;

enum Specilnist { KN, INF, MathEcon, PhysInf, WORK };
string predmetStr[] = { " ����. �����  ", " �����������  ", "���. �� ������", " Գ�. �� ���. ", " ����. ����.  " };

struct Student
{
	string prizv;
	unsigned kurs;
	Specilnist spec;
	int Physical;
	int Math;
	int Informatik;
};


void Create(Student* s, const int N);
void Print(Student* s, const int N);
void Sort(Student* s, const int N);
int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);
int BinSearch(Student* s, const int N, const string prizv, const double serb, const double otsi);


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int N;
	cout << "������ ������� ��������: "; cin >> N;

	Student* s = new Student[N];

	string prizv;
	unsigned kurs;
	Specilnist spec;
	int Physical;
	int Math;
	int Informatik;

	int found;
	double otsi, serb;

	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "������� ��:" << endl << endl;
		cout << " 1 - �������� ����� � ���������" << endl;
		cout << " 2 - ���� ����� �� �����" << endl;
		cout << " 3 - ������� ������������� �����" << endl;
		cout << " 4 - ������� �����" << endl;
		cout << " 5 - �������� ������������� �� ���� �����" << endl;
		cout << " 0 - ����� �� ���������� ������ ��������" << endl << endl;
		cout << "������ ��������: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(s, N);
			break;
		case 2:
			Print(s, N);
			break;
		case 3:
			Sort(s, N);
			Print(s, N);
			break;
		case 4:
			cout << "������ ����� ������:" << endl;
			cout << " �������: "; cin >> prizv;
			cout << " ������� ���: "; cin >> serb;
			cout << " ������ ����������: "; cin >> otsi;
			if ((found = BinSearch(s, N, prizv, serb, otsi)) != -1)
				cout << "������� ��������� �� ������� - " << found + 1 << endl;
			else
				cout << "�� ��������" << endl;
			break;
		case 5:
			PrintIndexSorted(s, IndexSort(s, N), N);
			break;
		case 0:
			break;
		default:
			cout << "�� ����� ��������� ��������! "
				"��� ������ ����� - ����� ��������� ������ ����" << endl;
		}
	} while (menuItem != 0);

	return 0;
}

void Create(Student* s, const int N)
{
	int spec;
	for (int i = 0; i < N; i++)
	{
		cout << "������� � " << i + 1 << ":" << endl;
		cin.get(); // ������� ����� ��������� � �� ����������� �������
		cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
		cout << " �������: "; getline(cin, s[i].prizv);
		cout << " ����: "; cin >> s[i].kurs;
		cout << "  ������� ������������ (0 - ����. ����� , 1 - ����������� , 2 - ���. �� ������ , 3 - Գ�. �� ���. , 4 - ����. ����. ): "; cin >> spec;
		s[i].spec = (Specilnist)spec;
		cout << " ������ � Գ����: "; cin >> s[i].Physical;
		cout << " ������ � ����������: "; cin >> s[i].Math;
		cout << " ������ � ������������: "; cin >> s[i].Informatik;


		cout << endl;
	}
}

void Print(Student* s, const int N)
{
	cout << "======================================================================================="
		<< endl;
	cout << "| � |      �������       | ���� | ������������ | Գ���� | ���������� | ������������ | "
		<< endl;
	cout << "---------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++) {
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(20) << left << s[i].prizv << "| " << setw(4) << right << s[i].kurs << " ";
		cout << "| " << setw(8) << right << predmetStr[s[i].spec] << " |";
		cout << "| " << setw(6) << setprecision(2) << fixed << right << s[i].Physical << right << " |";
		cout << " " << setw(10) << right << s[i].Math << " |";
		cout << " " << setw(12) << right << s[i].Informatik << " |" << endl;

	}
	cout << "=======================================================================================" << endl;
	cout << endl;
}


void Sort(Student* s, const int N)
{
	double ser = 0, ser1 = 0;
	Student tmp;
	for (int i = 0; i < N - 1; i++) // ����� "���������"
		for (int j = 0; j < N - i - 1; j++)
		{
			ser = ((s[j].Physical + s[j].Math + s[j].Informatik) / 3.);
			ser1 = ((s[j + 1].Physical + s[j + 1].Math + s[j + 1].Informatik) / 3.);

			if (ser > ser1
				||
				(ser == ser1 &&
					s[j].Math > s[j + 1].Math)
				||
				((ser == ser1 &&
					s[j].Math == s[j + 1].Math) &&
					s[j].prizv < s[j + 1].prizv))
			{
				tmp = s[j];
				s[j] = s[j + 1];
				s[j + 1] = tmp;
			}
		}
}



int* IndexSort(Student* s, const int N) {
	int* I = new int[N]; // �������� ��������� �����
	for (int i = 0; i < N; i++)
		I[i] = i; // ��������� ���� ����������� ������
	int i, j, value; // �������� ��������� ����� �������

	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((((s[I[j]].Physical + s[I[j]].Math + s[I[j]].Informatik) / 3.) > ((s[value].Physical + s[value].Math + s[value].Informatik) / 3.))
				||
				(((s[I[j]].Physical + s[I[j]].Math + s[I[j]].Informatik) / 3.) == ((s[value].Physical + s[value].Math + s[value].Informatik) / 3.) &&
					s[I[j]].Math > s[value].Math)
				||
				(((s[I[j]].Physical + s[I[j]].Math + s[I[j]].Informatik) / 3.) == ((s[value].Physical + s[value].Math + s[value].Informatik) / 3.) &&
					s[I[j]].Math == s[value].Math &&
					s[I[j]].prizv > s[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}

	return I;
}

void PrintIndexSorted(Student* s, int* I, const int N) {
	cout << "======================================================================================="
		<< endl;
	cout << "| � |      �������       | ���� | ������������ | Գ���� | ���������� | ������������ | "
		<< endl;
	cout << "---------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++) {
		cout << "| " << setw(1) << right << i + 1 << " ";
		cout << "| " << setw(20) << left << s[I[i]].prizv << "| " << setw(4) << right << s[I[i]].kurs << " ";
		cout << "| " << setw(8) << right << predmetStr[s[I[i]].spec] << " |"; 
		cout << "| " << setw(6) << setprecision(2) << fixed << right << s[I[i]].Physical << right << " |";
		cout << " " << setw(10) << right << s[I[i]].Math << " |";
		cout << " " << setw(12) << right << s[I[i]].Informatik << " |" << endl;

	}
	cout << "=======================================================================================" << endl;
	cout << endl;
}



int BinSearch(Student* s, const int N, const string prizv, const double serb, const double otsi)
{ // ������� ������ ���������� �������� ��� -1, ���� ������� ������� ������� 
	int L = 0, R = N - 1, m;
	
	
	do {
		m = (L + R) / 2;

		double ser = ((s[m].Physical + s[m].Math + s[m].Informatik) / 3.);
		
		if (s[m].prizv == prizv && ser == serb && s[m].Math == otsi)
			return m;
		if ((ser < serb)
			||
			(ser == serb &&
				s[m].Math < otsi)
			||
			(ser == serb &&
				s[m].Math == otsi &&
				s[m].prizv < prizv))
		{
			L = m + 1;
		}
		else
		{
			R = m - 1;
		}
	} while (L <= R);


	return -1;
}

