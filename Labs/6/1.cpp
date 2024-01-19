/*Како успешен студент на ФИНКИ вие сте повикани да работите на подобрување на IKnow системот. Како дел од системот треба да се додаде нов дел кој ќе биде одговорен за обработување на дисциплински мерки, па како дел од тимот за развивање на софтверот ќе треба да ја имплементирате класата DisciplinaryAction која ќе ги чува следните информации:
    Името на студентот (динамички алоцирана низа од карактери)
    Индексот на студентот (int)
    Причината за дисциплинската мерка (динамички алоцирана низа од карактери)
    бројот на сесии во кои студентот нема право да полага (int)
Класата треба да ги има следните методи и конструктори:
    Default конструктор
    Copy конструктор
    Конструктор со аргументи
    Деструктор
    Set и Get методи за индексот
    Оператор =
    оператор << за печатење на информации за студентот
    оператор ++ за зголемување на бројот на сесии во кои студентот е казнет (во префикс нотација)
    оператор >= за споредба на дисциплински постапки според бројот на сесии во кои студентот е казнет
Операторот << треба да печати според следниот формат:
Student: [Name]
Student's index: [Index]
Reason: [Reason]
Sessions: [Sessions]
При што вредностите во [] треба да се заменат со вредностите во класата!
!!! ДА НЕ СЕ ПРАВАТ ПРОМЕНИ ВО MAIN() ФУНКЦИЈАТА !!!*/

#include <iostream>
#include <cstring>

using namespace std;
class DisciplinaryAction{
    char *ime;
    int indeks;
    char *prichina;
    int n;
public:
    DisciplinaryAction(const char *ime="", int indeks=0,const  char *prichina="",int n=0)
    {
        this->indeks=indeks;
        this-> ime= new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->prichina= new char[strlen(prichina)+1];
        strcpy(this->prichina,prichina);
        this->n=n;
    }
    DisciplinaryAction(const DisciplinaryAction &d){
        indeks=d.indeks;
        ime= new char[strlen(d.ime)+1];
        strcpy(ime,d.ime);
        prichina= new char[strlen(d.prichina)+1];
        strcpy(prichina,d.prichina);
        n=d.n;
    }
    DisciplinaryAction& operator= (const DisciplinaryAction &dop){
        if(this != &dop){
            delete [] ime;
            this->ime= new char[strlen(dop.ime) + 1];
            strcpy(this->ime, dop.ime);
            delete [] prichina;
            this->prichina= new char[strlen(dop.prichina) + 1];
            strcpy(this->prichina, dop.prichina);
            this->indeks = dop.indeks;
            n=dop.n;
        }
        return *this;
    }

    int getIndex() const {
        return indeks;
    }

    void setIndex(int i) {
    indeks=i;
    }
    bool operator>=(const DisciplinaryAction &rhs) const {
        return n>=rhs.n;
    }

    friend ostream &operator<<(ostream &out, const DisciplinaryAction &merka) {
        out<<"Student: "<<merka.ime<<endl;
        out<<"Student's index: "<<merka.indeks<<endl;
        out<<"Reason: "<<merka.prichina<<endl;
        out<<"Sessions: "<<merka.n<<endl;
        return out;
    }
    DisciplinaryAction &operator++(){
        n++;
        return *this;
    }
    ~DisciplinaryAction(){
        delete [] ime;
        delete [] prichina;
    }
};



/// Do NOT edit the main() function

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for (int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;
        int sessions;

        cin >> name >> index >> reason >> sessions;

        arr[i] = DisciplinaryAction(name, index, reason, sessions);
    }

    cout << "-- Testing operator = & operator <<  --\n";
    cout << arr[0];

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    cout << arr[0];

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    cout << merka;

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for (int i = 0; i < n; i++)
        cout << arr[i];


    cout << "\nTesting operator ++ and <<" << endl;
    for (int i = 0; i < n; i++)
        cout << (++arr[i]);


    cout << "\nTesting operator >=" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                cout << i << " " << ((arr[i] >= arr[j]) ? ">= " : "< ") << j << endl;
            }
        }
    }

    return 0;
}
