#ifndef LINEAR_OSCILLATOR_H_
#define LINEAR_OSCILLATOR_H_

#include "model.h"

class LinearOscillator : public Model
{
public:
   LinearOscillator(double beta, double gamma, double omega);
   ~LinearOscillator();
   
   int rhs(double t, const double *x, double *Dx) const;

   // this function is inlined for speed
   int dimen() const { return kDimen_; }

private:
   // All instances of this class have kDimen_ == 2
   static const int kDimen_ = 2;
   const double beta_;                        // damping constant
   const double gamma_;                        // amplitude of forcing
   const double omega_;                        // frequency of forcing
};

#endif  // DUFFING_H_