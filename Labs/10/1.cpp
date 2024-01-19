/*Дадени ви се класите User и SocialNetwork. 
Во класата User се чуваат информации за корисничко име, возраст и број на пријатели во рамки на некоја социјална мрежа.
Во класата SocialNetwork се чува листа на членови (објекти од класата User) и големина на листата.
Да се дополни почетниот код со следните работи:
    Да се спречи додавање на корисник со веќепостоечко корисничко име преку фрлање исклучок од тип UserAlreadyExistsException. Справете се со исклучокот на потребното место. 
    Да се додаде променлива за лимитот на дозволени пријатели на еден корисник (цел број). Променливата да важи за сите корисници (објекти од класа User) и истата да може да се менува преку методот setLimit. Иницијално променливата да има вредност 3.
    Да се фрли исклучок од тип UserNotFoundException во методот friendRequest доколку friendRequest или secondUsername не се кориснички имиња на корисници во социјалната мрежа. Справете се со исклучокот на потребното место. 
    Да се спречи зголемување на бројот на пријатели на некој корисник (над дозволениот лимит) со исклучок од тип FriendsLimitExceededException. Справете се со исклучокот на потребното место.*/

#include<iostream>
#include<cstring>
using namespace std;

class UserAlreadyExistsException {
//TODO
char text[50];
public:
    UserAlreadyExistsException(char *text=""){
        strcpy(this->text,text);
    }
    void print(){
        cout<<"User with username "<<text<<" already exists!"<<endl;
    }
};

class UserNotFoundException {
//TODO
char text[50];
public:
UserNotFoundException(char *text=""){
        strcpy(this->text,text);
    }
    void print(){
        cout<<"User with username "<<text<<" was not found!"<<endl;
    }
};

class FriendsLimitExceededException {
//TODO
int n;
public:
    FriendsLimitExceededException(int n=0){
        this->n=n;
    }
    void print(){
        cout<<"Can't have more than "<<n<<" friends."<<endl;
    }
};

class User {
private:
    char username[50];
    int age;
    int friends;
    static int limit;
public:
    User(char *username = "", int age = 18) : age(age) {
        strcpy(this->username, username);
        friends = 0;
    }

    friend ostream &operator<<(ostream &os, const User &user) {
        os << "Username: " << user.username << " Age: " << user.age << " # of friends: " << user.friends;
        return os;
    }

    User &operator++() {
        ++friends;
        return *this;
    }
    static void setLimit(int a){
        limit=a;
    }
    friend class SocialNetwork;


};
int User::limit=3;
class SocialNetwork {
private:
    User *users;
    int n;
public:
    SocialNetwork() {
        n = 0;
        users = new User[n];
    }

    SocialNetwork &operator+=(User &u) {
    for(int i=0;i<n;i++){
        if(strcmp(u.username,users[i].username) == 0){
            throw UserAlreadyExistsException(u.username);
        }
    }
        User *tmp = new User[n + 1];
        for (int i = 0; i < n; i++) {
            tmp[i] = users[i];
        }
        tmp[n++] = u;
        delete[] users;
        users = tmp;
        return *this;
    }

    void friendRequest(char *firstUsername, char *secondUsername) {
        int zname1=0,zname2=0,ind1,ind2;
        for (int i = 0; i < n; i++) {
            if (strcmp(users[i].username, firstUsername) == 0) {
                zname1=1;
                ind1=i;
                for (int j = 0; j < n; j++) {
                    if (strcmp(users[j].username, secondUsername) == 0) {
                        zname2=1;
                        ind2=j;
                        if(users[ind1].friends>=User::limit||users[ind2].friends>=User::limit){
                            throw FriendsLimitExceededException(User::limit);
                        }
                        ++users[i];
                        ++users[j];
                        return;
                    }
                }
            }
        }
        if(!zname2){
        throw  UserNotFoundException(secondUsername);
        }
        else{
            throw  UserNotFoundException(firstUsername);
        }
    }


    friend ostream &operator<<(ostream &os, const SocialNetwork &network) {
        os << "Users: " << endl;
        for (int i=0;i<network.n;i++) {
            os << network. users[i] << endl;
        }
        return os;
    }
};


int main() {
    SocialNetwork sn;
    int n;
    cin >> n;
    for (int i=0;i<n;i++){
        char username[50]; int age;
        cin >> username >> age;
        User u(username, age);
        try {
            sn += u;
        }
        catch (UserAlreadyExistsException exception){
            exception.print();
        }
    }

    cout << "Registration of users " << endl;
    cout << sn << endl;
    cout << "Friend requests " << endl;

    int friendships;
    cin >> friendships;
    for (int i=0;i<friendships;i++){
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try {
            sn.friendRequest(username1, username2);
        }
        catch(UserNotFoundException exception){
            exception.print();
        }
        catch (FriendsLimitExceededException exception){
            exception.print();
        }
    }

    cout << sn << endl;

    cout << "CHANGE STATIC VALUE" << endl;

    int maxFriends;
    cin >> maxFriends;
    cin >> friendships;
    User::setLimit(maxFriends);
    for (int i=0;i<friendships;i++){
        char username1[50], username2[50];
        cin >> username1 >> username2;
        try {
            sn.friendRequest(username1, username2);
        }
        catch(UserNotFoundException exception){
            exception.print();
        }
        catch (FriendsLimitExceededException exception){
            exception.print();
        }
    }
    cout << sn;
    return 0;
}
