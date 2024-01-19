/*За да се овозможи прецизна контрола и евиденција во еден аеродромски сервис, потребно е да се имплементира модул со следниве класи и функционалности:
Да се имплементира класа Airplane во која ќе се чуваат информации за:
    Регистарска ознака (низа од најмногу 12 знаци)
    Име на авиокомпанија која го поседува авионот (динамички алоцирана низа од знаци)
    Матичен аеродром на авиокомпанијата (низа од најмногу 20 знаци)
    Состојба (авионот може да се најде во состојба НЕИСПРАВЕН, СЕ_ПОПРАВА или ИСПРАВЕН)
    Вкупен број на часови налет (цел број)
За класата да се имплементираат потребните конструктори, оператор = и методи за да функционира решението. (10 поени). Дополнително за класата да се имплементира метод void print() за печатење на информациите за авионот (според тест примерите). (5 поени)
Да се имплементира класа AirportService во која ќе се чуваат информации за:
    Име на аеродромот каде се наоѓа сервисот (низа од најмногу 20 знаци)
    Листа на авиони кои моментално се наоѓаат во сервисот (динимички алоцирана низа од објекти од класата Airplane, иницијално без елементи)
    Број на авиони во сервисот (број на елементи во низата со авиони - цел број, иницијално е 0)
За класата да се имплементираат потребните конструктори и методи со цел да функционира решението. (5 поени) Дополнително во класата да се имплементираат:
    метод void addAirplane (Airplane plane) - за додавање нoв авион во сервисот (5 поени). Еден авион може да се додаде во сервисот само ако се наоѓа во состојба НЕИСПРАВЕН. Дополнително, ако веќе во сервисот има авион од иста авиокомпанија како авионот кој сакаме да го додадеме, потребно е во сервисот да остане авионот со поголем број на часови налет. Кога авион се додава во сервисот неговата состојба преминува во состојба СЕ_ПОПРАВА (10 поени).
    метод Airplane serviceOldestAirplane() - за сервисирање на најстариот авион. За најстар авион се смета оној авион од листата кој има најмногу часови налет. Сервисирањето на еден авион претствува:
        Потребно е авионот да биде избришан од листата со авиони во сервисот
        Авионот треба да премине од состојба СЕ_ПОПРАВА во состојба ИСПРАВЕН
        Доколку има повеќе авиони со ист број на часови налет при одредувањето на најстар авион, тогаш потребно е да се избрише авионот чиј што матичен аеродром на авиокомпанијата на авионот е аеродромот каде што се наоѓа сервисот. Во ваква ситуација, секогаш само еден од авионите ќе има ист матичен аеродром со аеродромот на сервисот.  (15 поени)
    метод void print() - за печатење на информации за сите авиони кои моментално се наоѓаат на поправка во сервисот (формат во тест примери) (10 поени)*/

#include <iostream>
#include <cstring>
using namespace std;

class Airplane {
private:
    char registarskaOnaka[12];
    char *imeNaAvioKompanija;
    char matichenAerodrom[20];
    int sostojba;
    int vkBrojCasoviNalet;
    void copy(const Airplane &other){
        strcpy(this->registarskaOnaka,other.registarskaOnaka);
        this->imeNaAvioKompanija=new char [strlen(other.imeNaAvioKompanija)+1];
        strcpy(this->imeNaAvioKompanija,other.imeNaAvioKompanija);
        strcpy(this->matichenAerodrom,other.matichenAerodrom);
        this->vkBrojCasoviNalet=other.vkBrojCasoviNalet;
        this->sostojba=other.sostojba;
    }
public:
    Airplane(){
        imeNaAvioKompanija= nullptr;
        vkBrojCasoviNalet=0;
        sostojba=0;
    }

