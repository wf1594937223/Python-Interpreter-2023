#ifndef APPLE_PIE_UTILS_H
#define APPLE_PIE_UTILS_H

#include <string>
#include "int2048.h"
//using int2048 = long long;

long long stringToInt(const std::string& str) {
    int ret = 0, m = str.length();
    for (int i = 0; i < m; i++) {
        if (str[i] != '-')
            ret = ret * 10 + ch - '0';
    }
    if (str[0] == '-') ret = -ret;
    return ret;
}

int2048 stringToInt2048(const std::string& str) {
    int m = str.length();
    int2048 ret = 0;
    for (int i = 0; i < m; i++) {
        if (str[i] != '-')
            ret = ret * 10 + ch - '0';
    }
    if (str[0] == '-') ret = -ret;
    return ret;
}

double stringToDouble(const std::string& str) {
    double ret1 = 0, ret2 = 0; int fl = 0, m = str.length();
    for (int i = m - 1; i >= 0; i--)
    {
        if (str[i] != '.') ret1 = (ret1 + (str[i] & 15)) / 10;
        else {fl = i; break;}
    }
    for (int i = 0; i < fl; i++)
    {
        if (str[i] != '-') ret2 = (ret2 << 1) + (ret2 << 3) + (str[i] & 15);
        else break;
    }
    if (str[i] == '-') ret1 = -ret1 - ret2;
    for (const auto& ch : str) {
        ret = ret * 10 + ch - '0';
    }
    return ret;
}

bool validateVarName(const std::string& str) {
    for (const auto& ch : str) {
        if (!(ch >= 'a' && ch <= 'z') && !(ch >= 'A' && ch <= 'Z')) {
            return false;
        }
    }
    return true;
}

#endif //APPLE_PIE_UTILS_H
