#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdio.h>
#include <fstream>

using namespace std;

unsigned char* KeyInput(unsigned char*); //Ввод головного рядка з клавіатури
unsigned char* FileInput(unsigned char*); //Ввод головного рядка з файлу
unsigned char* FileProcessing(unsigned char*, unsigned char*); //Ввод підрядка з файлу та обробка(виклик функції алгоритму)
unsigned char* KeyProcessing(unsigned char*, unsigned char*); //Ввод підрядка з клавіатури та обробка(виклик функції алгоритму)

void About();//about
void Output(unsigned char*, unsigned char*, int); //Вивод результату роботи на екран
void FileOutput(unsigned char*, unsigned char*, int); //Запис результату роботи в файл
void Counter(char*); //Функція обрахунку кількості символів в файлі

void BadCharHeuristic(unsigned char*, int, int[]);  //Побудова таблиці стоп-символів
int Search(unsigned char*, unsigned char*);  //Алгоритм Боуера-Мура для пошуку підрядка в рядку
int Max(int, int); //Знаходження максимального значення (для алгоритму)

int NumberOfSymbols = 0; //Кількість символів в головному рядку

int main() //Головна функція програми
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    unsigned char* my_str = new  unsigned char[NumberOfSymbols]; //Оголошення масиву символів для головного рядка
    my_str[0] = '\0'; //Очищення масиву від 'сміття'
    unsigned char* find_str = new unsigned char[NumberOfSymbols]; //Оголошення масиву символів для шуканого підрядка
    find_str[0] = '\0'; //Очищення масиву від 'сміття'
    int S = 0; //Змінна яка дорівнює номеру входження підрядка в рядок (якщо входження немає то змінна = 0)

    char punkt;//Змінна для користуванням меню

label1: //Точка повернення в меню
    system("cls");
    cout << '\t' << "Курсова робота Яновича Владислава з теми:" << endl;
    cout << " Розпізнавання ланцюгів символів (Алгоритм Боуера-Мура)" << endl << endl;
    cout << '\t' << "Головне меню програми:" << endl << endl;
    cout << " 1 - Ввод з клавіатури" << endl << " 2 - Ввод з файлу" << endl;
    cout << " 3 - Обробка з клавіатури" << endl << " 4 - Обробка з файлу" << endl << " 5 - Вивод на екран" << endl;
    cout << " 6 - Запис в файл" << endl << " 7 - Про програму" << endl << " 8 - Вихід" << endl << endl << " ЗРОБІТЬ ВИБІР НАТИСНУВШИ НА ПОТРІБНУ ЦИФРУ НА КЛАВІАТУРІ" << endl;
    punkt = _getch();
    switch (punkt)
    {

    case '1'://Ввод головного рядка з клавіатури
    {
        system("cls");
        cout <<'\t'<< "Ввод з клавіатури" << endl;
        my_str = KeyInput(my_str);
        find_str = new unsigned char[NumberOfSymbols];//виділення пам'яті для підрядка
        find_str[0] = '\0';
        system("pause");
        goto label1;
    }
    case '2'://Ввод головного рядка з файлу
    {
        system("cls");
        cout <<'\t'<<"Ввод з файлу" << endl;
        my_str = FileInput(my_str);
        find_str = new unsigned char[NumberOfSymbols];//виділення пам'яті для підрядка
        find_str[0] = '\0';//очищення масиву від 'сміття'
        system("pause");
        goto label1;
    }
    case '3'://Ввод підрядка з клавіатури та обробка(виклик функції алгоритму)
    {
        system("cls");
        cout <<'\t'<<"Обробка з клавіатури" << endl;
        find_str = KeyProcessing(my_str, find_str);
        S = Search(my_str, find_str);
        system("pause");
        goto label1;
    }
    case '4'://Ввод підрядка з файлу та обробка(виклик функції алгоритму)
    {
        system("cls");
        cout <<'\t'<<"Обробка з файлу" << endl;
        find_str = FileProcessing(find_str, my_str);
        S = Search(my_str, find_str);
        system("pause");
        goto label1;
    }
    case '5'://Вивод результату роботи на екран
    {
        system("cls");
        cout <<'\t'<< "Вивод на екран" << endl;
        Output(my_str, find_str, S);
        system("pause");
        goto label1;
    }
    case '6'://Запис результату роботи в файл
    {
        system("cls");
        cout <<'\t'<< "Запис в файл" << endl;
        FileOutput(my_str, find_str, S);
        system("pause");
        goto label1;
    }
    case '7'://Інформація про програму
    {
        system("cls");
        cout <<'\t'<< "Про програму" << endl;
        About();
        system("pause");
        goto label1;
    }

    case '8'://Вихід з програми
    {
        system("cls");
        cout << endl << '\t' << "Робота програми заверена! Гарного вам дня :)" << endl<<endl;
        system("pause");
        return 0;
    }

    default:
    {
        cout << endl << "Натиснуто не ту клавішу!" << endl;
        system("pause");
        goto label1;
    }
    }
    delete[] my_str; 
    delete[] find_str;
    return 0;
}

unsigned char* KeyInput(unsigned char* str)//Ввод головного рядка з клавіатури
{
    cout << "Введіть розмір рядка (мінімум 255) ->";
    cin >> NumberOfSymbols;
    if (NumberOfSymbols < 255)
    {
        cout << "Ви ввели малий розмір, буде встановлено розмір 255 символів" << endl;
        NumberOfSymbols = 255;
    }
    str = new unsigned char[NumberOfSymbols];
    cout << "Введіть головний рядок -> ";
    cin.ignore();
    gets_s((char*)str, NumberOfSymbols);
    return str;
}

