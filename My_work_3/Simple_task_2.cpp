#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

int main()
{
    int T;
    double dt, k, R, v0;

    T = 10;
    R = 6400000-10;
    v0 = 10.0;
    dt = 0.1;
    k = 3.0d;
    int iter = T/dt;
    double a_old = R;
    double b_old = v0;
    double a_new, b_new, t = 0.0;

    std::ofstream out;
    out.open("Data.txt");
    if (out.is_open()){
        out << T << ';' << dt << ';' << k << ';' << R << ';' << v0 << '\n';
        for(int i=0; i<iter; ++i){
            a_new = a_old + b_old*dt;
            b_new = b_old - a_old*k*dt;
            out << t << ';' << a_old << ';' << b_old << '\n';
            a_old = a_new;
            b_old = b_new;
            t += dt;
        }
    }
    out.close();
    std::cout << "finished" << '\n';
    return 0;
}
