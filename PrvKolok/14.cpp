/*Потребно е да се имплементираат класи File (датотека) и Folder (директориум) за работа со едноставен податочен систем.
Во класата File треба да се чуваат следниве податоци:
    Име на датотеката (динамички алоцирана низа од знаци)
    Екстензија на датотеката (енумерација со можни вредности: txt, pdf, exe)
    Име на сопственикот на датотеката (динамички алоцирана низа од знаци)
    Големина на датотеката (цел број на мегабајти)
Дополнително, во класата потребно е да се напишат и:
    Конструктор без параметри
    Конструктор со параметри
    Конструктор за копирање
    Деструктор
    Преоптоварување на операторот =
    Метод за печатење на информациите за една датотека (видете го излезот од тест примерите за структурата на печатење) - print()
    Метод за проверка на еднаквост помеѓу две датотеки со потпис bool equals(const File & that) кој ќе враќа true ако датотеките имаат исто име, екстензија и сопственик
    Метод за споредба на типот помеѓу две датотеки со потпис bool equalsType(const File & that) кој ќе враќа true ако датотеките се од ист тип, т.е. имаат исто име и екстензија
Во класата Folder треба да се чуваат следниве податоци:
    Име на директориумот (динамички алоцирана низа од знаци)
    Број на датотеки во него (на почеток директориумот е празен)
    Динамички алоцирана низа од датотеки, објекти од класата File
Дополнително, во класата потребно е да се напишат и:
    Конструктор со потпис Folder(const char* name)
    Деструктор
    Метод за печатење на информациите за еден директориум (видете го излезот од тест примерите за структурата на печатење) - print()
    Метод за бришење на датотека од директориумот со потпис void remove(const File & file) кој ќе ја избрише првата датотека од директориумот која е еднаква според equals методот
    Метод за додавање на датотека во директориумот со потпис void add(const File & file) кој ќе додава датотеката во директориумот
Не го менувајте почетниот код.*/

#include<iostream>
#include<cstring>
using namespace std;
enum Extension{pdf=0,txt=1,exe=2};
class File{
    char *ime;
    enum Extension ext;
    char *sopstvenik;
    int golemina;
public:
    File(char *ime="", char *sopstvenik="", int golemina=0,enum Extension ext=txt) {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->ext=ext;
        this->sopstvenik=new char[strlen(sopstvenik)+1];
        strcpy(this->sopstvenik,sopstvenik);
        this->golemina=golemina;
    }
    File(const File &f) {
        this->ime=new char[strlen(f.ime)+1];
        strcpy(this->ime,f.ime);
        this->ext=f.ext;
        this->sopstvenik=new char[strlen(f.sopstvenik)+1];
        strcpy(this->sopstvenik,f.sopstvenik);
        this->golemina=f.golemina;
    }
    File &operator=(const File &f) {
        if (this != &f) {
            delete[] ime;
            this->ime = new char[strlen(f.ime) + 1];
            strcpy(this->ime, f.ime);
            this->ext = f.ext;
            delete [] sopstvenik;
            this->sopstvenik = new char[strlen(f.sopstvenik) + 1];
            strcpy(this->sopstvenik, f.sopstvenik);
            this->golemina = f.golemina;
        }
        return *this;
    }

    char *getIme() const {
        return ime;
    }

    void setIme(char *i) {
        strcpy(ime,i);
    }

    enum Extension getTip() const {
        return ext;
    }

    void setTip(enum Extension t) {
        ext = t;
    }

    char *getSopstvenik() const {
        return sopstvenik;
    }

    void setSopstvenik(char *s) {
        strcpy(sopstvenik, s);
    }

    int getGolemina() const {
        return golemina;
    }

