#include <iostream>
#include <string>

#include "solver.h"
#include "heun_solver.h"
#include "rk4_solver.h"
#include "saving.h"

#include "arbitrary_pend1.h"

template<typename type>
void process(type T, type dt, type tau, type w, type b, type W, type F0, type x0, type v0,
             std::string file1, std::string file2, std::string file3, std::string file4,
             int se, int sh, int srk, int shh)
{
    Solver<type> s;
    HeunSolver<type> hs;
    RK4Solver<type> rks;

    ArbitraryPend1<type> pend1(w, b, W, F0);

    if(sh){
        hs.take_exp(&pend1, {x0, v0});
        hs.solve(T, dt, tau);
        save_data(file2, hs.get_time(), hs.get_values(), hs.get_energy(), {x0, v0, w, b, W, F0}, 2);
    }

    if(se){
        s.take_exp(&pend1, {x0, v0});
        s.solve(T, dt, tau);
        save_data(file1, s.get_time(), s.get_values(), s.get_energy(), {x0, v0, w, b, W, F0}, 2);
    }
    if(srk){
        rks.take_exp(&pend1, {x0, v0});
        rks.solve(T, dt, tau);
        save_data(file3, rks.get_time(), rks.get_values(), rks.get_energy(), {x0, v0, w, b, W, F0}, 2);
    }
}

int main()
{
    std::string folder = "Arbitrary_pend_data/";
    std::string par = "Params_arbitrary.txt";

    int a, se, sh, srk, shh;
    double T, dt, tau, w, b, W, F0, x0, v0;
    std::ifstream out(folder+par);
    std::string str1, str2;
    if (out.is_open()){
        getline(out, str2);
        getline(out, str1);
        T = stod(str1);

        getline(out, str2);
        getline(out, str1);
        dt = stod(str1);

        getline(out, str2);
        getline(out, str1);
        tau = stod(str1);

        getline(out, str2);
        getline(out, str1);
        w = stod(str1);

        getline(out, str2);
        getline(out, str1);
        b = stod(str1);

        getline(out, str2);
        getline(out, str1);
        W = stod(str1);

        getline(out, str2);
        getline(out, str1);
        F0 = stod(str1);

        getline(out, str2);
        getline(out, str1);
        x0 = stod(str1);

        getline(out, str2);
        getline(out, str1);
        v0 = stod(str1);

        getline(out, str2);
        getline(out, str1);
        se = stoi(str1);

        getline(out, str2);
        getline(out, str1);
        sh = stoi(str1);

        getline(out, str2);
        getline(out, str1);
        srk = stoi(str1);

        getline(out, str2);
        getline(out, str1);
        shh = stoi(str1);

        getline(out, str2);
        getline(out, str1);
        a = stoi(str1);
    }
    out.close();

    std::string name3 = "RK4/Data_" + std::to_string(a) + ".txt";
    std::string name2 = "Heun/Data_" + std::to_string(a) + ".txt";
    std::string name1 = "Euler/Data_" + std::to_string(a) + ".txt";

    process(T, dt, tau, w, b, W, F0, x0, v0, folder+name1, folder+name2, folder+name3, "", se, sh, srk, shh);

    ChangeStringInFileC(folder+par, CountLinesInFile(folder+par)-1, std::to_string(a+1));

    std::cout << "Finished" << '\n';
    return 0;
}
