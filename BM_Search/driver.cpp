#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#include <fstream>

using namespace std;

unsigned char* KeyInput(unsigned char*); //���� ��������� ����� � ���������
unsigned char* FileInput(unsigned char*); //���� ��������� ����� � �����
unsigned char* FileProcessing(unsigned char*, unsigned char*); //���� ������� � ����� �� �������(������ ������� ���������)
unsigned char* KeyProcessing(unsigned char*, unsigned char*); //���� ������� � ��������� �� �������(������ ������� ���������)

void About();//about
void Output(unsigned char*, unsigned char*, int); //����� ���������� ������ �� �����
void FileOutput(unsigned char*, unsigned char*, int); //����� ���������� ������ � ����
void Counter(char*); //������� ��������� ������� ������� � ����

void BadCharHeuristic(unsigned char*, int, int[]);  //�������� ������� ����-�������
int Search(unsigned char*, unsigned char*);  //�������� ������-���� ��� ������ ������� � �����
int Max(int, int); //����������� ������������� �������� (��� ���������)

int NumberOfSymbols = 0; //ʳ������ ������� � ��������� �����

int main() //������� ������� ��������
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned char* my_str = new  unsigned char[NumberOfSymbols]; //���������� ������ ������� ��� ��������� �����
    my_str[0] = '\0'; //�������� ������ �� '�����'
    unsigned char* find_str = new unsigned char[NumberOfSymbols]; //���������� ������ ������� ��� �������� �������
    find_str[0] = '\0'; //�������� ������ �� '�����'
    int S = 0; //����� ��� ������� ������ ��������� ������� � ����� (���� ��������� ���� �� ����� = 0)

    char punkt;//����� ��� ������������� ����

label1: //����� ���������� � ����
    system("cls");
    cout << '\t' << "������� ������ ������� ���������� � ����:" << endl;
    cout << " ������������ ������� ������� (�������� ������-����)" << endl << endl;
    cout << '\t' << "������� ���� ��������:" << endl << endl;
    cout << " 1 - ���� � ���������" << endl << " 2 - ���� � �����" << endl;
    cout << " 3 - ������� � ���������" << endl << " 4 - ������� � �����" << endl << " 5 - ����� �� �����" << endl;
    cout << " 6 - ����� � ����" << endl << " 7 - ��� ��������" << endl << " 8 - �����" << endl << endl << " ������� ����� ���������� �� ���в��� ����� �� ���²���в" << endl;
    punkt = _getch();
    switch (punkt)
    {

    case '1'://���� ��������� ����� � ���������
    {
        system("cls");
        cout <<'\t'<< "���� � ���������" << endl;
        my_str = KeyInput(my_str);
        find_str = new unsigned char[NumberOfSymbols];//�������� ���'�� ��� �������
        find_str[0] = '\0';
        system("pause");
        goto label1;
    }
    case '2'://���� ��������� ����� � �����
    {
        system("cls");
        cout <<'\t'<<"���� � �����" << endl;
        my_str = FileInput(my_str);
        find_str = new unsigned char[NumberOfSymbols];//�������� ���'�� ��� �������
        find_str[0] = '\0';//�������� ������ �� '�����'
        system("pause");
        goto label1;
    }
    case '3'://���� ������� � ��������� �� �������(������ ������� ���������)
    {
        system("cls");
        cout <<'\t'<<"������� � ���������" << endl;
        find_str = KeyProcessing(my_str, find_str);
        S = Search(my_str, find_str);
        system("pause");
        goto label1;
    }
    case '4'://���� ������� � ����� �� �������(������ ������� ���������)
    {
        system("cls");
        cout <<'\t'<<"������� � �����" << endl;
        find_str = FileProcessing(find_str, my_str);
        S = Search(my_str, find_str);
        system("pause");
        goto label1;
    }
    case '5'://����� ���������� ������ �� �����
    {
        system("cls");
        cout <<'\t'<< "����� �� �����" << endl;
        Output(my_str, find_str, S);
        system("pause");
        goto label1;
    }
    case '6'://����� ���������� ������ � ����
    {
        system("cls");
        cout <<'\t'<< "����� � ����" << endl;
        FileOutput(my_str, find_str, S);
        system("pause");
        goto label1;
    }
    case '7'://���������� ��� ��������
    {
        system("cls");
        cout <<'\t'<< "��� ��������" << endl;
        About();
        system("pause");
        goto label1;
    }

    case '8'://����� � ��������
    {
        system("cls");
        cout << endl << '\t' << "������ �������� ��������! ������� ��� ��� :)" << endl<<endl;
        system("pause");
        return 0;
    }

    default:
    {
        cout << endl << "��������� �� �� ������!" << endl;
        system("pause");
        goto label1;
    }
    }
    delete[] my_str; 
    delete[] find_str;
    return 0;
}

unsigned char* KeyInput(unsigned char* str)//���� ��������� ����� � ���������
{
    cout << "������ ����� ����� (����� 255) ->";
    cin >> NumberOfSymbols;
    if (NumberOfSymbols < 255)
    {
        cout << "�� ����� ����� �����, ���� ����������� ����� 255 �������" << endl;
        NumberOfSymbols = 255;
    }
    str = new unsigned char[NumberOfSymbols];
    cout << "������ �������� ����� -> ";
    cin.ignore();
    gets_s((char*)str, NumberOfSymbols);
    return str;
}

unsigned char* FileInput(unsigned char* str)//���� ��������� ����� � �����
{
    char name[80];
    cout << "������ ����� �����->";
    gets_s(name, 80);
    ifstream fread(name);
    if (!fread.is_open())
    {
        cout << "���� ������� �� �������" << endl;
    }
    else
    {
        Counter(name);
        str = new unsigned char[NumberOfSymbols];
        fread.getline((char*)str, NumberOfSymbols);
        cout << "�� ������� � �����:" << endl;
        cout << str << endl;
    }
    fread.close();
    return str;
}

