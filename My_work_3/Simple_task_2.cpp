#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

int main()
{
    int T;
    double dt, k, R;

    T = 100;
    R = 3400000;
    dt = 0.1;
    k = 1.0d;

    int iter = T/dt;
//    std::vector<double> a(iter, 0);
//    std::vector<double> b(iter, 0);
//    std::vector<double> time(iter, 0);
//    a[0] = R;
//    for(int i=0; i<iter-1; ++i){
//        a[i+1] = a[i] + b[i]*dt;
//        b[i+1] = b[i] - a[i]*k*dt;
//        time[i+1] = time[i] + dt;
//    }
    double a_old = R;
    double b_old = 0.0;
    double a_new, b_new, t = 0.0;

    std::ofstream out;
    out.open("Data.txt");
    if (out.is_open()){
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
