#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>

int main()
{
    int T;
    double dt, k, R, v0;

    int regime = 0;


    double time_step = 0.05;
    T = 1;
    R = 6400;
    v0 = 0;
    dt = 1.0/pow(10, 6);
    k = 1.0d;

    if (regime == 1){
        T = 1;
        R = 6400;
        v0 = 0;
        k = 1.0d;
        dt = 1.0/pow(10, 6);
    }

    long long int iter = static_cast<long long int> (T/dt);
    long long int write = static_cast<long long int> (time_step/dt);
    double a_old = R;
    double b_old = v0;
    double a_new, b_new, t = 0.0;

    std::ofstream out;
    std::string file1 = "Data.txt";
    std::string file2 = "Energy.txt";

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
            a_new = a_old + b_old*dt;
            b_new = b_old - a_old*k*dt;
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
    return 0;
}