unsigned char* KeyProcessing(unsigned char* txt, unsigned char* pat)//���� ������� � ��������� �� �������(������ ������� ���������)
{
    if (strlen((char*)txt) == 0)
    {
        cout << "�� �� ����� �������� �����" << endl;
    }
    else
    {
        cout << "������ ������� ��� ������ -> ";
        gets_s((char*)pat, NumberOfSymbols);
        while ((strlen((char*)txt) <= strlen((char*)pat)))
        {
            cout << "������� ��� ������� ������, �������� ������:" << endl;
            gets_s((char*)pat, NumberOfSymbols);
        }
        cout << endl << "������� ������:) ������ ������� ��������� �� ����� ��� �������� ���� � ����" << endl << endl;
    }
    return pat;
}

unsigned char* FileProcessing(unsigned char* pat, unsigned  char* txt)//���� ������� � ����� �� �������(������ ������� ���������)
{
    char name[80];
    cout << "������ ����� �����->";
    gets_s(name, 80);
    ifstream fread(name);
    if (!fread.is_open())
    {
        cout << "���� ������� �� �������" << endl;
    }
    else
    {
        Counter(name);
        pat = new unsigned char[NumberOfSymbols];
        fread.getline((char*)pat, NumberOfSymbols);
        if ((strlen((char*)txt) <= strlen((char*)pat) || strlen((char*)pat) == 0))
        {
            cout << "������� �������. ������� ����� ������ �� �������� ����� ��� �������� ����� �� �������"<< endl;
            pat[0] = '\0';
        }
        else
        {
            cout << "�� ������� � �����:" << endl;
            cout << pat << endl;
            cout <<endl<<"������� ������:) ������ ������� ��������� �� ����� ��� �������� ���� � ����"<<endl<< endl;
        }
    }
    fread.close();
    return pat;
}

void Counter(char* name) //������� ��������� ������� ������� � ����
{
    unsigned char sym;
    int n = 0;
    ifstream fread(name);
    while (!fread.eof())
    {
        sym = fread.get();
        n++;
    }
    NumberOfSymbols = n;
    fread.close();
}


void Output(unsigned char* txt, unsigned  char* pat, int S)//����� ���������� ������ �� �����
{
    if (strlen((char*)pat) == 0)
    {
        cout << "�� �� ����� ���� ��� �������, ���������� �� ��������� ������" << endl;
    }
    else
    {
        cout << "������� �����:" << endl;
        cout << txt << endl << endl;
        cout << "�� ������ -> " << pat << endl << endl;
        if (S > 0 && S <= strlen((char*)txt))
        {
            cout << "��������� ��������-> " << S << "-� ������" << endl << endl;
        }
        else
            cout << "��������� �� ��������" << endl;
    }
}

void FileOutput(unsigned char* txt, unsigned  char* pat, int S)//����� ���������� ������ � ����
{
    if (strlen((char*)pat) == 0)
    {
        cout << "�� �� ����� ���� ��� �������, ���������� �� ��������� ������" << endl;
    }
    else
    {
        char outname[80];
        cout << "������ ����� ����� (�� ���� ���� �������) ��� ������->";
        gets_s(outname, 80);
        ofstream fout(outname);
        if (!fout.is_open())
        {
            cout << "��������/������� ���� ��� ������ ���������" << endl;
            system("pause");
        }
        else
        {
            fout << "������� �������� �����:" << endl << txt << endl << endl << "�� ������->" << pat << endl;
            if (S >= 0 || S < strlen((char*)txt))
            {
                fout <<endl<<"��������� ��������-> " << S << "-� ������" << endl;
            }
            else
            {
                fout <<endl<<"��������� �� ��������" << endl;
            }
            cout << "����� � ���� " << outname << " ������� :)" << endl;
            fout.close();
        }
    }
}

void About()
{
    char ch = '\0';
    ifstream about_file("about.txt",ios::in);
    while (!about_file.eof())
    {
        cout << ch;
        ch = about_file.get();
    }
    cout<<endl;
    about_file.close();
}

void BadCharHeuristic(unsigned char* string, int size, int* badchar)//�������� ������� ���� �������
{
    for (int i = 0; i < 256; i++)
        badchar[i] = -1;

    for (int i = 0; i < size - 1; i++)
        badchar[(int)string[i]] = i;
}


int Search(unsigned char* string, unsigned char* pattern)//�������� ������-���� ��� ������ ������� � �����
{
    int strsize, patsize, j, shift;
    int badchar[256]; //������� ����-�������

    strsize = strlen((char*)string); //��������� ������� ��������� �����
    patsize = strlen((char*)pattern); //��������� ������� ������� ��� ������

    BadCharHeuristic(pattern, patsize, badchar); //������ ������� ��� �������� ������� ���� �������

    shift = 0;

    while (shift <= strsize - patsize) //���� ���������� ������ ������� �� ���� ���� ��� �� ���� �������� ���������
    {
        j = patsize - 1;

        while (j >= 0 && pattern[j] == string[shift + j]) //���� ������� �������
            j--; //������� �� ���������� ������� ����

        if (j < 0)
            break; //���� ��������� ��������, �� ����� � �����

        else
            shift += Max(1, j - badchar[string[shift + j]]);//��������� ����� ������
    }

    if (j > 0)
        return -1;

    else
        return shift + 1;
}

int Max(int a, int b)//����������� ������������� �������� (��� ���������)
{
    return (a > b) ? a : b;
}