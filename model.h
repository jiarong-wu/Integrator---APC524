#ifndef MODEL_H_
#define MODEL_H_

// ABC for a system of first-order ODEs
class Model
{
public:
   virtual ~Model() {}

  // Dx = f(x,t).  Returns 0 if successful, else an error code
  virtual int rhs(double t, const double *x, double *Dx) const = 0;
  // The "= 0" above is just syntax to indicate that this method is
  // "pure virtual"; including at least one pure virtual method is the
  // C++ way of making a class formally an ABC (so that it cannot be
  // directly instantiated).

  // Returns number of variables in ODE system (size of x)
  virtual int dimen() const = 0;
};

#endif  // MODEL_H_
