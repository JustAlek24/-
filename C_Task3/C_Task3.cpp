#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cstdio>
#include <cctype>
#include <iomanip>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    const int size = 26;
    int count[size] = {0};

    FILE* f1 = fopen("f1.txt", "r");
    if (f1 == NULL) {
        cout << "Ошибка: файл f1.txt не существует." << endl;
        return 1;
    }

    char symbol;
    while ((symbol = fgetc(f1)) != EOF) {
        if (isalpha(symbol)) {
            symbol = tolower(symbol);
            int i = symbol - 'a';
            if (i >= 0 && i < size) {
                count[i]++;
            }
        }
    }
    fclose(f1);

    FILE* f2 = fopen("f2.txt", "w");

    if (f2 == NULL)
    {
        cout << "Ошибка: не удалось создать файл f2.txt." << endl;
        return 1;
    }

    fprintf(f2, "Буква | Количество\n");
    fprintf(f2, "------------------\n");

    for (int i = 0; i < size; i++) {
        if (count[i] != 0) {
            fprintf(f2, "  %c   |  %d\n", 'a' + i, count[i]);
        }
    }
    fclose(f2);

    cout << "Файл f2.txt успешно сохранён.\n";

    return 0;
}