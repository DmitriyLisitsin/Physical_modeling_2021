#ifndef arbitrary_pend2_h
#define arbitrary_pend2_h

#include "expression.h"
#include <vector>
#include <cmath>


template<typename type>
class ArbitraryPend2: public Exp<type> {
private:
    const unsigned int n = 2;
    type w;
    type w2;
    type b;
    type F;
    type W;

public:
    ArbitraryPend2(type w0, type b0, type W0, type F0): w{w0}, b{b0}, F{F0}, W{W0} {w2 = w*w;}

    void f(std::vector<type> &P_new, type t, std::vector<type> &P_old) const override
    {
        P_new[0] = P_old[1];
        P_new[1] = -w2*P_old[0] - b*P_old[1] + force(t, P_old);
    }

    type force(type t, std::vector<type> const& P) const override
    {
        return ((std::cos(W*t) > 0.0) ? F : 0.0);
    }

    type energy(std::vector<type> const& P) const override
    {
        return 0.5*(std::pow(w*P[0], 2) + std::pow(P[1], 2));
    }

    const unsigned int get_n() const override {return n;}
};

#endif // arbitrary_pend2_h
