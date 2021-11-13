#include <iostream>
#include <string>

#include "expression.h"
#include "solver.h"
#include "heun_solver.h"
#include "saving.h"

#include "math_pend.h"

int main()
{
    double T = 100;
    double dt = 0.001;
    double tau = 0.05;

    double w = 1.0;

    double x0 = 1.0;
    double v0 = 0.0;

    int a = 1;

    std::string folder = "Force_pend_data/";
    std::string name1 = "Heun/Data_" + std::to_string(a) + ".txt";
    std::string name2 = "Euler/Data_" + std::to_string(a) + ".txt";

    Solver<double> s;
    HeunSolver<double> hs;

    MathPend<double> pend(1.0);

    hs.take_exp(&pend, {x0, v0});
    hs.solve(T, dt, tau);
    save_data(folder+name1, hs.get_time(), hs.get_values(), {x0, v0, w}, 2);

//    s.take_exp(&pend, {x0, v0});
//    s.solve(T, dt, tau);

    std::cout << "Finished" << '\n';

    return 0;
}
