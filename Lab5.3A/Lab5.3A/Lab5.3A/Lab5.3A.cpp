#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <Windows.h>               // ������������ ����������� ��������

using namespace std;

enum Specialty { KOMP_NAYK, INFORMATUKA, MATEM_EKONOM, FIZ_MATEM, TRUD_NAVCH };

string specialtyStr[] = { "����'����� �����", "�����������", "���������� �� ��������", "Գ���� �� �����������", "������� ��������" };

struct Student
{
	char surname[64];
	unsigned course;
	Specialty specialty;
	unsigned physics;
	unsigned maths;
	unsigned comp_science;
};

void CreateBIN(const char* filename);
void PrintBIN(const char* filename);
void fWrite(fstream& f, const int i, Student x);
Student fRead(fstream& f, const int i);
void fChange(fstream& f, const int i, const int j);
void SortBIN(const char* filename);
void IndexSortBIN(const char* filename, const char* newfile);
void PrintIndexSortedBIN(const char* filename, const char* newfile);
int BinSearch(const char* filename, const char* surname, const double sreb, const double trate);

int main()
{                             // ������������ ����������� ��������:
	SetConsoleCP(1251);       // ������������ ������� win-cp1251 � ���� �����
	SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������

	char f[100] = "";
	char g[15] = "newfile.bat";
	char surname[64];
	double serb, trate;
	int found;

	int menuItem;
	do {
		cout << endl;
		cout << " ������� ��: " << endl << endl;
		cout << " [1] - �������� ����� � ��������� " << endl;
		cout << " [2] - ���� ����� �� ����� " << endl;
		cout << " [3] - ������� ������������� ����� " << endl;
		cout << " [4] - �������� ������������� �� ���� ����� " << endl;
		cout << " [5] - ������� ����� " << endl;
		cout << " [0] - ����� �� ���������� ������ �������� " << endl << endl;
		cout << " ������ ��������: ";
		cin >> menuItem;
		cout << endl;

		switch (menuItem)
		{
		case 1:
			if (strcmp(f, "") == 0) {
				cout << "������ ��'� �����: ";
				cin >> f;
			}
			CreateBIN(f);
			break;
		case 2:
			if (strcmp(f, "") == 0) {
				cout << "���� �� ����, �������� ������� ���� (����� 1)." << endl;
				break;
			}
			PrintBIN(f);
			break;
		case 3:
			if (strcmp(f, "") == 0) {
				cout << "���� �� ����, �������� ������� ���� (����� 1)." << endl;
				break;
			}
			SortBIN(f);
			PrintBIN(f);
			break;
		case 4:
			if (strcmp(f, "") == 0) {
				cout << "���� �� ����, �������� ������� ���� (����� 1)." << endl;
				break;
			}
			IndexSortBIN(f, g);
			PrintIndexSortedBIN(f, g);
			break;
		case 5:
			if (strcmp(f, "") == 0) {
				cout << "���� �� ����, �������� ������� ���� (����� 1)." << endl;
				break;
			}
			cout << "������ ����� ������:" << endl;
			cout << " �������: ";
			cin.get();
			cin.sync();
			cin >> surname;
			cout << " ������� ���: ";
			cin >> serb;
			cout << " ������ � �������� ��������: ";
			cin >> trate;
	
			found = BinSearch(f, surname, serb, trate);
			if (found == -1) {
				cout << " �������� �������� �� ��������" << endl;
			}
			else {
				ifstream fin(f, ios::binary);
				if (!fin) {
					cout << "Main: ������� �������� �����. " << f << endl;
					return -1;
				}
				cout << " �������� �������� � ������� � " << found + 1 << endl;
			}
			break;
		case 0:
			break;
		default:
			cout << " �� ����� ��������� ��������! "
				" ��� ������ ����� - ����� ��������� ������ ���� " << endl;
		}
	} while (menuItem != 0);

	return 0;
}

