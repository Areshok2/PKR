#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // ������������ ����������� ��������
using namespace std;

enum Kurs { I = 1, II, III, IV, V, VI };

string KursStr[] = {
    "I", "II", "III", "IV", "V", "VI"
};

enum Spec { KN, INF, MATHandECONOM, PHandINF, WORK };

string SpecStr[] = {
    "����.� �����",
    "������.",
    "�����. �� �����.",
    "Գ�. �� ������.",
    "����. ��������"
};

struct Student {
    string prizv;
    Kurs kurs;
    Spec spec;
    int physics, maths;
    union {
        int programming;
        int numMethods;
        int pedagogy;
    };
};

void Create(Student* s, const int N);
void Print(Student* s, const int N);
void Sort(Student* s, const int N);
int BinSearch(Student* s, const int N, const string prizv, const double serb, const double otsi);
int* IndexSort(Student* s, const int N);
void PrintIndexSorted(Student* s, int* I, const int N);

int main() {
    SetConsoleCP(1251); // ������������ ������� win-cp1251 � ���� �����
    SetConsoleOutputCP(1251); // ������������ ������� win-cp1251 � ���� ������

    int N;
    cout << "������ N: "; cin >> N;

    Student* s = new Student[N];

    int ispec, found;
    double otsi, serb;
    string prizv;

    int menuItem;
    do {
        cout << endl << endl << endl;
        cout << "������� ��:" << endl << endl;
        cout << " [1] - �������� ����� � ���������" << endl;
        cout << " [2] - ���� ����� �� �����" << endl;
        cout << " [3] - ������� ������������� �����" << endl;
        cout << " [4] - ������� ����� " << endl;
        cout << " [5] - �������� ������������� �� ���� �����" << endl;
        cout << " [0] - ����� �� ���������� ������ ��������" << endl << endl;
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
            cout << "������ �������� ��������: ";  cin >> otsi;
            
            if ((found = BinSearch(s, N, prizv, serb, otsi)) != -1)
                cout << "�������� ���������� � ������� " << found + 1 << endl;
            else
                cout << "�������� ���������� �� ��������" << endl;
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

void Create(Student* s, const int N) {
    int kurs, spec;
    for (int i = 0; i < N; i++) {
        cout << "������� � " << i + 1 << ":" << endl;
        cout << "�������: "; cin >> s[i].prizv;
        cout << "����: "; cin >> kurs;
        s[i].kurs = (Kurs)kurs;
        cout << "������������: 0 - ��������� �����,  1 - �����������, \n 2 - ���������� �� ��������, 3 - Գ���� �� �����������, 4 - ������� ��������"
            << endl << "������ ������������: ";
        cin >> spec;        s[i].spec = (Spec)spec;
        cout << "������ � ������: "; cin >> s[i].physics;
        cout << "������ � ����������: "; cin >> s[i].maths;
        switch (s[i].spec) {
        case KN:
            cout << "������ � �������������: "; cin >> s[i].programming;
            break;
        case INF:
            cout << "������ � ��������� ������: "; cin >> s[i].numMethods;
            break;
        case MATHandECONOM:
        case PHandINF:
        case WORK:
            cout << "������ � ���������: "; cin >> s[i].pedagogy;
            break;
        }
        cout << endl;
    }
}

void Print(Student* s, const int N) {
    cout << "==================================================================================================="
        << endl;
    cout << "| � |  �������  | ���� |   ������������   | Գ���� | �����. | �������. | ���. ���. | ��������� |"
        << endl;
    cout << "---------------------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << right << i + 1 << " ";
        cout << "| " << setw(11) << left << s[i].prizv
            << "| " << setw(4) << right << KursStr[(int)s[i].kurs - 1] << " "
            << "| " << setw(18) << left << SpecStr[s[i].spec]
            << "| " << setw(6) << right << s[i].physics << " "
            << "| " << setw(6) << right << s[i].maths << " ";
        switch (s[i].spec) {
        case KN:
            cout << "| " << setw(8) << right
                << s[i].programming << " | " << setw(12) << right
                << " | " << setw(12) << right << " |" << endl;
            break;
        case INF:
            cout << "| " << setw(11) << right
                << " | " << setw(9) << right << s[i].numMethods
                << " | " << setw(12) << right << " |" << endl;
            break;
        case MATHandECONOM:
        case PHandINF:
        case WORK:
            cout << "| " << setw(11) << right
                << " | " << setw(12) << right
                << " | " << setw(10) << right << s[i].pedagogy << " |" << endl;
            break;
        }
    }
    cout << "===================================================================================================" << endl;
    cout << endl;
}

void Sort(Student* s, const int N) {

    double ser = 0, ser1 = 0;
    Student tmp;
    for (int i = 0; i < N - 1; i++) // ����� "���������"
        for (int j = 0; j < N - i - 1; j++)
        {
            ser = (s[j].maths + s[j].physics + s[j].programming) / 3.;
            ser1 = (s[j + 1].maths + s[j + 1].physics + s[j + 1].programming) / 3.;

            if (ser > ser1
                ||
                (ser == ser1 &&
                    s[j].programming > s[j + 1].programming)
                ||
                (ser == ser1 &&
                    s[j].programming == s[j + 1].programming &&
                    s[j].prizv < s[j + 1].prizv))
            {
                tmp = s[j];
                s[j] = s[j + 1];
                s[j + 1] = tmp;
            }
        }
}

int BinSearch(Student* s, const int N, const string prizv, const double serb, const double otsi)
{ // ������� ������ ���������� �������� ��� -1, ���� ������� ������� ������� 
    int L = 0, R = N - 1, m;
    do {
        m = (L + R) / 2;

        double ser = (s[m].maths + s[m].physics + s[m].programming) / 3.;

        if (s[m].prizv == prizv && ser == serb && s[m].programming == otsi)
            return m;
        if ((ser < serb)
            ||
            (ser == serb &&
                s[m].programming  < otsi)
            ||
            (ser == serb &&
                s[m].programming == otsi &&
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

int* IndexSort(Student* s, const int N) {
    int* I = new int[N]; // �������� ��������� �����
    for (int i = 0; i < N; i++)
        I[i] = i; // ��������� ���� ����������� ������
    int i, j, value; // �������� ��������� ����� �������


    for (i = 1; i < N; i++) 
    {

        value = I[i];
        for (j = i - 1;
            j >= 0 && (((s[I[j]].maths + s[I[j]].physics + s[I[j]].programming) / 3. > (s[value].maths + s[value].physics + s[value].programming) / 3.)
                ||
                ((s[I[j]].maths + s[I[j]].physics + s[I[j]].programming) / 3. == (s[value].maths + s[value].physics + s[value].programming) / 3. &&
                    s[I[j]].programming > s[value].programming)
                ||
                ((s[I[j]].maths + s[I[j]].physics + s[I[j]].programming) / 3. == (s[value].maths + s[value].physics + s[value].programming) / 3. &&
                    s[I[j]].programming == s[value].programming &&
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
    cout << "==================================================================================================="
        << endl;
    cout << "| � |  �������  | ���� |   ������������   | Գ���� | �����. | �������. | ���. ���. | ��������� |"
        << endl;
    cout << "---------------------------------------------------------------------------------------------------"
        << endl;
    for (int i = 0; i < N; i++)
    {
        cout << "| " << right << i + 1 << " ";
        cout << "| " << setw(11) << left << s[I[i]].prizv
            << "| " << setw(4) << right << KursStr[(int)s[I[i]].kurs - 1] << " "
            << "| " << setw(18) << left << SpecStr[s[I[i]].spec]
            << "| " << setw(6) << right << s[I[i]].physics << " "
            << "| " << setw(6) << right << s[I[i]].maths << " ";
        switch (s[I[i]].spec) {
        case KN:
            cout << "| " << setw(8) << right
                << s[I[i]].programming << " | " << setw(12) << right
                << " | " << setw(12) << right << " |" << endl;
            break;
        case INF:
            cout << "| " << setw(11) << right
                << " | " << setw(9) << right << s[I[i]].numMethods
                << " | " << setw(12) << right << " |" << endl;
            break;
        case MATHandECONOM:
        case PHandINF:
        case WORK:
            cout << "| " << setw(11) << right
                << " | " << setw(12) << right
                << " | " << setw(10) << right << s[I[i]].pedagogy << " |" << endl;
            break;
        }
    }
    cout << "===================================================================================================" << endl;
    cout << endl;
}