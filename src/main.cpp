#include <main.h>
#include <iostream>
#include <fstream>
#include <boost/regex.hpp>


std::vector<float> readFile(std::string path)
{
    std::vector<float> quads;
    boost::regex line_regex("\\[([ ]*-?[0-9]+\\.?[0-9]*[ ]*){10}\\]");
    boost::regex number_regex("-?[0-9]+\\.?[0-9]*");

    std::ifstream infile(path.c_str());

    std::string line;
    while (std::getline(infile, line))
    {
        std::vector<float> data;
        boost::smatch results;
        std::string::const_iterator begin = line.begin();
        std::string::const_iterator end = line.end();
        if (boost::regex_match(line, results, line_regex))
        {
            while (boost::regex_search(begin, end, results, number_regex))
            {
                for (int i=0;i<results.size(); ++i)
                {
                    std::stringstream ss;
                    ss << results[i];
                    float v;
                    ss >> v;
                    quads.push_back(v);
                }
                begin = results[results.size()-1].second;
            }
        }
    }

    return quads;
}

int main() {
    std::vector<float> spinquads = readFile("/home/kamil/Projekty/Mgr/cucs_demo/build/spin_quadrics_compress.txt");
    unsigned long long seed = 2568305073;
    cucs_set_seed(seed);
    std::vector<u_int32_t> n1, n2;
    std::vector<float4> v = cucs_compute_random_spinors(1000000);
    cucs_compute_unique_spinors(spinquads, v);
    cucs_compute_neighbours(spinquads, v, n1, n2);
    //std::vector<float4> v;
    //cucs_compute_unique_spinors(spinquads, v);
    //cucs_compute_spinors_and_neighbours(spinquads, 1000000, v, n1, n2);
    std::cout << "Size: " << v.size() << std::endl;
    std::cout << "Size: " << n1.size() << " " << n2.size() << std::endl;
    //cucs_entry();
    return 0;
}
