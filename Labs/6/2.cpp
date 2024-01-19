/*Да се дефинира класа Flight во која што ќе се чуваат податоци за лет:
    име на лет (динамички алоцирана низа од знаци)
    полетување од (динамички алоцирана низа од знаци)
    пристигнување во (динамички алоцирана низа од знаци)
    цена на лет (цел број)
За класата да се дефинира copy конструктор, default конструктор, конструктор со аргументи и да се преоптоварат следните оператори:
    оператор << за печатење во формат ([flight_name] [from] [to] [price])
    оператор = за доделување на вредности
    оператор == за споредување на 2 летови според името
Потоа да се креира класа Airport во која што се чуваат следните податоци:
    име на аеродром (низа од максимум 50 карактери)
    број на летови на аеродромот(цел број)
    низа од летови на аеродромот(динамичка низа од објекти од Flight класата)
Да се креира конструктор со аргументи за класата, конструктор без аргументи и да се преоптоварат следните оператори:
    оператор += за додавање на нов лет 
    оператор -= за бришење на лет (според името се брише)
    оператор << за печатење во формат: [airport_name] и летовите.
Да се креира метод void printBelowPrice(int) ги печати летовите кои се под внесената цена.
ДА НЕ СЕ МЕНУВА MAIN ФУНКЦИЈАТА.*/

#include <iostream>
#include <cstring>
using namespace std;
class Flight{
    char *imeNaLet;
    char *poletuvanjeOd;
    char *pristignuvanjeVo;
    int cena;
public:
    Flight(char *imeNaLet="", char *poletuvanjeOd="", char *pristignuvanjeVo="", int cena=0) {
        this->imeNaLet=new char[strlen(imeNaLet)+1];
        strcpy(this->imeNaLet,imeNaLet);
        this->poletuvanjeOd=new char[strlen(poletuvanjeOd)+1];
        strcpy(this->poletuvanjeOd,poletuvanjeOd);
        this->pristignuvanjeVo=new char[strlen(pristignuvanjeVo)+1];
        strcpy(this->pristignuvanjeVo,pristignuvanjeVo);
        this->cena=cena;
    }
    Flight(const Flight &f) {
        this->imeNaLet=new char[strlen(f.imeNaLet)+1];
        strcpy(this->imeNaLet,f.imeNaLet);
        this->poletuvanjeOd=new char[strlen(f.poletuvanjeOd)+1];
        strcpy(this->poletuvanjeOd,f.poletuvanjeOd);
        this->pristignuvanjeVo=new char[strlen(f.pristignuvanjeVo)+1];
        strcpy(this->pristignuvanjeVo,f.pristignuvanjeVo);
        this->cena=f.cena;
    }
    Flight &operator= (const Flight &f) {
        if (this != &f) {
            delete [] imeNaLet;
            delete [] poletuvanjeOd;
            delete [] pristignuvanjeVo;
            this->imeNaLet = new char[strlen(f.imeNaLet) + 1];
            strcpy(this->imeNaLet, f.imeNaLet);
            this->poletuvanjeOd = new char[strlen(f.poletuvanjeOd) + 1];
            strcpy(this->poletuvanjeOd, f.poletuvanjeOd);
            this->pristignuvanjeVo = new char[strlen(f.pristignuvanjeVo) + 1];
            strcpy(this->pristignuvanjeVo, f.pristignuvanjeVo);
            this->cena = f.cena;
        }
        return *this;
    }
    bool operator==(const Flight &rhs) const {
        return !(strcmp(imeNaLet,rhs.imeNaLet));
    }

