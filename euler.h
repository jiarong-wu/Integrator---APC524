#ifndef EULER_H_
#define EULER_H_

#include "integrator.h"
class Model;                   // Forward declaration
// Above is better than include-ing "model.h" b/c the Euler class
// doesn't need to know anything about how Model works, just that
// there is a data type (i.e. a class) called "Model"

// Fixed-timestep Euler integrator
class Euler : public Integrator
{
public:
   Euler(double dt, const Model &model);
   ~Euler();

   int Step(double t, double *x);

private:
   const double dt_;	       // integration timestep

   const Model &model_;	       // object w/ info about ODE system,
			       // including dimension of state vector
			       // and function f(x,t) for evaluating
			       // derivative of the state vector

   const int dimen_;           // dimension of state vector x
   double *Dx_;		       // temp space to hold f(x,t) output 
};

#endif	// EULER_H_