unsigned char* FileInput(unsigned char* str)//Ввод головного рядка з файлу
{
    char name[80];
    cout << "Введіть назву файлу->";
    gets_s(name, 80);
    ifstream fread(name);
    if (!fread.is_open())
    {
        cout << "Файл відкрити не вдалося" << endl;
    }
    else
    {
        Counter(name);
        str = new unsigned char[NumberOfSymbols];
        fread.getline((char*)str, NumberOfSymbols);
        cout << "Ви считали з файлу:" << endl;
        cout << str << endl;
    }
    fread.close();
    return str;
}

unsigned char* KeyProcessing(unsigned char* txt, unsigned char* pat)//Ввод підрядка з клавіатури та обробка(виклик функції алгоритму)
{
    if (strlen((char*)txt) == 0)
    {
        cout << "Ви не ввели головний рядок" << endl;
    }
    else
    {
        cout << "Введіть підрядок для пошуку -> ";
        gets_s((char*)pat, NumberOfSymbols);
        while ((strlen((char*)txt) <= strlen((char*)pat)))
        {
            cout << "Помилка при введенні данних, повторіть спробу:" << endl;
            gets_s((char*)pat, NumberOfSymbols);
        }
        cout << endl << "Обробка успішна:) Можете вивести результат на екран або записати його в файл" << endl << endl;
    }
    return pat;
}

unsigned char* FileProcessing(unsigned char* pat, unsigned  char* txt)//Ввод підрядка з файлу та обробка(виклик функції алгоритму)
{
    char name[80];
    cout << "Введіть назву файлу->";
    gets_s(name, 80);
    ifstream fread(name);
    if (!fread.is_open())
    {
        cout << "Файл відкрити не вдалося" << endl;
    }
    else
    {
        Counter(name);
        pat = new unsigned char[NumberOfSymbols];
        fread.getline((char*)pat, NumberOfSymbols);
        if ((strlen((char*)txt) <= strlen((char*)pat) || strlen((char*)pat) == 0))
        {
            cout << "Сталася помилка. Можливо текст більший за головний рядок або головний рядок не введено"<< endl;
            pat[0] = '\0';
        }
        else
        {
            cout << "Ви зчитали з файлу:" << endl;
            cout << pat << endl;
            cout <<endl<<"Обробка успішна:) Можете вивести результат на екран або записати його в файл"<<endl<< endl;
        }
    }
    fread.close();
    return pat;
}

void Counter(char* name) //Функція обрахунку кількості символів в файлі
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


void Output(unsigned char* txt, unsigned  char* pat, int S)//Вивод результату роботи на екран
{
    if (strlen((char*)pat) == 0)
    {
        cout << "Ви не ввели данні для обробки, поверніться до попередніх пунктів" << endl;
    }
    else
    {
        cout << "Заданий текст:" << endl;
        cout << txt << endl << endl;
        cout << "Ви шукаєте -> " << pat << endl << endl;
        if (S > 0 && S <= strlen((char*)txt))
        {
            cout << "Входження знайдено-> " << S << "-й символ" << endl << endl;
        }
        else
            cout << "Входження не знайдено" << endl;
    }
}

void FileOutput(unsigned char* txt, unsigned  char* pat, int S)//Запис результату роботи в файл
{
    if (strlen((char*)pat) == 0)
    {
        cout << "Ви не ввели данні для обробки, поверніться до попередніх пунктів" << endl;
    }
    else
    {
        char outname[80];
        cout << "Введіть назву файлу (та шлях якщо потрібно) для запису->";
        gets_s(outname, 80);
        ofstream fout(outname);
        if (!fout.is_open())
        {
            cout << "Створити/відкрити файл для запису неможливо" << endl;
            system("pause");
        }
        else
        {
            fout << "Заданий головний рядок:" << endl << txt << endl << endl << "Ви шукали->" << pat << endl;
            if (S >= 0 || S < strlen((char*)txt))
            {
                fout <<endl<<"Входження знайдено-> " << S << "-й символ" << endl;
            }
            else
            {
                fout <<endl<<"Входження не знайдено" << endl;
            }
            cout << "Запис в файл " << outname << " успішний :)" << endl;
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

void BadCharHeuristic(unsigned char* string, int size, int* badchar)//Побудова таблиці стоп символів
{
    for (int i = 0; i < 256; i++)
        badchar[i] = -1;

    for (int i = 0; i < size - 1; i++)
        badchar[(int)string[i]] = i;
}


int Search(unsigned char* string, unsigned char* pattern)//Алгоритм Боуера-Мура для пошуку підрядка в рядку
{
    int strsize, patsize, j, shift;
    int badchar[256]; //таблиця стоп-символів

    strsize = strlen((char*)string); //отримання довжини головного рядка
    patsize = strlen((char*)pattern); //отримання довжини підрядка для пошуку

    BadCharHeuristic(pattern, patsize, badchar); //виклик функції для побудови таблиці стоп символів

    shift = 0;

    while (shift <= strsize - patsize) //цикл виконується допоки підрядок не дійде кінця або не буде знайдено входження
    {
        j = patsize - 1;

        while (j >= 0 && pattern[j] == string[shift + j]) //якщо символи співпали
            j--; //перехід до наступного символа зліва

        if (j < 0)
            break; //якщо входження знайдено, то вийти з циклу

        else
            shift += Max(1, j - badchar[string[shift + j]]);//обрахунок зсуву вправо
    }

    if (j > 0)
        return -1;

    else
        return shift + 1;
}

int Max(int a, int b)//Знаходження максимального значення (для алгоритму)
{
    return (a > b) ? a : b;
}