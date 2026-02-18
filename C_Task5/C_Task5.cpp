#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <windows.h>
#include <locale>

using namespace std;

void setupRussianConsole() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
}

// Абстрактный класс Пассажироперевозчик
class PassengerCarrier {
protected:
    string name;
    int maxPassengers;
    double speed;
    double ticketPrice;

public:
    PassengerCarrier(const string& name, int maxPass, double spd, double price)
        : name(name), maxPassengers(maxPass), speed(spd), ticketPrice(price) {
    }

    virtual ~PassengerCarrier() {}

    virtual void displayInfo() const = 0;
    virtual double calculateTravelTime(double distance) const = 0;
    virtual double calculateCost(int passengers, double distance) const = 0;
    virtual string getType() const = 0;

    string getName() const { return name; }
    int getMaxPassengers() const { return maxPassengers; }
    double getSpeed() const { return speed; }
    double getTicketPrice() const { return ticketPrice; }
};

// Класс Самолет
class Airplane : public PassengerCarrier {
private:
    string airline;
    bool hasBusinessClass;

public:
    Airplane(const string& name, int maxPass, double spd, double price,
        const string& airline, bool businessClass = false)
        : PassengerCarrier(name, maxPass, spd, price),
        airline(airline), hasBusinessClass(businessClass) {
    }

    void displayInfo() const override {
        cout << "САМОЛЕТ: " << name << endl;
        cout << "   Авиакомпания: " << airline << endl;
        cout << "   Макс. пассажиров: " << maxPassengers << endl;
        cout << "   Скорость: " << speed << " км/ч" << endl;
        cout << "   Цена билета: " << ticketPrice << " руб." << endl;
        cout << "   Бизнес-класс: " << (hasBusinessClass ? "да" : "нет") << endl;
    }

    double calculateTravelTime(double distance) const override {
        double flightTime = distance / speed;
        double additionalTime = 1.5;
        return flightTime + additionalTime;
    }

    double calculateCost(int passengers, double distance) const override {
        if (passengers > maxPassengers) {
            cout << "ПРЕВЫШЕНА ВМЕСТИМОСТЬ!" << endl;
            return -1;
        }
        double baseCost = passengers * ticketPrice;
        double distanceMultiplier = 1.0 + (distance / 1000) * 0.1;
        return baseCost * distanceMultiplier;
    }

    string getType() const override { return "Самолет"; }
};

// Класс Поезд
class Train : public PassengerCarrier {
private:
    int carriageCount;
    string trainType;

public:
    Train(const string& name, int maxPass, double spd, double price,
        int carriages, const string& type = "пассажирский")
        : PassengerCarrier(name, maxPass, spd, price),
        carriageCount(carriages), trainType(type) {
    }

    void displayInfo() const override {
        cout << "ПОЕЗД: " << name << endl;
        cout << "   Тип: " << trainType << endl;
        cout << "   Макс. пассажиров: " << maxPassengers << endl;
        cout << "   Количество вагонов: " << carriageCount << endl;
        cout << "   Скорость: " << speed << " км/ч" << endl;
        cout << "   Цена билета: " << ticketPrice << " руб." << endl;
    }

    double calculateTravelTime(double distance) const override {
        double travelTime = distance / speed;
        double stopTime = (distance / 100) * 0.25;
        return travelTime + stopTime;
    }

    double calculateCost(int passengers, double distance) const override {
        if (passengers > maxPassengers) {
            cout << "ПРЕВЫШЕНА ВМЕСТИМОСТЬ!" << endl;
            return -1;
        }
        double baseCost = passengers * ticketPrice;
        double distanceMultiplier = 1.0 + (distance / 1000) * 0.05;
        return baseCost * distanceMultiplier;
    }

    string getType() const override { return "Поезд"; }
};

// Класс Автомобиль
class Automobile : public PassengerCarrier {
private:
    string carType;
    double fuelConsumption;

public:
    Automobile(const string& name, int maxPass, double spd, double price,
        const string& type, double fuelConsump)
        : PassengerCarrier(name, maxPass, spd, price),
        carType(type), fuelConsumption(fuelConsump) {
    }

    void displayInfo() const override {
        cout << "АВТОМОБИЛЬ: " << name << endl;
        cout << "   Тип: " << carType << endl;
        cout << "   Макс. пассажиров: " << maxPassengers << endl;
        cout << "   Скорость: " << speed << " км/ч" << endl;
        cout << "   Цена за место: " << ticketPrice << " руб." << endl;
        cout << "   Расход топлива: " << fuelConsumption << " л/100км" << endl;
    }

