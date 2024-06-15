/*
 * Proyecto Simulador Pandemias
 * clase Population
 * Mateo Minghi Vega
 * A01711231
 * 11/06/2024
 * Esta clase defina objeto de tipo Population que contiene todos
 * los atributos y métodos para realizar la simulación de pandemias 
 */

#ifndef POPULATION_H_
#define POPULATION_H_

#include "Person.h"
#include <iostream>
#include <iomanip>
using namespace std;

class Population {
private:
  //atributos relacionados a la poblacion
  int population_size;
  int vaccination_rate;
  int average_age;
  double num_vaccinated;
  double Vaccine_effectiveness;
  Person **people; //se define como doble apuntador porque es un arreglo
  //dinámico cuyo tamaño se define por el usuario
  int counter = 0;

  //atributos para el método numérico de Euler para la simulación
  int Virus;
  double B;
  double new_B;
  double new_B_nv;
  double gamma = 0.1;
  int I0;
  int R0 = 0;
  double dt = 0.000001;
  int days;
  int steps;

  double *S_vaccinated; //arreglo dinámico susceptibles vacunados
  double *S_non_vaccinated; //arreglo dinámico susceptibles no vacunados
  double *I; //arreglo dinámico infectados
  double *R; //arreglo dinámico removidos

public:
  //constructor por default y metodos públicos
  Population();
  void create_population();
  double transmission_rate_vaccinated();
  double transmission_rate_non_vaccinated();
  void simulation();
  void add_person();
  void print_population();
};

/*
 * Population() crea la instancia de la población.
 * Permite al usuario establecer el valor de los atributos usados
 * en la simulación de la pandemia.
 * Arreglos dinámicos se establecen aquí porque su tamaño depende 
 * del input del usuario.
 */
Population::Population() {
  cout << "Tamano de la poblacion: ";
  cin >> population_size;
  
  cout << "Elige una variante para infectar a la poblacion:" << endl;
  cout << "Original (1), Omnicron(2), Delta(3): ";
  cin >> Virus;
  if (Virus == 1){B = 0.7;}
  else if (Virus == 2){B = 0.9;}
  else if (Virus == 3){B = 0.8;}

  cout << "Porcentaje de la poblacion vacunada: ";
  cin >> vaccination_rate;

  cout << "Efectividad de la vacuna: ";
  cin >> Vaccine_effectiveness;

  cout << "Edad promedio de la poblacion: ";
  cin >> average_age;

  cout << "Cantidad de infectados para iniciar la simulacion: ";
  cin >> I0;

  cout << "Numero de dias para correr la simulacion: ";
  cin >> days;


  num_vaccinated = population_size * (vaccination_rate / 100.0);
  steps = static_cast<int>(days/dt);//cantidad de pasos del método de Euler
  people = new Person *[population_size];

  S_vaccinated = new double[steps + 1];
  S_non_vaccinated = new double[steps + 1];
  I = new double[steps + 1];
  R = new double[steps + 1];

  S_non_vaccinated[0] = population_size - num_vaccinated;//susceptibles  
  //vacunados iniciales
  S_vaccinated[0] = num_vaccinated - I0;//susceptibles no vacunados iniciales
  I[0] = I0; //Infectados iniciales
  R[0] = R0; //removidos iniciales
}

/*
 * create_population() automatiza la creación de instancias 
 * de vacunados y no vacunados, en base al porcentaje de vacunación
 * sobre la población total. Esto es definido por el usuario.
 * 
 * Se llena el arreglo dinámico (Person *[population_size])en su totalidad. 
 */
void Population::create_population() {
  for (int i = 0; i < num_vaccinated; i++) {
    people[counter] = new Vaccinated(average_age, true);
    counter++;
  }

  for (int i = 0; i < (population_size - num_vaccinated); i++) {
    people[counter] = new NonVaccinated(average_age, false);
    counter++;
  }
}

/*
 * La tasa de transmisión cambia si una persona está vacunada.
 * 
 * transmission_rate_vaccinated() ajusta el valor de la tasa
 * de transmisión basado en la vacunación y en la edad. 
 *
 * @returns la tasa de transmisión para vacunados
 */
