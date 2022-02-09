#include <iostream>
#include <fstream>

int main()
{
    int N = 10;
    //std::cin >> N;
    int a, b, c;
    a = b = 1;
    std::ofstream out;
    out.open("Fibonacci.txt");
    if (out.is_open()){
        out << 1 << ' ' << a << '\n';
        out << 2 << ' ' << b << '\n';
        for(int i=3; i<N+1; ++i){
            c = a+b;
            out << i << ' ' << c << '\n';
            a = b;
            b = c;
        }
    }
    out.close();
    return 0;
}

