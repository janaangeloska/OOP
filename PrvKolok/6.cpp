/*Да се креира структура Воз во која се чуваат податоци за релацијата по која се движи возот (низа од најмногу 50 знаци), предвиден бројот на километри што треба да се поминат (реален број), како и бројот на патници во возот (цел број).
Потоа да се креирa структура ZeleznickaStanica во која се чуваат податоци за градот во кој се наоѓа (низа од 20 знаци), низа од возови што поаѓаат од станицата (најмногу 30) и бројот на возови (цел број).
Треба да се направи функција со потпис
void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad)
во која се печати релацијата и бројот на километри на возот што поминува најкратка релација (најмалку километри), а поаѓа од железничката станица од градот што се проследува како влезен аргумент. Ако има повеќе возови со ист најмал број на километри, да се испечати релацијата на последниот таков.
Забелешка: Задачата да се реши во програмскиот јазик C++*/

#include<iostream>
#include <cstring>
using namespace std;

struct Voz{
	char relacija[50];
    int kilometri;
    int patnici;
};

struct ZeleznickaStanica{
	char grad[20];
    Voz vozovi[30];
    int brvozovi;
};

void najkratkaRelacija(ZeleznickaStanica* zs, int n, char* grad){
    int targetZs;
    int minPtr = 0;
    for(int i = 0; i < n; i++){
        if(strcmp(zs[i].grad, grad) == 0){
            targetZs = i;
            
            int minVal = zs[targetZs].vozovi[0].kilometri;      
            for(int j = 0; j < zs[i].brvozovi; j++){
                if(zs[targetZs].vozovi[j].kilometri <= minVal){
                	minVal = zs[targetZs].vozovi[j].kilometri;
                    minPtr = j;
                }
            }
            cout<<"Najkratka relacija: "<< zs[targetZs].vozovi[minPtr].relacija << " " << "(" <<
            zs[targetZs].vozovi[minPtr].kilometri << " km)" << endl;
        }
    }
}
int main(){
	
    int n;
	cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
        cin>>zStanica[i].grad;
        cin>>zStanica[i].brvozovi;
        for(int j = 0; j < zStanica[i].brvozovi; j++){
        	cin>>zStanica[i].vozovi[j].relacija;
            cin>>zStanica[i].vozovi[j].kilometri;
            cin>>zStanica[i].vozovi[j].patnici;
        }
    }
    
    char grad[25];
    cin>>grad;

	najkratkaRelacija(zStanica,n,grad);
	return 0;
}
