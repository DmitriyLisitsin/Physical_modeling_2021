#ifndef double_pend_h
#define double_pend_h

#include "expression.h"
#include <vector>
#include <cmath>

using std::sin, std::cos, std::pow;

template<typename type>
class DoublePend: public Exp<type> {
private:
    const unsigned int n = 4;
    type m1;
    type m2;
    type L1;
    type L2;
    type g;

public:
    DoublePend(type m10, type m20, type L10, type L20, type g0): m1{m10}, m2{m20}, L1{L10}, L2{L20}, g{g0} {}

    void f(std::vector<type> &P_new, type t, std::vector<type> &P) const override
    {
        P_new[0] = P[2];
        P_new[1] = P[3];
        P_new[2] = (m2*g*cos(P[0]-P[1])*sin(P[1]) - (m1+m2)*g*sin(P[0]) -
                    m2*L1*cos(P[0]-P[1])*sin(P[0]-P[1])*pow(P[2], 2) - m2*L2*sin(P[0]-P[1])*pow(P[3], 2)) /
                    L1/(m1 + m2 - m2*pow(cos(P[0]-P[1]), 2));

        P_new[3] = (-(m1+m2)*g*cos(P[0]-P[1])*sin(P[0]) + (m1+m2)*g*sin(P[1]) -
                    (m1+m2)*L1*sin(P[0]-P[1])*pow(P[2], 2) - m2*L2*cos(P[0]-P[1])*sin(P[0]-P[1])*pow(P[3], 2)) /
                    L2/(-m1 - m2 + m2*pow(cos(P[0]-P[1]), 2));
    }

    type force(type t, std::vector<type> const& P) const override
    {
        return 0.0;
    }

    type energy(std::vector<type> const& P) const override
    {
        return 0.5*(m1*pow(L1*P[2], 2) + m2*(pow(L1*P[2], 2) + pow(L2*P[3], 2) + 2*L1*L2*cos(P[0]-P[1])*P[2]*P[3])) -
                L1*cos(P[0])*(m1+m2)*g - L2*cos(P[1])*m2*g;
    }

    const unsigned int get_n() const override {return n;}
};

#endif // double_pend_h
