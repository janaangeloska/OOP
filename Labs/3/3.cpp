/*Да се дефинира класа Employee во која ќе се чуваат информации за:
    name(низа од максимум 100 карактери) -име на вработениот
    surname(низа од максимум 100 карактери) - презиме
    salary(цел број) - колку му е платата
методи кои што класата треба да ги има:
    print() 
-Принта во формат:
Employee name: 
Employee surname: 
Employee salary: 
Да се дефинира класа TechCompany во која ќе се чуваат информации за:
    name(низа од максимум 100 карактери) -име на фирмата
    employees(низа од вработени) 
    numOfEmployees(цел број) - колку вработени има во фирмата 
методи кои што класата треба да ги има:
    print() 
-Принта во формат:
Tech company name: 
Number of employees: 
     double getAverageOfEmployeeсSalary()
-Враќа средна врендност од платите на секој вработен во таа фирма
Сите променливи внатре во класите треба да бидат приватни. Соодветно во рамките на класите да се дефинираат:
    конструктор (без и со параметри)
    деструктор
    set методи
    get методи
    copy constructor
Функции надвор од класата:
    printCompanyWithHighestAverageSalary(TechCompany companies[], int numCompanies)
-Го враќа TechCompany објектот што има најголема средна вредност за плати на неговите вработени
    printCompanyWithHighestStdSalary(TechCompany companies[], int numCompanies)
-Го враќа TechCompany објектот што има најголема стандардна девијација за плати на неговите вработени
VAR=∑for each Employee e[(e.salary−AVG)2]n−1STD=(√VAR)
-Помош: AVG е средната вредност на платите на сите вработен во таа фирма, STD е стандардна девијација, VAR  е помошна променлива. И прво квадрирајте го изразот па потоа додадете го во сумата!
    isSameCompany(TechCompany company1, TechCompany company2)
-Враќа boolean вредност: две фирми се исти ако имаат исто име. Треба само да се првери дали им е исто името!
ДА НЕ СЕ МЕНУВА MAIN ФУНКЦИЈАТА.*/

#include <iostream>
#include<cstring>
#include <cmath>
using namespace std;
class Employee{
private:
    char name[100];
    char surname[100];
    int salary;
public:
    Employee(){}
    Employee(char *name, char *surname, int salary){
        strcpy(this->name,name);
        strcpy(this->surname,surname);
        this->salary=salary;
    }
    Employee(const Employee &e){
        strcpy(this->name,e.name);
        strcpy(this->surname,e.surname);
        this->salary=e.salary;
    }
    ~Employee(){}
    char *getName() {
        return name;
    }
    char *getSurname()  {
        return surname;
    }
    int getSalary() const {
        return salary;
    }
    void setSalary(int s) {
        salary=s;
    }
    void setName(char *n){
        strcpy(name,n);
    }
    void setSurname(char *sn){
        strcpy(surname,sn);
    }
    void printEmployee(){
        cout<<"Employee name: "<<name<<endl;
        cout<<"Employee surname: "<<surname<<endl;
        cout<<"Employee salary: "<<salary<<endl;
    }
    friend class TechCompany;
};
class TechCompany{
    char name[100];
    Employee employees[20];
    int numOfEmployees;
public:
    TechCompany(char *name="", int numOfEmployees=0) {
        strcpy(this->name,name);
        this->numOfEmployees=numOfEmployees;
    }
    TechCompany(char *name, const Employee &employees, int numOfEmployees) {
        strcpy(this->name,name);
        this->numOfEmployees=numOfEmployees;
    }

