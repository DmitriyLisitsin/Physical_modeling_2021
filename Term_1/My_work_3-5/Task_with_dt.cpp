#include <iostream>
#include <cmath>

int main()
{
    double dt = 1.0/std::pow(2, 50);
    double T = 1.0;
    double t = 0.0;
    long long int iter = static_cast<long long int> (T/dt);
    std::cout << "Iter = " << iter << '\n';
    long long int i = 0;
    while (t<T){
        t += dt;
        ++i;
    }
    std::cout << "   i = " << i << '\n';
    return 0;
}
