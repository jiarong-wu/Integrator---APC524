

integrators = euler.o runge-kutta.o adams-bashforth.o
equations = duffing.o linear-oscillator.o lorenz.o
objects = ode_solver.o $(integrators) $(equations)

CXXFLAGS = -g -Wall -std=c++11

all: ode_solver

ode_solver : $(objects)
	$(CXX) $(CXXFLAGS) -o  $@ $^

clean:
	$(RM) *.o
	$(RM) .depend

# The code below helps auto-generate dependencies in a separate file,
# which then gets "included" into this Makefile
depend:
	$(CXX) -MM $(CXXFLAGS) *.cc > project.depend

-include project.depend
