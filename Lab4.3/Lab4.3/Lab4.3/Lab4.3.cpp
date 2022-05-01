#define _CRT_SECURE_NO_WARNINGS
#pragma warning (disable : 4996)
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <Windows.h>


using namespace std;

struct Zodiac {
    string fullName;
    string zodiac_sign;
    int birthDate[3];
};

void AddTXT(char* fname);
void PrintTXT(char* fname);
int SearchTXT(char* fname, char zodiac_sign[]);

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    char fname[100];

    int menuItem;
    do {
        cout << "������ ��: " << endl;
        cout << "[1]  C������� ����." << endl;
        cout << "[2]  ������ �������� �� ������." << endl;
        cout << "[3]  ���� �� �����." << endl;
        cout << "[4]  ����� �� ������ ������." << endl;
        cout << "[5]  ³������ ����." << endl;
        cout << "[0]  ����� �� ���������� ������ ��������" << endl << endl;
        cout << "������ ��������: "; cin >> menuItem;
        cout << endl;
        switch (menuItem) {
        case 1:
            cout << "������ ��'� �����: "; cin >> fname;
            AddTXT(fname);
            break;
        case 2:
            AddTXT(fname);
            break;
        case 3:
            PrintTXT(fname);
            break;
        case 4:
            char m[100];
            cout << "������ ���� ������: "; cin >> m;
            SearchTXT(fname, m);
            break;
        case 5:
            cout << "������ ��'� �����: "; cin >> fname;
            break;
        case 0:
            break;
        default:
            cout << "�� ����� ��������� ��������! ��� ������ ����� - ����� ��������� ������ ����" << endl;
        }
    } while (menuItem != 0);

    system("pause");
    cin.get();
    return 0;
}

void AddTXT(char* fname) {
    ofstream fout;
    fout.open(fname, ios::app);
    string s;
    int k;
    cout << "ʳ������ ��������: "; cin >> k;
    Zodiac* b = new Zodiac[k];
    for (int i = 0; i < k; i++) {
        cin.get();
        cin.sync();
        cout << "����� ��'�: "; getline(cin, b[i].fullName);
        fout << b[i].fullName << ' ';
        cout << "���� ������: "; getline(cin, b[i].zodiac_sign);
        fout << b[i].zodiac_sign << ' ';
        cout << "���� ����������: "; cin >> b[i].birthDate[0];
        cout << "̳��� ����������: "; cin >> b[i].birthDate[1];
        cout << "г� ����������: "; cin >> b[i].birthDate[2];
        fout << b[i].birthDate[0] << '.' << b[i].birthDate[1] << '.' << b[i].birthDate[2] << endl;
    }
}

void PrintTXT(char* fname) {
    ifstream fin(fname);
    string s;
    while (getline(fin, s)) {
        cout << s << endl;
    }
    cout << endl;
}

int  SearchTXT(char* fname, char zodiac_sign[]) {
    ifstream fin(fname);
    char s[400];
    char* w;
    bool find = false;
    cin.ignore();

    while (fin.getline(s, sizeof(s))) {
        char tmp[400];
        strcpy(tmp, s);
        w = strtok(tmp, " ");
        while (w != NULL) {
            if (strcmp(w, zodiac_sign) == 0) {
                cout << "��� ��� ������ �� �������� ������ ������: " << s << endl;

                find = true;
            }
            w = strtok(NULL, " ");
        }
    }
    if (find == false) {
        cout << "�� ��������� ����������� �� �������� � ������ ���������." << endl;
        return -1;
    }
    else {
        return 1;
    }
}