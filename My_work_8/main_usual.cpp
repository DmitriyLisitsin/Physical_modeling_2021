#include <iostream>
#include <string>

#include "solver.h"
#include "heun_solver.h"
#include "rk4_solver.h"
#include "saving.h"
#include "process.h"

#include "arbitrary_pend1.h"
#include "arbitrary_pend2.h"

int main()
{
    std::string folder = "Arbitrary_pend_data/";
    std::string par = "Params_arbitrary.txt";

    int a, se, sh, srk, shh;

    double T, dt, tau, w, b, W, F0, x0, v0;        // can be changed

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

        out.close();
    }

    ArbitraryPend1<double> pendl(w, b, W, F0);     // can be changed

    std::string name3 = "RK4/Data_" + std::to_string(a) + ".txt";
    std::string name2 = "Heun/Data_" + std::to_string(a) + ".txt";
    std::string name1 = "Euler/Data_" + std::to_string(a) + ".txt";

    process(&pendl, T, dt, tau, {w, b, W, F0}, {x0, v0},
            folder+name1, folder+name2, folder+name3, "", se, sh, srk, shh);

    ChangeStringInFileC(folder+par, CountLinesInFile(folder+par)-1, std::to_string(a+1));

    std::cout << "Finished" << '\n';
    return 0;
}

