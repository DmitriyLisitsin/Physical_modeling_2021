#include <iostream>

#include "expression.h"
#include "solver.h"
#include "heun_solver.h"

#include "math_pend.h"
#include "pend_with_friction.h"
#include "pend_with_friction_and_force.h"


int main()
{
    Solver<double> s;
    HeunSolver<double> hs;

    MathPend<double> pend1(1.0);
    //hs.take_exp(&pend1, {1.0, 0.0});
    //hs.solve(100, 0.001, 0.05);
    hs.save_data("Data_math_pend");
    s.take_exp(&pend1, {1.0, 0.0});
    //s.solve(100, 0.001, 0.05);
    //s.save_data("Data_math_pend");

    FrictionPend<double> pend2(1.0, 5.0);
    hs.take_exp(&pend2, {0.0, 1.0});
    hs.solve(50, 0.001, 0.05);
    hs.save_data("Data_friction_pend(1.0, 5.0)");
    s.take_exp(&pend2, {0.0, 1.0});
    //s.solve(100, 0.001, 0.05);
    //s.save_data("Data_friction_pend");

    FrictionPendWithForce<double> pend3(1.0, 0.1, 3.0, 1.3);
    hs.take_exp(&pend3, {0.0, 0.0});
    s.take_exp(&pend3, {0.0, 0.0});
    //hs.solve(300, 0.001, 0.05);
    //hs.save_data("Data_friction_pend_with_force");
    //s.solve(300, 0.001, 0.05);
    //s.save_data("Data_friction_pend_with_force");


    std::cout << "Finished" << '\n';

    return 0;
}
