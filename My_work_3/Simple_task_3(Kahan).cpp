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


    type time_step = 0.05;
    T = 100;
    R = 6400;
    v0 = 0;
    dt = 1.0/pow(10, 5);
    k = 1.0;

    if (regime == 1){
        T = 1;
        R = 6400;
        v0 = 0;
        k = 1.0;
        dt = 1.0/pow(10, 6);
    }

    long long int iter = static_cast<long long int> (T/dt);
    long long int write = static_cast<long long int> (time_step/dt);
    type a_old = R;
    type b_old = v0;
    type a_new, b_new, a_n, b_n;
    type t = 0.0;

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
            a_n = a_old + b_old*dt;
            b_n = b_old - a_old*k*dt;

            a_new = a_old + (b_old + b_n)/2*dt;
            b_new = b_old - (a_old + a_n)*k/2*dt;

            if (regime == 0 && i % write == 0){
                std::cout << "Write" << '\n';
                out << t << ';' << a_old << ';' << b_old << '\n';
            }

            a_old = a_new;
            b_old = b_new;
            t += dt;
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
