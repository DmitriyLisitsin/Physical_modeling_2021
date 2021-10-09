#include <iostream>
#include <cmath>

float two_power(int n)
{
    return 1.0/std::pow(2, n);
}

float harmonic(int n)
{
    return 1.0/n;
}

float back_squares(int n)
{
    return 1.0/(n*n);
}

float Sum(int N, float f(int))
{
    float sum;
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
