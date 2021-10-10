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

    T = 1;
    R = 6400;
    v0 = 0;
    dt = 1.0/pow(10, 9);
    k = 1.0d;
    double time_step = 0.1;
    if (regime == 1){
        T = 1;
        R = 6400;
        v0 = 0;
        k = 1.0d;
        dt = 1.0/pow(10, 9);
    }

    long long int iter = T/dt;
    long long int write = time_step/dt;
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
        std::cout << iter << std::endl;
        std::cout << write << std::endl;
        for(int i=0; i<iter; ++i){
            //std::cout << "I'm here" <<std::endl;
            a_new = a_old + b_old*dt;
            b_new = b_old - a_old*k*dt;
            if (regime == 0 && i % write == 0)
                out << t << ';' << a_old << ';' << b_old << '\n';
            a_old = a_new;
            b_old = b_new;
            t += dt;
        }
        if (regime == 1)
            //std::cout << (k*pow(a_old, 2) + pow(b_old, 2))/2 << '\n';
            out << dt << ';' << (k*pow(a_old, 2) + pow(b_old, 2))/2 << '\n';
    }
    out.close();
    std::cout << "finished" << '\n';
    return 0;
}
