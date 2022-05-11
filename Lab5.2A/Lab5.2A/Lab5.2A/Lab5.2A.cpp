#include <iostream>
#include <fstream>
#include <iomanip>
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
int LineSearch(const char* filename);
string LineSearch2(const char* filename);


int main()
{                             // ������������ ����������� ��������:
	SetConsoleCP(1251);       // ������������ ������� win-cp1251 � ���� �����
	SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������

	char f[100] = "";

	int menuItem;
	do {
		cout << endl;
		cout << " ������� ��: " << endl << endl;
		cout << " [1] - �������� ����� � ��������� " << endl;
		cout << " [2] - ���� ����� �� ����� " << endl;
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
			cout << " ʳ������ ������� ��� 4.5 �����: " << LineSearch(f) << endl;
			cout << " ������� ������� ��� ����� ���������: " << LineSearch2(f) << endl;
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

	cout << "===============================================================================================" << endl;
	cout << " |  �  |    �������    | ���� |      ������������      | Գ���� | ���������� | ����������� | " << endl;
	cout << "-----------------------------------------------------------------------------------------------" << endl;

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
	cout << "===============================================================================================" << endl;
	cout << endl;
}

int LineSearch(const char* filename)
{
	ifstream f(filename, ios::binary);

	Student student;
	int count = 0;
	double d;

	while (f.read((char*)&student, sizeof(Student)))
	{
		double d = (student.physics + student.maths + student.comp_science) / 3.0;
		if (d > 4.5)
			count++;
	}

	f.close();
	return count;
}

string LineSearch2(const char* filename)
{
	ifstream f(filename, ios::binary);

	Student student;
	string max;
	int N = 3;
	double inf = 0, math = 0, phys = 0;
	double I, M, F;

	while (f.read((char*)&student, sizeof(Student)))
	{
		inf += student.comp_science;
		math += student.maths;
		phys += student.physics;

	}
	f.close();

	I = inf / N;
	M = math / N;
	F = phys / N;

	if (I == F && F == M && I == M)
		return "�� �������� ����� ���������� ������� ���";
	if (I == F || I == M || M == F)
		return "��� �������� ����� ���������� ������� ���";
	if (F > M && F > I)
		return "physics";
	if (M > F && M > I)
		return "math";
	if (I > F && I > M)
		return "informatik";
}


