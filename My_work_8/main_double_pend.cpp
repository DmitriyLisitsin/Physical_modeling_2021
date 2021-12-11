#include <iostream>
#include <string>

#include "solver.h"
#include "heun_solver.h"
#include "rk4_solver.h"
#include "saving.h"
#include "process.h"

#include "arbitrary_pend1.h"
#include "arbitrary_pend2.h"
#include "pend_with_friction_and_force.h"
#include "double_pend.h"

int main()
{
    std::string folder = "Double_pend_data/";
    std::string par = "Params_double_pend.txt";

    int a, se, sh, srk, shh;

    double T, dt, tau, m1, m2, L1, L2, x10, x20, v10, v20;        // can be changed

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
        m1 = stod(str1);

        getline(out, str2);
        getline(out, str1);
        m2 = stod(str1);

        getline(out, str2);
        getline(out, str1);
        L1 = stod(str1);

        getline(out, str2);
        getline(out, str1);
        L2 = stod(str1);

        getline(out, str2);
        getline(out, str1);
        x10 = stod(str1);

        getline(out, str2);
        getline(out, str1);
        x20 = stod(str1);

        getline(out, str2);
        getline(out, str1);
        v10 = stod(str1);

        getline(out, str2);
        getline(out, str1);
        v20 = stod(str1);

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

    DoublePend<double> pendl(m1, m2, L1, L2, 9.8);

    std::string name3 = "RK4/Data_" + std::to_string(a) + ".txt";
    std::string name2 = "Heun/Data_" + std::to_string(a) + ".txt";
    std::string name1 = "Euler/Data_" + std::to_string(a) + ".txt";

    process(&pendl, T, dt, tau, {m1, m2, L1, L2}, {x10, x20, v10, v20},
            folder+name1, folder+name2, folder+name3, "", se, sh, srk, shh);

    ChangeStringInFileC(folder+par, CountLinesInFile(folder+par)-1, std::to_string(a+1));

    std::cout << "Finished" << '\n';
    return 0;
}

