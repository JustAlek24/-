#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include <windows.h>

using namespace std;

struct Climber {
    string firstName;
    string lastName;
    string address;
};

struct Ascent {
    string startDate;
    string endDate;
    vector<Climber> climbers;
    string mountainName;
    int height;
    string country;
    string region;
};

string removeBOM(const string& str) {
    if (str.length() >= 3 &&
        static_cast<unsigned char>(str[0]) == 0xEF &&
        static_cast<unsigned char>(str[1]) == 0xBB &&
        static_cast<unsigned char>(str[2]) == 0xBF) {
        return str.substr(3);
    }
    return str;
}

void addAscent(vector<Ascent>& ascents) {
    Ascent newAscent;
    cout << "\nДобавление нового восхождения" << endl;

    cout << "Дата начала: ";
    cin >> newAscent.startDate;
    cout << "Дата завершения: ";
    cin >> newAscent.endDate;
    cin.ignore();

    cout << "Название горы: ";
    getline(cin, newAscent.mountainName);
    cout << "Высота горы: ";
    cin >> newAscent.height;
    cin.ignore();
    cout << "Страна: ";
    getline(cin, newAscent.country);
    cout << "Район: ";
    getline(cin, newAscent.region);

    int numClimbers;
    cout << "Количество альпинистов: ";
    cin >> numClimbers;

    for (int i = 0; i < numClimbers; i++) {
        Climber climber;
        cout << "Альпинист " << i + 1 << ":" << endl;
        cout << "  Имя: ";
        cin >> climber.firstName;
        cout << "  Фамилия: ";
        cin >> climber.lastName;
        cin.ignore();
        cout << "  Адрес: ";
        getline(cin, climber.address);
        newAscent.climbers.push_back(climber);
    }

    ascents.push_back(newAscent);
    cout << "Восхождение добавлено." << endl;
}

void deleteAscent(vector<Ascent>& ascents) {
    if (ascents.empty()) {
        cout << "Нет данных о восхождении" << endl;
        return;
    }

    cout << "\nСписок восхождений для удаления" << endl;
    for (size_t i = 0; i < ascents.size(); i++) {
        const Ascent& a = ascents[i];
        cout << i + 1 << ". " << a.mountainName << " (" << a.height << " м)"
            << " - " << a.startDate << " - " << a.endDate
            << " - " << a.country << ", " << a.region << endl;
    }

    int choice;
    cout << "\nВведите номер восхождения для удаления (0 для отмены): ";
    cin >> choice;

    if (choice == 0) {
        cout << "Удаление отменено." << endl;
        return;
    }

    if (choice < 1 || choice > static_cast<int>(ascents.size())) {
        cout << "Неверный номер восхождения!" << endl;
        return;
    }
    else {
        ascents.erase(ascents.begin() + choice - 1);
        cout << "Восхождение успешно удалено!" << endl;
    }
}

void deleteClimber(vector<Ascent>& ascents) {
    if (ascents.empty()) {
        cout << "Нет данных о восхождениях." << endl;
        return;
    }

    string firstName, lastName;
    cout << "\nУдаление альпиниста" << endl;
    cout << "Введите имя альпиниста: ";
    cin >> firstName;
    cout << "Введите фамилию альпиниста: ";
    cin >> lastName;

    vector<int> ascentIndices;
    vector<int> climberIndices;

    for (int i = 0; i < ascents.size(); i++) {
        for (int j = 0; j < ascents[i].climbers.size(); j++) {
            if (ascents[i].climbers[j].firstName == firstName &&
                ascents[i].climbers[j].lastName == lastName) {
                ascentIndices.push_back(i);
                climberIndices.push_back(j);
            }
        }
    }

    if (ascentIndices.empty()) {
        cout << "Альпинист " << firstName << " " << lastName << " не найден." << endl;
        return;
    }

    if (ascentIndices.size() == 1) {
        int ascIndex = ascentIndices[0];
        int climIndex = climberIndices[0];

        cout << "Альпинист успешно удален!" << endl;
        cout << "Имя: " << ascents[ascIndex].climbers[climIndex].firstName << " "
            << ascents[ascIndex].climbers[climIndex].lastName << endl;
        cout << "Адрес: " << ascents[ascIndex].climbers[climIndex].address << endl;
        cout << "Участвовал в восхождении: " << ascents[ascIndex].mountainName << endl;

        ascents[ascIndex].climbers.erase(ascents[ascIndex].climbers.begin() + climIndex);
        
        return;
    }


    cout << "\nНайдено несколько альпинистов с именем " << firstName << " " << lastName << ":" << endl;
    cout << "=============================================" << endl;

    for (int i = 0; i < ascentIndices.size(); i++) {
        int ascIndex = ascentIndices[i];
        int climIndex = climberIndices[i];

        cout << i + 1 << ". " << ascents[ascIndex].climbers[climIndex].firstName << " "
            << ascents[ascIndex].climbers[climIndex].lastName << endl;
        cout << "   Адрес: " << ascents[ascIndex].climbers[climIndex].address << endl;
        cout << "   Восхождение: " << ascents[ascIndex].mountainName << " (" << ascents[ascIndex].height << " м)" << endl;
        cout << "   Период: " << ascents[ascIndex].startDate << " - " << ascents[ascIndex].endDate << endl;
        cout << endl;
    }

    int choice;
    cout << "Введите номер альпиниста для удаления: ";
    cin >> choice;

    if (choice < 1 || choice > ascentIndices.size()) {
        cout << "Неверный номер!" << endl;
        return;
    }

    int selectedIndex = choice - 1;
    int ascIndex = ascentIndices[selectedIndex];
    int climIndex = climberIndices[selectedIndex];

    cout << "Альпинист успешно удален из восхождения." << endl;

    ascents[ascIndex].climbers.erase(ascents[ascIndex].climbers.begin() + climIndex);
    
}