    void setGolemina(int g) {
        golemina = g;
    }
~File(){
        delete[]ime;
        delete[]sopstvenik;
    }
    void print(){
        cout<<"File name: "<<ime;
        if(this->ext == pdf)
            cout<<".pdf"<<endl;
        if(this->ext == txt)
            cout<<".txt"<<endl;
        if(this->ext == exe)
            cout<<".exe"<<endl;
        cout<<"File owner: "<<sopstvenik<<endl;
        cout<<"File size: "<<golemina<<endl;
    }
    bool equals(const File & that){
        if(!(strcmp(ime,that.ime)) && ext == that.ext && !(strcmp(sopstvenik, that.sopstvenik)))
            return true;
        else{
            return false;
        }
    }
    bool equalsType(const File & that){
        if(!(strcmp(ime,that.ime)) && ext == that.ext)
            return true;
        else{
            return false;
        }
    }
};
class Folder{
    char *imeNaDirektorium;
    int n;
    File *files;
public:
    Folder(const char* name){
        imeNaDirektorium=new char[strlen(name)+1];
        strcpy(imeNaDirektorium,name);
        this->n=0;
        this->files= nullptr;
    }
    Folder(const Folder &f){
        imeNaDirektorium=new char[strlen(f.imeNaDirektorium)];
        strcpy(imeNaDirektorium,f.imeNaDirektorium);
        n=f.n;
        files=new File[n];
        for(int i=0;i<n;i++){
            this->files[i]=f.files[i];
        }
    }
    Folder&operator=(const Folder &f){
        delete[]imeNaDirektorium;
        imeNaDirektorium=new char[strlen(f.imeNaDirektorium)];
        strcpy(imeNaDirektorium,f.imeNaDirektorium);
        n=f.n;
        delete[]files;
        files=new File[n];
        for(int i=0;i<n;i++){
            this->files[i]=f.files[i];
        }
    }
    ~Folder(){
        delete [] imeNaDirektorium;
        delete [] files;
    }
    void print(){
        cout<<"Folder name: "<<imeNaDirektorium<<endl;
        for(int i=0;i<n;i++){
            files[i].print();
        }
    }
    // void remove(const File & file) {
    //     int a=0,j, i, flag = -1;
    //     File *tmp = new File[n-1];
    //     for (i = 0; i < n; i++) {
    //         if (files[i].equals(file)) {
    //             flag = i;
    //             break;
    //         }
    //     }
    //     if (flag!=-1) {
    //         for (j = 0; j < n; j++) {
    //             tmp[a++] = files[j];
    //         }
    //         n--;
    //         delete[]files;
    //         files=tmp;
    //     }
    // }
    void remove(const File& file) {
    int i, j, flag = -1;
    File* tmp = new File[n - 1];
    for (i = 0; i < n; i++) {
        if (files[i].equals(file)) {
            flag = i;
            break;
        }
    }
    if (flag != -1) {
        for (j = 0, i = 0; i < n; i++) {
            if (i != flag) {
                tmp[j++] = files[i];
            }
        }
        n--;
        delete[] files;
        files = tmp;
    } else {
        delete[] tmp;
    }
}
    void add(const File & file){
        File *tmp=new File[n+1];
        for(int i=0;i<n;i++){
            tmp[i]=files[i];
        }
        tmp[n++]=file;
        delete[]files;
        files=tmp;
    }
};
int main() {
    char fileName[20];
    char fileOwner[20];
    int ext;
    int fileSize;

    int testCase;
    cin >> testCase;
    if (testCase == 1) {
        cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File created = File(fileName, fileOwner, fileSize, (Extension) ext);
        File copied = File(created);
        File assigned = created;

        cout << "======= CREATED =======" << endl;
        created.print();
        cout << endl;
        cout << "======= COPIED =======" << endl;
        copied.print();
        cout << endl;
        cout << "======= ASSIGNED =======" << endl;
        assigned.print();
    }
    else if (testCase == 2) {
        cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File first(fileName, fileOwner, fileSize, (Extension) ext);
        first.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File second(fileName, fileOwner, fileSize, (Extension) ext);
        second.print();

        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File third(fileName, fileOwner, fileSize, (Extension) ext);
        third.print();

        bool equals = first.equals(second);
        cout << "FIRST EQUALS SECOND: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equals = first.equals(third);
        cout << "FIRST EQUALS THIRD: ";
        if (equals)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        bool equalsType = first.equalsType(second);
        cout << "FIRST EQUALS TYPE SECOND: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

        equalsType = second.equals(third);
        cout << "SECOND EQUALS TYPE THIRD: ";
        if (equalsType)
            cout << "TRUE" << endl;
        else
            cout << "FALSE" << endl;

    }
    else if (testCase == 3) {
        cout << "======= FOLDER CONSTRUCTOR =======" << endl;
        cin >> fileName;
        Folder folder(fileName);
        folder.print();

    }
    else if (testCase == 4) {
        cout << "======= ADD FILE IN FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        folder.print();
    }
    else {
        cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
        char name[20];
        cin >> name;
        Folder folder(name);

        int iter;
        cin >> iter;

        while (iter > 0) {
            cin >> fileName;
            cin >> fileOwner;
            cin >> fileSize;
            cin >> ext;

            File file(fileName, fileOwner, fileSize, (Extension) ext);
            folder.add(file);
            iter--;
        }
        cin >> fileName;
        cin >> fileOwner;
        cin >> fileSize;
        cin >> ext;

        File file(fileName, fileOwner, fileSize, (Extension) ext);
        folder.remove(file);
        folder.print();
    }
    return 0;
}
