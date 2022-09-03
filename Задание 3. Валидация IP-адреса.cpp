#include <iostream>
using namespace std;

bool checkIpAddress (string lineString);

int main() {

    string ipAddress = "";
    do {
        cout << "Введите IP адрес: ";
        cin >> ipAddress;

        if (checkIpAddress(ipAddress)) {
            cout << "IP address is correct\n";
        } else {
            cout << "!!! IP address is not correct !!! \n";
        }
        cout << endl;
    } while (true);

    return 0;
}
/**
 * Преобразует строку с номером октеты IP адреса в целое число
 * Полученное значение возвращаете через указатель параметра oNumber
 * @param oString - строка с цифрами октеты
 * @param oNumber - указатель на переменную вызывающей функции
 * @return - истину если число октеты корректное
 */
bool stoi_ip (string oString, int &oNumber)
{
    if (oString[0] == '0' && oString.length() > 1) return false;
    oNumber = stoi(oString);
    if (oNumber < 0 || oNumber > 255) return false;
    return true;
}

bool checkIpAddress (string lineString)
{
    int length = (int) lineString.length();
    if (lineString.empty() ||
        lineString[0] == '.' ||
        lineString[length - 1] == '.') return false;

    string oString;
    int oNumber, dotsCount = 0;
    for (char i : lineString)
    {
        if (i >= '0' && i <= '9') {
            oString += i;                                       // сюда накапливаем цифры
        } else if (i == '.') {
            if (dotsCount++ == 3) return false;                 // точек более 3х
            length = (int) oString.length();
            if (length == 0 || length > 3) return false;        // найден дубль точек или цифр много
            if (!stoi_ip(oString, oNumber)) return false;    // продолжаем если число корректное
            oString = "";                                       // обнуляем строку октеты
        } else return false;                                    // не корректный символ
    }
    if (!stoi_ip(oString, oNumber)) return false;            // продолжаем если число корректное
    return true;
}
