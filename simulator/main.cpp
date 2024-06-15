#include <iostream>
#include "Person.h"
#include "Population.h"

using namespace std;

int main() {
  Population pop;
  pop.create_population();
  pop.simulation();
}
