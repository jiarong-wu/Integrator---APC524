#ifndef LORENZ_H_
#define LORENZ_H_

#include "model.h"

//   \dot x = sigma*(y-x)
//   \dot y = rho*x - y - x*z 
//   \dot z = -beta*z + x*y
class Lorenz : public Model
{
public:
   Lorenz(double sigma, double rho, double beta);
   ~Lorenz();   
   int rhs(double t, const double *x, double *Dx) const;
   int dimen() const { return kDimen_; }

private:
   // All instances of this class have kDimen_ == 3
   static const int kDimen_ = 3;
   const double sigma_;                       
   const double rho_;                        
   const double beta_;                        
};

#endif  // LORENZ_H_