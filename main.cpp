#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include "input.h"
#include <iomanip>

std::map<std::string, short int> vocab_tree(const std::vector<std::string> &v) {
    std::map<std::string, short int> m;
    for (auto &i : v) {
        for (int j = 1; j < i.size(); ++j) {
            if (m[i.substr(0, j)] != 2) {
                m[i.substr(0, j)] = 1;
            }
        }
        m[i] = 2;
    }
    return m;
}

int main() {
    std::ifstream vs;
    std::ifstream ps;
    vs.open("vocab.in");
    ps.open("para.in");

    if (!vs) {
        vs.close();
        std::string vfn;
        std::cout << "Vocabulary file path: ";
        std::cin >> vfn;
        vs.open(vfn);
    }
    if (!ps) {
        ps.close();
        std::string pfn;
        std::cout << "Paragraph file path: ";
        std::cin >> pfn;
        ps.open(pfn);
    }


    std::vector<std::string> v = read_vocab(vs);
    std::map<std::string, short int> vt = vocab_tree(v);
    std::string p = read_para(ps);
    std::map<std::string, int> cnt;

    for (int i = 0; i < p.size(); ++i) {
        std::string can;
        int j;
        for (j = 1; j <= p.size() - i; ++j) {
            if (vt[p.substr(i, j)] == 2) {
                can = p.substr(i, j);
            } else if (vt[p.substr(i, j)] != 1) {
                break;
            }
        }
        if (!can.empty()) {
            i += j - 3;
            cnt[can]++;
        }
    }
    int cvd = 0;
    for (auto &i : v) {
        if (cnt[i] > 0) {
            cvd++;
            std::cout << "(" << cnt[i] << ") " << i << std::endl;
        } else {
            std::cout << "(X)" << " " << i << std::endl;
        }
    }

    std::cout << cvd << "/" << v.size();
    std::cout << " " << std::fixed << std::setprecision(1) << 1.0 * cvd / v.size() * 100 + 0.05 << "% " << std::endl;
    return 0;
}