    friend ostream &operator<<(ostream &out, const Flight &f) {
        out << f.imeNaLet <<" "<< f.poletuvanjeOd<<" " << f.pristignuvanjeVo<<" "<<f.cena<<endl;
        return out;
    }
    ~Flight(){
        delete [] imeNaLet;
        delete [] poletuvanjeOd;
        delete [] pristignuvanjeVo;
    }
    friend class Airport;
};
class Airport{
    char aerodrom[50];
    int n;
    Flight *flight;
public:
    Airport(char *aerodrom=""){
        strcpy(this->aerodrom,aerodrom);
        n=0;
        this->flight=new Flight[0];
    }
    Airport(const Airport &a){
        strcpy(aerodrom,a.aerodrom);
        n=a.n;
        flight=new Flight[n];
        for(int i=0;i<n;i++){
            flight[i]=a.flight[i];
        }
    }
    Airport &operator=(const Airport &a) {
        if (this != &a) {
            delete[] flight;
            strcpy(aerodrom, a.aerodrom);
            n = a.n;
            flight = new Flight[n];
            for (int i = 0; i < n; i++) {
                flight[i] = a.flight[i];
            }
        }
        return *this;
    }
    Airport &operator+=(const Flight &aa){
        Flight *temp=new Flight[n+1];
        for(int i=0;i<n;i++){
            temp[i]=flight[i];
        }
        temp[n++]=aa;
        delete [] flight;
        flight=temp;
        return *this;
    }
    Airport &operator -=(Flight &f){
        int j=0;
        for(int i=0;i<n;i++){
            if((strcmp(f.imeNaLet,flight[i].imeNaLet))!=0){
                flight[j++]=flight[i];
            }
        }
        this->n=j;
        return *this;
    }
    friend ostream &operator<<(ostream &out, const Airport &a) {
        out<<a.aerodrom<<endl;
        for(int i=0;i<a.n;i++){
            out<<a.flight[i];
        }
        return out;
    }
    void printBelowPrice(int price) {
        for (int i = 0; i < n; i++) {
            if (flight[i].cena<=price){
                cout<<flight[i];
            }
        }
    }
};
int main() {
    int testCase;

    cin>>testCase;

    if(testCase==1){
        cout<<"TESTING FLIGHT CLASS CONSTRUCTORS"<<endl;

        Flight flight = Flight("OS776", "SKOPJE(SKP)" , "VIENNA(VIE)", 100);

        cout<<flight;

        cout<<"TESTING FLIGHT CLASS OPERATORS"<<endl;

        Flight flight1 = Flight("OS776", "SKOPJE(SKP)" , "VIENNA(VIE)", 100);
        if(flight==flight1){
            cout<<flight;
        }
        else{
            cout<<"Ne se isti letovi";
        }
    }
    else if(testCase==2){
        cout<<"TESTING FLIGHT CLASS CONSTRUCTORS"<<endl;

        Flight flight = Flight("LTNSKP112", "LONDON(LTN)" ,"SKOPJE(SKP)", 200);

        cout<<flight;

        cout<<"TESTING FLIGHT CLASS OPERATORS"<<endl;

        Flight flight1 = Flight("IATA110", "SKOPJE(SKP)", "ISTANBUL(IST)" , 80);
        if(flight==flight1){
            cout<<flight;
        }
        else{
            cout<<"Ne se isti letovi";
        }
    }
    else if(testCase==3){
        Airport airport("SkopjeInternationalAirport");
        int n;
        cin>>n;

        for (int i=0;i<n;i++)
        {
            char name[100];
            char from[100];
            char to[100];
            int price;

            cin >> name;
            cin >> from;
            cin >> to;
            cin >> price;

            Flight f=Flight(name, from, to, price);

            //dodavanje na let
            airport+=f;

        }

        cout<<"TESTING AIRPORT OPERATOR +="<<endl;

        cout<<airport;
    }
    else if(testCase==4){
        Airport airport("JohnF.Kennedy");
        int n;
        cin>>n;

        for (int i=0;i<n;i++)
        {
            char name[100];
            char from[100];
            char to[100];
            int price;

            cin >> name;
            cin >> from;
            cin >> to;
            cin >> price;

            Flight f=Flight(name, from, to, price);

            //dodavanje na let
            airport+=f;

        }

        cout<<"TESTING AIRPORT OPERATOR -="<<endl;

        //se cita greshen let, za koj shto letot so isto ime treba da se izbrishe
        char name[100];
        char from[100];
        char to[100];
        int price;

        cin >> name;
        cin >> from;
        cin >> to;
        cin >> price;

        Flight greshka=Flight(name, from, to, price);

        //brishenje na let
        airport-=greshka;

        cout<<airport;
    }
    else if(testCase==5){
        Airport airport("Beauvais–Tillé-Airport");
        int n;
        cin>>n;

        for (int i=0;i<n;i++)
        {
            char name[100];
            char from[100];
            char to[100];
            int price;

            cin >> name;
            cin >> from;
            cin >> to;
            cin >> price;

            Flight f=Flight(name, from, to, price);

            //dodavanje na let
            airport+=f;

        }

        cout<<"TESTING AIRPORT OPERATOR -= AND PRINTBELOWPRICE METHOD"<<endl;

        //se cita grehsen let, za koj shto let so isto ime treba da se izbrishe
        char name[100];
        char from[100];
        char to[100];
        int price;

        cin >> name;
        cin >> from;
        cin >> to;
        cin >> price;

        Flight greshka=Flight(name, from, to, price);

        //brishenje na let
        airport-=greshka;

        airport.printBelowPrice(80);
    }


    return 0;
}
