#include "runge-kutta.h"
#include "model.h"

RungeKutta::RungeKutta(double dt, const Model &model)
   : dimen_(model.dimen()), 	
     dt_(dt),			
     model_(model)		
{
   k1_ = new double[dimen_];
   k2_ = new double[dimen_];
   k3_ = new double[dimen_];
   k4_ = new double[dimen_];
   temp_ = new double[dimen_];
}

RungeKutta::~RungeKutta()
{
   delete [] k1_;
   delete [] k2_;
   delete [] k3_;
   delete [] k4_;
   delete [] temp_;
}


int RungeKutta::Step(double t, double *x)
{  
   model_.rhs(t, x, k1_);
   for (int i = 0; i < dimen_; ++i)
    temp_[i] = x[i] + 0.5*dt_*k1_[i];  
   model_.rhs(t + 0.5*dt_, temp_, k2_);
   for (int i = 0; i < dimen_; ++i)
    temp_[i] = x[i] + 0.5*dt_*k2_[i];  
   model_.rhs(t + 0.5*dt_, temp_, k3_);
   for (int i = 0; i < dimen_; ++i)
    temp_[i] = x[i] + dt_*k3_[i]; 
   model_.rhs(t + dt_, temp_, k4_);
   for (int i = 0; i < dimen_; ++i)
   {
      x[i] += dt_ * (1./6.*(k1_[i] + k4_[i]) + 1./3.*(k2_[i] + k3_[i]));
   }
   return 0;
}
