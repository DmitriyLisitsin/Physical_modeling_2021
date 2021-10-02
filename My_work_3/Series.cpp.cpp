#include <iostream>
#include <cmath>

double two_power(int n)
{
    return 1.0/std::pow(2, n);
}

double harmonic(int n)
{
    return 1.0/n;
}

double back_squares(int n)
{
    return 1.0/(n*n);
}

double Sum(int N, double f(int))
{
    double sum;
    for(int i = 1; i<N; ++i)
        sum += f(i);
    return sum;
}

int main()
{
    int N = 1000;
    std::cout << Sum(N, two_power) << '\n';
    std::cout << Sum(N, harmonic) << '\n';
    std::cout << Sum(N, back_squares) << '\n';
    return 0;
}
