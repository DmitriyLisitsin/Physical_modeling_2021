#ifndef process_h
#define process_h

#include <string>
#include <vector>

#include "solver.h"
#include "heun_solver.h"
#include "rk4_solver.h"
#include "saving.h"
#include "expression.h"

template<typename type>
void process(Exp<type> * exp, type T, type dt, type tau,
             std::vector<type> const& params, std::vector<type> const& P0,
             std::string file1, std::string file2, std::string file3, std::string file4,
             int se, int sh, int srk, int shh)
{
    Solver<type> s;
    HeunSolver<type> hs;
    RK4Solver<type> rks;

    if(sh){
        hs.take_exp(exp, P0);
        hs.solve(T, dt, tau);
        save_data(file2, hs.get_time(), hs.get_values(),
                  hs.get_force(), hs.get_energy(), P0, params, 2);
    }
    if(se){
        s.take_exp(exp, P0);
        s.solve(T, dt, tau);
        save_data(file1, s.get_time(), s.get_values(),
                  s.get_force(), s.get_energy(), P0, params, 2);
    }
    if(srk){
        rks.take_exp(exp, P0);
        rks.solve(T, dt, tau);
        save_data(file3, rks.get_time(), rks.get_values(),
                  rks.get_force(), rks.get_energy(), P0, params, 2);
    }
}
#endif // process_h
