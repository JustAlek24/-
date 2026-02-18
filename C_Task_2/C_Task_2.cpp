#include <iostream>
#include <cmath>
#include <limits>
#include <sstream>
#include <clocale>
using namespace std;

void sizeInput(int& size);
double** createMatrix(int size);
double** allocateMatrix(int size);
void elementInput(double** matrix, int i, int j);
double determinant(double** matrix, int n);
double** createMinorMatrix(double** matrix, int n, int excludeRow, int excludeCol);
double** createCofactorMatrix(double** matrix, int n);
double** transposeMatrix(double** matrix, int n);
void showMatrix(double** matrix, int size);
void deleteMatrix(double** matrix, int size);


int main() {
    setlocale(LC_ALL, "Rus");

    int size;

    sizeInput(size);
    double** matrix = createMatrix(size);
    showMatrix(matrix, size);
    double det = determinant(matrix, size);

    cout << "Определитель матрицы: " << det << endl;

    if (abs(det) < 1e-10) {
        cout << "Ошибка: Определитель равен нулю. Обратная матрица не существует." << endl;
        deleteMatrix(matrix, size);
        return 1;
    }

    double** cofactor = createCofactorMatrix(matrix, size);
    double** trans = transposeMatrix(cofactor, size);

    double** inverse = allocateMatrix(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            inverse[i][j] = trans[i][j] / det;
        }
    }

    cout << "Обратная матрица:" << endl;
    showMatrix(inverse, size);

    deleteMatrix(cofactor, size);
    deleteMatrix(trans, size);
    deleteMatrix(matrix, size);
    deleteMatrix(inverse, size);
    return 0;
}

double** createMatrix(int size) {

    double** matrix = new double* [size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new double[size];
    }

    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            elementInput(matrix, i, j);
        }
    }

    return matrix;
}

double** allocateMatrix(int size) {
    double** matrix = new double* [size];
    for (int i = 0; i < size; i++) {
        matrix[i] = new double[size];
    }
    return matrix;
}

void elementInput(double** matrix, int i, int j) {
    bool valid = false;
    while (!valid) {
        cout << "Введите элемент из " << i + 1 << " строки " << j + 1 << " столбца: " << "\t";
        string input;
        if (getline(cin, input)) {

            for (char& ch : input) {
                if (ch == ',') ch = '.';
            }

            stringstream streamInput(input);
            if (streamInput >> matrix[i][j]) {
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
}

void sizeInput(int& size) {
    bool valid = false;
    while (!valid) {
        cout << "Введите размер квадратной матрицы:" << "\t";

        if (cin >> size) {

            if (cin.peek() == '\n' && size >= 4) {
                valid = true;
                cin.ignore(); // Очистка буфера после успешного ввода размера
            }
            else {
                cout << "Ошибка. Введите целое число не менее 4." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        else {
            cout << "Валидность ввода нарушена." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

double determinant(double** matrix, int n) {
    if (n == 1) {
        return matrix[0][0];
    }
    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
    }

    double det = 0;

    for (int j = 0; j < n; j++) {
        double** minor = createMinorMatrix(matrix, n, 0, j);

        double minor_det = determinant(minor, n - 1);

        if (j % 2 == 0) {
            det += matrix[0][j] * minor_det;
        }
        else {
            det -= matrix[0][j] * minor_det;
        }

        deleteMatrix(minor, n - 1);
    }

    return det;
}

double** createMinorMatrix(double** matrix, int n, int excludeRow, int excludeCol) {
    double** minor = new double* [n - 1];
    for (int i = 0; i < n - 1; i++) {
        minor[i] = new double[n - 1];
    }

    int minor_i = 0;
    for (int i = 0; i < n; i++) {
        if (i == excludeRow) continue;

        int minor_j = 0;
        for (int j = 0; j < n; j++) {
            if (j == excludeCol) continue;

            minor[minor_i][minor_j] = matrix[i][j];
            minor_j++;
        }
        minor_i++;
    }

    return minor;
}

double** createCofactorMatrix(double** matrix, int n) {
    double** cofactor = new double* [n];
    for (int i = 0; i < n; i++) {
        cofactor[i] = new double[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            double** minor = createMinorMatrix(matrix, n, i, j);
            double minor_det = determinant(minor, n - 1);


            cofactor[i][j] = ((i + j) % 2 == 0 ? 1 : -1) * minor_det;

            deleteMatrix(minor, n - 1);
        }
    }

    return cofactor;
}

double** transposeMatrix(double** matrix, int n) {
    double** transposed = new double* [n];
    for (int i = 0; i < n; i++) {
        transposed[i] = new double[n];

    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            transposed[j][i] = matrix[i][j];
        }
    }

    return transposed;
}

void showMatrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
}

void deleteMatrix(double** matrix, int size) {
    for (int i = 0; i < size; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}