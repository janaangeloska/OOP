/*Define a class Goal that keeps information for:
    the goal scorer (dynamically allocated array of characters),
    time (the minute) of the goal scoring event (integer),
    name of the team that scored the goal (char array max 50).
For this class implement:
    constructor with all three arguments
    operator << for printing on ostream an object of class Goal (print the minute and the name)
    operator ++ (postfix) notation for incrementing the minute for one,
    operator -- (prefix) notation for decrementing the minute for one.
Also create a class Game that keeps dynamically allocated array of objects from the class Goal and the names of the teams that play that game (two char arrays of 50). For this class implement:
    constructor with two arguments the names of the teams that play the game
    the unary operator += for adding an object of class Goal in the array of objects. If the name of the object from the class Goal is not equal to the one of the names of the teams that play the game then throw an exception of type InvalidTeamName. Handling the exception should be in the appropriate place in the main function, by printing the message Invalid team name: [the_name]
    operator << for printing on the ostream the teams that play the game and all the scorers.
*/


#include <iostream>
#include <cstring>
using namespace std;

class InvalidTeamName{
    char team[50];
public:
    InvalidTeamName(char *team=""){
        strcpy(this->team,team);
    }
    char *what(){
        return team;
    }
};
class Goal{
    char *name;
    int time;
    char team[50];
public:
    Goal(char *name="", int time=0, char *team="") {
        this->name=new char [strlen(name)+1];
        strcpy(this->name,name);
        this->time=time;
         strcpy(this->team,team);
    }

    friend ostream &operator<<(ostream &os, Goal &goal) {
        os << goal.time<< " " << goal.name<<endl;
        return os;
    }
    //prefiks
    Goal &operator++(){
        ++time;
        return *this;
    }
    //sufiks
    Goal &operator--(){
        Goal tmp=*this;
        --time;
        return tmp;
    }
    friend class Game;
    ~Goal(){}
};
class Game{
    Goal *goals;
    char team1[50];
    char team2[50];
    int n;
public:
    Game(char *team1="", char *team2="")  {
        n=0;
        strcpy(this->team1,team1);
        strcpy(this->team2,team2);
    this->goals=new Goal[0];
    }
Game &operator+=( Goal &g){
        if(strcmp(team1,g.team)!=0&&strcmp(team2,g.team)!=0){
            throw InvalidTeamName(g.team);
        }
            Goal *tmp=new Goal[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=goals[i];
        }
        tmp[n++]=g;
        delete [] goals;
        goals=tmp;
    return *this;
    }

    friend ostream &operator<<(ostream &os, Game &game) {
        os  << game.team1 << " - " << game.team2<<endl;
        for(int i=0;i<game.n;i++){
            os<<game.goals[i];
        }
        return os;
    }
};


int main() {
    char team1[50];
    char team2[50];
    cin >> team1;
    cin >> team2;
    Game n(team1, team2);
    int x;
    cin >> x;
    char player[100];
    int m;
    for(int i = 0; i < x; ++i) {
        cin >> player;
        cin >> m;
        cin >> team1;
        Goal g(player, m, team1);
        try {
            n += g;
        } catch(InvalidTeamName &e) {
            cout << "Invalid team name: " << e.what() << endl;
        }
    }
    cout << n << endl;
    return 0;
}
