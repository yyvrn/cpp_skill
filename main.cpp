#include <iostream>
#include <string>

using namespace std;

// ==================== Базовый класс Car ====================
class Car {
private:
    string brand;
    int cylinders;
    int power;
    static int objectCount;  // Статический счетчик объектов

protected:
    // Защищенные методы для управления счетчиком
    static void incrementCount() { objectCount++; }
    static void decrementCount() { objectCount--; }

public:
    // Конструкторы
    Car();
    Car(const string& b, int c, int p);
    Car(const Car& other);
   
    // Деструктор
    virtual ~Car();
   
    // Геттеры
    string getBrand() const { return brand; }
    int getCylinders() const { return cylinders; }
    int getPower() const { return power; }
   
    // Сеттеры
    void setBrand(const string& b) { brand = b; }
    void setCylinders(int c) { cylinders = c; }
    void setPower(int p) { power = p; }
   
    // Перегрузка операторов
    Car& operator=(const Car& other);
   
    // Дружественная функция для подсчета объектов
    friend int count();
   
    // Дружественные операторы ввода/вывода
    friend ostream& operator<<(ostream& os, const Car& car);
    friend istream& operator>>(istream& is, Car& car);
};

// Инициализация статического члена
int Car::objectCount = 0;

// Конструктор без параметров
Car::Car() : brand("Unknown"), cylinders(4), power(100) {
    incrementCount();
    cout << "Car default constructor called. Total objects: " << objectCount << endl;
}

// Конструктор с параметрами
Car::Car(const string& b, int c, int p)
    : brand(b), cylinders(c), power(p) {
    incrementCount();
    cout << "Car parameterized constructor called. Total objects: " << objectCount << endl;
}

// Конструктор копирования
Car::Car(const Car& other)
    : brand(other.brand), cylinders(other.cylinders), power(other.power) {
    incrementCount();
    cout << "Car copy constructor called. Total objects: " << objectCount << endl;
}

// Деструктор
Car::~Car() {
    decrementCount();
    cout << "Car destructor called. Total objects: " << objectCount << endl;
}

// Перегрузка оператора присваивания
Car& Car::operator=(const Car& other) {
    cout << "Car assignment operator called" << endl;
    if (this != &other) {
        brand = other.brand;
        cylinders = other.cylinders;
        power = other.power;
    }
    return *this;
}

// Перегрузка оператора вывода
ostream& operator<<(ostream& os, const Car& car) {
    os << "Car Information:" << endl;
    os << "  Brand: " << car.brand << endl;
    os << "  Cylinders: " << car.cylinders << endl;
    os << "  Power: " << car.power << " HP" << endl;
    return os;
}

// Перегрузка оператора ввода
istream& operator>>(istream& is, Car& car) {
    cout << "Enter car information:" << endl;
    cout << "  Brand: ";
    is >> car.brand;
    cout << "  Number of cylinders: ";
    is >> car.cylinders;
    cout << "  Power (HP): ";
    is >> car.power;
    return is;
}

// ==================== Производный класс Lorry ====================
class Lorry : public Car {
private:
    int loadCapacity;  // грузоподъемность в кг

public:
    // Конструкторы
    Lorry();
    Lorry(const string& b, int c, int p, int capacity);
    Lorry(const Lorry& other);
   
    // Деструктор
    ~Lorry();
   
    // Геттеры и сеттеры
    int getLoadCapacity() const { return loadCapacity; }
    void setLoadCapacity(int capacity) { loadCapacity = capacity; }
   
    // Перегрузка операторов
    Lorry& operator=(const Lorry& other);
   
    // Дружественные операторы ввода/вывода
    friend ostream& operator<<(ostream& os, const Lorry& lorry);
    friend istream& operator>>(istream& is, Lorry& lorry);
};

// Конструктор без параметров
Lorry::Lorry() : Car(), loadCapacity(5000) {
    cout << "Lorry default constructor called" << endl;
}

// Конструктор с параметрами
Lorry::Lorry(const string& b, int c, int p, int capacity)
    : Car(b, c, p), loadCapacity(capacity) {
    cout << "Lorry parameterized constructor called" << endl;
}

// Конструктор копирования
Lorry::Lorry(const Lorry& other)
    : Car(other), loadCapacity(other.loadCapacity) {
    cout << "Lorry copy constructor called" << endl;
}

// Деструктор
Lorry::~Lorry() {
    cout << "Lorry destructor called" << endl;
}

// Перегрузка оператора присваивания
Lorry& Lorry::operator=(const Lorry& other) {
    cout << "Lorry assignment operator called" << endl;
    if (this != &other) {
        Car::operator=(other);  // Вызов оператора присваивания базового класса
        loadCapacity = other.loadCapacity;
    }
    return *this;
}

