#ifndef POPULATION_H_
#define POPULATION_H_

#include "Person.h"
#include <iostream>
#include <iomanip>
using namespace std;

class Population {
private:
  int population_size;
  double vaccination_rate;
  int average_age;
  double num_vaccinated;
  double Vaccine_effectiveness;
  Person **people; 
  int counter = 0;

  //attributes for Euler's method
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

  double *S_vaccinated; 
  double *S_non_vaccinated; 
  double *I; 
  double *R; 

public:
  Population();
  ~Population();
  void create_population();
  double transmission_rate_vaccinated();
  double transmission_rate_non_vaccinated();
  void simulation();
};


Population::Population() {
  cout << "Population size: ";
  cin >> population_size;
  
  cout << "Choose a variant to inffect the population:" << endl;
  cout << "Original (1), Omnicron(2), Delta(3): ";
  cin >> Virus;
  if (Virus == 1){B = 0.7;}
  else if (Virus == 2){B = 0.9;}
  else if (Virus == 3){B = 0.8;}

  cout << "Percentage of vaccinated people: ";
  cin >> vaccination_rate;

  cout << "Vaccine effectiveness: ";
  cin >> Vaccine_effectiveness;

  cout << "Average population age: ";
  cin >> average_age;

  cout << "Number of initial inffected individuals: ";
  cin >> I0;

  cout << "Number of days to run the simulation: ";
  cin >> days;


  num_vaccinated = population_size * vaccination_rate;
  steps = static_cast<int>(days/dt);
  people = new Person *[population_size];

  S_vaccinated = new double[steps + 1];
  S_non_vaccinated = new double[steps + 1];
  I = new double[steps + 1];
  R = new double[steps + 1];

  S_non_vaccinated[0] = population_size - num_vaccinated;
  S_vaccinated[0] = num_vaccinated - I0;
  I[0] = I0; 
  R[0] = R0; 
}

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

Population::~Population() {
  delete[] S_vaccinated;
  delete[] S_non_vaccinated;
  delete[] I;
  delete[] R;

  for (int i = 0; i < population_size; ++i) {
    delete people[i];
  }
  delete[] people;
}

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
      cout << "After " << n << " days:" << endl; 
      cout << "Susceptible: " << S_vaccinated[n + 1] + 
        S_non_vaccinated[n + 1] << endl;
      cout << "Infected: " << I[n + 1] << endl;
      cout << "Removed: " << R[n + 1] << endl;
      break; 
    }
  }

  cout << "After " << days << " days:" << endl;
  cout << fixed << setprecision(2) << "Susceptibles: " << 
    S_vaccinated[steps] + S_non_vaccinated[steps] << endl;
  cout << fixed << setprecision(2) << "Infected: " << I[steps] << endl;
  cout << fixed << setprecision(2) << "Removed: " << R[steps] << endl;
}


#endif