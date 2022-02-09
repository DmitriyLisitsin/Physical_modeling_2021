#include <iostream>
#include <cmath>

void KahanSum(float T, float dt)
{
    std::cout << "\nKahan sum" << '\n';
    float t = 0.0;
    long long int iter = static_cast<long long int> (T/dt);
    std::cout << "Iter = " << iter << '\n';
    long long int i = 0;
    float c = 0.0;
    while (t < T){
        float y = dt - c;
        float tt = t + y;
        c = (tt - t) - y;
        t = tt;

        ++i;
    }
    std::cout << "   i = " << i << '\n';
}

void UsualSum(float T, float dt)
{
    std::cout << "\nUsual sum" << '\n';
    float t = 0.0;
    long long int iter = static_cast<long long int> (T/dt);
    std::cout << "Iter = " << iter << '\n';
    long long int i = 0;
    while (t<T){
        t += dt;
        ++i;
    }
    std::cout << "   i = " << i << '\n';
}

int main()
{
    float T = 1.0;
    float dt = 1.0/std::pow(10, 8);
    //UsualSum(T, dt);

    KahanSum(T, dt);

    return 0;
}
