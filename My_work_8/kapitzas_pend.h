#ifndef kapitzas_pend_h
#define kapitzas_pend_h

#include "expression.h"
#include <vector>
#include <cmath>

using std::sin, std::cos, std::pow;

template<typename type>
class KapitzasPend: public Exp<type> {
private:
    const unsigned int n = 2;
    type L;
    type F0;
    type W;
    type g;

public:
    KapitzasPend(type L0, type F00, type W0, type g0):
        L{L0}, F0{F00}, W{W0}, g{g0} {}

    void f(std::vector<type> &P_new, type t, std::vector<type> &P) const override
    {
        P_new[0] = P[1];
        P_new[1] = (-g+W*W*force(t, P))*sin(P[0])/L;
    }

    type force(type t, std::vector<type> const& P) const override
    {
        return -F0*cos(W*t);
    }

    type energy(std::vector<type> const& P) const override
    {
        //return 0.5*L*L*P[1]*P[1] + F0*L*W*sin(W*t)*sin(P[0])*P[1] + 0.5*pow(L*W*sin(W*t), 2) -
        //        g*(L*cos(P[0]) + F0*cos(W*t));
        return 0.5*L*L*P[1]*P[1] - g*L*cos(P[0]);
    }

    const unsigned int get_n() const override {return n;}
};

#endif // double_pend_h
