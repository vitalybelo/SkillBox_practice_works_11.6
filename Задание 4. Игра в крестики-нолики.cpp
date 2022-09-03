#include <iostream>
using namespace std;

int checkPlayerPass (string row1, string row2, string row3, char playerSign);
int checkFieldOnWinner (string row1, string row2, string row3, char playerSign);
bool checkFieldOnCorrect (string row1, string row2, string row3);

int main() {
    system("chcp 65001");
    //setlocale(LC_ALL, "Russian_Russia.1251");

    string row1 = ".X.";
    string row2 = "OXX";
    string row3 = "OXO";

    bool fieldCorrect = checkFieldOnCorrect (row1, row2, row3);
    int winsPlayerX = checkFieldOnWinner(row1, row2, row3, 'X');
    int winsPlayerO = checkFieldOnWinner(row1, row2, row3, 'O');
    int countPassesX = checkPlayerPass(row1, row2, row3, 'X');
    int countPassesO = checkPlayerPass(row1, row2, row3, 'O');

    cout << endl;
    cout << "| " << row1 << " |" << endl;
    cout << "| " << row2 << " |" << endl;
    cout << "| " << row3 << " |" << endl << endl;

    if (!fieldCorrect) {
        cout << "Incorrect (допускаются X, O и точка)";
    } else if (countPassesO > countPassesX) {
        cout << "Incorrect (ноликов больше чем крестиков)";
    } else if (winsPlayerX > 0 && winsPlayerO > 0) {
        cout << "Incorrect (выявлено несколько победителей одновременно)";
    } else if (winsPlayerX > 1 || winsPlayerO > 1) {
        cout << "Incorrect (нолики или крестики победили несколько раз)";
    } else if (winsPlayerO > 0 && countPassesX != countPassesO) {
        cout << "Incorrect (нолики победили, но число крестиков - некорректное !)";
    } else if (winsPlayerX > 0 && countPassesO != countPassesX - 1) {
        cout << "Incorrect (крестики победили, но число ноликов - некорректное !)";
    } else if (winsPlayerX > 0) {
        cout << "Петя победил !";
    } else if (winsPlayerO > 0) {
        cout << "Вася победил !";
    } else if (countPassesX + countPassesO < 9) {
        cout << "Ничья (но партия не доиграна !)";
    } else if (countPassesX == countPassesO) {
        cout << "Ничья !";
    }
    cout << endl;
    return 0;
}

/**
 * Возвращает символ игрового поля "крестики нолики"
 * по заданным координатам X и Y
 * @param row1 - строка первого ряда игрового поля
 * @param row2 - строка второго ряда игрового поля
 * @param row3 - строка третьего ряда игрового поля
 * @param x - координата X = от 0 до 2
 * @param y - координата Y = от 0 до 2
 * @return - символы 'X','O','.' или '*' = not found
 */
char getXY (string row1, string row2, string row3, int x, int y) {
    switch (x) {
        case 0: return row1[y];
        case 1: return row2[y];
        case 2: return row3[y];
        default: return '*';
    }
}

/**
 * Считает сколько ходов сделал игрок под символом PlayerSign
 * @param row1 - строка первого ряда игрового поля
 * @param row2 - строка второго ряда игрового поля
 * @param row3 - строка третьего ряда игрового поля
 * @param playerSign - символ игрока на проверку - X или O
 * @return - количество ходов сделанных игроком от 0 до 9
 */
int checkPlayerPass (string row1, string row2, string row3, char playerSign) {
    int passCount = 0;
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (getXY(row1, row2, row3, x, y) == playerSign) passCount++;
        }
    }
    return passCount;
}
/**
 * Ищет любой некорректный символ с игровом поле и возвращает
 * ложь если находит, а если нет - возвращает значение истина
 * @param row1 - строка первого ряда игрового поля
 * @param row2 - строка второго ряда игрового поля
 * @param row3 - строка третьего ряда игрового поля
 * @return = false при наличии символов отличных от 'X','O','.';
 */
bool checkFieldOnCorrect (string row1, string row2, string row3) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            char inc = getXY(row1, row2, row3, x, y);
            if (inc != 'X' && inc != 'O' && inc != '.') return false;
        }
    }
    return true;
}

/**
 * Проверяет игровое поле для задаваемого знака на выигрыш.
 * Проверяются все варианты выигрышей, по линиям и диагоналям.
 * @param row1 - строка первого ряда игрового поля
 * @param row2 - строка второго ряда игрового поля
 * @param row3 - строка третьего ряда игрового поля
 * @param playerSign - символ игрока на проверку - X или O
 * @return - количество побед по линиям или диагоналям, или = 0
 */
int checkFieldOnWinner (string row1, string row2, string row3, char playerSign) {

    int winCount = 0;
    // проверяем горизонтальную линейную победу
    for (int x = 0, y = 0; x < 3; x++, y=0) {
        if (getXY(row1,row2,row3,x,y++) == playerSign &&
            getXY(row1,row2,row3,x,y++) == playerSign &&
            getXY(row1,row2,row3,x,y++) == playerSign) winCount++;
    }
    // проверяем вертикальную линейную победу
    for (int x = 0, y = 0; y < 3; y++, x=0) {
        if (getXY(row1,row2,row3,x++,y) == playerSign &&
            getXY(row1,row2,row3,x++,y) == playerSign &&
            getXY(row1,row2,row3,x++,y) == playerSign) winCount++;
    }
    // проверяем два варианта диагональных побед
    if (getXY(row1,row2,row3,0,0) == playerSign &&
        getXY(row1,row2,row3,1,1) == playerSign &&
        getXY(row1,row2,row3,2,2) == playerSign) winCount++;

    if (getXY(row1,row2,row3,2,0) == playerSign &&
        getXY(row1,row2,row3,1,1) == playerSign &&
        getXY(row1,row2,row3,0,2) == playerSign) winCount++;

    return winCount;
}
