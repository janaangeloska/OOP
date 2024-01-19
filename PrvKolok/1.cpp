/*Да се дефинира класата Pesna во која се чуваат информации за (5 поени):
    име на песна (динамички алоцирано поле од знаци)
    времетраење на песната во минути
    тип на песна кој може да биде: поп, рап или рок (енумерација tip)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (10 поени)
Дополнително за оваа класа да се дефинира методот:
    pecati() - функција во која ќе се печатат одделени со цртичка(-): името на песната во наводници и времетраењето на песната со постфикс min. (5 поени)
Да се креира класата CD во која се чуваат информации за (5 поени):
    низа од песни снимени на CD-то (Поле од најмногу 10 објекти од класата Pesna )
    број на песни снимени на CD-то
    максимално времетраење на песните на CD-то (во минути)
Да се обезбедат сите потребни методи за класата за правилно функционирање на програмата. (5 поени)
Дополнително за оваа класа да се дефинираат методите:
    dodadiPesna (Pesna p) - со кој се додава песната p на CDто, но само ако има доволно преостанато место (земајќи го предвид максималното времетраење на песните на CDто и времетраењата на песните на CD-то) и ако има помалку од 10 песни на CD-то. (10 поени)
    pecatiPesniPoTip(tip t) – со кој се печатат информациите за сите песни од тип t (поп, рап или рок). (10 поени)
Комплетна функционалност (5 поени).*/
#include<iostream>
#include <cstring>
using namespace std;
enum tip{
    pop,rap,rok
};
class Pesna{
    char *pesna;
    int vremetraenje;
    enum tip tip;
public:
    Pesna(char *pesna="", int vremetraenje=0,enum tip tip=pop) {
        this->pesna=new char[strlen(pesna)+1];
        strcpy(this->pesna,pesna);
        this->vremetraenje=vremetraenje;
        this->tip=tip;
    }
    Pesna(const Pesna &p) {
        this->pesna = new char[strlen(p.pesna) + 1];
        strcpy(this->pesna, p.pesna);
        this->vremetraenje = p.vremetraenje;
        this->tip = p.tip;
    }
    Pesna &operator= (const Pesna &pe){
        if(this != &pe){
            delete [] pesna;
            this->pesna = new char[strlen(pe.pesna) + 1];
            strcpy(this->pesna, pe.pesna);
            this->vremetraenje = pe.vremetraenje;
            this->tip = pe.tip;
        }
        return *this;
    }
    ~Pesna(){
        delete [] pesna;
    }

    char *getPesna() {
        return pesna;
    }

    void setPesna(char *pe) {
        strcpy(pesna,pe);
    }

    int getVremetraenje() const {
        return vremetraenje;
    }

    void setVremetraenje(int vr) {
        vremetraenje = vr;
    }

    enum tip getTip() const {
        return tip;
    }

    void setTip(enum tip t) {
        tip = t;
    }
void pecati() const {
        cout<<"\""<<pesna<< "\""<<"-"<<vremetraenje<<"min"<<endl;
    }
    friend class Pesna;
};
class CD {
    Pesna pesna[10];
    int brpesni;
    int traenje;
public:
    CD(int traenje = 0) {
        this->traenje = traenje;
        brpesni = 0;}
    CD(Pesna *pesna = nullptr, int brpesni = 0, int traenje = 0) {
//        pesna=new Pesna[10];
        for (int i = 0; i < 10; i++) {
            this->pesna[i] = pesna[i];
        }
        this->brpesni = brpesni;
        this->traenje = traenje;
    }

    CD(const CD &cd) {
        for (int i = 0; i < 10; i++) {
            this->pesna[i] = cd.pesna[i];
        }
        this->brpesni = cd.brpesni;
        this->traenje = cd.traenje;
    }

    CD &operator=(const CD &c) {
        if (this != &c) {
            for (int i = 0; i < 10; i++) {
                this->pesna[i] = c.pesna[i];
            }
            this->brpesni = c.brpesni;
            this->traenje = c.traenje;
        }
        return *this;
    }

    ~CD() {}

    Pesna getPesna(int i) const {
        return pesna[i];
    }

    int getBroj() const {
        return brpesni;
    }

    void setBrpesni(int brp) {
        brpesni = brp;
    }

    int getTraenje() const {
        return traenje;
    }

    void setTraenje(int tr) {
        traenje = tr;
    }

    void dodadiPesna(Pesna &p) {
        int i, br = 0,vkupnovreme=0;
            for (i = 0; i < brpesni;i++){
                vkupnovreme+=pesna[i].getVremetraenje();
            }
        if (brpesni < 10 && (vkupnovreme+p.getVremetraenje())<=traenje) {
              pesna[brpesni++]=p;
            }
        }
        void pecatiPesniPoTip(tip t){
    for(int i=0;i<brpesni;i++){
        if(pesna[i].getTip()==t){
            cout<<"\""<<pesna[i].getPesna()<<"\""<<"-"<<pesna[i].getVremetraenje()<<"min"<<endl;
        }
    }
}
};
int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;
	
	int n, minuti, kojtip;
	char ime[50];
	
	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBroj(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);
        	
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);
        	
    }
    
return 0;
}