void CreateBIN(const char* filename)
{
	ofstream f(filename, ios::binary); // ������� ���� ��� ������
	char ch; // ������� ����������� � �� ������������ ��������
	int n = 1;
	int specialty;
	Student student;

	do {
		cout << " ������� � " << n << ":" << endl;
		cin.get(); // ������� ����� ��������� � �� ����������� �������
		cin.sync(); // "����� �����", �� �� ����� ������ ��������� ������� �����
		cout << " �������: ";
		cin >> student.surname;
		cout << " ����: ";
		cin >> student.course;
		cout << " ������������ (0 - ����'����� �����, 1 - �����������, 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������): ";
		cin >> specialty;
		student.specialty = (Specialty)specialty;
		cout << " ������ � ������: ";
		cin >> student.physics;
		cout << " ������ � ����������: ";
		cin >> student.maths;
		cout << " ������ � �����������: ";
		cin >> student.comp_science;
		cout << endl;
		f.write((char*)&student, sizeof(Student)); // �������� � ����
		n++;
		cout << "������ ��? (y/n): ";
		cin >> ch;
		cout << endl;
	}

	while (ch == 'y' || ch == 'Y');
	cout << endl;
	f.close();
}

void PrintBIN(const char* filename)
{
	ifstream f(filename, ios::binary); // ������� ���� ��� ����������
	if (!f) {
		cout << "PrintBIN: ������� �������� �����." << endl;
		return;
	}

	cout << "==============================================================================================" << endl;
	cout << " |  �  |    �������    | ���� |      ������������      | Գ���� | ���������� | ����������� |" << endl;
	cout << "----------------------------------------------------------------------------------------------" << endl;

	Student student;
	int i = 1;

	while (f.read((char*)&student, sizeof(Student))) {
		cout << " | " << setw(2) << right << i << " ";
		cout << " | " << setw(14) << left << student.surname;
		cout << " |  " << setw(2) << right << student.course << " ";
		cout << " | " << setw(23) << left << specialtyStr[student.specialty];
		cout << " | " << setw(4) << right << student.physics << "  ";
		cout << " | " << setw(6) << right << student.maths << "    ";
		cout << " | " << setw(6) << right << student.comp_science << "   " << "   |";
		cout << endl;
		i++;
	}
	cout << "==============================================================================================" << endl;
	cout << endl;
}

void fWrite(fstream& f, const int i, Student x)
{
	f.seekp(i * (long)sizeof(Student));   // ���������� ��������
	f.write((char*)&x, sizeof(Student));  // �������� ��������
}

Student fRead(fstream& f, const int i)
{
	Student x;
	f.seekg(i * (long)sizeof(Student));   // ���������� ��������
	f.read((char*)&x, sizeof(Student));   // ��������� ��������
	return x;
}

void fChange(fstream& f, const int i, const int j)
{
	Student x = fRead(f, i);
	Student y = fRead(f, j);
	fWrite(f, i, y);
	fWrite(f, j, x);
}

void SortBIN(const char* filename)
{   //���������� ����� � �� ��������� ������� ������� �� �����
	fstream f(filename, ios::binary | ios::in | ios::out);
	f.seekg(0, ios::end);
	int size = f.tellg() / sizeof(Student);
	f.seekg(0, ios::beg);

	for (int i = 1; i < size; i++) {
		for (int j = 0; j < size - i; j++)
		{	
			Student a = fRead(f, j);
			Student b = fRead(f, j + 1);

			double ser = ((a.physics + a.maths + a.comp_science) / 3.);
			double ser1 = ((b.physics + b.maths + b.comp_science) / 3.);

	
			if ((ser > ser1)
				||
				(ser == ser1 &&
					a.comp_science > b.comp_science)
				||
				(ser == ser1 &&
					a.comp_science == b.comp_science &&
					strcmp(a.surname, b.surname) == 1))
			{
				fChange(f, j, j + 1);
			}
		}
	}

	f.seekp(0, ios::end);
}

