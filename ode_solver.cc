#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include "duffing.h"
#include "linear-oscillator.h"
#include "lorenz.h"
#include "euler.h"
#include "runge-kutta.h"
#include "adams-bashforth.h"

// Print a line
//    time x[0] x[1] ...
// to standard out
void PrintState(double n, double t, const double *x) {
  printf("%15.8f", t);
  for (int i = 0; i < n; ++i) {
    printf("%15.8f", x[i]);
  }
  printf("\n");
}

int main(int argc, char *argv[]) {
  // Don't worry about error-trapping the args. You can omit this
  // block, which isn't particularly thorough as an error-trap anyway.
  if (argc != 5) {
    printf("USAGE: %s <model> <integrator> <timestep> <numsteps>\n", argv[0]);
    exit(1);
  }
  // ode_solve <model> <integrator> <timestep> <numsteps>
  // {duffing, lorenz, linear}
  const double dt = atof(argv[3]);
  const int nsteps = atoi(argv[4]);
  int *dimen = new int;
  double *x = new double[*dimen]; 
  double *x_last = new double[*dimen];  // To store last step results for ab2 method
  Model *model;
  Integrator *integrator;
  AB *integrator_ab;

  // Set up model
  if (strcmp(argv[1], "duffing") == 0)
  {
    const double delta = 0.2;
    const double gamma = 0.3;
    const double omega = 1.0;
    model = new Duffing(delta, gamma, omega);
    *dimen = model->dimen();
    for (int i = 0; i < *dimen; ++i)
      x[i] = 0;
  }
  else if (strcmp(argv[1], "linear") == 0)
  {
    const double beta = 0.1;
    const double gamma = 1;
    const double omega = 0.9;
    model = new LinearOscillator(beta, gamma, omega);
    *dimen = model->dimen(); 
    for (int i = 0; i < *dimen; ++i)
      x[i] = 0;
  }  
  else if (strcmp(argv[1], "lorenz") == 0)
  {
    const double sigma = 10;
    const double rho = 28;
    const double beta = 8./3.;
    model = new Lorenz(sigma, rho, beta);
    *dimen = model->dimen();   
    x[0] = 0;
    x[1] = 0.01;
    x[2] = 0;
  }
  else 
    std::cout << "Error: system must be one of duffing, linear or lorenz!" << std::endl;

  // Set up integration scheme
  // {euler, rk4, ab2} 
  if (strcmp(argv[2], "euler") == 0)
  {
    integrator = new Euler(dt, *model);
    integrator_ab = new AB(dt, *model);
  }
  else if (strcmp(argv[2], "rk4") == 0)
  {
    integrator = new RungeKutta(dt, *model);
    integrator_ab = new AB(dt, *model);
  }
  else if (strcmp(argv[2], "ab2") == 0)
  {
    integrator = new AB(dt, *model);
    integrator_ab = new AB(dt, *model);
  }
  else
    std::cout << "Error: integrator must be one of euler, rk4 or ab2!" << std::endl;

  double t = 0;

  PrintState(*dimen, t, x);
  for (int i = 0; i < nsteps; ++i) {
    // If using ab2
    if (strcmp(argv[2], "ab2") == 0)
    {
      if (i == 0)
      {
        for (int j = 0; j < *dimen; ++j)
          x_last[j] = x[j];
        RungeKutta temp_integrator(dt, *model);
        temp_integrator.Step(t, x);      
      }
      else 
      {
        for (int j = 0; j < *dimen; ++j)
          x_last[j] = x[j];
        integrator_ab->GetLast(x_last);
        integrator_ab->Step(t, x);
        // integrator->GetLast(x_last);
        // integrator->Step(t, x);
      }
    }
    // Not using ab2
    else
      integrator->Step(t, x);
    t = (i+1) * dt;
    PrintState(*dimen, t, x);
  }

  delete integrator;
  delete model;
  delete integrator_ab;
  delete x;
  delete x_last;

  return 0;
}
