/*Да се дефинира класа Student за која се чува:
    name(низа од карактери, динамички алоцирана) - неговото име
    age (цел број) - колку години има
    major (низа од карактери, динамички алоцирана) - што студира
За класата да се дефинира default конструктор, конструктор со аргументи и copy конструктор.
Потоа да се дефинира класа Classroom за која се чува:
    students (динамички алоцирана низа од Студенти)
    numStudents(int)
    capacity(int)
За класата да се дефинира  default конструктор и конструктор со аргументи. 
Треба за класата Classroom да се дефинираат следните методи:
    add - да се додаде нов студент
    remove - да се отстрани некој студент со дадено име name
    findMedianAge - наоѓа која е медијаната за години на стидентите во дадениот Classroom. 
Пример: 2 4 5 6 7 8 10
Медијана: 6
Пример: 2 4 5 7 8 10 12 20
Медијана: (7 + 8)/2
Мора да е растечки редослед!
По потреба може да се креираат get и set методи.
Сите студенти имаат уникатно име.
Да не се менува main функцијата.*/

#include <iostream>
#include <cstring>
using namespace std;
class Student{
    char *name;
    int age;
    char *major;
public:
   friend class Classroom;
    Student(char *name="", int age=0, char *major=""){
        this->name=new char[(strlen(name)+1)];
        strcpy(this->name,name);
        this->age=age;
        this->major=new char[(strlen(major)+1)];
        strcpy(this->major,major);
    }
    Student(const Student &s){
        this->name=new char[(strlen(s.name) + 1)];
        strcpy(this->name, s.name);
        this->age=s.age;
        this->major=new char[(strlen(s.major) + 1)];
        strcpy(this->major, s.major);
    }
    Student &operator= (const Student &st){
        if(this != &st){
            delete [] name;
            this->name= new char[strlen(st.name) + 1];
            strcpy(this->name, st.name);
            delete [] major;
            this->major= new char[strlen(st.major) + 1];
            strcpy(this->major, st.major);
            this->age = st.age;
        }
        return *this;
    }
    ~Student(){
        delete [] name;
        delete [] major;
    }

    char *getName() {
        return name;
    }

    void setName(char *a) {
        strcpy(name,a);
    }

    int getAge() const  {
        return age;
    }

    void setAge(int a) {
    age=a;
    }

    char *getMajor()  {
        return major;
    }

    void setMajor(char *a) {
    strcpy(major,a);
    }
    void print()
    {
        cout<<name<<" ("<<age<<", "<<major<<")"<<endl;
    }
};
class Classroom {
    Student *students;
    int numStudents;
    int capacity;
public:
    Classroom(Student *students=nullptr, int numStudents = 0, int capacity = 0) {
        this->students = new Student[numStudents];
        for (int i = 0; i < numStudents; i++) {
            this->students[i] = students[i];
        }
        this->numStudents = numStudents;
        this->capacity = capacity;
    }

    Classroom(const Classroom &cl) {
        this->students = new Student[cl.numStudents];
        for (int i = 0; i < cl.numStudents; i++) {
            this->students[i] = cl.students[i];
        }
        this->numStudents = cl.numStudents;
        this->capacity = cl.capacity;
    }

    Classroom &operator=(const Classroom &cla) {
        if (this != &cla) {
            delete[] students;
            this->students = new Student[cla.numStudents];
            for (int i = 0; i < cla.numStudents; i++) {
                this->students[i] = cla.students[i];
            }
            this->numStudents = cla.numStudents;
            this->capacity = cla.capacity;
        }
        return *this;
    }

    ~Classroom() {
        delete[] students;
    }

    Student getStudents(int i){
        return students[i];
    }

    void setStudents(Student *stu) {
        for (int i = 0; i < numStudents; i++)
            students[i] = stu[i];
    }

    int getNumStudents() const {
        return numStudents;
    }

    void setNumStudents(int num) {
        numStudents = num;
    }

    int getCapacity() const {
        return capacity;
    }

    void setCapacity(int c) {
        capacity = c;
    }

    void add(Student &student) {
        int i=0;
        Student *newMmry = new Student[numStudents + 1];
        while(i<numStudents){
            newMmry[i] = students[i];
            i++;
        }
        newMmry[numStudents] = student;
        delete[] students;
        students = newMmry;
        numStudents++;
    }
    void remove(char *name) {
    Student *newNiza = new Student[numStudents];
    int j = 0;
    int i = 0;
    while (i < numStudents) {
        if (strcmp(students[i].name, name) == 0) {
        } else {
            newNiza[j] = students[i];
            j++;
        }
        i++;
    }
    numStudents = j;
    delete[] students;
    students = newNiza;
}
    void printStudents()
    {
        int i=0;
        while(i<numStudents)
        {
            students[i].print();
            i++;
        }
        cout<<endl;
    }

};
void sortira(Classroom& classr, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = i; j < n; j++) {
            if (classr.getStudents(i).getAge() < classr.getStudents(j).getAge()) {
                Student temp = classr.getStudents(i);
                classr.getStudents(i) = classr.getStudents(j);
                classr.getStudents(j) = temp;
            }
        }
    }
}

double findMedianAge(Classroom classroom) {
    int nr = classroom.getNumStudents();
    double median = 0;
    sortira(classroom, nr);
    if (nr % 2 == 0) {
        median = (classroom.getStudents(nr / 2 - 1).getAge() + classroom.getStudents(nr / 2).getAge()) / 2.0;
    } else {
        median = classroom.getStudents(nr / 2).getAge();
    }
    return median;
}

//DO NOT CHANGE
int main() {
    int numClassrooms, numStudents;
    cin >> numClassrooms;
    Classroom classrooms[100];
    Student students[100];

    // Testing add method
    for (int i = 0; i < numClassrooms; i++) {
        cin >> numStudents;
        for (int j = 0; j < numStudents; j++) {
            char name[100], major[100];
            int age;
            cin >> name >> age >> major;
            Student student(name, age, major);
            classrooms[i].add(student);
            students[i*numStudents + j] = student;
        }
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }


    // Testing findMedianAge method
    int targetClassroom;
    cin >> targetClassroom;
    double medianAge = findMedianAge(classrooms[targetClassroom]);
    cout << "The median age in classroom " << targetClassroom << " is: " << medianAge << endl;
    cout<<"After removing the elements:"<<endl; /// Added 
    // Testing remove method
    cin >> numStudents;
    for (int j = 0; j < numStudents; j++) {
        char name[100];
        cin >> name;
        for (int i = 0; i < numClassrooms; i++) {
            classrooms[i].remove(name);
        }
    }
    for (int i = 0; i < numClassrooms; i++) {
        cout<<"Classroom "<<i<<endl;
        classrooms[i].printStudents();
    }

    return 0;
}
