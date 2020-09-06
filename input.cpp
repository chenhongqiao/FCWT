//
// Created by harry on 9/4/20.
//

#include <vector>
#include <iostream>

std::string read_para(std::istream &in) {
    std::string p;
    while (in) {
        char tmp;
        in.get(tmp);
        p += tmp;
    }
    return p;
}

std::vector<std::string> read_vocab(std::istream &in) {
    std::string tv;
    std::vector<std::string> v;
    while (in) {
        char tc;
        in.get(tc);
        if (in && (tc == 10 || tc == 32)) {
            v.push_back(tv);
            tv.clear();
        } else {
            tv += tc;
        }
    }
    return v;
}
