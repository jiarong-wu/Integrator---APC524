#ifndef DUFFING_H_
#define DUFFING_H_

#include "model.h"
// Here, we must include the whole "model.h" header b/c Duffing is a
// subclass of Model. Consequently, the compiler needs to furnish
// Duffing with all the internal structure of Model (since every
// instance of Duffing is also, by necessity, an instance of Model,
// with everything that entails). And the internal layout of Model is
// specified in "model.h".


// Forced Duffing oscillator:
//   \dot x = y
//   \dot y = x - x^3 - delta * y + gamma * cos(omega t)
class Duffing : public Model
{
public:
   Duffing(double delta, double gamma, double omega);
   ~Duffing();
   
   int rhs(double t, const double *x, double *Dx) const;

   // this function is inlined for speed
   int dimen() const { return kDimen_; }

private:
   // All instances of this class have kDimen_ == 2
   static const int kDimen_ = 2;
   const double delta_;                        // damping constant
   const double gamma_;                        // amplitude of forcing
   const double omega_;                        // frequency of forcing
};

#endif  // DUFFING_H_
