#include "duffing.h"
#include <math.h>

Duffing::Duffing(double delta, double gamma, double omega)
   : delta_(delta),
     gamma_(gamma),
     omega_(omega)
{}

Duffing::~Duffing()
{}

int Duffing::rhs(double t, const double *x, double *Dx) const
{
   Dx[0] = x[1];
   Dx[1] = x[0] * (1 - x[0]*x[0]) - delta_ * x[1]
      + gamma_ * cos(omega_*t);

   // Return 0 to indicate success
   return 0;
}
