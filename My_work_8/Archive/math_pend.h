#ifndef math_pend_h
#define math_pend_h

#include "expression.h"
#include <vector>

template<typename type>
class MathPend: public Exp<type> {
private:
    const unsigned int n = 2;
    type a;

public:
    MathPend(type b): a{b} {}

    void f(std::vector<type> &P_new, type t, std::vector<type> &P_old) const override
    {
        P_new[0] = P_old[1];
        P_new[1] = -a*P_old[0];
    }

    type energy(std::vector<type> const& P)
    {
        return 0.5*(std::pow(w*P[0], 2) + std::pow(P[1], 2));
    }

    const unsigned int get_n() const override {return n;}
};

#endif // math_pend_h
