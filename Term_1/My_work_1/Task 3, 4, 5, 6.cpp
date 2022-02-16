#include <iostream>
#include <fstream>

int main()
{
    int N = 30;
    std::cin >> N;

    std::ofstream out;
    out.open("Digits.txt");
    if (out.is_open()){
        for(int i=1; i<N+1; ++i){
            out << i << ' ';
        }
    }
    out.close();
    return 0;
}
