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

//Classe Person es abstracta
class Person {
protected:
    //atributo protected
    int Age;
public:
    //métodos públicos
    Person();
    Person(int age): Age(age){};
    virtual void vaccination() = 0; //método sobreescrito abstracto
    virtual void print_person() = 0; //método sobreescrito abstracto
    
    //modificadores de acceso
    int getAge() const{return Age;}
    void setAge(const int &age){Age = age;}
};

/*
 * Person() es constructor por default, valor definidos por el usuario
 */
Person::Person(){
    cout << "Edad promedio de la población: ";
    cin >> Age;
}

//Clase Vaccinated. Hereda de Person
class Vaccinated : public Person{
private:
    //atributos privados
    bool vaccination_status;
public:
    //métodos públicos
    Vaccinated(); //constructor por default 
    Vaccinated(int age, bool v_s): Person(age), vaccination_status(v_s){}; 
    void vaccination() ;
    void print_person();
    bool getVaccination()const{return vaccination_status;}
};

/*
 * Constructor por default. 
 * Incluye lo definido en el constructor de clase padre.
 */
Vaccinated::Vaccinated() : Person(){
    vaccination_status = true;
}

/*
 * vaccination() imprime que la persona está vacunada
 * Sobreescribe a vaccination() de la clase padre
 *
 * Uso de método abstracto 
 */
void Vaccinated::vaccination(){
    cout << "Persona vacunada" << endl; 
}

/*
 * print_person() toda la información de la persona
 * Sobreescribe a print_person() de la clase padre
 *
 * Uso de método abstracto 
 */
void Vaccinated::print_person(){
  cout << "Esta persona tiene " << Age << " años" << endl;
  cout << "vacunacción: " << vaccination_status << endl;
}

//Clase NonVaccinated. Hereda de Person.
class NonVaccinated : public Person{
private:
    //atributos privados
    bool vaccination_status;
public:
    //métodos públicos
    NonVaccinated(); //constructor por default
    NonVaccinated(int age, bool v_s): Person(age), vaccination_status(v_s){};
    void vaccination(); 
    void print_person();
    bool getVaccination()const{return vaccination_status;}
};

/*
 * Constructor por default. 
 * Incluye lo definido en el constructor de clase padre.
 */
NonVaccinated::NonVaccinated(): Person(){
    vaccination_status = false;
}

/*
 * vaccination() imprime que la persona está vacunada
 * Sobreescribe a vaccination() de la clase padre
 *
 * Uso de método abstracto 
 */
void NonVaccinated::vaccination(){
    cout << "Persona no vacunada" << endl; 
}

/*
 * print_person() toda la información de la persona
 * Sobreescribe a print_person() de la clase padre
 *
 * Uso de método abstracto 
 */
void NonVaccinated::print_person(){
  cout << "Esta persona tiene " << Age << " años" << endl;
  cout << "vacunacción: " << vaccination_status << endl;
}


#endif