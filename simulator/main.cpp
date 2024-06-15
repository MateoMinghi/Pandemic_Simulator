/*
 * Proyecto Simulador Pandemias
 * Mateo Minghi Vega
 * A01711231
 * 11/06/2024
 * Desde esta función se llaman a las funciones para correrlas
 */

#include <iostream>
#include "Person.h"
#include "Population.h"

using namespace std;

int main() {
  Population pop;
  pop.create_population();
  pop.simulation();
  pop.add_person();
  //pop.print_population() no recomiendo correrlo si la
  //población es demasiado grande
}
