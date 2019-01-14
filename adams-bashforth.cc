#include "adams-bashforth.h"
#include "model.h"

AB::AB(double dt, const Model &model)
   : dimen_(model.dimen()), 
     dt_(dt),			
     model_(model)		
{
   Dx1_ = new double[dimen_];
   Dx2_ = new double[dimen_];
   x_last_ = new double[dimen_];
}

AB::~AB()
{
   delete [] Dx1_;
   delete [] Dx2_;
   delete [] x_last_;
}

int AB::GetLast(double *x_last)
{
  x_last_ = x_last;
}

int AB::Step(double t, double *x)
{
   model_.rhs(t, x, Dx1_);
   model_.rhs(t - dt_, x_last_, Dx2_);
   for (int i = 0; i < dimen_; ++i)
   {
      x[i] += dt_ * (1.5 * Dx1_[i] - 0.5 * Dx2_[i]); 
   }
   return 0;
}