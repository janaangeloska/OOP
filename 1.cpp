/*Издавачката куќа FINKI-Education издава онлајн и печатени книги. За секоја книга се чуваат податоци за ISBN бројот (низа од најмногу 20 знаци),
насловот (низа од најмногу 50 знаци), авторот (низа од најмногу 30 знаци) и основната цена изразена во $ (реален број).
Класата за опишување на книгите е апстрактна (5 поени).
За секоја онлајн книга дополнително се чуваат податоци за url од каде може да се симне (динамички резервирана низа од знаци) 
и големината изразена во MB (цел број). За секоја печатена книга дополнително се чуваат податоци за масата изразена во килограми (реален број) 
и дали ја има на залиха (логичка променлива). (5 поени)
За секој објект од двете изведени класи треба да бидат на располагање следниве методи:
    Метод bookPrice, за пресметување на продажната цена на книгата на следниот начин: (10 поени)
        За онлајн книга - цената се зголемува за 20% од основната цена ако книгата е поголема од 20MB
        За печатена книга - цената се зголемува за 15% од основната цена ако масата на книгата е поголема од 0.7kg
    Преоптоварен оператор > за споредба на две книги од каков било вид според нивната цена. (5 поени)
    Преоптоварен оператор << за печатење на податоците за книгите во формат: (5 поени)
Да се имплементира функција mostExpensiveBook со потпис:
void mostExpensiveBook (Book** books, int n)
во која се печати вкупниот број на онлајн, односно, печатени книги во проследената низа посебно. (5 поени) Потоа се наоѓа и печати најскапата книга. (5 поени)
Да се обезбедат сите потребни функции за правилно функционирање на програмата. (5 поени)*/

#include<iostream>
#include <cstring>
using namespace std;
class Book{
protected:
    char ISBN[20];
    char ime[50];
    char avtor[30];
    double cena;
public:
    Book(char *ISBN="", char *ime="", char *avtor="", double cena=0) {
        strcpy(this->ISBN, ISBN);
        strcpy(this->ime, ime);
        strcpy(this->avtor, avtor);
        this->cena = cena;
    }
    virtual double bookPrice()=0;
    bool operator > (Book &b) const{
        return this->cena>b.cena;
   }

    friend ostream &operator<<(ostream &out, Book &book) {
        out << book.ISBN << ": " << book.ime << ", " << book.avtor << " " << book.bookPrice()<<endl;
        return out;
    }

    void setISBN(char *a) {
        strcpy(ISBN,a);
    }
virtual ~Book(){}
};
class OnlineBook : public Book{
    char *url;
    int MB;
public:
    OnlineBook(char *ISBN="", char *ime="", char *avtor="", double cena=0,char *url="",int MB=0) : Book(ISBN,ime,avtor,cena){
        this->url=new char[strlen(url)+1];
        strcpy(this->url,url);
        this->MB=MB;
    }
    OnlineBook(const OnlineBook &b){
        strcpy(this->ISBN, b.ISBN);
        strcpy(this->ime, b.ime);
        strcpy(this->avtor, b.avtor);
        this->cena = b.cena;
        this->url=new char[strlen(b.url) + 1];
        strcpy(this->url, b.url);
        this->MB=b.MB;
    }
    OnlineBook &operator=(const OnlineBook &b){
        if(this!=&b){
            strcpy(this->ISBN, b.ISBN);
            strcpy(this->ime, b.ime);
            strcpy(this->avtor, b.avtor);
            this->cena = b.cena;
            delete [] url;
            this->url=new char[strlen(b.url)+1];
            strcpy(this->url,url);
            this->MB=b.MB;
        }
        return *this;
    }

    double bookPrice(){
        if(MB>20){
            return cena+(cena*0.2);
        }
        else{
            return cena;
        }
    }
     ~OnlineBook(){
        delete [] url;
    }
};


class PrintBook : public Book{
    double masa;
    bool dostapnost;
public:
    PrintBook(char *ISBN="", char *ime="", char *avtor="", double cena=0,double masa=0,bool dostapnost=false) : Book(ISBN,ime,avtor,cena){
        this->masa=masa;
        this->dostapnost=dostapnost;
    }
    double bookPrice(){
        if(masa>0.7){
            return cena+(cena*0.15);
        }
        else {
            return cena;
        }
    }
    ~PrintBook(){}
};
void mostExpensiveBook (Book** books, int n){
    int indeks,online=0,pecateni=0;
    Book *max=books[0];
    for(int i=0;i<n;i++){
        OnlineBook *pok = dynamic_cast<OnlineBook*>(books[i]);
        if(pok!=0){
            online++;
        }
        else{
            pecateni++;
        }
        if(*books[i]>*max){
            max=books[i];
            indeks=i;
        }
    }
    cout<<"FINKI-Education" << endl;
    cout<<"Total number of online books: "<<online<<endl;
    cout<<"Total number of print books: "<<pecateni<<endl;
    cout<<"The most expensive book is: "<<endl;
    cout<<*books[indeks];
}
int main(){
	char isbn[20], title[50], author[30], url[100];
	int size, tip;
	float price, weight;
	bool inStock;
	Book  **books;
	int n;

	int testCase;
	cin >> testCase;

	if (testCase == 1){
		cout << "====== Testing OnlineBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> url;
			cin >> size;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new OnlineBook(isbn, title, author, price, url, size);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 2){
		cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
		cin >> isbn;
		cin.get();
		cin.getline(title, 50);
		cin.getline(author, 30);
		cin >> price;
		cin >> url;
		cin >> size;
		cout << "CONSTRUCTOR" << endl;
		OnlineBook ob1(isbn, title, author, price, url, size);
		cout << ob1 << endl;
		cout << "COPY CONSTRUCTOR" << endl;
		OnlineBook ob2(ob1);
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
		cout << "OPERATOR =" << endl;
		ob1 = ob2;
		cin >> isbn;
		ob2.setISBN(isbn);
		cout << ob1 << endl;
		cout << ob2 << endl;
	}
	if (testCase == 3){
		cout << "====== Testing PrintBook class ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i < n; i++){
			cin >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			cin >> weight;
			cin >> inStock;
			cout << "CONSTRUCTOR" << endl;
			books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			cout << "OPERATOR <<" << endl;
			cout << *books[i];
		}
		cout << "OPERATOR >" << endl;
		cout << "Rezultat od sporedbata e: " << endl;
		if (*books[0] > *books[1])
			cout << *books[0];
		else
			cout << *books[1];
	}
	if (testCase == 4){
		cout << "====== Testing method mostExpensiveBook() ======" << endl;
		cin >> n;
		books = new Book *[n];

		for (int i = 0; i<n; i++){

			cin >> tip >> isbn;
			cin.get();
			cin.getline(title, 50);
			cin.getline(author, 30);
			cin >> price;
			if (tip == 1) {

				cin >> url;
				cin >> size;

				books[i] = new OnlineBook(isbn, title, author, price, url, size);

			}
			else {
				cin >> weight;
				cin >> inStock;

				books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
			}
		}

		mostExpensiveBook(books, n);
	}

	for (int i = 0; i<n; i++) delete books[i];
		delete[] books;
	return 0;
}
