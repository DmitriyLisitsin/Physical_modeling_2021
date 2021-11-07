#ifndef saving_h
#define saving_h

#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

template<typename type>
void save_data(std::string path, std::vector<type> const &T,
               std::vector<std::vector<type>> const &P, std::vector<type> const &params, int n)
    {
        std::ofstream out;
        out.open(path);
        if (out.is_open()){
            out << std::setprecision(8);
            out << std::scientific;
            for(int i = 0; i<params.size()-1; ++i){
                out << params[i] << ' ';
            }
            out << params[params.size()-1] << '\n';
            for(int i = 0; i<T.size(); ++i){
                out << T[i];
                for(int j=0; j<n; ++j){
                    out << ' ' << P[i][j] << ' ';
                }
                out << '\n';
            }
        }
        out.close();
    }

#endif // saving_h
