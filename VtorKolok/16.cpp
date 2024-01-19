/*Туристичка агенција нуди различни понуди за транспорт на патници. За секоја понуда се чуваат податоци за дестинацијата (низа од знаци), 
основна цена (цел број) и податок за растојанието до дестинацијата изразено во km (цел број).
Од класата Transport да се изведат класите AvtomobilTransport и KombeTransport за моделирање на понудите за транспорт 
кои нудат транспорт со автомобил или комбе, соодветно. За секоја понуда за транспорт со автомобил се чува податок за тоа дали во понудата 
има платен шофер (булова променлива), а за транспорт со комбе бројот на луѓе кои може да се превезат во комбето (цел број). (5 поени)
За секој објект од двете изведени класи треба да бидат на располагање следниве методи:
    конструктор со аргументи што одговараат на податочните членови и set и get методи за податочните членови (5 поени)
    метод cenaTransport, за пресметување на цената на понудата на следниот начин:
        За транспорт со автомобил - основната цена се зголемува за 20% ако има платен шофер
        За транспорт со комбе - основната цена ќе се намали зависно од бројот на патници во комбето. За секој патник во комбето цената се намалува за 200 (10 поени)
    преоптоварен оператор < за споредба на две понуди за транспорт на патник според растојанието до дестинацијата. (5 поени)
Да се имплементира функција pecatiPoloshiPonudi што на влез прима низа од понуди за транспорт на патник, бројот на елементите од низата и една понуда T. 
Функцијата ја печати дестинацијата, растојанието до дестинацијата и цената за понудите од низата кои се поскапи од понудата T сортирани во растечки 
редослед по растојанието до дестинацијата (погледни го повикот на функцијата) (10 поени)
Комплетна функционалност на кодот (5 поени)*/

#include <iostream>
#include <cstring>
using namespace std;
class Transport{
protected:
    char destinacija[100];
    int osnovnaCena;
    int rastojanie;
public:
    Transport(char *destinacija="", int osnovnaCena=0, int rastojanie=0) {
        strcpy(this->destinacija,destinacija);
        this->osnovnaCena=osnovnaCena;
        this->rastojanie=rastojanie;
    }

    virtual double cenaTransport(){
        return osnovnaCena;
    }
    bool operator <(Transport &patnik){
        return rastojanie<patnik.rastojanie;
    }
       char *getDestinacija() {
        return destinacija;
    }

    int getOsnovnaCena(){
        return osnovnaCena;
    }

    int getRastojanie() {
        return rastojanie;
    }

    virtual ~Transport(){}
};

class AvtomobilTransport : public Transport{
private:
    bool platenSofer;
public:
    AvtomobilTransport(char *destinacija="", int osnovnaCena=0, int rastojanie=0,bool platenSofer=false): Transport(destinacija,osnovnaCena,rastojanie){
        this->platenSofer=platenSofer;
    }
    double cenaTransport(){
        double osnovnaC=Transport::cenaTransport();
        if(platenSofer){
            return osnovnaC+(osnovnaC*0.2);
        }
        else{
            return osnovnaC;
        }
    }
};

class KombeTransport : public Transport{
private:
    int kapacitet;
public:
    KombeTransport(char *destinacija="", int osnovnaCena=0, int rastojanie=0,int kapacitet=0): Transport(destinacija,osnovnaCena,rastojanie) {
        this->kapacitet = kapacitet;
    }
    double cenaTransport() {
        double osnovnaC=Transport::cenaTransport(),namaluvanje;
        namaluvanje=osnovnaC-(kapacitet*200);
        return namaluvanje;
    }
    };
    void pecatiPoloshiPonudi(Transport **tr,int n,Transport &t) {
        double cenaT = t.cenaTransport();
        Transport *tmp1;
    for(int i=0;i<n-1;i++){
        for(int j=i;j<n;j++){
            if(tr[i]->cenaTransport()>tr[j]->cenaTransport()){
                tmp1=tr[i];
                tr[i]=tr[j];
                tr[j]=tmp1;
            }
        }
    }
    for(int a=0;a<n;a++){
        if(tr[a]->cenaTransport()>cenaT){
            cout<<tr[a]->getDestinacija()<<" "<<tr[a]->getRastojanie()<<" "<<tr[a]->cenaTransport()<<endl;
        }
    }
    }
int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
