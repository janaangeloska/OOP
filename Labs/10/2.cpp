/*Да се имплементира класа Car за која се чуваат информации за:
    производител (низа од максимум 50 карактери)
    модел (низа од максимум 50 карактери)
    година на производство (цел број)
    сериски број (низа од максимум 7 карактери)
    цена (цел број)
За оваа класа да се имплементираат следните методи:
    функција displayInfo() за печатење на информации во формат: 
    Manufacturer : [производител]
    Model : [модел]
    Year : [година на производство]
    Serial number : [сериски број]
    Price : [цена со ДДВ]
    функција totalPrice() што ја враќа цената со 18% ДДВ.
Потоа да се имплементира класа ElectricCar за која покрај основните информации за автомобилот се чува и:
    батерија (цел број, големина на батерија во киловат часови)
За оваа класа да се препокријат следните методи:
    функција displayInfo() за печатење на информации во формат:
    Model : [модел]
    Battery : [батерија]
    Serial number : [сериски број]
    Price : [цена]
    функција totalPrice() која што основната цена ја зголемува за Х(статичка променлива со вредност 5)% за секој еден киловат час. Доколку при пресметување на цената првата буква од серискиот број не е A, B, C да се фрли исклучок InvalidSerialNumberException кој на екран ќе печати "Invalid Serial Number Exception".*/

#include <iostream>
#include <cstring>
using namespace std;
class  InvalidSerialNumberException{
    char text[50];
public:
    InvalidSerialNumberException(char *text=""){
        strcpy(this->text,text);
    }
    void print(){
        cout<<text<<endl;
    }
};
class Car{
protected:
    char proizvoditel[50];
    char model[50];
    int godina;
    char seriskiBroj[8];
    int cena;
public:
    Car(char *proizvoditel="", char *model="", int godina=0, char *seriskiBroj="", int cena=0){
        strcpy(this->proizvoditel,proizvoditel);
        strcpy(this->model,model);
        this->godina=godina;
        strcpy(this->seriskiBroj,seriskiBroj);
        this->cena=cena;
    }
    virtual void displayInfo(){
        cout<<"Manufacturer : "<<proizvoditel<<endl;
        cout<<"Model : "<<model<<endl;
        cout<<"Year : "<<godina<<endl;
        cout<<"Serial number : "<<seriskiBroj<<endl;
        cout<<"Price : "<<totalPrice()<<endl;
    }
    virtual float totalPrice(){
       float vkcena=cena+(cena*0.18);
        return vkcena;
    }
};
class ElectricCar:public Car{
private:
    int baterija;
    static float x;
public:
    ElectricCar(char *proizvoditel="", char *model="", int godina=0, char *seriskiBroj="", int cena=0,int baterija=0):Car(proizvoditel,model,godina,seriskiBroj,cena) {
    this->baterija=baterija;
    }
    float totalPrice(){
        if(seriskiBroj[0]=='A'||seriskiBroj[0]=='B'||seriskiBroj[0]=='C') {
            float prvaCena=Car::totalPrice();
            prvaCena+=x*cena;
            return prvaCena;
        }
        else{
            throw InvalidSerialNumberException((char *)"Invalid Serial Number Exception\n");
        }
    }
     void displayInfo() {
        totalPrice();
        cout<<"Model : "<<model<<endl;
        cout<<"Battery : "<<baterija<<endl;
        cout<<"Serial number : "<<seriskiBroj<<endl;
        cout<<"Price : "<<totalPrice()<<endl;
    }

    };
    float ElectricCar::x=0.05;
int main()
{
    int choice;
    cin>>choice;
    if(choice==1)
    {
        cout<<"--- Testing Car class ---"<<endl;
        char manufacturer[50], model[50], serialNumber[7];
        int price, year;
        cin>>manufacturer>>model>>year>>serialNumber>>price;
        Car car(manufacturer, model, year, serialNumber, price);
        car.displayInfo();
    }
    else if(choice==2)
    {
        cout<<"--- Testing ElectricCar class ---"<<endl;
        char manufacturer[50], model[50], serialNumber[7];
        int price, year, battery;
        cin>>manufacturer>>model>>year>>serialNumber>>price>>battery;
        ElectricCar car(manufacturer, model, year, serialNumber, price, battery);
        car.displayInfo();
    }
    else if(choice==3)
    {
        cout<<"--- Testing Exceptions ---"<<endl;
        char manufacturer[50], model[50], serialNumber[7];
        int price, year, battery;
        cin>>manufacturer>>model>>year>>serialNumber>>price>>battery;
        ElectricCar car(manufacturer, model, year, serialNumber, price, battery);
        try {
            car.displayInfo();
        }
        catch(InvalidSerialNumberException ex){
            ex.print();
        }
        }
    return 0;
}
