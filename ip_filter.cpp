#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


using my_vec = std::vector<std::vector<std::string>>;

void OutPutIP(const std::vector<std::string>& vec){
    for (auto ip_part = vec.cbegin(); ip_part != vec.cend(); ++ip_part)
    {
        if (ip_part != vec.cbegin()) std::cout << ".";
        std::cout << *ip_part;
    }
}

void FilterAny(my_vec& vector, const std::string& any) {
    for (auto& row : vector) {
        if (std::find(row.begin(), row.end(), any) != row.end()) {
            OutPutIP(row);
            std::cout << std::endl;
        }
    }
}

void FilterOutput(my_vec& vector, std::string fst) {
    for (auto& row : vector)
        if (row[0] == fst) {
            OutPutIP(row);
            std::cout << std::endl;
        }
}

void FilterOutput(my_vec& vector, std::string fst, std::string snd) {
    for (auto& row : vector)
        if (row[0] == fst && row[1] == snd) {
            OutPutIP(row);
            std::cout << std::endl;
        }
}


struct MySort {
    bool operator()(const std::vector<std::string>& vec1, const std::vector<std::string>& vec2) const {
        for (size_t i = 0; i < 4; ++i) {
            int num1 = std::stoi(vec1[i]);
            int num2 = std::stoi(vec2[i]);

            if (num1 != num2)
                return num1 < num2;
        }
        return false;
    }
};

auto Split(const std::string &str, char d) -> std::vector<std::string> {
    std::vector<std::string> r;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);

    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

int main(int argc, char const *argv[])
{
    try
    {
        my_vec ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = Split(line, '\t');
            ip_pool.push_back(Split(v.at(0), '.'));
        }

        // TODO reverse lexicographically sort DONE
        std::sort(ip_pool.begin(), ip_pool.end(), MySort());
        for(const auto & ip : ip_pool)
        {
            for(auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part)
            {
                if (ip_part != ip.cbegin())
                {
                    std::cout << ".";

                }
                std::cout << *ip_part;
            }
            std::cout << std::endl;
        }

        //std::cout << "Filter by 1st byte"<< std::endl;
        FilterOutput(ip_pool, "1");
        //std::cout << "Filter by 1st and 2nd byte"<< std::endl;
        FilterOutput(ip_pool, "46", "70");
        //std::cout << "Filter any"<< std::endl;
        FilterAny(ip_pool,  "46");
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
