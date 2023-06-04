/*Да се креира класа која претставува слика (Image) во рамките на еден компјутер. За секоја датотека се чуваат (5 поени):
    име на сликата (дин. алоцирана низа од знаци). Предефинирано поставено на untitled.
    име на корисникот кој е сопственик на датотеката (низа од макс. 50 знаци). Предефинирано поставено на unknown.
    димензии на сликата (2 цели броеви кои претставуваат ширина и висина во пиксели). Предефинирано поставени на 800.
Од класата Imageда се изведе класата TransparentImage, која претставува слика која содржи поддржува транспарентност. За транспарентна слика дополнително се чува :
    дали поддржува нивоа на транспарентност (bool променлива, предефинирано не поддржува транспарентност).
За класите Image и TransparentImage да биде достапна метода (fileSize)за пресметка на големината на сликата (во бајти). Големината се пресметува на сл. начин (5 поени):
    за објектите од класата Image, големината на датотеката е еднаква на:висината * ширината * 3.
    за TransparentImage, доколку поддржува нивоа на транспарентност, големината на датотеката е еднаква на ширина * висина * 4. Доколку не поддржува транспарентност, големината на сликата се пресметува како ширина * висина + бр._на_пиксели_присутни_во_сликата / 8.
За класите Image и TransparentImage да се преоптоварат следниве оператори (5 поени):
    оператор << кој ги печати податоците од датотеката во сл. формат:
    ime_fajl avtor golemina_na_fajlot_vo_bajti
    оператор > кој ги споредува сликите според нивната големина.
Да се дефинира класа Folder, што репрезентира директориум во кој може да се поставуваат слики. За секој фолдер се чува (5 поени):
    име на фолдерот (низа од макс 255 знаци)
    име на корисникот кој е сопственик на фолдерот (низа од макс. 50 знаци). Предефинирано поставено на unknown.
    низа од покажувачи кон Image објекти (макс. 100 во рамките на еден фолдер).
Да се имплементираат следниве методи (5 поени):
    метода за пресметка на големината на фолдерот (folderSize). Големината на фолдерот е сума од големините од сите слики во рамките на фолдерот.
    метода за пронаоѓање на наголемата слика во рамките на фолдерот (getMaxFile). Методата враќа покажувач кон најголемата слика во фолдерот (сметано во бајти).
За класата Folder да се имплементира и оператор += кој додава објекти од типот Image/TransparentImage во рамките на фолдерот (5 поени).
Да се креираат следниве функционалности за класите (5 поени):
    operator << - со кој се печатат податоците за фолдерот во формат (5 поени):
    ime_folder sopstvenik --
        imeslika avtor goleminanafajlotvo_bajti
        imeslika avtor goleminanafajlotvobajti -- goleminanafoldervo_bajti
    operator [] - кој враќа покажувач кон соодветната слика во фолдерот. Доколку не постои слика на тој индекс, треба да се врати NULL (5 поени).
Да се креира и глобална функција max_folder_size која го прима низа од објекти од типот Folder и го враќа фолдерот кој има зафаќа најмногу простор (во бајти). (5 поени)
Да се овозможи правилно функционирање на класите (потребни set или get методи/оператори/конструктори/деструктори) според изворниот код кој е веќе зададен. Сите податочни членови на класите се protected. (5 поени)*/

//NOTICE:ako imash problem so testcase2 stavi ja default vrednosta na transparentnost=true 

#include <iostream>
#include <cstring>
using namespace std;