    TechCompany(const TechCompany &t) {
        strcpy(name,t.name);
        for(int i=0;i<t.numOfEmployees;i++){
            employees[i]=t.employees[i];
        }
        numOfEmployees=t.numOfEmployees;
    }
    char *getName() {
        return name;
    }
    Employee getEmployee(int n) {
        return employees[n];
    }
    int getNumEmployees() const {
        return numOfEmployees;
    }
    void setName(char *a){
        strcpy(name,a);
    }
    void setNumOfEmployees(int a) {
        numOfEmployees=a;
    }
    void addEmployee(const Employee &vr){
        int i=numOfEmployees;
        if(i<20){
            employees[i]=vr;
            i++;
            numOfEmployees=i;
        }
    }
    void print(){
        cout<<"Tech company name: "<<name<<endl;
        cout<<"Number of employees: "<<numOfEmployees<<endl;
    }
    double getAverageOfEmployeecSalary(){
        double average=0,sum=0;
        for(int i=0;i<numOfEmployees;i++){
            sum+=employees[i].salary;
        }
        average=sum/numOfEmployees;
        return average;
    }
};
TechCompany printCompanyWithHighestAverageSalary(TechCompany companies[], int numCompanies){
    double max;
    int index=0;
    max=companies[0].getAverageOfEmployeecSalary();
    for(int i=1;i<numCompanies;i++){
        if(companies[i].getAverageOfEmployeecSalary()>max){
            max=companies[i].getAverageOfEmployeecSalary();
            index=i;
        }
    }
    return companies[index];
}
TechCompany printCompanyWithHighestStdSalary(TechCompany companies[], int numCompanies){
double VAR = 0, STDmax = 0, pl,razlika,STDplata;
int VkVraboteni,indeks,j=0;
        for (int i = 0; i < numCompanies; i++) {
    VkVraboteni = companies[i].getNumEmployees();
    pl = companies[i].getAverageOfEmployeecSalary();
    VAR=0;
    j=0;
while (j < VkVraboteni) {
    razlika = companies[i].getEmployee(j).getSalary() - pl;
    VAR += pow(razlika,2);
    j++;
}
    STDplata = sqrt(VAR / (VkVraboteni - 1));
        if (STDplata > STDmax) {
    STDmax = STDplata;
    indeks = i;
}
}
return companies[indeks];
}
bool isSameCompany(TechCompany &t1,TechCompany &t2){
    if(strcmp(t1.getName(),t2.getName())==0){
    return true;
} else{
    return false;
}
}
//DO NOT CHANGE main()

int main() {
    const int MAX_COMPANIES = 10;
    const int MAX_EMPLOYEES = 20;

    TechCompany companies[MAX_COMPANIES];

    int n;
    std::cin >> n;

    for (int i = 0; i < n; i++) {
        char name[100];
        std::cin >> name;

        TechCompany company(name);

        int m;
        std::cin >> m;

        for (int j = 0; j < m; j++) {
            char name[100];
            char surname[100];
            int salary;

            std::cin >> name;

            std::cin >> surname;

            std::cin >> salary;

            Employee employee(name, surname, salary);

            company.addEmployee(employee);
        }

        companies[i] = company;
    }

    TechCompany copy = companies[0];

    std::cout<<"-->Testing get and set methods for one object and copy constructor"<<std::endl;
    copy.setName("copy");
    std::cout << copy.getName() << std::endl;


    std::cout<<"-->Testing addEmployee function"<<std::endl;
    Employee newEmployee("John", "Doe", 5000);
    copy.addEmployee(newEmployee);
    std::cout << "Number of employees in copy: " << copy.getNumEmployees() << std::endl;


    std::cout<<"-->Testing copy of first employee"<<std::endl;
    Employee firstEmployee = copy.getEmployee(0);
    firstEmployee.printEmployee();


    std::cout<<"-->Testing methods"<<std::endl;
    TechCompany t = printCompanyWithHighestAverageSalary(companies, n);
    TechCompany t1 = printCompanyWithHighestStdSalary(companies, n);

    std::cout << "Tech company with the highest average salary: " << t.getName() << std::endl;
    std::cout << "Tech company with the highest standard deviation for salaries: " <<t1.getName() << std::endl;

    if (isSameCompany(t, t1)){
        std::cout<<"The tech company: "<<t.getName()<<" has the highest standard deviation and highest average salary"<<std::endl;
    }
    return 0;
}
