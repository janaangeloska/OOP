/*Во програмскиот јазик C да се креира структура Movie за опишување на филм во рамките на една стриминг платформа. Структурата за филм треба да ги содржи следниве полиња: (5 поени)
    Име (низа од 100 знаци)
    Рејтинг (реален број)
    Жанр (низа од 40 знаци)
Да се креира структура StreamingService, што ги содржи следниве полиња: (5 поени)
    Име на стриминг платформата (низа од 50 знаци)
    Низа од достапни филмови (низа од максимум 30 елементи од структурата Movie)
    Број на елементи во низата (цел број)
Да се креира глобална функција print за печатење на информациите за дадена стриминг платформа во следниот формат: (10 поени)
[Ime na streaming platformata]
[ImeFilm1] [Rejting1]
[ImeFilm2] [Rejting2]
[ImeFilm3] [Rejting3]
...
Да се креира функција showBestStreamningService, што прима низа од променливи од типот StreamingService, и променлива genre. Оваа функција треба да го испечати името на стриминг платформата која нуди најмногу филмови кои се од даден жанр (во зависност од пратената променлива genre). Ако има повеќе такви стриминг платформи со максимален број на филмови од пратениот жанр, се печати првата.(15 поени)
Да се дополни функцијата main (5 поени).*/

#include <stdio.h>
#include <string.h>
typedef struct {
    char name[100];
    float rating;
    char genre[40];
} Movie;

typedef struct {
    char platformName[50];
    Movie movies[30];
    int numMovies;
} StreamingService;

void print(StreamingService service) {
    printf("%s\n", service.platformName);
    for (int i = 0; i < service.numMovies; i++) {
        printf("%s %.1f\n", service.movies[i].name, service.movies[i].rating);
    }
}

void showBestStreamingService(StreamingService services[], int numServices, char genre[]) {
    int maxNumMovies = -1;
    char *bestPlatformName;
    int flag=1;
    for (int i = 0; i < numServices; i++) {
        int numMovies = 0;
        for (int j = 0; j < services[i].numMovies; j++) {
            if (strcmp(services[i].movies[j].genre, genre) == 0) {
                numMovies++;
                flag=0;
            }
        }
        if (numMovies > maxNumMovies) {
            maxNumMovies = numMovies;
            bestPlatformName = services[i].platformName;
        }
    }
    if(flag==1){
        printf("No service has movies of the given genre.");
    }
    else{
    printf("Best streaming service is: %s\n", bestPlatformName);
}
}
int main() {
    int num_services;
    scanf("%d", &num_services);
    StreamingService services[num_services];
    
    //read streaming services
    for (int i = 0; i < num_services; i++) {
        scanf("%s", services[i].platformName);
        scanf("%d", &services[i].numMovies);
        for (int j = 0; j < services[i].numMovies; j++) {
            scanf("%s", services[i].movies[j].name);
            scanf("%f", &services[i].movies[j].rating);
            scanf("%s", services[i].movies[j].genre);
        }
    }
    //print
    for (int i = 0; i < num_services; i++) {
        print(services[i]);
    }
    //call to best streaming service
    char genre[40];
    scanf("%s", genre);
    showBestStreamingService(services, num_services, genre);

    return 0;
}
