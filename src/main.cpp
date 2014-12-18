#include <main.h>
#include <iostream>
#include <fstream>
#include <bitset>
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

typedef u_int32_t hashtype;
#define HASH_MASK 0x1F
#define HASHSIZE 4
#define HASHBITS (8*HASHSIZE)

static inline hashtype get_hash_mask(size_t spinquadCount, int sq_j, size_t parts, int part_i)
{
    //std::cerr << __PRETTY_FUNCTION__ << " " << spinquadCount << " " << sq_j << " " << parts << " " << part_i << " ";

    hashtype retval = 0;
    size_t offset = sq_j % HASHBITS;
    size_t currentPart = parts - 1 - sq_j / HASHBITS;

    if (part_i == currentPart)
        retval = (1 << offset);

    //std::cerr << "RV: " << retval << std::endl;
    return retval;
}

template<typename T>
inline static T inc_div(T a, T b)
{
    return (a+b-1) / b;
}

int main() {
    std::vector<float> spinquads = readFile("../examples/spin_quadrics_compress.txt");
    //std::vector<float> spinquads = readFile("../examples/spin_quadrics_knob.txt");
    unsigned long long seed = 2568305073;
    cucs_set_seed(seed);
    std::vector<u_int32_t> n1, n2;
    std::vector<float4> v;
    //v = cucs_compute_random_spinors(1000000);
    //cucs_compute_unique_spinors(spinquads, v);
    //cucs_compute_neighbours(spinquads, v, n1, n2);

    for (int i=0; i < 10; ++i)
    cucs_compute_spinors_and_neighbours(spinquads, 1000000, v, n1, n2);
    std::cout << "Size: " << v.size() << std::endl;
    std::cout << "Size: " << n1.size() << " " << n2.size() << std::endl;
    std::cout << "Size: " << spinquads.size()/10 << std::endl;

    //std::cerr << n1.size() << " " << n2.size() << std::endl;

    //Sort pairs
    //std::vector<std::pair<u_int32_t, u_int32_t> > nbs(n1.size());
    //for (int j=0;j<n1.size();++j)
        //nbs[j] = std::make_pair(n1[j], n2[j]);

    //std::sort(nbs.begin(), nbs.end());

    //for (int j=0;j<nbs.size();++j)
    {
        //std::cout << nbs[j].first << " " << nbs[j].second << std::endl;
    }

    //for (int j=0;j<10/*spinquads.size()*/;++j)
    //for (int j=0;j<spinquads.size();++j)
    {
        //std::cout << cucs_to_coord_string(v[j], spinquads) << std::endl;
    }
    //for(int i=0;i<10;++i)
    //    std::cout << d_hashes[i] << "\n";

    return 0;
}
