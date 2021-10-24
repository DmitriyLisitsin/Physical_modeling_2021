#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>


template<typename type>
class Exp {
public:
    virtual type f_x(type t, type x, type v) const = 0;

    virtual type f_v(type t, type x, type v) const = 0;

    virtual ~Exp() = default;
};

template<typename type>
class PhysicalPend: public Exp<type> {
private:
    type a;

public:
    PhysicalPend(type b): a{b} {}

    type f_x(type t, type x, type v) const override
    {
        return v;
    }

    type f_v(type t, type x, type v) const override
    {
        return -a*std::sin(x);
    }
};


template<typename type>
class MathPend: public Exp<type> {
private:
    type a;

public:
    MathPend(type b): a{b} {}

    type f_x(type t, type x, type v) const override
    {
        return v;
    }

    type f_v(type t, type x, type v) const override
    {
        return -a*x;
    }
};


template<typename type>
class Solver{
private:
    Exp<type>* expression;
    std::vector<type> X;
    std::vector<type> V;
    std::vector<type> T;
    type x_old, x_new, x_tmp1, x_tmp2, x_comp = (type)0;
    type x_m, x_m_tmp1, x_m_tmp2, x_m_comp = (type)0;
    type v_old, v_new, v_tmp1, v_tmp2, v_comp = (type)0;
    type v_m, v_m_tmp1, v_m_tmp2, v_m_comp = (type)0;

public:
    Solver() {}

    void take_exp(Exp<type>* exp, type x0, type v0)
    {
        expression = exp;
        x_old = x_new = x_tmp1 = x_tmp2 = x_comp = (type)0;
        x_m = x_m_tmp1 = x_m_tmp2 = x_m_comp = (type)0;
        v_old = v_new = v_tmp1 = v_tmp2 = v_comp = (type)0;
        v_m = v_m_tmp1 = v_m_tmp2 = v_m_comp = (type)0;

        x_old = x0;
        v_old = v0;
    }

    void Euler_solve(type time, type dt, type tau)
    {
        long long int iter = static_cast<long long int> (time/dt);
        long long int write = static_cast<long long int> (tau/dt);
        size_t size = static_cast<size_t> (time/tau);
        std::vector<type> x(size, (type)0);
        std::vector<type> v(size, (type)0);
        std::vector<type> t(size, (type)0);
        int I = 0;
        int j = 1;
        x[0] = x_old;
        v[0] = v_old;
        t[0] = (type)0;
        for(long long int i=0; i<iter; ++i){
            if (I == write){
                x[j] = x_old;
                v[j] = v_old;
                t[j] = i*dt;
                ++j;
                I = 0;
            }
            x_new = x_old + expression->f_x(i*dt, x_old, v_old)*dt;
            v_new = v_old + expression->f_v(i*dt, x_old, v_old)*dt;

            x_old = x_new;
            v_old = v_new;
            ++I;
        }

        X = x;
        V = v;
        T = t;
    }

    void Hoen_solve(type time, type dt, type tau)
    {
        long long int iter = static_cast<long long int> (time/dt);
        long long int write = static_cast<long long int> (tau/dt);
        size_t size = static_cast<size_t> (time/tau);
        std::vector<type> x(size, (type)0);
        std::vector<type> v(size, (type)0);
        std::vector<type> t(size, (type)0);
        int I = 0;
        int j = 1;
        x[0] = x_old;
        v[0] = v_old;
        t[0] = (type)0;
        for(long long int i=0; i<iter; ++i){
            if (I == write){
                x[j] = x_old;
                v[j] = v_old;
                t[j] = i*dt;
                ++j;
                I = 0;
            }
            x_m = x_old + expression->f_x(i*dt, x_old, v_old)*dt;
            v_m = v_old + expression->f_v(i*dt, x_old, v_old)*dt;

            x_new = x_old + expression->f_x(i*dt, x_old + x_m, v_old + v_m)*dt/2;
            v_new = v_old + expression->f_v(i*dt, x_old + x_m, v_old + v_m)*dt/2;

            x_old = x_new;
            v_old = v_new;
            ++I;
        }

        X = x;
        V = v;
        T = t;
    }

    void Hoen_solve_with_kahan(type time, type dt, type tau)
    {
        long long int iter = static_cast<long long int> (time/dt);
        long long int write = static_cast<long long int> (tau/dt);
        size_t size = static_cast<size_t> (time/tau);
        std::vector<type> x(size, (type)0);
        std::vector<type> v(size, (type)0);
        std::vector<type> t(size, (type)0);
        int I = 0;
        int j = 1;
        x[0] = x_old;
        v[0] = v_old;
        t[0] = (type)0;
        for(long long int i=0; i<iter; ++i){
            if (I == write){
                x[j] = x_old;
                v[j] = v_old;
                t[j] = i*dt;
                ++j;
                I = 0;
            }
            x_tmp1 = expression->f_x(i*dt, x_old, v_old)*dt - x_comp;
            x_tmp2 = x_old + x_tmp1;
            x_comp = (x_tmp2 - x_old) - x_tmp1;
            x_m = x_tmp2;

            v_tmp1 = expression->f_v(i*dt, x_old, v_old)*dt - v_comp;
            v_tmp2 = v_old + v_tmp1;
            v_comp = (v_tmp2 - v_old) - v_tmp1;
            v_m = v_tmp2;

            x_m_tmp1 = expression->f_x(i*dt, x_old + x_m, v_old + v_m)*dt/2;
            x_m_tmp2 = x_old + x_m_tmp1;
            x_m_comp = (x_m_tmp2 - x_old) - x_m_tmp1;
            x_new = x_m_tmp2;

            v_m_tmp1 = expression->f_v(i*dt, x_old + x_m, v_old + v_m)*dt/2;
            v_m_tmp2 = v_old + v_m_tmp1;
            v_m_comp = (v_m_tmp2 - v_old) - v_m_tmp1;
            v_new = v_m_tmp2;

            x_old = x_new;
            v_old = v_new;
            ++I;
        }

        X = x;
        V = v;
        T = t;
    }

    void save_data(std::string path)
    {
        std::ofstream out;
        out.open(path);
        if (out.is_open()){
            out << std::setprecision(8);
            out << std::scientific;
            for(int i = 0; i<T.size(); ++i){
                out << T[i] << ' ' << X[i] << ' ' << V[i] << '\n';
            }
        }
        out.close();
    }
};


int main()
{
    Solver<double> s;
    PhysicalPend<double> pend1(1.0);
    s.take_exp(&pend1, 0.0, 1.00);
    s.Euler_solve(100, 0.001, 0.05);
    //s.Hoen_solve(120, 0.001, 0.05);
    //s.Hoen_solve_with_kahan(100, 0.001, 0.05);
    s.save_data("Data.txt");

//    MathPend<double> pend2(1.0);
//    s.take_exp(&pend2, 6400.0, 0.0);
//    s.Hoen_solve_with_kahan(100, 0.001, 0.1);
//    s.save_data("Data.txt");

    std::cout << "Finished" << '\n';
    return 0;
}
