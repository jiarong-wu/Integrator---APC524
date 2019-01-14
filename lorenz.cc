#include "lorenz.h"
#include <math.h>

Lorenz::Lorenz(double sigma, double rho, double beta)
   : sigma_(sigma),
   	 rho_(rho),
   	 beta_(beta)
{}

Lorenz::~Lorenz()
{}

int Lorenz::rhs(double t, const double *x, double *Dx) const
{
   Dx[0] = sigma_ * (x[1] - x[0]);
   Dx[1] = rho_ * x[0]  - x[1] - x[0] * x[2];
   Dx[2] = - beta_ * x[2] + x[0] * x[1];

   // Return 0 to indicate success
   return 0;
}