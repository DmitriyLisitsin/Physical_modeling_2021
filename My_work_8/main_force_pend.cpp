#include <iostream>
#include <string>

#include "solver.h"
#include "heun_solver.h"
#include "saving.h"

#include "pend_with_friction_and_force.h"

int main()
{
    double T = 100;
    double dt = 0.001;
    double tau = 0.05;

    double w = 1.0;
    double b = 0.2;

    double W = 0.3;
    double F0 = 3;

    double x0 = 0.0;
    double v0 = 0.0;

    int a = 12;

    std::string folder = "Force_pend_data/";
    std::string name1 = "Heun/Data_" + std::to_string(a) + ".txt";
    std::string name2 = "Euler/Data_" + std::to_string(a) + ".txt";

    Solver<double> s;
    HeunSolver<double> hs;

    FrictionPendWithForce<double> pend1(w, b, W, F0);

    hs.take_exp(&pend1, {x0, v0});
    hs.solve(T, dt, tau);
    save_data(folder+name1, hs.get_time(), hs.get_values(), {x0, v0, w, b, W, F0}, 2);

    s.take_exp(&pend1, {x0, v0, w, b, W, F0});
    s.solve(T, dt, tau);
    save_data(folder+name2, s.get_time(), s.get_values(), {x0, v0, w, b, W, F0}, 2);

    std::cout << "Finished" << '\n';

    return 0;
}



