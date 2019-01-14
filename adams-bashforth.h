#ifndef ADAMS_BASHFORTH_H_
#define ADAMS_BASHFORTH_H_

#include "integrator.h"
class Model;

class AB : public Integrator
{
public:
   AB(double dt, const Model &model);
   ~AB();
   int GetLast(double *xlast);
   int Step(double t, double *x);

private:
   const double dt_;	       
   const Model &model_;	       
   const int dimen_;    
   // Array to store Dx at 2 different timestep, and solution from
   // last time step
   double *Dx1_, *Dx2_;	
   double *x_last_;       
};

#endif	// ADAMS_BASHFORTH_H_