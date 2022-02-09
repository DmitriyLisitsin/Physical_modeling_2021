#include <iostream>
#include <string>
#include <random>
#include <chrono>
#include <vector>
#include <fstream>

int rand_int(int K)
{
    std::mt19937_64 rng{static_cast<long long unsigned int>(time(0))};
    std::uniform_int_distribution<int> dstr(1, K);
    return dstr(rng);
}

std::vector<int> rand_int_vec(int N, int K)
{
    std::vector<int> vec(N);
    std::mt19937_64 rng{static_cast<long long unsigned int>(time(0))};
    std::uniform_int_distribution<int> dstr(1, K);
    for(int i=0; i<N; ++i){
        vec[i] = dstr(rng);
    }
    return vec;
}

std::vector<double> normal_real_vec(int N, double M, double sigma)
{
    std::vector<double> vec(N);
    std::mt19937_64 rng{static_cast<long long unsigned int>(time(0))};
    std::normal_distribution<double> dstr(M , sigma);
    for(int i=0; i<N; ++i){
        vec[i] = dstr(rng);
    }
    return vec;
}

template<typename I>
std::vector<int> hist(int n, I beg, I end)
{
    std::vector<int> vec(n, 0);
    auto min = *beg;
    auto max = min;
    for(I i=beg; i!= end; ++i){
        if (*i > max){
            max = *i;
        }
        else if (*i < min){
            min = *i;
        }
    }
    double step = 1.0 * (max - min)/n;
    int a = 0;
    for(I i=beg; i!= end; ++i){
        a = std::floor((*i-min)/step);
        if (a == n) --a;
        ++vec[a];
    }
    return vec;
}

template<typename I>
void save(std::string path, I beg, I end)
{
    std::ofstream out;
    out.open(path);
    if (out.is_open()){
        for(I i=beg; i!=end; ++i){
            out << *i << ' ';
        }
    }
}

template<typename I>
void print(I beg, I end)
{
    for(I i=beg; i!= end; ++i){
        std::cout << *i << ' ';
    }
    std::cout << '\n';
}

int main()
{
    int N = 100;
    int K = 50;
    std::vector<int> A = rand_int_vec(N, K);
    print(A.begin(), A.end());

    std::cout << rand_int(10) << '\n';

    std::vector<double> B = normal_real_vec(10, 0.0, 2.0);
    print(B.begin(), B.end());

    std::vector<int> C = hist(2, A.begin(), A.end());
    print(C.begin(), C.end());

    save("Array.txt", A.begin(), A.end());

    return 0;
}


