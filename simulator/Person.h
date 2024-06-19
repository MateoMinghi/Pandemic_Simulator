#ifndef PERSON_H_
#define PERSON_H_

#include <iostream>
using namespace std;

class Person {
protected:
    int Age;
public:
    Person();
    Person(int age): Age(age){};
    
    int getAge() const{return Age;}
    void setAge(const int &age){Age = age;}
};

Person::Person(){
    cout << "Average age of the population: ";
    cin >> Age;
}

class Vaccinated : public Person{
private:
    bool vaccination_status;
public:
    Vaccinated(); 
    Vaccinated(int age, bool v_s): Person(age), vaccination_status(v_s){}; 

    bool getVaccination()const{return vaccination_status;}
};

Vaccinated::Vaccinated() : Person(){
    vaccination_status = true;
}


class NonVaccinated : public Person{
private:
    bool vaccination_status;
public:
    NonVaccinated(); 
    NonVaccinated(int age, bool v_s): Person(age), vaccination_status(v_s){};

    bool getVaccination()const{return vaccination_status;}
};

NonVaccinated::NonVaccinated(): Person(){
    vaccination_status = false;
}

#endif