// Перегрузка оператора вывода
ostream& operator<<(ostream& os, const Lorry& lorry) {
    // Используем оператор вывода базового класса
    os << static_cast<const Car&>(lorry);
    os << "  Load Capacity: " << lorry.loadCapacity << " kg" << endl;
    return os;
}

// Перегрузка оператора ввода
istream& operator>>(istream& is, Lorry& lorry) {
    // Используем оператор ввода базового класса
    is >> static_cast<Car&>(lorry);
    cout << "  Load capacity (kg): ";
    is >> lorry.loadCapacity;
    return is;
}

// ==================== Дружественная функция count ====================
int count() {
    return Car::objectCount;
}

// ==================== Демонстрационные функции ====================
void demonstrateCarOperations() {
    cout << "\n=== Demonstrating Car Operations ===\n" << endl;
   
    // Создание объектов разными конструкторами
    Car car1;  // конструктор без параметров
    Car car2("Toyota", 6, 250);  // конструктор с параметрами
    Car car3(car2);  // конструктор копирования
   
    cout << "\nCar1 (default):" << endl;
    cout << car1;
   
    cout << "\nCar2 (parameterized):" << endl;
    cout << car2;
   
    cout << "\nCar3 (copy of Car2):" << endl;
    cout << car3;
   
    // Демонстрация сеттеров
    cout << "\nModifying Car1 using setters:" << endl;
    car1.setBrand("Honda");
    car1.setCylinders(4);
    car1.setPower(150);
    cout << car1;
   
    // Демонстрация геттеров
    cout << "Car2 brand (using getter): " << car2.getBrand() << endl;
   
    // Демонстрация оператора присваивания
    cout << "\nAssigning Car2 to Car1:" << endl;
    car1 = car2;
    cout << "Car1 after assignment:" << endl;
    cout << car1;
}

void demonstrateLorryOperations() {
    cout << "\n=== Demonstrating Lorry Operations ===\n" << endl;
   
    // Создание объектов Lorry
    Lorry lorry1;  // конструктор без параметров
    Lorry lorry2("Volvo", 8, 400, 15000);  // конструктор с параметрами
    Lorry lorry3(lorry2);  // конструктор копирования
   
    cout << "\nLorry1 (default):" << endl;
    cout << lorry1;
   
    cout << "\nLorry2 (parameterized):" << endl;
    cout << lorry2;
   
    cout << "\nLorry3 (copy of Lorry2):" << endl;
    cout << lorry3;
   
    // Демонстрация сеттеров
    cout << "\nModifying Lorry1 using setters:" << endl;
    lorry1.setBrand("MAN");
    lorry1.setCylinders(6);
    lorry1.setPower(320);
    lorry1.setLoadCapacity(12000);
    cout << lorry1;
   
    // Демонстрация оператора присваивания
    cout << "\nAssigning Lorry2 to Lorry1:" << endl;
    lorry1 = lorry2;
    cout << "Lorry1 after assignment:" << endl;
    cout << lorry1;
}

void demonstrateInputOutput() {
    cout << "\n=== Demonstrating Input/Output Operators ===\n" << endl;
   
    Car inputCar;
    cin >> inputCar;
    cout << "\nYou entered:" << endl;
    cout << inputCar;
   
    Lorry inputLorry;
    cin >> inputLorry;
    cout << "\nYou entered:" << endl;
    cout << inputLorry;
}

void demonstratePolymorphism() {
    cout << "\n=== Demonstrating Polymorphism ===\n" << endl;
   
    // Создание объектов через указатели базового класса
    Car* carPtr = new Car("BMW", 6, 300);
    Car* lorryPtr = new Lorry("Scania", 8, 450, 20000);
   
    cout << "\nThrough Car pointer to Car object:" << endl;
    cout << *carPtr;
   
    cout << "\nThrough Car pointer to Lorry object:" << endl;
    cout << *lorryPtr;  // Вызовется operator<< для Lorry благодаря виртуальному деструктору
   
    delete carPtr;
    delete lorryPtr;
}

// ==================== Главная функция ====================
int main() {
    cout << "=== Car and Lorry Class Demonstration ===" << endl;
    cout << "Initial object count: " << count() << endl;
   
    // Демонстрация операций с Car
    demonstrateCarOperations();
    cout << "\nObject count after Car operations: " << count() << endl;
   
    // Демонстрация операций с Lorry
    demonstrateLorryOperations();
    cout << "\nObject count after Lorry operations: " << count() << endl;
   
    // Демонстрация полиморфизма
    demonstratePolymorphism();
    cout << "\nObject count after polymorphism demo: " << count() << endl;
   
    // Демонстрация ввода/вывода (закомментировано для автоматического выполнения)
    // demonstrateInputOutput();
   
    cout << "\n=== End of Program ===" << endl;
    cout << "Final object count: " << count() << endl;
   
    return 0;
}