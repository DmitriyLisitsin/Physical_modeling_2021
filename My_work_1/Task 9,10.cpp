#include <array>
#include <vector>
#include <iostream>

int main()
{
    const int N = 10;
    //std::cin >> N;
    //std::array<int, N> arr;
    std::vector<double> arr(N, 0);
    std::cout << std::scientific;
    for(int i=0; i<N; ++i){
        arr[i] = 1.0/(i+1);
        std::cout << arr[i] << ' ';
    }
    return 0;
}