double Population::transmission_rate_vaccinated() {
  double Age_modifier;
  if (average_age < 18) { 
    Age_modifier = 1.2;
  } else if (average_age <= 65) { 
    Age_modifier = 1.0;
  } else { 
    Age_modifier = 1.5;
  }
  return B * Age_modifier * (1 - Vaccine_effectiveness);
}

/*
 * La tasa de transmisión cambia si una persona no está vacunada.
 * 
 * transmission_rate_vaccinated() ajusta el valor de la tasa
 * de transmisión basado en la edad solamente. 
 *
 * @returns la tasa de transmisión para no vacunados
 */
double Population::transmission_rate_non_vaccinated() {
  double Age_modifier;
  if (average_age < 18) { 
    Age_modifier = 1.2;
  } else if (average_age <= 65) { 
    Age_modifier = 1.0;
  } else { 
    Age_modifier = 1.5;
  }
  return B * Age_modifier;
}

/*
 * simulation() lleva a cabo la simulación con el método numérico de Euler
 * 
 * Utiliza las tasas de transmisión calculadas anteriormente.
 * Cada iteración calcula el valor siguiente, basado en 
 * las condiciones iniciales definidas en el constructor. 
 *
 * Imprime el último valor calculado, que coincide con el número de días que
 * se quiere correr la simulación. Se aplica un condicional para evitar
 * que se impriman valores sin sentido.
 *
 * setprecision() imprime valores con solo dos decimales.
 */
void Population::simulation() {
  double b_v = transmission_rate_vaccinated();
  double b_nv = transmission_rate_non_vaccinated();

  for (int n = 0; n < steps; ++n) {
    S_non_vaccinated[n + 1] = S_non_vaccinated[n] - 
      b_nv * S_non_vaccinated[n] * I[n] * dt;
    S_vaccinated[n + 1] = S_vaccinated[n] - 
      b_v * S_vaccinated[n] * I[n] * dt;
    I[n + 1] = I[n] + 
      ((b_nv * S_non_vaccinated[n] + b_v * S_vaccinated[n]) * I[n] - 
      gamma * I[n]) * dt;
    R[n + 1] = R[n] + gamma * I[n] * dt;

    if (S_non_vaccinated[n + 1] < 0 || S_vaccinated[n + 1] < 0 || 
        I[n + 1] < 0 || R[n + 1] < 0) {
      cout << "Despues de " << n << " dias:" << endl; 
      cout << "Susceptibles: " << S_vaccinated[n + 1] + 
        S_non_vaccinated[n + 1] << endl;
      cout << "Infectados: " << I[n + 1] << endl;
      cout << "Removidos: " << R[n + 1] << endl;
      break; 
    }
  }

  cout << "Despues de " << days << " dias:" << endl;
  cout << fixed << setprecision(2) << "Susceptibles: " << 
    S_vaccinated[steps] + S_non_vaccinated[steps] << endl;
  cout << fixed << setprecision(2) << "Infectados: " << I[steps] << endl;
  cout << fixed << setprecision(2) << "Removidos: " << R[steps] << endl;
}


/*
 * add_person() crea un objeto de tipo Person, vacunado o no vacunado,
 * y lo agrega al arreglo de la población. 
 * Como ese arreglo está lleno en su totalidad, se le suma a population_size
 * para abrir más espacio en memoria.
 */
void Population::add_person(){
  int decision; 
  cout << "Agregar vacunado(1) o no vacunado(2) a la poblacion?: ";
  cin >> decision;

  if (decision == 1){
    people[counter] = new Vaccinated(average_age, true);
    counter++;
    population_size++;}
  else if (decision == 2){
    people[counter] = new NonVaccinated(average_age, false);
    counter++;
    population_size++;}
}

/*
 * print_population() recorre el arreglo de instancias de Person
 * y utiliza el método print_person(), declarado dentro de las clases
 * de Person, para imprimir datos de cada persona.
 *
 * No recomendado usarlo si la población es muy grande.
 */
void Population::print_population(){
  for (int i = 0; i < counter; i++)
    people[i] -> print_person();
}

#endif