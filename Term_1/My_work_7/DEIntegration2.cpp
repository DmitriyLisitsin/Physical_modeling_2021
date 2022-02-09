#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>


template<typename type>
class Exp {
public:
    virtual void f(std::vector<type> &P_new, type t, std::vector<type> &P_old) const = 0;

    virtual ~Exp() = default;

    virtual const unsigned int get_n() const = 0;
};

template<typename type>
class PhysicalPend: public Exp<type> {
private:
    const unsigned int n = 2;
    type k;

public:
    PhysicalPend(type b): k{b} {}

    void f(std::vector<type> &P_new, type t, std::vector<type> &P_old) const override
    {
        P_new[0] = P_old[1];
        P_new[1] = -k*std::sin(P_old[0]);
    }

    const unsigned int get_n() const override {return n;}
};


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
    FrictionPendWithForce(type w0, type b0, type F0, type W0): w{w0}, b{b0}, F{F0}, W{W0} {w2 = w*w;}

    void f(std::vector<type> &P_new, type t, std::vector<type> &P_old) const override
    {
        P_new[0] = P_old[1];
        P_new[1] = -w2*P_old[0] - b*P_old[1] + F*std::cos(W*t);
    }

    const unsigned int get_n() const override {return n;}
};



template<typename type>
class Solver{
private:
    unsigned int n;
    Exp<type>* expression;
    std::vector<type> P_old;
    std::vector<type> P_new;
    std::vector<type> P_m;
    std::vector<type> P_f1;
    std::vector<type> P_f2;
    std::vector<type> P_tmp1;
    std::vector<type> P_tmp2;
    std::vector<type> P_comp;
    std::vector<type> P_m_tmp1;
    std::vector<type> P_m_tmp2;
    std::vector<type> P_m_comp;
    std::vector<std::vector<type>> P;
    std::vector<type> T;

public:
    Solver() {}

    void take_exp(Exp<type>* exp, std::vector<type> P0)
    {
        n = exp->get_n();
        expression = exp;
        P_old = P0;
        std::vector<type> p_new(n, (type)0);
        std::vector<type> p_m(n, (type)0);
        std::vector<type> p_f1(n, (type)0);
        std::vector<type> p_f2(n, (type)0);
        std::vector<type> p_tmp1(n, (type)0);
        std::vector<type> p_tmp2(n, (type)0);
        std::vector<type> p_comp(n, (type)0);
        std::vector<type> p_m_tmp1(n, (type)0);
        std::vector<type> p_m_tmp2(n, (type)0);
        std::vector<type> p_m_comp(n, (type)0);

        P_new = p_new;
        P_m = p_m;
        P_f1 = p_f1;
        P_f2 = p_f2;
        P_tmp1 = p_tmp1;
        P_tmp2 = p_tmp2;
        P_comp = p_comp;
        P_m_tmp1 = p_m_tmp1;
        P_m_tmp2 = p_m_tmp2;
        P_m_comp = p_m_comp;
    }

    void Euler_solve(type time, type dt, type tau)
    {
        long long int iter = static_cast<long long int> (time/dt);
        long long int write = static_cast<long long int> (tau/dt);
        size_t size = static_cast<size_t> (time/tau);
        std::vector<std::vector<type>> p(size, std::vector<type> (n, (type)0));
        std::vector<type> t(size, (type)0);
        int I = 0;
        int j = 1;
        p[0] = P_old;
        t[0] = (type)0;
        for(long long int i=0; i<iter; ++i){
            if (I == write){
                p[j] = P_old;
                t[j] = i*dt;
                ++j;
                I = 0;
            }
            expression->f(P_f1, i*dt, P_old);
            for(auto i=0; i<n; ++i)
                P_new[i] = P_old[i] + P_f1[i]*dt;

            P_old = P_new;
            ++I;
        }

        P = p;
        T = t;
    }

    void Hoen_solve(type time, type dt, type tau)
    {
        long long int iter = static_cast<long long int> (time/dt);
        long long int write = static_cast<long long int> (tau/dt);
        size_t size = static_cast<size_t> (time/tau);
        std::vector<std::vector<type>> p(size, std::vector<type> (n, (type)0));
        std::vector<type> t(size, (type)0);
        int I = 0;
        int j = 1;
        p[0] = P_old;
        t[0] = (type)0;
        for(long long int i=0; i<iter; ++i){
            if (I == write){
                p[j] = P_old;
                t[j] = i*dt;
                ++j;
                I = 0;
            }
            expression->f(P_f1, i*dt, P_old);
            for(int i=0; i<n; ++i)
                P_m[i] = P_old[i] + P_f1[i]*dt;
            expression->f(P_f2, (i+1)*dt, P_m);
            for(int i=0; i<n; ++i)
                P_new[i] = P_old[i] + (P_f1[i] + P_f2[i])*dt*0.5;

            P_old = P_new;
            ++I;
        }

        P = p;
        T = t;
    }

    void Hoen_solve_with_kahan(type time, type dt, type tau)
    {
        long long int iter = static_cast<long long int> (time/dt);
        long long int write = static_cast<long long int> (tau/dt);
        size_t size = static_cast<size_t> (time/tau);
        std::vector<std::vector<type>> p(size, std::vector<type> (n, (type)0));
        std::vector<type> t(size, (type)0);
        int I = 0;
        int j = 1;
        p[0] = P_old;
        t[0] = (type)0;
        for(long long int i=0; i<iter; ++i){
            if (I == write){
                p[j] = P_old;
                t[j] = i*dt;
                ++j;
                I = 0;
            }
            expression->f(P_f1, i*dt, P_old);
            for(int i=0; i<n; ++i)
                P_tmp1[i] = P_f1[i]*dt - P_comp[i];
            for(int i=0; i<n; ++i)
                P_tmp2[i] = P_old[i] + P_tmp1[i];
            for(int i=0; i<n; ++i)
                P_comp[i] = (P_tmp2[i] - P_old[i]) - P_tmp1[i];
            for(int i=0; i<n; ++i)
                P_m[i] = P_tmp2[i];

            expression->f(P_f2, (i+1)*dt, P_m);
            for(int i=0; i<n; ++i)
                P_m_tmp1[i] = (P_f1[i] + P_f2[i])*dt/2 - P_m_comp[i];
            for(int i=0; i<n; ++i)
                P_m_tmp2[i] = P_old[i] + P_m_tmp1[i];
            for(int i=0; i<n; ++i)
                P_m_comp[i] = (P_m_tmp2[i] - P_old[i]) - P_m_tmp1[i];
            for(int i=0; i<n; ++i)
                P_new[i] = P_m_tmp2[i];

            P_old = P_new;
            ++I;
        }

        P = p;
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
                out << T[i];
                for(int j=0; j<n; ++j){
                    out << ' ' << P[i][j] << ' ';
                }
                out << '\n';
            }
        }
        out.close();
    }
};


int main()
{
    Solver<double> s;
    FrictionPendWithForce<double> pend1(1.0, 0.1, 2.0, 1.3);
    //FrictionPend<double> pend1(1.0, 0.1);

    s.take_exp(&pend1, {0.0, 1.0});
    //s.Euler_solve(10, 0.001, 0.05);
    s.Hoen_solve(150, 0.001, 0.05);
    //s.Hoen_solve_with_kahan(50, 0.001, 0.05);
    s.save_data("Data_friction_with_force.txt");
    std::cout << "Finished" << '\n';
    return 0;
}

