#ifndef pend_with_friction_h
#define pend_with_friction_h

#include "expression.h"
#include <vector>


template<typename type>
class FrictionPend: public Exp<type> {
private:
    const unsigned int n = 2;
    type w;
    type b;
    type w2;

public:
    FrictionPend(type w0, type b0): w{w0}, b{b0} {w2 = w*w;}

    void f(std::vector<type> &P_new, type t, std::vector<type> &P_old) const override
    {
        P_new[0] = P_old[1];
        P_new[1] = -w2*P_old[0] - b*P_old[1];
    }

    const unsigned int get_n() const override {return n;}
};

#endif // pend_with_friction_h
