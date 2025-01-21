#include <algorithm>
#include <array>
#include <iostream>
#include <string>
#include <vector>

using ip_address = std::array<int, 4>;
using ip_pool_type = std::vector<ip_address>;

void OutPutIP(const ip_address& ip) {
    for (auto it = ip.cbegin(); it != ip.cend(); ++it) {
        if (it != ip.cbegin()) std::cout << ".";
        std::cout << *it;
    }
    std::cout << std::endl;
}

void FilterAny(const ip_pool_type& ip_pool, int any) {
    for (const auto& ip : ip_pool) {
        if (std::find(ip.begin(), ip.end(), any) != ip.end()) {
            OutPutIP(ip);
        }
    }
}

void FilterOutput(const ip_pool_type& ip_pool, int fst) {
    for (const auto& ip : ip_pool) {
        if (ip[0] == fst) {
            OutPutIP(ip);
        }
    }
}

void FilterOutput(const ip_pool_type& ip_pool, int fst, int snd) {
    for (const auto& ip : ip_pool) {
        if (ip[0] == fst && ip[1] == snd) {
            OutPutIP(ip);
        }
    }
}

struct MySort {
    bool operator()(const ip_address& ip1, const ip_address& ip2) const {
        return ip1 > ip2;
    }
};

auto SplitStr(const std::string& str, char d) -> std::vector<std::string> {
    std::vector<std::string> r;
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);

    while (stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

ip_address Split(const std::string& str, char d) {
    ip_address result{};
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);

    for (int i = 0; i < 4; ++i) {
        result[i] = std::stoi(str.substr(start, stop - start));
        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    return result;
}

int main() {
    try {
        ip_pool_type ip_pool;

        for (std::string line; std::getline(std::cin, line);) {
            std::vector<std::string> v = SplitStr(line, '\t');
            ip_pool.push_back(Split(v.at(0), '.'));
        }

        std::sort(ip_pool.begin(), ip_pool.end(), MySort());

        for (const auto& ip : ip_pool) {
            OutPutIP(ip);
        }

        std::cout << "Filter by 1st byte (1):" << std::endl;
        FilterOutput(ip_pool, 1);

        std::cout << "Filter by 1st and 2nd byte (46, 70):" << std::endl;
        FilterOutput(ip_pool, 46, 70);

        std::cout << "Filter any (46):" << std::endl;
        FilterAny(ip_pool, 46);
    }
    catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}