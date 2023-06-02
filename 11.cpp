/*Потребно е да се моделира продажба на карти за прикажување на претстави во некој културен центар. За таа цел, да се направи класа DELO. За класата се чуваат следните атрибути:
    Име на делото (низа од 50 знаци)
    Година кога е напишано (цел број)
    Земја на потекло (низа од 50 знаци)
За класата да се направат потребниот конструктор, get и set методи. За класата DELO да се преоптовари операторот == кој ќе споредува дали две дела се исти (две дела се исти ако имаат исто име) (5 поени).
Да се дефинира класа PRЕTSTAVA. За класата се чуваат информации за:
    Делото кое се прикажува (објект од класата DELO)
    Број на продадени карти (цел број)
    Дата на прикажување (низа од 15 знаци)
За класата да се дефинира потребниот конструктор, set и get методите Дополнително, за класата PRETSTAVA да се напише метода cena која треба да ја врати цената на една карта. (5 поени) Цената зависи од староста на делото и од земјата на потекло и се пресметува по следната формула: Цена = N + М, каде М = 50ден. ако делото е напишано во 20 или 21 век, М = 75ден. ако делото е напишано во 19 век и М = 100ден. ако делото е напишано пред 19 век. N = 100ден ако делото е од Италија, N = 150ден ако делото е од Русија. Делата од останатите земји имаат N = 80ден.
Претставите можат да бидат опера и балет. За балетите се чува дополнителен атрибут за цената на балетот која се додава на оригиналната цена на картата и таа вредност е иста за сите балетски претстави. На почеток изнесува 150 денари, со можност да се променува ако така одлучи менаџментот на културниот центар. (10 поени)
Да се дефинира надворешна функција prihod која како аргумент прима низа од покажувачи кон претстави кои се прикажале во еден месец и големина на низата, а како резултат треба да го пресмета и врати вкупниот приход на културниот центар. (10 поени)
Да се дефинира надворешна функција brojPretstaviNaDelo која како аргумент прима низа од покажувачи кон претстави кои се прикажале во еден месец, големина на низата и едно дело. Оваа функција пресметува на колку од дадените претстави е прикажано даденото дело. (5 поени)
(Напомена: Во низата од претстави која се проследува како аргумент во функциите prihod и brojPretstaviNaDelo може да имаме повеќе претстави за едно исто дело)
Целосна функционалност на задачата (5 поени)*/

//NOTICE: pazi na delenjeto na godina i 100 za da go dobiesh vekot kako shto se bara vo zadachata (prm: 2000/100=20 ama toa e 21vi vek)


#include<iostream>
#include<string.h>
using namespace std;

class Delo{
protected:
    char ime[50];
    int godina;
    char zemjaNaPoteklo[50];
public:
    Delo(char *ime="", int godina=0, char *zemjaNaPoteklo=""){
        strcpy(this->ime,ime);
        this->godina=godina;
        strcpy(this->zemjaNaPoteklo,zemjaNaPoteklo);
    }

    bool operator==(Delo &rhs){
        return strcmp(this->ime, rhs.ime)==0;
    }

    char *getIme() {
        return ime;
    }

    int getGodina(){
        return godina;
    }

     char *getZemjaNaPoteklo() {
        return zemjaNaPoteklo;
    }
};
class Pretstava{
protected:
    Delo delo;
    int prodadeniKarti;
    char data[15];
public:
    Pretstava(Delo delo= nullptr, int prodadeniKarti=0, char *data=""){
        this->delo=delo;
        this->prodadeniKarti=prodadeniKarti;
        strcpy(this->data,data);
    }
    virtual int cena(){
        int m=0,n=0;
        if(delo.getGodina()/100==20||delo.getGodina()/100==19){
            m=50;
        }
        else if(delo.getGodina()/100==18){
            m=75;
        }
        else{
            m=100;
        }
        if(strcmp(delo.getZemjaNaPoteklo(),"Italija")==0){
            n=100;
        }
        else if(strcmp(delo.getZemjaNaPoteklo(),"Rusija")==0){
            n=150;
        }
        else{
            n=80;
        }
        return m+n;
    }