    Airplane(char *registarskaOnaka, char *imeNaAvioKompanija, char *matichenAerodrom, int vkBrojCasoviNalet){
        strcpy(this->registarskaOnaka,registarskaOnaka);
        this->imeNaAvioKompanija=new char [strlen(imeNaAvioKompanija)+1];
        strcpy(this->imeNaAvioKompanija,imeNaAvioKompanija);
        strcpy(this->matichenAerodrom,matichenAerodrom);
        this->vkBrojCasoviNalet=vkBrojCasoviNalet;
        this->sostojba=0;
    }
    Airplane(char *registarskaOnaka, char *imeNaAvioKompanija, char *matichenAerodrom, int vkBrojCasoviNalet, int sostojba){
        strcpy(this->registarskaOnaka,registarskaOnaka);
        this->imeNaAvioKompanija=new char [strlen(imeNaAvioKompanija)+1];
        strcpy(this->imeNaAvioKompanija,imeNaAvioKompanija);
        strcpy(this->matichenAerodrom,matichenAerodrom);
        this->vkBrojCasoviNalet=vkBrojCasoviNalet;
        this->sostojba=sostojba;
    }
    ~Airplane(){
        delete [] imeNaAvioKompanija;
    }
    Airplane(const Airplane &other){
        copy(other);
    }
    Airplane & operator = (const Airplane &other){
        if(this!=&other){
            delete [] imeNaAvioKompanija;
            copy(other);
        }
        return *this;
    }
    void print() {
        cout<< "ID: " << registarskaOnaka << " - ";
        if(sostojba==0){
            cout << "NOT_WORKING";
        }else if(sostojba==1) {
            cout << "REPAIRING";
        }else if(sostojba==2){
            cout << "WORKING";
        }
        cout << " " << imeNaAvioKompanija << ", " << vkBrojCasoviNalet << ", " << matichenAerodrom << endl;
    }

    int getSostojba() const {
        return sostojba;
    }
    bool sameAviokompanija(Airplane airplane){
        if(strcmp(airplane.imeNaAvioKompanija,imeNaAvioKompanija)==0){
            return true;
        }else return false;
    }

    int getVkBrojCasoviNalet() const {
        return vkBrojCasoviNalet;
    }

    void setSostojba(int sostojba) {
        this->sostojba=sostojba;
    }

    const char *getMatichenAerodrom() const {
        return matichenAerodrom;
    }
};

class AirportService{
private:
    char imeNaServis[20];
    Airplane *airplanes;
    int brNaAvioni;
    void copy(const AirportService &other){
        strcpy(this->imeNaServis,other.imeNaServis);
        brNaAvioni=other.brNaAvioni;
        this->airplanes=new Airplane [other.brNaAvioni];
        for(int i=0;i<other.brNaAvioni;i++){
            this->airplanes[i]=other.airplanes[i];
        }
    }
public:
    AirportService(char *imeNaServis=""){
        strcpy(this->imeNaServis,imeNaServis);
        brNaAvioni=0;
        this->airplanes=new Airplane [brNaAvioni];
    }
    ~AirportService(){
        delete [] airplanes;
    }
    AirportService(const AirportService &other){
        copy(other);
    }
    AirportService & operator = (const AirportService &other){
        if(this!=&other){
            delete [] airplanes;
            copy(other);
        }
        return *this;
    }

    void addAirplane(Airplane airplane) {
        if(airplane.getSostojba()!=0){
            return;
        }
        for(int i=0;i<brNaAvioni;i++){
            if(airplanes[i].sameAviokompanija(airplane)){
                if(airplane.getVkBrojCasoviNalet()>airplanes[i].getVkBrojCasoviNalet()){
                    airplane.setSostojba(1);
                    airplanes[i]=airplane;
                    return;
                }
            }
        }
        airplane.setSostojba(1);
        Airplane *temp = new Airplane [brNaAvioni+1];
        for(int i=0;i<brNaAvioni;i++){
            temp[i]=airplanes[i];
        }
        temp[brNaAvioni++]=airplane;
        delete [] airplanes;
        airplanes=temp;
    }

