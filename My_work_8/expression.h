#ifndef expression_h
#define expression_h

#include <vector>

template<typename type>
class Exp {
public:
    virtual void f(std::vector<type> &P_new, type t, std::vector<type> &P_old) const = 0;

    virtual ~Exp() = default;

    virtual const unsigned int get_n() const = 0;
};

#endif // expression_h
