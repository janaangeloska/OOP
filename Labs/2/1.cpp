/*Да се дефинира класа MobilePhone во која ќе се чуваат податоци за еден мобилен телефон:
    модел (низа од карактери не подолга од 20 карактери)
    број на модел (цел број)
    година на издавање (цел број)
За класата да се дефинира default конструктор, конструктор со аргументи, copy конструктор, деструктор и доколку има потреба get методи. Исто така да се дефинира и фунцкија за печатење на информации за класата која ќе печати во следниот формат „(модел) (број на модел) release year: (година на издавање)“.
Потоа да се дефинира класа Owner во која се чуваат следните информации:
    име (низа од карактери не подолга од 20 карактери)
    презиме (низа од карактери не подолга од 20 карактери)
    мобилен телефон (објект од класа MobilePhone)
Да се креира default конструктор, конструктор со аргументи, деструктор и доколку има потреба get методи. Исто така да се дефинира и функција за печатење на информации за класата која ќе печати во следниот формат: 
„(име) (презиме) has a mobile phone:
(информации за мобилен телефон)“
ДА НЕ СЕ МЕНУВА MAIN ФУНКЦИЈАТА!!!*/

#include <iostream>
#include<cstring>
using namespace std;

//YOUR CODE HERE

class MobilePhone{
    char model[20];
    int broj;
    int godina;
public:
    MobilePhone(char *model="", int broj=0, int godina=0){
        strcpy(this->model,model);
        this->broj=broj;
        this->godina=godina;
    }
    MobilePhone(const MobilePhone &m){
    strcpy(model,m.model);
    broj=m.broj;
    godina=m.godina;
    }
    ~MobilePhone(){}
    char *getModel(){
        return model;
    }
    int getBroj() {
        return broj;
    }
    void setBroj(int broj) {
        MobilePhone::broj = broj;
    }
    int getGodina(){
        return godina;
    }
    void setGodina(int godina) {
        MobilePhone::godina = godina;
    }
};
class Owner{
    char ime[20];
    char prezime[20];
    MobilePhone mobilen;

public:
    Owner(){}
    Owner(char *ime, char *prezime, const MobilePhone mobilen)  {
        strcpy(this->ime,ime);
        strcpy(this->prezime,prezime);
        this->mobilen=mobilen;
    }
    ~Owner(){}
    void print(){
        cout<<ime<<" "<<prezime<<" has a mobile phone: "<<endl;
        cout<<mobilen.getModel()<<" "<<mobilen.getBroj()<<" release year: "<<mobilen.getGodina()
        ;
    }
};

//DO NOT CHANGE THE MAIN FUNCTION
int main() {
    char model[20];
    int modelNumber;
    int year;
    char name[20];
    char surname[20];

    int testCase;

    cin>>testCase;

    cin>>model;
    cin>>modelNumber;
    cin>>year;
    cin>>name;
    cin>>surname;

    if(testCase==1){
        MobilePhone mobilePhone(model,modelNumber,year);

        Owner owner(name,surname,mobilePhone);
        owner.print();
    }
    if(testCase==2){
        MobilePhone mobilePhone(MobilePhone(model,modelNumber,year));

        Owner owner(name,surname,mobilePhone);
        owner.print();
    }

}
