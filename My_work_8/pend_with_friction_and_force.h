#ifndef pend_with_friction_and_force_h
#define pend_with_friction_and_force_h

#include "expression.h"
#include <vector>
#include <cmath>


template<typename type>
class FrictionPendWithForce: public Exp<type> {
private:
    const unsigned int n = 2;
    type w;
    type w2;
    type b;
    type F;
    type W;

public:
    FrictionPendWithForce(type w0, type b0, type W0, type F0): w{w0}, b{b0}, F{F0}, W{W0} {w2 = w*w;}

    void f(std::vector<type> &P_new, type t, std::vector<type> &P_old) const override
    {
        P_new[0] = P_old[1];
        P_new[1] = -w2*P_old[0] - b*P_old[1] + F*std::cos(W*t);
    }

    const unsigned int get_n() const override {return n;}
};

#endif // pend_with_friction_and_force_h
