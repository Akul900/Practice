#include <iostream>
#include <Windows.h>
#include <string>
#include <fstream>
using namespace std;
int fillAr(int* A, string& str)
{
    int count = 0;
    string s;
    for (const auto& ch : str)
    {
        if (ch != ' ')
        {
            s += ch;
        }
        else {
            A[count] = (atoi(s.c_str()));
            s = "";
            count++;
        }

    }
    A[count] = (atoi(s.c_str()));
    return count;
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    fstream input;
    string txt;
    string key;
    string V;

    cout << "1. Шифровать" << endl << "2. Дешифровать" << endl;
    do
    {
        cin >> V;
        if (V != "1" && V != "2")
        {
            cout << "Ошибка ввода" << endl;
            cout << "1. Шифровать" << endl << "2. Дешифровать" << endl;
        }
    } while (V != "1" && V != "2");

    if (V == "1")
    {
        input.open("crypto.txt", fstream::in | fstream::out | fstream::trunc);
        cout << "Введите текст" << endl;
        cin.ignore();
        getline(cin, txt);
        cout << "Введите ключ" << endl;
        do
        {
            getline(cin, key);
            if (key == "")
            {
                cout << "Ошибка! ключ не может быть пустым" << endl;
                cout << "Введите ключ" << endl;
            }
        } while (key == "");
        cout << endl;
        int* crypto = new int[txt.length()];
        if (!input.is_open())
        {
            cout << "Ошибка открытия файла" << endl;
        }
        else
        {
            for (int i = 0; i < txt.length(); i++)
            {
                crypto[i] = txt[i] ^ key[i % key.length()];
                if (i == txt.length() - 1)
                {
                    input << crypto[i];
                }
                else
                {
                    input << crypto[i] << " ";
                }
            }
        }
        input.close();
        cout << "Зашифрованный текст" << endl;
        for (int i = 0; i < txt.length(); i++)
        {
            crypto[i] = txt[i] ^ key[i % key.length()];
            cout << crypto[i] << " ";
        }
        cout << endl << endl;
    }
    else
    {
        input.open("crypto.txt", fstream::in | fstream::out);
        cin.ignore();
        if (!input.is_open())
        {
            cout << "Ошибка открытия файла" << endl;
        }
        else
        {
            cout << "Введите ключ" << endl;
            do
            {
                getline(cin, key);
                if (key == "")
                {
                    cout << "Ошибка! ключ не может быть пустым" << endl;
                    cout << "Введите ключ" << endl;
                }

            } while (key == "");
            cout << endl << "Дешифрованный текст" << endl << endl;
            while (!input.eof())
            {
                input >> txt;
                int* crypto = new int[txt.length()];
                int* decrypto = new int[txt.length()];
                int size = fillAr(crypto, txt);
                for (int i = 0; i < size + 1; i++)
                {
                    decrypto[i] = crypto[i] ^ (key[i % key.length()]);
                    cout << (char)decrypto[i];
                }
            }
            cout << endl << endl;
        }
        input.close();
    }
    return 0;
}

