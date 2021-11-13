#include <iostream>
#include <string>

#include "solver.h"
#include "heun_solver.h"
#include "saving.h"

#include "pend_with_friction_and_force.h"

template<typename type>
void process(type T, type dt, type tau, type w, type b, type W, type F0, type x0, type v0,
             std::string file1, std::string file2, std::string file3, int se, int sh, int shh)
{
    Solver<type> s;
    HeunSolver<type> hs;

    FrictionPendWithForce<type> pend1(w, b, W, F0);

    if(sh){
        hs.take_exp(&pend1, {x0, v0});
        hs.solve(T, dt, tau);
        save_data(file2, hs.get_time(), hs.get_values(), {x0, v0, w, b, W, F0}, 2);
    }

    if(se){
        s.take_exp(&pend1, {x0, v0, w, b, W, F0});
        s.solve(T, dt, tau);
        save_data(file1, s.get_time(), s.get_values(), {x0, v0, w, b, W, F0}, 2);
    }
}

int main()
{
    std::string folder = "Force_pend_data/";
    std::string par = "Params.txt";

    int a, se, sh, shh;
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
        shh = stoi(str1);

        getline(out, str2);
        getline(out, str1);
        a = stoi(str1);
    }
    out.close();

    std::string name2 = "FR/Heun/Data_" + std::to_string(a) + ".txt";
    std::string name1 = "FR/Euler/Data_" + std::to_string(a) + ".txt";

    process(T, dt, tau, w, b, W, F0, x0, v0, folder+name1, folder+name2, "", se, sh, shh);

    ChangeStringInFileC(folder+par, CountLinesInFile(folder+par)-1, std::to_string(a+1));

//    std::vector<double> Wa = {0.3, 0.35, 0.4, 0.45, 0.50, 0.55, 0.60, 0.64, 0.68, 0.72, 0.76, 0.80, 0.82, 0.84, 0.86,
//                            0.88, 0.90, 0.92, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99, 1.0, 1.01, 1.02, 1.03, 1.04,
//                            1.05, 1.06, 1.08, 1.10, 1.12, 1.14, 1.16, 1.18, 1.2, 1.24, 1.28, 1.32, 1.36, 1.4, 1.45,
//                            1.5, 1.55, 1.6, 1.65, 1.7, 1.75, 1.8, 1.85, 1.9, 1.95, 2.0};
//    for(int i=0; i<Wa.size(); ++i){
//        std::cout << Wa[i] << '\n';
//        process(T, dt, tau, w, b, Wa[i], F0, x0, v0,
//                folder+"FR/Euler/Data_"+std::to_string(i+1)+".txt", folder+"FR/Heun/Data_"+std::to_string(i+1) + ".txt",
//                "", se, sh, shh);
//    }
    std::cout << "Finished" << '\n';
    return 0;
}



