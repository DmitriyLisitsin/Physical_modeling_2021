#include <iostream>
#include <vector>
#include <random>
#include <fstream>
#include <chrono>
#include <iomanip>

double ProbTest(std::vector<int> seq0, int n, int seed)
{
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<int> dstr(1, 3);
    int sum = 0;
    for(int i=0; i<n; ++i){
        int seq1 = dstr(rng);
        int seq2 = dstr(rng);
        int seq3 = 0;
        int s = 0;
        sum += 2;
        //std::cout << seq0[2] << '\n';
        while(s == 0){
            seq3 = dstr(rng);
            //std::cout << seq3 << ' ';
            if(seq1 == seq0[0] && seq2 == seq0[1] && seq3 == seq0[2]){
                s = 1;
            }
            //std::cout <<(seq3 == seq0[2]) << '\n';
            seq1 = seq2;
            seq2 = seq3;
            ++sum;
        }
        //sum += j;
    }
    return 1.0*sum/n;
}

int main()
{
//    std::vector<std::string> sequences = {"111", "112", "113", "121", "122", "123","131", "132", "133",
//                                          "211", "212", "213", "221", "222", "223", "231", "232", "233",
//                                          "311", "312", "313", "321", "322", "323", "331", "332", "333"};
    std::vector<std::vector<int>> sequences = {{1,1,1}, {1,1,2}, {1,1,3}, {1,2,1}, {1,2,2}, {1,2,3}, {1,3,1}, {1,3,2}, {1,3,3},
                                               {2,1,1}, {2,1,2}, {2,1,3}, {2,2,1}, {2,2,2}, {2,2,3}, {2,3,1}, {2,3,2}, {2,3,3},
                                               {3,1,1}, {3,1,2}, {3,1,3}, {3,2,1}, {3,2,2}, {3,2,3}, {3,3,1}, {3,3,2}, {3,3,3}};
    int n = 100000;
    int seed = 0;
    std::ofstream out;
    out.open("monkey_data.txt");
    if (out.is_open()){
        for (auto seq: sequences){
            seed = static_cast<long long unsigned int>(time(0)) + seq[2];
            double p = ProbTest(seq, n, seed);
            //std::cout << seq.size() << '\n';
            out << seq[0] << seq[1] << seq[2] << ' ' << p << '\n';
            std::cout << seq[0] << seq[1] << seq[2] << ' ' << p << '\n';
        }
    }
    return 0;
}
