/*За програмски јазик да се употреби C.
Да се креира структура Employee во која се чуваат податоци за еден вработен. За вработениот се чуваат информации за името на вработениот (низа од карактери), матичен број (ЕМБГ) на вработениот(низа од карактери), име на одделот во кој што работи (низа од карактери), плата (цел број).
Потоа, да се креира структура Company во која се чуваат податоци за името на компанијата (низа од карактери), низа од вработени во компанијата и број на вработени.
Да се направи функција:
void printEmployeesBelowAverageSalary(Company *comp, int numCompanies)
која што за секоја компанија, ќе ги испечати сите вработени чија што плата е пониска од просекот на платите на сите вработени во таа компанија.
Да се направи функција: 
void printHighestSalaryEmployee(Company *comp, int numCompanies, char *department) 
кoja што за секоја компанија ќе го испечати вработениот со највисока плата во дадениот оддел.
Напомена: Прво од тастатура се чита бројот на компании, потоа компаниите (името и бројот на вработени), а потоа податоците за нивните вработени соодветно, a на крај се чита одделот кој што ќе биде искористен во printHighestSalaryEmployee функцијата.*/

#include <stdio.h>
#include<string.h>
typedef struct Employee{
    char ime[50];
    char EMBG[50];
    char oddel[50];
    int plata;
}vraboten;
typedef struct Company{
    char ImeNaKompanija[50];
    vraboten vraboteni[100];
    int BrNaVraboteni;
}comp;

void printEmployeesBelowAverageSalary(struct Company *comp, int numCompanies){
    printf("Employees with salaries below the average:\n");
    float Avg;
    int i,j,k, VkupnaPlata=0;
    for(i=0;i<numCompanies;i++){
        VkupnaPlata=0;
    for(j=0;j<comp[i].BrNaVraboteni;j++){
        VkupnaPlata+=comp[i].vraboteni[j].plata;
    }
    Avg=(float)VkupnaPlata/(float)comp[i].BrNaVraboteni;
    for(k=0;k<comp[i].BrNaVraboteni;k++){
        if(comp[i].vraboteni[k].plata<Avg){
            printf("%s %s %s %d\n",comp[i].vraboteni[k].ime,comp[i].vraboteni[k].EMBG,
                   comp[i].vraboteni[k].oddel,comp[i].vraboteni[k].plata);
        }
    }
    }
}
void printHighestSalaryEmployee(struct Company *comp, int numCompanies, char *department){
    printf("Employees with highest salaries for given department:\n");
    int i, j, MaxPlata,flag, BrNaRabotnik;
    for(i=0;i<numCompanies;i++){
        MaxPlata=0, flag=0;
        for(j=0;j<comp[i].BrNaVraboteni;j++) {
            if ((strcmp(comp[i].vraboteni[j].oddel, department) == 0 && comp[i].vraboteni[j].plata > MaxPlata)) {
                flag = 1;
                MaxPlata = comp[i].vraboteni[j].plata;
                BrNaRabotnik = j;
            }
        }
            printf("%s %s %s %d\n",comp[i].vraboteni[BrNaRabotnik].ime, comp[i].vraboteni[BrNaRabotnik].EMBG,
                   comp[i].vraboteni[BrNaRabotnik].oddel,comp[i].vraboteni[BrNaRabotnik].plata);
    }
}
int main(){
int NumberOfCompanies, i, j;
char oddel[50];
    scanf("%d",&NumberOfCompanies);
    comp kompanii[100];
    for(i=0;i<NumberOfCompanies;i++){
        scanf("%s\n",kompanii[i].ImeNaKompanija);
        scanf("%d\n",&kompanii[i].BrNaVraboteni);
        for(j=0;j<kompanii[i].BrNaVraboteni;j++){
            scanf("%s ",kompanii[i].vraboteni[j].ime);
            scanf("%s ",kompanii[i].vraboteni[j].EMBG);
            scanf("%s ",kompanii[i].vraboteni[j].oddel);
            scanf("%d ",&kompanii[i].vraboteni[j].plata);
        }
    }
    printEmployeesBelowAverageSalary(kompanii, NumberOfCompanies);
    scanf("%s",oddel);
    printHighestSalaryEmployee(kompanii,NumberOfCompanies,oddel);
    return 0;
}
//ima greshka vo expected delot
