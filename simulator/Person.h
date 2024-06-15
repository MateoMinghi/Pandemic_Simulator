/*
 * Proyecto Simulador Pandemias
 * clase Person
 * Mateo Minghi Vega
 * A01711231
 * 11/06/2024
 * Esta clase define objeto de tipo Person que contiene 
 * las clases heredadas de Vaccinated y NonVaccinated. 
 */

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
    virtual void vaccination() = 0; 
    virtual void print_person() = 0; 
    
    int getAge() const{return Age;}
    void setAge(const int &age){Age = age;}
};

Person::Person(){
    cout << "Edad promedio de la población: ";
    cin >> Age;
}

class Vaccinated : public Person{
private:
    bool vaccination_status;
public:
    Vaccinated(); 
    Vaccinated(int age, bool v_s): Person(age), vaccination_status(v_s){}; 
    void vaccination() ;
    void print_person();
    bool getVaccination()const{return vaccination_status;}
};

Vaccinated::Vaccinated() : Person(){
    vaccination_status = true;
}

void Vaccinated::vaccination(){
    cout << "Persona vacunada" << endl; 
}

void Vaccinated::print_person(){
  cout << "Esta persona tiene " << Age << " años" << endl;
  cout << "vacunacción: " << vaccination_status << endl;
}

class NonVaccinated : public Person{
private:
    bool vaccination_status;
public:
    NonVaccinated(); 
    NonVaccinated(int age, bool v_s): Person(age), vaccination_status(v_s){};
    void vaccination(); 
    void print_person();
    bool getVaccination()const{return vaccination_status;}
};

NonVaccinated::NonVaccinated(): Person(){
    vaccination_status = false;
}

void NonVaccinated::vaccination(){
    cout << "Persona no vacunada" << endl; 
}

void NonVaccinated::print_person(){
  cout << "Esta persona tiene " << Age << " años" << endl;
  cout << "vacunacción: " << vaccination_status << endl;
}


#endif