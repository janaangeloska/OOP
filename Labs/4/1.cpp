/*Како успешен студент на ФИНКИ вие сте повикани да работите на подобрување на IKnow системот. Како дел од системот треба да се додаде нов дел кој ќе биде одговорен за обработување на дисциплински мерки, па како дел од тимот за развивање на софтверот ќе треба да ја имплементирате класата DisciplinaryAction која ќе ги чува следните информации:
    Името на студентот (динамички алоцирана низа од карактери)
    Индексот на студентот (int)
    Причината за дисциплинската мерка (динамички алоцирана низа од карактери)
Класата треба да ги има следните методи и конструктори:
    Default конструктор
    Copy конструктор
    Конструктор со аргументи
    Деструктор
    Set и Get методи за индексот
    void print() метод
    Оператор = 
Print() методот треба да печати според следниот формат:
Student: [Name]
Student's index: [Index]
Reason: [Reason]
При што вредностите во [] треба да се заменат со вредностите во класата!
!!! ДА НЕ СЕ ПРАВАТ ПРОМЕНИ ВО MAIN() ФУНКЦИЈАТА !!!*/

#include <iostream>
#include <cstring>

using namespace std;

class DisciplinaryAction{
    char *ime;
    int indeks;
    char *prichina;
public:
    DisciplinaryAction(const char *ime="", int indeks=0,const  char *prichina="")
    {
        this->indeks=indeks;
        this-> ime= new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->prichina= new char[strlen(prichina)+1];
        strcpy(this->prichina,prichina);
    }
    DisciplinaryAction(const DisciplinaryAction &d){
        indeks=d.indeks;
        ime= new char[strlen(d.ime)+1];
        strcpy(ime,d.ime);
        prichina= new char[strlen(d.prichina)+1];
        strcpy(prichina,d.prichina);
    }
    ~DisciplinaryAction(){
        delete [] ime;
        delete [] prichina;
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
        }
        return *this;
    }

    int getIndex() const {
        return indeks;
    }

    void setIndex(int i) {
    indeks=i;
    }
    void print(){
        cout<<"Student: "<<ime<<endl;
        cout<<"Student's index: "<<indeks<<endl;
        cout<<"Reason: "<<prichina<<endl;
    }
};


/// Do NOT edit the main() function

int main() {
    int n;
    cin >> n;

    /// Testing Default constructor and equal operator
    /// Array input

    DisciplinaryAction arr[n];

    for(int i = 0; i < n; i++) {
        char name[100];
        char reason[100];
        int index;

        cin >> name >> index >> reason;

        arr[i] = DisciplinaryAction(name, index, reason);
    }

    cout << "-- Testing operator = & print() --\n";
    arr[0].print();

    /// Testing copy constructor & set index

    DisciplinaryAction merka(arr[0]);
    merka.setIndex(112233);

    cout << "\n-- Testing copy constructor & set index --\n";
    cout << "-------------\n";
    cout << "Source:\n";
    cout << "-------------\n";
    arr[0].print();

    cout << "\n-------------\n";
    cout << "Copied and edited:\n";
    cout << "-------------\n";
    merka.print();

    /// Testing if array is OK

    cout << "\n-- Testing if array was inputted correctly --\n";

    for(int i = 0; i < n; i++)
        arr[i].print();

    return 0;
}
