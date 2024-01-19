/*Да се имплементира класа Game за која се чува:
    title (низа од карактери)
Во класата да се имплементира виртуелна функција void displayInfo() која на екран печати информации за дадената игра и виртуелна функција int complexity() која ја враќа комплексноста на играта.
Потребно е да се имплементира класите BoardGame и CardGame кои што ќе наследуваат од класата Game.
За класата BoardGame дополнително се чуваат:
    maxPlayers - максимален број на играчи (цел број)
Доколку максималниот број на играчи е поголем од 6 тогаш комплексноста е 10, доколку  максималниот број на играчи е поголем од 3 а помал од 6 тогаш комплексноста е 5, а доколку е помал од 3, тогаш комплексноста е 3.
Функцијата displayInfo() печати во формат:
Game: [наслов на игра]
Max players: [максимален број на играчи]
Complexity: [комплексност]
За класата CardGame дополнително се чуваат:
    numCards - број на карти (цел број)
Доколку бројот на карти е поголем од 20 тогаш комплексноста е 10, доколку  бројот на карти е поголем од 10 а помал од 20 тогаш комплексноста е 5, а доколку е помал од 10, тогаш комплексноста е 3.
Функцијата displayInfo() печати во формат:
Game: [наслов на игра]
Number of cards: [број на карти]
Complexity: [комплексност]
Потребно е да се имплементира класата BoardCardGame која што ќе наследува од класите BoardGame и CardGame.
Комплексноста е пресметана на следниот начин: (комплексноста на CardGame + комплексноста на BoardGame)/2
Функцијата displayInfo() печати во формат:
Game: [наслов на игра]
Complexity: [комплексност]
Да се направи глобална функција Game *mostComplexCardGame(Game **games, int n) што ќе врати покажувач до најкомплексната игра со карти.*/

#include <iostream>
#include <cstring>
using namespace std;
class Game{
protected:
    char title[100];
public:
    Game(char *title=""){
        strcpy(this->title,title);
    }
    virtual void displayInfo()=0;
    virtual int complexity()=0;
    virtual ~Game(){}
};
class BoardGame : virtual public Game{
protected:
    int maxPlayers;
public:
    BoardGame(char *title="",int maxPlayers=2): Game(title){
        this->maxPlayers=maxPlayers;
    }
    int complexity(){
        if(maxPlayers<3){
            return 3;
        }
        if(maxPlayers>3&&maxPlayers<6){
            return 5;
        }
        if(maxPlayers>6){
            return 10;
        }
        return 0;
    }
    void displayInfo(){
        cout<<"Game: "<<title<<endl;
        cout<<"Max players: "<<maxPlayers<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }
    ~BoardGame(){}

};
class CardGame : virtual public Game{
protected:
    int numCards;
public:
    CardGame(char *title="",int numCards=2): Game(title){
        this->numCards=numCards;
    }
    int complexity(){
        if(numCards<10){
            return 3;
        }
        if(numCards>10&&numCards<20){
            return 5;
        }
        if(numCards>20){
            return 10;
        }
        return 0;
    }
    void displayInfo(){
        cout<<"Game: "<<title<<endl;
        cout<<"Number of cards: "<<numCards<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }
    ~CardGame(){}
};
class BoardCardGame: public BoardGame, public CardGame{
public:
    BoardCardGame(char *title="",int maxPlayers=2,int numCards=2):Game(title), BoardGame(title,maxPlayers), CardGame(title,numCards){}
    int complexity(){
        return (CardGame::complexity()+BoardGame::complexity())/2;
    }
    void displayInfo(){
        cout<<"Game: "<<title<<endl;
        cout<<"Complexity: "<<complexity()<<endl;
    }
    ~BoardCardGame(){}
};
Game *mostComplexCardGame(Game **games, int n){
    CardGame* maxCG = nullptr;
    int maxComplexity = 0;
    for (int i = 0; i < n; i++) {
        CardGame* CG = dynamic_cast<CardGame*>(games[i]);
        if (CG){
            if(CG->complexity() > maxComplexity) {
            maxComplexity = CG->complexity();
            maxCG = CG;
        }
    }
    }
    return maxCG;
}
int main() {
    char title[50];
    int maxPlayers;
    int numCards;
    int n;
    int choice;

    cin>>choice;
    if(choice==1)
    {
        cin>>title;
        BoardCardGame boardCardGame(title, 8, 15);
        boardCardGame.displayInfo();
    }
    else {

        cin >> n;

        Game **g = new Game *[n];
        for (int i = 0; i < n; i++) {
            cin >> choice;
            if (choice == 1) {
                cin >> title >> maxPlayers;

                g[i] = new BoardGame(title, maxPlayers);
            } else {
                cin >> title >> numCards;

                g[i] = new CardGame(title, numCards);
            }

        }

        mostComplexCardGame(g,n)->displayInfo();

    }


    return 0;
}
