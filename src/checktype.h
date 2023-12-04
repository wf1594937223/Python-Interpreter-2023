#ifndef CHECKTYPE_H
#define CHECKTYPE_H
# include <any>
# include <string>
# include <sstream>
#include <iomanip>
# include "int2048.h"
# include "None.h"
const double eps = 1e-9;
//using int2048 = long long;
using sjtu::int2048;
int checktype(std::any x)
{
    bool* ptr1 = std::any_cast <bool> (&x);
    if (ptr1 != NULL) return 1;
    int2048* ptr2 = std::any_cast <int2048> (&x);
    if (ptr2 != NULL) return 2;
    double* ptr3 = std::any_cast <double> (&x);
    if (ptr3 != NULL) return 3;
    std::string* ptr4 = std::any_cast <std::string> (&x);
    if (ptr4 != NULL) return 4;
}
bool tobool(std::any x)
{
    int m = checktype(x);
    if (m == 1) return (std::any_cast <bool> (x));
    if (m == 2) return (std::any_cast <int2048> (x)) != 0;
    if (m == 3) return (std::any_cast <double> (x)) != 0;
    if (m == 4) return (std::any_cast <std::string> (x)) != "";
}
std::string tostr(std::any x)
{
    int m = checktype(x); std::string s;
    if (m == 4) return (std::any_cast <std::string> (x));
    if (m == 1) return (std::any_cast <bool> (x)) == true ? "true" : "false";
    if (m == 2) return trans(std::any_cast <int2048> (x));
    if (m == 3)
    {
        double y = std::any_cast <double> (x);
//        if (y < 0 + eps) {s += '-'; y = -y;}
        std::stringstream ss;
        ss << std::fixed << std::setprecision(6) << y;
        ss >> s;
        return s;
    }
}
int2048 strtoint(std::string s)
{
    int i, j = s.length(), k, fl = 0; k = j;
    for (i = j - 1; i >= 0; i--)
        if (s[i] == '.') {k = i; break;}
    if (k == j)
        return (int2048)s;
    for (i = k + 1; i < j; i++)
        if (s[i] != '0') {fl = 1; break;}
    s.erase(k - 1);
    return (int2048)s;
}
double strtodouble(std::string s)
{
    double x;
    std::stringstream ss;
    ss << s;
    ss >> x;
    return x;
}
/*
double stringToDouble(const std::string& str) {
    double ret1 = 0, ret2 = 0; int fl = 0, m = str.length();
    char ch;
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
*/
int2048 toint(std::any x)
{
    int m = checktype(x);
    if (m == 2) return (std::any_cast <int2048> (x));
    if (m == 1) return (std::any_cast <bool> (x)) == true ? 1 : 0;
    return strtoint(tostr(x));
}
double todouble(std::any x)
{
    int m = checktype(x);
    if (m == 3) return (std::any_cast <double> (x));
    if (m == 1) return (std::any_cast <bool> (x)) == true ? 1 : 0;
    return strtodouble(tostr(x));
}
#endif