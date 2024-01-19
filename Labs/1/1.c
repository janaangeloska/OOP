/*За програмски јазик да се употреби C.
Да се напише програма во која од стандарден влез се внесува бројот N (бројот на трансакции), а потоа N трансакциски сметки и како резултат ги печати идентификацискиот број и вкупната сума (со провизија) на сите трансакции платени со кредитна картичка. Во случај да нема трансакција платена со кредитна картичка да се испечати "No credit card transaction".
Во структурата Трансакција (Transaction) треба да се чуваат следните информации:
- Идентификациски број (int)
- Платена сума (int)
- Провизија (int)
- Дали е платено со дебитна или кредитна картичка (0 - дебитна, 1 - кредитна)
Ограничување: 0 < N < 100
Структура на влезните податоци:
N
id1 sum1 commission1 type1
...
idn sumn Commissionn typen*/

#include <stdio.h>
typedef struct Transaction{
    int ID;
    int PlatenaSuma;
    int Provizija;
    int KreditnaDebitna;
}transakcija;

int main() {
    int n,flag=1;
    scanf("%d", &n);
    for(int i=0;i<n;i++){
        transakcija tran;
        scanf("%d %d %d %d",&tran.ID,&tran.PlatenaSuma,&tran.Provizija,&tran.KreditnaDebitna);
        if(tran.KreditnaDebitna==1){
            flag=0;
            printf("%d %d\n",tran.ID,tran.PlatenaSuma+tran.Provizija);
        }
    }
    if(flag){
        printf("No credit card transaction");
    }
    return 0;
}