    double calculateTravelTime(double distance) const override {
        double driveTime = distance / speed;
        double trafficFactor = 1.2;
        double restTime = (distance > 500) ? 1.0 : 0;
        return driveTime * trafficFactor + restTime;
    }

    double calculateCost(int passengers, double distance) const override {
        if (passengers > maxPassengers) {
            cout << "ПРЕВЫШЕНА ВМЕСТИМОСТЬ!" << endl;
            return -1;
        }
        double fuelCost = (distance / 100) * fuelConsumption * 50;
        double passengerCost = passengers * ticketPrice;
        return passengerCost + fuelCost;
    }

    string getType() const override { return "Автомобиль"; }
};

// Класс Автобус
class Bus : public PassengerCarrier {
private:
    bool hasLuggageCompartment;
    bool hasAirConditioning;

public:
    Bus(const string& name, int maxPass, double spd, double price,
        bool luggage = true, bool ac = true)
        : PassengerCarrier(name, maxPass, spd, price),
        hasLuggageCompartment(luggage), hasAirConditioning(ac) {
    }

    void displayInfo() const override {
        cout << "АВТОБУС: " << name << endl;
        cout << "   Макс. пассажиров: " << maxPassengers << endl;
        cout << "   Скорость: " << speed << " км/ч" << endl;
        cout << "   Цена билета: " << ticketPrice << " руб." << endl;
        cout << "   Багажное отделение: " << (hasLuggageCompartment ? "да" : "нет") << endl;
        cout << "   Кондиционер: " << (hasAirConditioning ? "да" : "нет") << endl;
    }

    double calculateTravelTime(double distance) const override {
        double travelTime = distance / speed;
        double stopTime = (distance / 50) * 0.1;
        return travelTime + stopTime;
    }

    double calculateCost(int passengers, double distance) const override {
        if (passengers > maxPassengers) {
            cout << "ПРЕВЫШЕНА ВМЕСТИМОСТЬ!" << endl;
            return -1;
        }
        return passengers * ticketPrice;
    }

    string getType() const override { return "Автобус"; }
};

int main() {
    // Настройка русской кодировки
    setupRussianConsole();

    vector<unique_ptr<PassengerCarrier>> carriers;

    carriers.push_back(make_unique<Airplane>("Boeing 737", 180, 850, 5000, "Аэрофлот", true));
    carriers.push_back(make_unique<Train>("Сапсан", 500, 250, 1500, 12, "скорый"));
    carriers.push_back(make_unique<Automobile>("Mercedes Vito", 7, 120, 300, "минивэн", 8.5));
    carriers.push_back(make_unique<Bus>("Нефаз", 45, 90, 800, true, true));
    carriers.push_back(make_unique<Airplane>("Airbus A320", 150, 800, 4500, "S7 Airlines", false));

    cout << "=== ДЕМОНСТРАЦИЯ РАБОТЫ С ПАССАЖИРОПЕРЕВОЗЧИКАМИ ===" << endl << endl;

    cout << "1. ИНФОРМАЦИЯ О ВСЕХ ПЕРЕВОЗЧИКАХ:" << endl;
    cout << "=====================================" << endl;
    for (const auto& carrier : carriers) {
        carrier->displayInfo();
        cout << endl;
    }

    cout << "2. РАСЧЕТ ПОЕЗДКИ МОСКВА-САНКТ-ПЕТЕРБУРГ (650 км):" << endl;
    cout << "==================================================" << endl;

    double distance = 650;
    int passengers = 4;

    for (const auto& carrier : carriers) {
        cout << carrier->getType() << " \"" << carrier->getName() << "\":" << endl;

        double time = carrier->calculateTravelTime(distance);
        double cost = carrier->calculateCost(passengers, distance);

        if (cost > 0) {
            cout << "   Время в пути: " << time << " часов" << endl;
            cout << "   Стоимость для " << passengers << " пассажиров: "
                << cost << " руб." << endl;
            cout << "   Стоимость на человека: " << cost / passengers << " руб." << endl;
        }
        cout << endl;
    }

    cout << "3. СРАВНЕНИЕ ТРАНСПОРТНЫХ СРЕДСТВ:" << endl;
    cout << "===================================" << endl;

    for (const auto& type : { "Самолет", "Поезд", "Автомобиль", "Автобус" }) {
        cout << type << ":" << endl;
        for (const auto& carrier : carriers) {
            if (carrier->getType() == type) {
                cout << "   - " << carrier->getName()
                    << " (вместимость: " << carrier->getMaxPassengers()
                    << ", скорость: " << carrier->getSpeed() << " км/ч)" << endl;
            }
        }
        cout << endl;
    }

    return 0;
}