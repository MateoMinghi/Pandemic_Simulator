<div align="center">
  <h1>Pandemic Simulator</h1>
</div>

To run the Simulator:

```
g++ main.cpp
```
---
The SIR mathematical model is used for describing the spread of infectious diseases within a population. It divides the population into three groups:

- **Susceptible (S)**: Individuals who are not infected but can get infected.
- **Infectious (I)**: Individuals who are currently infected and can transmit the disease.
- **Removed (R)**: Individuals who have either recovered or died from the disease.


## Differential Equations

The SIR model is described by the following set of differential equations:

1. **Susceptible Population (S)**:
   $\frac{dS}{dt} = -\beta \frac{SI}{N}$


2. **Infected Population (I)**:
   $\frac{dI}{dt} = \beta \frac{SI}{N} - \gamma I$

3. **Recovered Population (R)**:
   $\frac{dR}{dt} = \gamma I$

> Where $\beta$ is the transmission rate and $\gamma$ is the recovery rate.

In order to solve the differential equations, thus allowing us to know the number of susceptibles, infected, and removed individuals at a particular momment in time, I used Euler's numeric method:

1. **Susceptible Population (S)**:
   ${S_{n+1}} = {S_n}-\beta {S_nI_n \Delta t}$


2. **Infected Population (I)**:
   ${I_{n+1}} = {I_n}+ (\beta {S_nI_n - \gamma I_n \Delta t})$

3. **Recovered Population (R)**:
   ${R_{n+1}} = {R_n} + {\gamma I_n \Delta t}$