class Image{
protected:
    char *ime;
    char korisnik[50];
    int sirina;
    int visina;
public:
    Image(char *ime="untitled", char *korisnik="unknown",int sirina=800,int visina=800) {
        this->ime=new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        strcpy(this->korisnik,korisnik);
        this->visina=visina;
        this->sirina=sirina;
    }
    Image(const Image &i){
        this->ime=new char[strlen(i.ime)+1];
        strcpy(this->ime,i.ime);
        strcpy(this->korisnik,i.korisnik);
        this->sirina=i.sirina;
        this->visina=i.visina;
    }
    Image &operator=(const Image &i){
        if(this!=&i){
            delete [] ime;
            this->ime=new char[strlen(i.ime)+1];
            strcpy(this->ime,i.ime);
            strcpy(this->korisnik,i.korisnik);
            this->sirina=i.sirina;
            this->visina=i.visina;
        }
        return *this;
    }
    virtual int fileSize() {
        return visina*sirina*3;
    }
    friend ostream &operator<<(ostream &out,Image &i){
        out<<i.ime<<" "<<i.korisnik<<" "<<i.fileSize()<<endl;
        return out;
    }
    virtual void print(){
        cout<<ime<<" "<<korisnik<<" "<<fileSize()<<endl;
    }
    bool operator >(Image &im){
        return fileSize()>im.fileSize();
    }
    virtual ~Image(){
        delete [] ime;
    }
};
class TransparentImage:public Image{
protected:
    bool transparentnost;
public:
    TransparentImage(char *ime="untitled", char *korisnik="unknown", int sirina=800,int visina=800,bool transparentnost=true): Image(ime,korisnik,sirina,visina){
        this->transparentnost=transparentnost;
    }
    TransparentImage(const TransparentImage& ti): Image(ti){
        this->transparentnost = ti.transparentnost;
    }
    int fileSize(){
        if(transparentnost){
            return visina*sirina*4;
        }
        else{
            return sirina*visina+(sirina*visina)/8;
        }
    }
    friend ostream &operator<<(ostream &out,TransparentImage &ti){
        out<<ti.ime<<" "<<ti.korisnik<<" "<<ti.fileSize()<<endl;
        return out;
    }
    void print(){
        cout<<ime<<" "<<korisnik<<" "<<fileSize()<<endl;
    }
    bool operator >(TransparentImage &tim){
        return fileSize()>tim.fileSize();
    }
    ~TransparentImage(){}
};
class Folder{
protected:
    char ime[255];
    char korisnik[50];
    Image *images[100];
    int n;
public:
    Folder(char *ime="unknown", char *korisnik="unknown") {
        strcpy(this->ime,ime);
        strcpy(this->korisnik,korisnik);
        for(int i=0;i<100;i++){
            this->images[i]=nullptr;
        }
        this->n=0;
    }
    int folderSize(){
        int vk=0;
        for(int i=0;i<n;i++){
            vk+=images[i]->fileSize();
        }
        return vk;
    }
    Image *getMaxFile(){
        int indeks=0;
        int max=images[0]->fileSize();
        for(int i=0;i<n;i++){
            if(images[i]->fileSize()>max){
                max=images[i]->fileSize();
                indeks=i;
            }
        }
        return images[indeks];
    }
    /*
    Folder &operator+=(Image &im){
        for(int i=0;i<n;i++) {
            if(n<100) {
                if (dynamic_cast<TransparentImage *>(&im) != nullptr) {
                    images[n++] = dynamic_cast<TransparentImage *>(&im);
                } else {
                    images[n++] = &im;
                }
            }
        }
        return *this;
    }*/
    Folder &operator +=(Image &i){
        this->images[n++]=&i;
        return *this;
    }

    Folder &operator+=(TransparentImage &i)
    {
        this->images[n++]=&i;
        return *this;
    }
    friend ostream &operator<<(ostream &out,Folder &f){
        out<<f.ime<<" "<<f.korisnik<<endl;
        out<<"--"<<endl;
        for(int i=0;i<f.n;i++) {
         if (f.images[i] != nullptr) {
            f.images[i]->print();
        }
        }
        out<<"--"<<endl;
        out<<"Folder size: "<<f.folderSize()<<endl;
        return out;
    }
    Image *operator[](int indeks){
            if (indeks<0||indeks>=n) {
                return NULL;
            }
            else{
                Image *tmp=images[indeks];
                return tmp;
            }
        }
};

Folder &max_folder_size(Folder *f, int n) {
    int indeks=0,max;
    max=f[0].folderSize();
    for(int i=0;i<n;i++){
        if(f[i].folderSize()>max){
            max=f[i].folderSize();
            indeks=i;
        }
    }
    return f[indeks];
}
int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        cout<<max_folder_size(dir_list, folders_num);
    }
    return 0;
}
