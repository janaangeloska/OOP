/*Во програмскиот јазик C да се креира структура Laptop за опишување на спецификациите на даден преносен компјутер. Структурата треба да содржи: (5 поени)
    Фирма која го произведува ( низа од 100 знаци)
    Големина на монитор во инчи (реален број)
    Дали е со touch или не (булова променлива)
    Цена (цел број)
Да се креира структура ITStore, што содржи: (5 поени)
    Име на продавницата (низа од 100 знаци)
    Локација (низа од 100 знаци)
    Низа од достапни лаптопи (низа од максимум 100 елементи од структурата Laptop)
    Број на елементи во низата (цел број)
Да се креира функција print за печатење на информациите за сите лаптопи во една продавница во формат: (10 поени)
[Ime na prodavnicata] [Lokacija]
[Marka1] [dim_monitor1] [Cena1]
[Marka2] [dim_monitor2] [Cena2]
[Marka3] [dim_monitor3] [Cena3]
...
Да се креира функција najeftina_ponuda, што прима низа од променливи од типот ITStore и го печати името и локацијата на онаа продавница која нуди најевтин преносен компјутер и неговата цена. Најефтин преносен компјутер е оној што има најниска цена и плус опција за touch. Ако има повеќе такви продавници, се печати прво најдената.* (15 поени)*
Да се дополни функцијата main (10 поени).
Од тастатура се внесува бројот на продавници, па потоа за секоја продавница се внесуваат името и локацијата, а потоа бројот на компјутери, па за секој од компјутерите фирма која го произведува, големина на монитор, дали има touch и цена. Потоа се печатат сите внесени продавници и најевтината понуда.*/

#include<string.h>
#include <stdio.h>
typedef struct Laptop{
    char firma[100];
    float golemina;
    int touch;
    int cena;
}Laptop;
typedef struct ITStore{
    char prodavnica[100];
    char lokacija[100];
    Laptop laptop[100];
    int n;
}ITStore;
void print(ITStore *st,int n){
    int i,j;
    for(i=0;i<n;i++){
        printf("%s %s\n",st[i].prodavnica,st[i].lokacija);
        for(j=0;j<st[i].n;j++){
            printf("%s %g %d\n",st[i].laptop[j].firma,st[i].laptop[j].golemina,st[i].laptop[j].cena);
        }
    }
}
void najeftina_ponuda(ITStore *st,int n){
int najeftin=99999999,indeks;
for(int i=0;i<n;i++){
    for(int j=0;j<st[i].n;j++){
     if(st[i].laptop[j].cena<najeftin&&st[i].laptop[j].touch==1){
         najeftin=st[i].laptop[j].cena;
         indeks=i;
     }   
    }
}
    printf("Najeftina ponuda ima prodavnicata:\n");
    printf("%s %s\n",st[indeks].prodavnica,st[indeks].lokacija);
    printf("Najniskata cena iznesuva: %d",najeftin);
}

int main() {
    ITStore s[100];
    int n,i,j;
    scanf("%d",&n); //broj na IT prodavnici
    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for(i=0;i<n;i++){
        scanf("%s",s[i].prodavnica);
        scanf("%s",s[i].lokacija);
        scanf("%d\n",&s[i].n);
        for(j=0;j<s[i].n;j++){
            scanf("%s %f %d %d\n",
                  s[i].laptop[j].firma,
                  &s[i].laptop[j].golemina,
                  &s[i].laptop[j].touch,
                  &s[i].laptop[j].cena);
        }
    }
    //pecatenje na site prodavnici
    print(s,n);
    //povik na glavnata metoda
    najeftina_ponuda(s, n);
    return 0;
}
