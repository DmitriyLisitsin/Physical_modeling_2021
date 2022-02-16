#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include <iomanip>

template<typename I>
void print(I beg, I end)
{
    for(I i=beg; i!= end; ++i){
        std::cout << *i << ' ';
    }
    std::cout << '\n';
}

double ProbTest(int N, int K, int n, int seed)
{
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<int> dstr(0, K-1);
    int good = 0;
    for(int i=0; i<n; ++i){
        std::vector<int> boxes(K, 0);
        int a=0;
        for(int j=0; j<N; ++j){
            a = dstr(rng);
            ++boxes[a];
        }
        int s = 0;
        for(int k=0; k<K; ++k){
            if(boxes[k] == 0){
                s = 1;
            }
        }
        if (s == 0){
            ++good;
        }
    }
    return 1.0*good/n;
}

int main()
{
    int n = 10000;
    int seed = 0;

    int K = 5;

//    std::vector<int> Ns = {50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400, 425, 450, 475,
//                          500, 525, 550, 575, 600, 625, 650, 675, 700};

    std::vector<int> Ns = {5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30};

    std::ofstream out;
    out.open("5_boxes_data_1.txt");
    if (out.is_open()){
        out << std::setprecision(8);
        //out << std::scientific;
        std::cout << std::setprecision(8);
        for (int N: Ns){
            seed = static_cast<long long unsigned int>(time(0)) + N;
            double p = ProbTest(N, K, n, seed);
            out << N << ' ' << p << '\n';
            std::cout << N << ' ' << p << '\n';
        }
    }
    return 0;
}

