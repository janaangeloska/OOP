/*Треба да се напише класа Vehicle која што ги има овие две чисти виртуелни функции:
    calculateValue() - ја пресметува и враќа вредноста на возилото. Овој метод се имплементира различно во изведените класи.
    printInfo() - ги печати информациите за возилото. Овој метод се имплементира различно во изведените класи.
Исто така, треба класата да ги има следните информации:
    brand (динамички алоцирана низа од карактери) - ја претставува марката или производителот на возилото
    year (int)- ја претставува годината на производство на возилото
Понатаму, треба да креирате 2 подкласи на Vehicle наречени:
Car
Motorcycle
Класата Car треба да ги има овие информации:
    mileage (float) - ја претставува километражата на автомобилот.
Методи:
    Override calculateValue(): ја пресметува и ја враќа вредноста на автомобилот врз основа на километражата. Вредноста се пресметува со формулата: 10000 - (0,1 * километража).
    Override printInfo(): ги печати брендот, годината и километражата на автомобилот.
Класата Motorcycle треба да ги има овие информации:
    bool offroad (дали е offroad или не)
Методи:
    Override calculateValue(): ја пресметува и ја враќа вредноста на мотоциклот врз основа на тоа дали е надвор од патот или не. Вредноста е 8000 ако е надвор од патот, а 10000 во спротивно.
    Override printInfo(): ја печати марката, годината и статусот надвор од патот на мотоциклот.
Треба исто така да напишете глобална функција:
float getMaxVehicleValue(Vehicle* pVehicles[], int n)  , која што ја враќа максималната вредност меѓу сите возила во низата, пресметана со помош на методот calcuateValue().
Не ја менувајте main функцијата!*/

#include <iostream>
#include <cstring>
using namespace std;
class Vehicle{
protected:
    char *brand;
    int year;
public:
    Vehicle(char *brand= nullptr, int year=1800) {
        this->brand=new char[strlen(brand)+1];
        strcpy(this->brand,brand);
        this->year=year;
    }
    virtual ~Vehicle(){
        delete [] brand;
    }
    virtual float calculateValue()=0;
    virtual void printInfo()=0;
};

class Car : public Vehicle{
    float mileage;
public:
    Car(char *brand= nullptr, int year=1800,float mileage=0):Vehicle(brand,year){
        this->mileage=mileage;
    }
    float calculateValue(){
        return 10000 - (0.1 * mileage);
    }
    void printInfo(){
        cout<<"Brand: "<<brand<<endl;
        cout<<"Year: "<<year<<endl;
        cout<<"Mileage: "<<mileage<<endl;
    }
};

class Motorcycle : public Vehicle{
    bool offroad;
public:
    Motorcycle(char *brand= nullptr, int year=1800,bool offroad=false):Vehicle(brand,year) {
    this->offroad=offroad;
    }
    float calculateValue() {
    if(offroad){
        return 8000;
    }
    else{
        return 10000;
    }
    }
    void printInfo() {
        char dali[20];
        if(offroad) {
            strcpy(dali, "Yes");
        }
            if(!offroad){
                strcpy(dali,"No");
            }
        cout<<"Brand: "<<brand<<endl;
        cout<<"Year: "<<year<<endl;
        cout<<"Off-road: "<<dali<<endl;
    }
    };
float getMaxVehicleValue(Vehicle* pVehicles[], int n){
    int indeks;
    float maxVehicle=pVehicles[0]->calculateValue();
    for(int i=0;i<n;i++){
        if(pVehicles[i]->calculateValue()>maxVehicle){
            maxVehicle=pVehicles[i]->calculateValue();
        }
    }
    return maxVehicle;
}
int main() {
    int n;
    //cout << "Enter the number of vehicles: ";
    cin >> n;

    Vehicle* pVehicles[n];

    for (int i = 0; i < n; ++i) {
        char type[30];
        char brand[30];
        int year;
        float mileage;
        bool offRoad;

        //cout << "Enter vehicle type (car/motorcycle): ";
        cin >> type;

        //cout << "Enter brand: ";
        cin >> brand;

        //cout << "Enter manufacturing year: ";
        cin >> year;

        if (strcmp(type, "car") == 0) {
            //cout << "Enter mileage: ";
            cin >> mileage;
            pVehicles[i] = new Car(brand, year, mileage);
        } else if (strcmp(type, "motorcycle") == 0) {
            //cout << "Is it off-road (0/1): ";
            cin >> offRoad;
            pVehicles[i] = new Motorcycle(brand, year, offRoad);
        }
    }

    Vehicle* maxVehicle = nullptr;
    float maxValue = getMaxVehicleValue(pVehicles, n);

    for (int i = 0; i < n; ++i) {
        if (pVehicles[i]->calculateValue() == maxValue) {
            maxVehicle = pVehicles[i];
            break;
       

        }
    }

    if (maxVehicle != nullptr) {
        cout << "Vehicle with maximum value:\n";
        maxVehicle->printInfo();
    }

    // Deallocate memory
    for (int i = 0; i < n; ++i) {
        delete pVehicles[i];
    }

    return 0;
}
