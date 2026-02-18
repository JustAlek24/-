#include <iostream>
#include <cmath>
#include <limits>
#include <sstream>
using namespace std;

int main() {
    setlocale(LC_ALL, "Rus");

    int type;
    double f;
    double x;
    double y;
    bool valid = false;

    while (!valid) {
        cout << "Введите переменную x: ";

        string input;
        if (cin >> ws && getline(cin, input)) {
            for (char& ch : input) {
                if (ch == ',') ch = '.';
            }

            stringstream streamInput(input);
            if (streamInput >> x) {
                streamInput >> ws;
                if (streamInput.eof()) {
                    valid = true;
                }
                else {
                    cout << "Ошибка. Обнаружены лишние символы." << endl;
                }
            }
            else {
                cout << "Ошибка. Переменная введена некорректно." << endl;
            }
        }
        else {
            cout << "Ошибка чтения. Повторите ввод." << endl;
            cin.clear();
        }
    }

    valid = false;

    while (!valid) {
        cout << "Выберете вид функции f(x): " << endl;
        cout << "1 - f(x) = x^2" << endl;
        cout << "2 - f(x) = e^x" << endl;
        cout << "3 - f(x) = sin(x)" << endl;

        if (cin >> type) {

            if (cin.peek() == '\n' && type >= 1 && type <= 3) {
                valid = true;
            }
            else {
                cout << "Ошибка. Введите только целое число от 1 до 3." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        else {
            cout << "Валидность ввода нарушена, введите номер функции правильно." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    if (type == 1) {
        f = x * x;
    }
    else if (type == 2) {
        f = exp(x);
    }
    else {
        f = sin(x);
    }

    if (x > 0) {
        y = log(3 * x) + 2 * f * f;
    }
    else {
        y = sqrt(abs(f)) + sinh(x);
    }

    cout << "Значение выражения: ";
    cout << y << endl;

    return 0;
}