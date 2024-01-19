/*
NBAPlayer
Да се дефинира класа NBAPlayer за која ќе се чуваат:
    динамички алоцирана низа од карактери за името на играчот
    низа од максимум 40 карактери за тимот во кој играчот моментално настапува
    просечен број на поени на играчот оваа сезона (double)
    просечен број на асистенции на играчот оваа сезона (double)
    просечен број на скокови на играчот оваа сезона (double)
За потребите на класата да се дефинираат:
    default конструктор и конструктор со аргументи
    copy constructor и оператор =
    деструктор
    метод rating() кој го враќа рејтингот на кошаркарот кој се пресметува како:
    45% од поените + 30% од асистенциите + 25% од скоковите
    метод print() кој го печати играчот во следниот формат:
    Име - тим
    Points: поени
    Assists: асистенции
    Rebounds: скокови
    Rating: рејтинг

AllStarPlayer
Од претходната класа NBAPlayer да се изведе класата AllStarPlayer за која дополнително ќе се чуваат и:
    просечен број на поени на играчот од All Star натпреварите (double)
    просечен број на асистенции на играчот од All Star натпреварите (double)
    просечен број на скокови на играчот од All Star натпреварите (double)
За потребите на класата да се дефинираат:
    default конструктор
    конструктор кој прима објект од NBAPlayer и плус додатните информации (погледни main)
    конструктор кој ги прима сите аргументи (погледни main)
    copy constructor, оператор =, деструктор
    метод allStarRating() кој го враќа рејтингот на кошаркарот од All Star натпреварите и кој се пресметува како:
    30% од поените + 40% од асистенциите + 30% од скоковите
Да се препокријат методите:
    rating() кој го враќа просекот од обичниот рејтинг на кошаркарот и неговиот All Star рејтинг
    print() кој покрај основните информации за кошаркарот печати и:
    All Star Rating: рејтингот од All Star натпреварите
    New Rating: просечниот рејтинг
*/

#include <iostream>
#include <cstring>
using namespace std;
class NBAPlayer{
protected:
    char *ime;
    char tim[40];
    double prosekPoeni;
    double prosekAsistencii;
    double prosekSkokovi;
public:
    NBAPlayer(char *ime="", char *tim="", double prosekPoeni=0.0, double prosekAsistencii=0.0, double prosekSkokovi=0.0) {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        strcpy(this->tim,tim);
        this->prosekPoeni=prosekPoeni;
        this->prosekAsistencii=prosekAsistencii;
        this->prosekSkokovi=prosekSkokovi;
    }
    NBAPlayer(const NBAPlayer &p) {
        this->ime=new char[strlen(p.ime)+1];
        strcpy(this->ime,p.ime);
        strcpy(this->tim,p.tim);
        this->prosekPoeni=p.prosekPoeni;
        this->prosekAsistencii=p.prosekAsistencii;
        this->prosekSkokovi=p.prosekSkokovi;
    }
     NBAPlayer &operator= (const NBAPlayer &p) {
         if (this != &p) {
             delete [] ime;
             this->ime = new char[strlen(p.ime) + 1];
             strcpy(this->ime, p.ime);
             strcpy(this->tim, p.tim);
             this->prosekPoeni = p.prosekPoeni;
             this->prosekAsistencii = p.prosekAsistencii;
             this->prosekSkokovi = p.prosekSkokovi;
         }
         return *this;
     }
     ~NBAPlayer(){
        delete [] ime;
    }
    double rating(){
    double rejting=0.45*prosekPoeni+0.3*prosekAsistencii+0.25*prosekSkokovi;
    return rejting;
    }
    void print(){
        cout<<ime<<" - "<<tim<<endl;
        cout<<"Points: "<<prosekPoeni<<endl;
        cout<<"Assists: "<<prosekAsistencii<<endl;
        cout<<"Rebounds: "<<prosekSkokovi<<endl;
        cout<<"Rating: "<<rating()<<endl;
    }
};
class AllStarPlayer : public NBAPlayer{
private:
    double prosekAllStarPoeni;
    double prosekAllStarAsistencii;
    double prosekAllStarSkokovi;
public:
    AllStarPlayer(char *ime="", char *tim="", double prosekPoeni=0.0, double prosekAsistencii=0.0, double prosekSkokovi=0.0,
                  double prosekAllStarPoeni=0.0, double prosekAllStarAsistencii=0.0, double prosekAllStarSkokovi=0.0)
                  : NBAPlayer(ime, tim, prosekPoeni, prosekAsistencii, prosekSkokovi){
        this->prosekAllStarPoeni=prosekAllStarPoeni;
        this->prosekAllStarAsistencii=prosekAllStarAsistencii;
        this->prosekAllStarSkokovi=prosekAllStarSkokovi;
    }