void saveToFile(const vector<Ascent>& ascents, const string& filename) {
    ofstream file(filename);

    if (!file.is_open()) {
        cout << "Ошибка открытия файла!" << endl;
        return;
    }

    for (const Ascent& a : ascents) {
        file << a.startDate << "|" << a.endDate << "|"
            << a.mountainName << "|" << a.height << "|"
            << a.country << "|" << a.region << "|"
            << a.climbers.size();

        for (const Climber& c : a.climbers) {
            file << "|" << c.firstName << "|" << c.lastName << "|" << c.address;
        }
        file << endl;
    }

    file.close();
    cout << "Данные сохранены в файл!" << endl;
}

void loadFromFile(vector<Ascent>& ascents, const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Файл не найден. Будет создан новый." << endl;
        return;
    }

    ascents.clear();
    string line;
    bool firstLine = true;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (firstLine) {
            line = removeBOM(line);
            firstLine = false;
        }

        Ascent a;
        size_t pos = 0;
        string token;
        int field = 0;
        int numClimbers = 0;

        while ((pos = line.find('|')) != string::npos) {
            token = line.substr(0, pos);

            switch (field) {
            case 0: a.startDate = token; break;
            case 1: a.endDate = token; break;
            case 2: a.mountainName = token; break;
            case 3: a.height = stoi(token); break;
            case 4: a.country = token; break;
            case 5: a.region = token; break;
            case 6: numClimbers = stoi(token); break;
            default:
                if (field > 6) {
                    Climber c;
                    c.firstName = token;

                    pos = line.find('|');
                    token = line.substr(0, pos);
                    c.lastName = token;
                    line.erase(0, pos + 1);

                    pos = line.find('|');
                    token = line.substr(0, pos);
                    c.address = token;
                    line.erase(0, pos + 1);

                    a.climbers.push_back(c);
                    field += 2;
                }
                break;
            }

            line.erase(0, pos + 1);
            field++;
        }

        ascents.push_back(a);
    }

    file.close();
    if (!ascents.empty()) {
        cout << "Данные загружены из файла. Загружено восхождений: " << ascents.size() << endl;
    }
}

void displayAllAscents(const vector<Ascent>& ascents) {
    if (ascents.empty()) {
        cout << "Нет данных о восхождениях." << endl;
        return;
    }

    cout << "\nСписок всех восхождений" << endl;
    for (size_t i = 0; i < ascents.size(); i++) {
        const Ascent& a = ascents[i];
        cout << i + 1 << ". " << a.mountainName << " (" << a.height << " м)"
            << "\n   Период: " << a.startDate << " - " << a.endDate
            << "\n   Местоположение: " << a.country << ", " << a.region
            << "\n   Количество альпинистов: " << a.climbers.size() << endl << endl;
    }
}

void displayAllClimbers(const vector<Ascent>& ascents) {
    if (ascents.empty()) {
        cout << "Нет данных о восхождениях." << endl;
        return;
    }

    cout << "\nСписок всех альпинистов" << endl;
    int climberCount = 1;

    for (const Ascent& a : ascents) {
        for (const Climber& c : a.climbers) {
            cout << climberCount++ << ". " << c.lastName << " "
                << c.firstName
                << "\n   Адрес: " << c.address
                << "\n   Участвовал в восхождении: " << a.mountainName << endl << endl;
        }
    }
}

void displayMenu() {
    cout << "\nАльпинистский клуб" << endl;
    cout << "1. Добавить новое восхождение" << endl;
    cout << "2. Показать все восхождения" << endl;
    cout << "3. Показать всех альпинистов" << endl;
    cout << "4. Сохранить данные" << endl;
    cout << "5. Удалить восхождение" << endl;
    cout << "6. Удалить альпиниста" << endl;
    cout << "0. Выход" << endl;
    cout << "Выберите действие: ";
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Rus");

    vector<Ascent> ascents;
    const string filename = "ascents.txt";
    int choice;

    loadFromFile(ascents, filename);

    do {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            addAscent(ascents);
            break;
        case 2:
            displayAllAscents(ascents);
            break;
        case 3:
            displayAllClimbers(ascents);
            break;
        case 4:
            saveToFile(ascents, filename);
            break;
        case 5:
            deleteAscent(ascents);  
            break;
        case 6:
            deleteClimber(ascents);
            break;
        case 0:
            cout << "Выход из программы." << endl;
            break;
        default:
            cout << "Неверный выбор!" << endl;
        }
    } while (choice != 0);

    return 0;
}

