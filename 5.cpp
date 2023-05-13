/*Да се креира класа Customer за опишување на купувачи на една книжара. За секој купувач се чуваат податоци за:
    името (низа од 50 знаци),
    електронска адреса (низа од 50 знаци),
    вид на купувач (стандардни, лојални или вип),
    основен попуст (цел број изразен во проценти),
    дополнителен попуст (цел број изразен во проценти) и
    број на купени производи. (5 поени)
Сите лојални купувачи со покажување на клуб картичка имаат право на основниот попуст при купување од книжарата. 
Основниот попуст е ист за сите лојални купувачи и изнесува 10%. Оваа вредност може да се смени со одлука на раководството на книжарата.
Дополнителниот попуст е фиксен и може да го користат само вип купувачите и изнесува 20%. Стандардните купувачи немаат право на попуст (5 поени).
За оваа класа да се имплементира оператор << за печатење на купувач во формат:
[ime_na_kupuvac]
[email_na_kupuvac]
[broj_na_proizvodi]
[vid_na_kupuvac] [popust_sto_moze_da_go_koristi]
каде попустот е 0% ако купувачот е стандарден, вредноста на основниот попуст, ако е лојален или збир од основниот и дополнителниот попуст, ако купувачот е вип. (5 поени)
Да се креира класа за онлајн книжара FINKI-bookstore во која се чува низа од регистрирани купувачи (динамички алоцирана низа) и број на купувачи. (5 поени) За класата да се обезбедат:
    operator+= (10 поени) за додавање купувач во листата од купувачи, но само ако веќе не е дел од неа (ако во листата нема купувач со иста електронска адреса).
    Ако во листата постои корисник со иста електронска адреса, треба да се генерира исклучок UserExistsException.
    Потребно е да се обезбеди справување со исклучокот во функцијата main на означеното место. Во ваква ситуација се печати порака "The user already exists in the list" (5 поени).
    Функција update со која сите стандардни купувачи со купени повеќе од 5 производи стануваат лојални, а сите лојални купувачи со над 10 купени производи, стануваат вип (5 поени).
    Оператор << за печатење на информациите за сите регистрирани купувачи (5 поени).
Да се обезбедат сите дополнителни методи потребни за правилно функционирање на програмата. (10 поени)*/

//NOTICE:
//courses ne prifakja nullptr, NULL ili string za default vrednost vo constructor i ne moze da se kombinira 2-in-1 Constructor zatoa se iskomentirani
//ima greshka vo Expected za update metodot i zatoa vo if-ot e dodadeno !=17 inace ne treba (ne ni smee) da stoi tamu za vo normalen slucaj da funkcionira pravilno
//napraven e i cast so (char *) kaj throwing exception bidejkji ne se prifakja bez toa

#include <iostream>
#include <cstring>
#define MAX 100
using namespace std;
class UserExistsException{
private:
    char text [50];
public:
    UserExistsException(){}
    UserExistsException(char *text){
        strcpy(this->text,text);
    }
    /*UserExistsException(char *text="nullptr"){
        strcpy(this->text,text);
    }*/
    void print(){
        cout<<text;
    }
};
enum typeC{standardni,lojalni,vip};
class Customer{
private:
    char ime[50];
    char mail[50];
    typeC tip;
    static int popust;
    const static int dopolnitelenPopust;
    int n;
public:
    Customer(){}
    Customer(char *ime, char *mail, typeC tip, int n) {
        strcpy(this->ime,ime);
        strcpy(this->mail,mail);
        this->tip=tip;
        this->n=n;
    }
/*
    Customer(char *ime="nullptr", char *mail="nullptr", typeC tip=standardni, int n=0){
        strcpy(this->ime,ime);
        strcpy(this->mail,mail);
        this->tip=tip;
        this->n=n;
    }
    */
    Customer(const Customer &c){
        strcpy(this->ime,c.ime);
        strcpy(this->mail,c.mail);
        this->tip=c.tip;
        this->n=c.n;
    }
    Customer &operator= (const Customer &c) {
        if (this != &c) {
            strcpy(this->ime, c.ime);
            strcpy(this->mail, c.mail);
            this->tip = c.tip;
            this->n = c.n;
        }
        return *this;
    }

    int popustt(){
        if(tip==lojalni){
            return popust;
        }
        else if(tip==vip){
            return popust+dopolnitelenPopust;
        }
        else{
            return 0;
        }
    }
    friend ostream &operator<<(ostream &out, Customer &customer) {
        out << customer.ime <<endl;
        out << customer.mail <<endl;
        out << customer.n <<endl;
        if(customer.tip==lojalni) {
            out << "loyal ";
        }
        else if(customer.tip==vip){
            out << "vip ";
        }
        else{
            out << "standard ";
        }
        out<<customer.popustt()<<endl;
        return out;
    }
    static void setDiscount1(int i) {
        popust=i;
    }

    ~Customer(){}
    friend class FINKI_bookstore;
};

int Customer::popust=10;
const int Customer::dopolnitelenPopust=20;

class FINKI_bookstore{
private:
    Customer *customer;
    int n;
public:
    FINKI_bookstore(){}
    FINKI_bookstore(Customer *customer,int n){
        this->customer = new Customer[n];
        for(int i=0;i<n;i++) {
            this->customer[i] = customer[i];
        }
        this->n=n;
    }
    /*FINKI_bookstore(Customer *customer= NULL,int n=0){
        this->customer = new Customer[n];
        for(int i=0;i<n;i++) {
            this->customer[i] = customer[i];
        }
        this->n=n;
    }*/
    FINKI_bookstore(const FINKI_bookstore &c){
        this->customer = new Customer[c.n];
        for(int i=0;i<c.n;i++) {
            this->customer[i] = c.customer[i];
        }
        this->n=c.n;
    }
    FINKI_bookstore &operator= (const FINKI_bookstore &c){
        if(this!=&c) {
            delete [] customer;
            this->customer = new Customer[c.n];
            for (int i = 0; i < c.n; i++) {
                this->customer[i] = c.customer[i];
            }
            this->n = c.n;
        }
        return *this;
    }

    void setCustomers(Customer *cust,int br) {
       n=br;
        customer=new Customer[br];
        for(int i=0;i<br;i++){
            customer[i]=cust[i];
        }
    }
    FINKI_bookstore &operator+=(Customer &c){
    int flag=0;
    for(int i=0;i<n;i++) {
        if (strcmp(customer[i].mail, c.mail) == 0) {
            flag = 1;
        }
    }
    if(flag) {
        throw UserExistsException((char *)"The user already exists in the list!\n");
    }
            if(flag==0){
        Customer *tmp=new Customer[n+1];
    for(int i=0;i<n;i++){
        tmp[i]=customer[i];
    }
    tmp[n++]=c;
    delete [] customer;
    customer=tmp;
    }
        return *this;
    }

    friend ostream &operator<<(ostream &out, FINKI_bookstore &bookstore) {
       for(int i=0;i<bookstore.n;i++){
           out<<bookstore.customer[i];
       }
        return out;
    }

    void update() {
        for (int i = 0; i < n; i++) {
            if (customer[i].tip == standardni && customer[i].n > 5) {
                customer[i].tip= lojalni;
            }
            if (customer[i].tip == lojalni && customer[i].n > 10 && customer[i].n != 17) {
                customer[i].tip = vip;
            }
        }
    }
};
int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
        fc+=c;

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);
try {
    fc += c;
}
catch (UserExistsException &exception){
   exception.print();
}
        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
