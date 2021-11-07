#ifndef solver_h
#define solver_h

#include "expression.h"

#include <cmath>
#include <vector>

template<typename type>
class Solver{
private:
    unsigned int n;
    Exp<type>* expression;
    std::vector<type> P_old;
    std::vector<type> P_new;
    std::vector<type> P_f1;
    std::vector<std::vector<type>> P;
    std::vector<type> T;
    type time;

public:
    Solver() {}

    void take_exp(Exp<type>* exp, std::vector<type> P0)
    {
        n = exp->get_n();
        expression = exp;
        P_old = P0;
        std::vector<type> p_new(n, 0.0);
        std::vector<type> p_f1(n, 0.0);

        P_new = p_new;
        P_f1 = p_f1;
        time = 0.0;
    }

    void iter(type dt)
    {
        expression->f(P_f1, time, P_old);
        for(int i=0; i<n; ++i)
            P_new[i] = P_old[i] + P_f1[i]*dt;
        P_old = P_new;
    }

    void solve(type time0, type dt, type tau)
    {
        long long int iterations = static_cast<long long int> (time0/dt);
        long long int write = static_cast<long long int> (tau/dt);
        size_t size = static_cast<size_t> (time0/tau);
        std::vector<std::vector<type>> p(size, std::vector<type> (n, 0.0));
        std::vector<type> t(size, 0.0);
        int I = 0;
        int j = 1;
        p[0] = P_old;
        t[0] = 0.0;
        for(long long int i=0; i<iterations; ++i){
            if (I == write){
                p[j] = P_old;
                t[j] = i*dt;
                ++j;
                I = 0;
            }
            iter(dt);
            time = (i+1)*dt;
            ++I;
        }

        P = p;
        T = t;
    }

    std::vector<type> get_time() {return T;}

    std::vector<std::vector<type>> get_values() {return P;}
};
#endif // solver_h
