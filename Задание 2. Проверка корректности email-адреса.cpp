#include <iostream>
using namespace std;

bool compileEmailString (string emailString);

int main() {
    setlocale(LC_ALL, "Russian_Russia.1251");
    string emailString;
    do {
        cout << "Введите адрес электронной почты: ";
        cin >> emailString;
    } while (emailString.empty());

    if (compileEmailString(emailString)) {
        cout << "\nВведенная строка: корректна.\n";
    } else {
        cerr << "\nВведенная строка: не корректна !\n";
    }
    return 0;
}

/**
 * Возвращает позицию первого найденного символа в строке
 * @param inString - строка поиска, где ищется нужный символ
 * @param lookChar - искомый символ в сроке поиска
 * @param indexPos - позиция с которой начинается поиск
 * @return - значение индекса в строке или -1 если не найден
 */
int find_first_of(string inString, char lookChar, int indexPos) {
    for (;indexPos < inString.length(); indexPos++) {
        if (lookChar == inString[indexPos]) return indexPos;
    }
    return -1;
}
/**
 * Возвращает подстроку из строки между двумя заданными индексами
 * @param inString - строка из которой извлекается подстрока
 * @param startPos - начальная позиция в строке
 * @param finalPos - конечная позиция в строке
 * @return - возвращаемая подстрока или "" пустая если не найдена
 */
string substring (string inString, int startPos, int finalPos) {
    if (inString.empty()) return "";
    int length = (int) inString.length();
    if (finalPos >= length) finalPos = length - 1;
    if (startPos > finalPos) return "";
    string resultString;
    for (; startPos <= finalPos; startPos++) {
        resultString += inString[startPos];
    }
    return resultString;
}
/**
 * Проверяет строку на соответствие каждого символа словарю. Если
 * в строке находится символ не из словаря, работа прекращается и
 * возвращается значение false. Проверяются условия максимальной
 * длины строки заданному параметром значению. Поверяется наличие
 * точек в начале и конце строки, а также двойные точки внутри строки.
 * @param lookString - строка которая проверяется
 * @param pattern - строка состоящая из символов допустимых для строки
 * @param maxPos - максимальная допустимая длина строки
 * @return - возвращает истину если строка содержит только символы из паттерна
 */
bool emailStringCheck (string lookString, string pattern, int maxPos) {
    int length = (int) lookString.length();
    if (length > maxPos || length < 1) return false;
    if (lookString[0] == '.' || lookString[length - 1] == '.') return false;

    for (int i = 0, checkDots = -2; i < length; i++) {
        if (lookString[i] == '.') {
            if (checkDots < i - 1) checkDots = i; else return false;
        } else {
            if (find_first_of(pattern, lookString[i], 0) == -1) return false;
        }
    }
    return true;
}

bool compileEmailString (string emailString) {

    string glossaryOne = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-!#$%&'*+-/=?^_`{|}~";
    string glossaryTwo = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-";
    int length = (int) emailString.length();
    int dogPos = find_first_of(emailString, '@',0);
    if (dogPos < 0 || length < 3) return false;

    string partOne = substring(emailString, 0, dogPos - 1);
    string partTwo = substring(emailString, dogPos + 1, length - 1);

    if (!emailStringCheck(partOne, glossaryOne, 64) ||
        !emailStringCheck(partTwo, glossaryTwo, 63)) return false;

    return true;
}