    AllStarPlayer(const NBAPlayer &p, double prosekAllStarPoeni, double prosekAllStarAsistencii,
                  double prosekAllStarSkokovi) : NBAPlayer(p) {
        this->prosekAllStarPoeni=prosekAllStarPoeni;
        this->prosekAllStarAsistencii=prosekAllStarAsistencii;
        this->prosekAllStarSkokovi=prosekAllStarSkokovi;
    }
    AllStarPlayer(const AllStarPlayer &p) : NBAPlayer(p){
        this->prosekAllStarPoeni=p.prosekAllStarPoeni;
        this->prosekAllStarAsistencii=p.prosekAllStarAsistencii;
        this->prosekAllStarSkokovi=p.prosekAllStarSkokovi;
    }
    AllStarPlayer &operator= (const AllStarPlayer &p) {
        if (this != &p) {
            this->prosekAllStarPoeni = p.prosekAllStarPoeni;
            this->prosekAllStarAsistencii = p.prosekAllStarAsistencii;
            this->prosekAllStarSkokovi = p.prosekAllStarSkokovi;
            NBAPlayer::operator=(p);
        }
        return *this;
    }
    ~AllStarPlayer()= default;

    double allStarRating(){
    double rejting;
    rejting=0.3*prosekAllStarPoeni+0.4*prosekAllStarAsistencii+0.3*prosekAllStarSkokovi;
        return rejting;
    }
    double rating(){
        double prosek;
        prosek=(NBAPlayer::rating()+allStarRating())/2;
        return prosek;
    }
    void print(){
        NBAPlayer::print();
        cout<<"All Star Rating: "<<allStarRating()<<endl;
        cout<<"New Rating: "<<rating()<<endl;
    }
};
int main() {
  char name[50];
  char team[40];
  double points;
  double assists;
  double rebounds;
  double allStarPoints;
  double allStarAssists;
  double allStarRebounds;

  NBAPlayer * players = new NBAPlayer[5];
  AllStarPlayer * asPlayers = new AllStarPlayer[5];
  int n;
  cin >> n;

  if (n == 1) {

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i = 0; i < 5; ++i) {
      cin >> name >> team >> points >> assists >> rebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      players[i].print();
    }
  }
  else if (n == 2) {

    for (int i=0; i < 5; ++i){
      cin >> name >> team >> points >> assists >> rebounds;
      cin >> allStarPoints >> allStarAssists >> allStarRebounds;
      players[i] = NBAPlayer(name,team,points,assists,rebounds);
      asPlayers[i] = AllStarPlayer(players[i],allStarPoints,allStarAssists,allStarRebounds);
    }

    cout << "NBA PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      players[i].print();

    cout << "ALL STAR PLAYERS:" << endl;
    cout << "=====================================" << endl;
    for (int i=0; i < 5; ++i)
      asPlayers[i].print();

    }
    else if (n == 3) {

      for (int i=0; i < 5; ++i){
        cin >> name >> team >> points >> assists >> rebounds;
        cin >> allStarPoints >> allStarAssists >> allStarRebounds;
        asPlayers[i] = AllStarPlayer(name, team, points, assists, rebounds,
                                     allStarPoints,allStarAssists,allStarRebounds);
      }
      cout << "ALL STAR PLAYERS:" << endl;
      cout << "=====================================" << endl;
      for (int i=0; i < 5; ++i)
        asPlayers[i].print();

    }
    
    delete [] players;
    delete [] asPlayers;
}
