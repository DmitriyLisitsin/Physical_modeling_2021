#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

template<typename type>
void count()
{
    int T;
    type dt, k, R, v0;

    int regime = 0;
    type time_step = 0.1;

    if (regime == 0){
        T = 100;
        R = 6400;
        v0 = 0;
        k = 1.0;
        dt = 1.0/pow(10, 3);
    }
    else if (regime == 1){
        T = 1;
        R = 6400;
        v0 = 0;
        k = 1.0;
        dt = 1.0/pow(10, 5);
    }

    long long int iter = static_cast<long long int> (T/dt);
    long long int write = static_cast<long long int> (time_step/dt);
    type a_old = R;
    type b_old = v0;
    type a_new, a_tmp1, a_tmp2, a_comp = (type)0;
    type a_m, a_m_tmp1, a_m_tmp2, a_m_comp = (type)0;
    type b_new, b_tmp1, b_tmp2, b_comp = (type)0;
    type b_m, b_m_tmp1, b_m_tmp2, b_m_comp = (type)0;
    type t = (type)0, t_new, t_tmp1, t_tmp2, t_comp = (type)0;

    std::ofstream out;
    std::string file1 = "Data(Kohen).txt";
    std::string file2 = "Energy(Kohen).txt";

    if (regime == 0){
        out.open(file1);
    }
    else if (regime == 1){
        out.open(file2, std::ios::app);
    }
    if (out.is_open()){

        out << std::setprecision(14);
        out << std::scientific;
        if (regime == 0){
            out << T << ';' << dt << ';' << k << ';' << R << ';' << v0 << '\n';
        }
        for(long long int i=0; i<iter; ++i){
            if (regime == 0 && i % write == 0){
              std::cout << "Write" << '\n';
              out << t << ';' << a_old << ';' << b_old << '\n';
            }
//            a_m = a_old + b_old*dt;
//            b_m = b_old - a_old*k*dt;
//            a_new = a_old + (b_old + b_m)/2*dt;
//            b_new = b_old - (a_old + a_m)*k/2*dt;
//            t += dt;

            a_tmp1 = b_old*dt - a_comp;
            a_tmp2 = a_old + a_tmp1;
            a_comp = (a_tmp2 - a_old) - a_tmp1;
            a_m = a_tmp2;

            b_tmp1 = -k*a_old*dt - b_comp;
            b_tmp2 = b_old + b_tmp1;
            b_comp = (b_tmp2 - b_old) - b_tmp1;
            b_m = b_tmp2;

            a_m_tmp1 = (b_m + b_old)/2*dt - a_m_comp;
            a_m_tmp2 = a_old + a_m_tmp1;
            a_m_comp = (a_m_tmp2 - a_old) - a_m_tmp1;
            a_new = a_m_tmp2;

            b_m_tmp1 = -(a_m + a_old)*k/2*dt - b_m_comp;
            b_m_tmp2 = b_old + b_m_tmp1;
            b_m_comp = (b_m_tmp2 - b_old) - b_m_tmp1;
            b_new = b_m_tmp2;

            t_tmp1 = dt - a_comp;
            t_tmp2 = t + t_tmp1;
            t_comp = (t_tmp2 - t) - t_tmp1;
            t_new = t_tmp2;
            t = t_new;

            a_old = a_new;
            b_old = b_new;
        }
        if (regime == 1){
            out << dt << ';' << (k*pow(a_old, 2) + pow(b_old, 2))/2 << '\n';
        }
    }
    out.close();
    std::cout << "Finished" << '\n';
}

int main()
{
    count<float>();
    return 0;
}