void IndexSortBIN(const char* filename, const char* newfile)
{	// ���������� ����� � �� ��������� ����������� �������: ������� � ������ ����� � �������� � �����
	fstream g(newfile, ios::binary | ios::in | ios::out | ios::trunc);
	fstream f(filename, ios::binary | ios::in | ios::out);

	f.seekg(0, ios::end);
	int size = f.tellg() / sizeof(Student);
	f.seekg(0, ios::beg);
	for (int i = 0; i < size; i++)
		g.write((char*)&i, sizeof(int));
	g.seekg(0, ios::beg);

	int x;
	int y;
	int i1;
	int i2;

	for (int i0 = 1; i0 < size; i0++) {
		for (int i1 = 0; i1 < size - i0; i1++) {
			g.seekg(i1 * (long)sizeof(int));
			g.read((char*)&x, sizeof(int));
			g.read((char*)&y, sizeof(int));
			Student a = fRead(f, x);
			Student b = fRead(f, y);

			double ser = ((a.physics + a.maths + a.comp_science) / 3.);
			double ser1 = ((b.physics + b.maths + b.comp_science) / 3.);
			
			if ((ser > ser1)
				||
				(ser == ser1 &&
					a.comp_science > b.comp_science)
				||
				(ser == ser1 &&
					a.comp_science == b.comp_science &&
					strcmp(a.surname, b.surname) == 1))
			{
				g.seekg(i1 * (long)sizeof(int));
				g.read((char*)&i1, sizeof(int));
				g.seekg((i1 + 1) * (long)sizeof(int));
				g.read((char*)&i2, sizeof(int));
				g.seekg(i1 * (long)sizeof(int));
				g.write((char*)&i2, sizeof(int));
				g.seekg((i1 + 1) * (long)sizeof(int));
				g.write((char*)&i1, sizeof(int));
			}
		}
	}

	g.seekg(0, ios::beg);
	f.seekp(0, ios::end);
	f.close();
	g.close();
}

void PrintIndexSortedBIN(const char* filename, const char* newfile)
{
	cout << "==============================================================================================" << endl;
	cout << " |  �  |    �������    | ���� |      ������������      | Գ���� | ���������� | ����������� |" << endl;
	cout << "----------------------------------------------------------------------------------------------" << endl;

	ifstream g(newfile, ios::binary);		// ������� ���� ��� ������
	if (!g) {
		cout << "PrintIndexSorted: ������� �������� �����. " << newfile << endl;
		return;
	}
	fstream f(filename, ios::binary | ios::in | ios::out);	// ������� ���� ��� ����������
	if (!f) {
		cout << "PrintIndexSorted: ������� �������� �����. " << filename << endl;
		return;
	}

	Student student;
	f.seekg(0, ios::end);
	int size = f.tellg() / sizeof(Student);
	f.seekg(0, ios::beg);

	int i = 1;
	int idx;

	while (g.read((char*)&idx, sizeof(int))) {
		f.seekg(idx * (long)sizeof(Student));
		f.read((char*)&student, sizeof(Student));
		cout << " | " << setw(2) << right << i++ << " ";
		cout << " | " << setw(14) << left << student.surname;
		cout << " |  " << setw(2) << right << student.course << " ";
		cout << " | " << setw(23) << left << specialtyStr[student.specialty];
		cout << " | " << setw(4) << right << student.physics << "  ";
		cout << " | " << setw(6) << right << student.maths << "    ";
		cout << " | " << setw(6) << right << student.comp_science << "   " << "   |";
		cout << endl;
	}
	cout << "==============================================================================================" << endl;
	cout << endl;
}

int BinSearch(const char* filename, const char* surname, const double serb, const double trate)
{   // ������� ������ ���������� �������� ��� -1, ���� ������� ������� �������
	fstream f(filename, ios::binary | ios::in | ios::out);
	if (!f) {
		cout << "Print_I: ������� �������� �����. " << filename << endl;
		return -1;
	}

	f.seekg(0, ios::end);
	int R = f.tellg() / sizeof(Student);
	int L = 0, m;
	f.seekg(0, ios::beg);

	do {
		m = (L + R) / 2;
		Student a = fRead(f, m);

		double ser = ((a.physics + a.maths + a.comp_science) / 3.);

		if (ser == serb && a.comp_science == trate && strcmp(a.surname, surname) == 0) {
			return m;
		}

		if ((ser > serb)
			||
			(ser == serb &&
				a.comp_science > trate)
			||
			(ser == serb &&
				a.comp_science == trate &&
				strcmp(a.surname, surname) == 1))
		{
			R = m - 1;
		}
		else {
			L = m + 1;
		}
	} while (L <= R);

	return -1;
}