     Delo &getDelo()  {
        return delo;
    }

    int getProdadeniKarti()  {
        return prodadeniKarti;
    }

     char *getData()  {
        return data;
    }
};
class Balet: public Pretstava{
static int price;
public:
    Balet(Delo delo= nullptr, int prodadeniKarti=0, char *data=""): Pretstava(delo,prodadeniKarti,data){
        this->delo=delo;
        this->prodadeniKarti=prodadeniKarti;
        strcpy(this->data,data);
    }
    int cena(){
    return Pretstava::cena()+price;
    }
    static void setCenaBalet(int pr){
        Balet::price=pr;
    }
};
int Balet::price=150;
class Opera:public Pretstava{
public:
    Opera(Delo delo= nullptr, int prodadeniKarti=0, char *data=""): Pretstava(delo,prodadeniKarti,data){
        this->delo=delo;
        this->prodadeniKarti=prodadeniKarti;
        strcpy(this->data,data);
    }
    int cena(){
        return Pretstava::cena();
    }
};
double prihod(Pretstava **p,int n){
    double vk=0;
    for(int i=0;i<n;i++){
        vk+=p[i]->cena()*p[i]->getProdadeniKarti();
    }
    return vk;
}
int brojPretstaviNaDelo(Pretstava **p, int n, Delo delo) {
    int vk=0;
    for(int i=0;i<n;i++){
        if(p[i]->getDelo()==delo){
            vk++;
        }
    }
    return vk;
}
//citanje na delo
Delo readDelo(){
    char ime[50];
    int godina;
    char zemja[50];
    cin>>ime>>godina>>zemja;
    return Delo(ime,godina,zemja);
}
//citanje na pretstava
Pretstava* readPretstava(){
    int tip; //0 za Balet , 1 za Opera
    cin>>tip;
    Delo d=readDelo();
    int brojProdadeni;
    char data[15];
    cin>>brojProdadeni>>data;
    if (tip==0)  return new Balet(d,brojProdadeni,data);
    else return new Opera(d,brojProdadeni,data);
}



int main(){
    int test_case;
    cin>>test_case;

    switch(test_case){
        case 1:
            //Testiranje na klasite Opera i Balet
        {
            cout<<"======TEST CASE 1======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->getDelo().getIme()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->getDelo().getIme()<<endl;
        }break;

        case 2:
            //Testiranje na  klasite Opera i Balet so cena
        {
            cout<<"======TEST CASE 2======="<<endl;
            Pretstava* p1=readPretstava();
            cout<<p1->cena()<<endl;
            Pretstava* p2=readPretstava();
            cout<<p2->cena()<<endl;
        }break;

        case 3:
            //Testiranje na operator ==
        {
            cout<<"======TEST CASE 3======="<<endl;
            Delo f1=readDelo();
            Delo f2=readDelo();
            Delo f3=readDelo();

            if (f1==f2) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;
            if (f1==f3) cout<<"Isti se"<<endl; else cout<<"Ne se isti"<<endl;

        }break;

        case 4:
            //testiranje na funkcijata prihod
        {
            cout<<"======TEST CASE 4======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();

            }
            cout<<prihod(pole,n);
        }break;

        case 5:
            //testiranje na prihod so izmena na cena za 3d proekcii
        {
            cout<<"======TEST CASE 5======="<<endl;
            int cenaBalet;
            cin>>cenaBalet;
            Balet::setCenaBalet(cenaBalet);
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }
            cout<<prihod(pole,n);
        }break;

        case 6:
            //testiranje na brojPretstaviNaDelo
        {
            cout<<"======TEST CASE 6======="<<endl;
            int n;
            cin>>n;
            Pretstava **pole=new Pretstava*[n];
            for (int i=0;i<n;i++){
                pole[i]=readPretstava();
            }

            Delo f=readDelo();
            cout<<brojPretstaviNaDelo(pole,n,f);
        }break;

    };


    return 0;
}
