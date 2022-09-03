#include <iostream>
using namespace std;

string encrypt_caesar(string inString, int code);
string decrypt_caesar(string inString, int code);

int main() {
    setlocale(LC_ALL, "Russian_Russia.1251");

    string lineCaesar;
    do {
        cout << "Введите строку: ";
        getline(cin, lineCaesar);
    } while (lineCaesar.empty());

    int codeCaesar;
    cout << "Введите число шифрования: ";
    cin >> codeCaesar;
    codeCaesar = abs(codeCaesar % 26);

    cout << (lineCaesar = encrypt_caesar(lineCaesar,codeCaesar)) << endl;
    cout << (lineCaesar = decrypt_caesar(lineCaesar,codeCaesar)) << endl;

    return 0;
}

string encrypt_caesar(string inString, int code) {
    /**
     * закручивает все прописные символы английского алфавита
     * в шифр. На вход дается строка и значение шифра, возврат
     * зашифрованная строка
     */
    int circleCode;
    string resultSting;
    for (char i: inString)
    {
        if (i >= 'A' && i <= 'Z') {
            circleCode = (int) i - 65 + code;
            circleCode = 65 + circleCode % 26;
            resultSting += (char) circleCode;
            continue;
        } else if (i >= 'a' && i <= 'z') {
            circleCode = (int) i - 97 + code;
            circleCode = 97 + circleCode % 26;
            resultSting += (char) circleCode;
            continue;
        }
        resultSting += i;
    }
    return resultSting;
}

string decrypt_caesar(string inString, int code) {
    /**
     * раскручивает все прописные символы английского алфавита
     * из зашифрованных в изначальную строку. Параметры: строка
     * зашифрованная кодом и значение этого кода. Возвращает
     * оригинальную строку
     */
    int circleCode;
    string resultSting;
    for (char i: inString)
    {
        if (i >= 'A' && i <= 'Z') {
            circleCode = 90 - (int) i + code;
            circleCode = 90 - circleCode % 26;
            resultSting += (char) circleCode;
            continue;
        } else if (i >= 'a' && i <= 'z') {
            circleCode = 122 - (int) i + code;
            circleCode = 122 - circleCode % 26;
            resultSting += (char) circleCode;
            continue;
        }
        resultSting += i;
    }
    return resultSting;
}

