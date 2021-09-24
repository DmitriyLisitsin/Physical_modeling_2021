#include <array>
#include <iostream>

int main()
{
    const int N = 10;
    //std::cin >> N;
    int a, b, c;
    std::array<int, N> arr;
    arr[0] = 1;
    arr[1] = 1;
    std::cout << arr[0] << ' ' << arr[1] <<' ';
    for(int i=2; i<N; ++i){
        arr[i] = arr[i-1]+arr[i-2];
        std::cout << arr[i] << ' ';
    }
    return 0;
}
