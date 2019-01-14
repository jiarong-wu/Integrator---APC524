#ifndef RUNGE_KUTTA_H_
#define RUNGE_KUTTA_H_

#include "integrator.h"
class Model;                 

// Fixed-timestep Runge-Kutta integrator
class RungeKutta : public Integrator
{
public:
   RungeKutta(double dt, const Model &model);
   ~RungeKutta();

   int Step(double t, double *x);

private:
   const double dt_;	     
   const Model &model_;	       
   const int dimen_;           
   double *k1_, *k2_, *k3_, *k4_, *temp_;	
   int Update(double dt, double *k);
};

#endif	// RUNGE_KUTTA_H_