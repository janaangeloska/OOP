/*Да се креира структура Igrac во која се чуваат податоци за еден играч на компјутерската игра. За играчот се чуваат информации за корисничкото име на играчот (низа од 15 знаци), број на ниво до кој играчот е стигнат (цел број) и број на освоени поени (цел број) (10 поени).
Потоа да се креирa структура KompjuterskaIgra во која се чуваат податоци за името на играта (низа од 20 знаци), низа од играчи кои ја играат играта (најмногу 30) и бројот на играчи. (10 поени)
Треба да се направи функција со потпис (15 поени)
void najdobarIgrac(KompjuterskaIgra *lista, int n)
Оваа функција треба да го испечати името на најдобриот играч на онаа игра која има најголема популарност (ја играат наjголем број на играчи). Најдобар играч е играчот кој има најголем број на освоени поени. Ако има повеќе играчи со ист максимален број на освоени поени, најдобар е играчот кој има достигнато најголемо ниво.
Печатењето е во форматот: "Najdobar igrac e igracot so korisnicko ime XXXXX koj ja igra igrata YYYYYY". (XXXXXX е корисничкото име на најдобриот играч,а YYYYY е името на играта која ја играат најголем број на играчи)
(Забелешка: секогаш ќе има точно еден најдобар играч)
Функционалност на задачата и дополнување на main функцијата (10 поени)
Забелешка: Задачата да се реши во програмскиот јазик C+*/

#include <iostream>
#include <cstring>
using namespace std;
struct Igrac{
    char korisnickoIme [15];
    int nivo;
    int poeni;
};
struct KompjuterskaIgra{
    char ime [15];
    Igrac lista[30];
    int n;
};
void najdobarIgrac(KompjuterskaIgra *lista, int n){
    int max=0, a=0,b=0,max1=0,max2=0;
    for(int i=0;i<n;i++){
    if(lista[i].n>max){
        max=lista[i].n;
        a=i;
    }
    }
    for(int j=0;j<lista[a].n;j++){
        if(lista[a].lista[j].poeni > max1){
            max1=lista[a].lista[j].poeni;
            b=j;
        }
        else if(lista[a].lista[j].poeni == max1){
            if(lista[a].lista[j].nivo > lista[a].lista[a].nivo){
                max1=lista[a].lista[j].poeni;
                b=j;
                max2=lista[a].lista[j].nivo;
            }
        }
    }
    cout << "Najdobar igrac e igracot so korisnicko ime " << lista[a].lista[b].korisnickoIme <<
         " koj ja igra igrata " << lista[a].ime<<endl;
}
int main() {
    int n,m;
    char ime[20];
    cin>>n;
    KompjuterskaIgra poleigri[100];
    for (int i=0; i<n; i++) {
        KompjuterskaIgra nova;
        cin>>nova.ime>>nova.n;
        Igrac pole[30];
        for (int j=0; j<nova.n; j++) {
            Igrac nov;
            cin>>nov.korisnickoIme>>nov.nivo>>nov.poeni;
            nova.lista[j]=nov;
        }
        poleigri[i]=nova;
    }

    najdobarIgrac(poleigri,n);
    return 0;
}