    void print() {
        cout << imeNaServis << endl;
        for (int i = 0; i < brNaAvioni; i++){
            airplanes[i].print();
        }
    }
Airplane serviceOldestAirplane() {
    int najstar = airplanes[0].getVkBrojCasoviNalet();
    int najI = 0;
    int i = 1;
    while (i < brNaAvioni) {
        if (airplanes[i].getVkBrojCasoviNalet() > najstar) {
            najstar = airplanes[i].getVkBrojCasoviNalet();
            najI = i;
        } else if (airplanes[i].getVkBrojCasoviNalet() == najstar) {
            if (!strcmp(airplanes[i].getMatichenAerodrom(), imeNaServis)) {
                najstar = airplanes[i].getVkBrojCasoviNalet();
                najI = i;
            }
        }
        i++;
    }
    
    int j = 0;
    airplanes[najI].setSostojba(2);
    Airplane removedPlane = airplanes[najI];
    Airplane *temp = new Airplane [brNaAvioni-1];
    i = 0;
    while (i < brNaAvioni) {
        if (i != najI) {
            temp[j++] = airplanes[i];
        }
        i++;
    }
    delete [] airplanes;
    airplanes = temp;
    brNaAvioni = j;
    return removedPlane;
}
};

int main() {
    int testCase;
    cin >> testCase;
    char ID[12];
    char company_name[20];
    char company_airport[20];
    int flight_hours;
    int state;
    if (testCase == 1) {
        cout << "TESTING CONSTRUCTOR FOR AIRPLANE" << endl;
        Airplane a;
        cout << "TEST FOR DEFAULT CONSTRUCTOR PASSED" << endl;
        Airplane a1("ZHN-96-TY", "FINKI-Airline", "TMF", 13);
        cout << "TEST FOR CONSTRUCTOR WITH 3 ARGUMENTS PASSED" << endl;
        Airplane a2("ZHN-96-TA", "FINKI1-Airline", "TMF", 13, 0);
        cout << "TEST FOR CONSTRUCTOR WITH 4 ARGUMENTS PASSED" << endl;
    } else if (testCase == 2) {
        cout << "TESTING COPY-CONSTRUCTOR AND OPERATOR = (ASSIGNMENT) FOR AIRPLANE" << endl;
        Airplane p("ZHN-96-TA", "FINKI-Airline", "TMF", 13, 0);
        Airplane p1(p);
        cout << "TEST FOR COPY CONSTRUCTOR PASSED" << endl;
        Airplane p2;
        p2 = p;
        cout << "TEST FOR OPERATOR = (ASSIGNMENT) PASSED" << endl;
    } else if (testCase == 3) {
        cout << "TESTING PRINT() FOR AIRPLANE" << endl;
        cin>>ID>>company_name>>company_airport>>flight_hours>>state;
        Airplane p(ID, company_name, company_airport, flight_hours, state);
        p.print();
    } else if (testCase == 4) {
        cout << "TESTING CONSTRUCTOR FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        cout << "TEST PASSED" << endl;
    } else if (testCase == 5) {
        cout << "TESTING ADD() AND PRINT() FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        int n;
        cin>>n;
        for(int i=0; i<n; i++){
            cin>>ID>>company_name>>company_airport>>flight_hours>>state;
            Airplane p(ID, company_name, company_airport, flight_hours, state);
            as.addAirplane(p);
        }
        as.print();
    } else if (testCase == 6) {
        cout << "TESTING serviceOldestAirplane() AND PRINT() FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        int n;
        cin>>n;
        for(int i=0; i<n; i++){
            cin>>ID>>company_name>>company_airport>>flight_hours>>state;
            Airplane p(ID, company_name, company_airport, flight_hours, state);
            as.addAirplane(p);
        }
        Airplane p = as.serviceOldestAirplane();
        cout<<"Removed plane:"<<endl;
        p.print();
        cout<<"-----------------"<<endl;
        as.print();
    }  else if (testCase == 7) {
        cout << "TESTING COPY CONSTRUCTOR AND OPERATOR = FOR AIRPORTSERVICE" << endl;
        AirportService as("FINKI");
        Airplane a1("ZHN-96-TY", "FINKI-Airline", "TMF", 13);
        as.addAirplane(a1);

        AirportService s1 = as; //copy constructor
        AirportService s2;
        s2 = s1; //operator =
        s1.print();
        s2.print();
    }
    return 0;
}
