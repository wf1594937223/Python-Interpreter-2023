# include <any>
# include <string>
# include <sstream>
#include <iomanip>
# include "int2048.h"
const double eps = 1e-9;
//using int2048 = long long;
int checktype(std::any x)
{
    bool* ptr1 = std::any_cast <bool> (&x);
    if (ptr != NULL) return 1;
    int2048* ptr1 = std::any_cast <int2048> (&x);
    if (ptr != NULL) return 2;
    double* ptr1 = std::any_cast <double> (&x);
    if (ptr != NULL) return 3;
    std::string* ptr1 = std::any_cast <std::string> (&x);
    if (ptr != NULL) return 4;
}
bool tobool(std::any x)
{
    int m = checktype(x);
    if (m == 1) return (std::any_cast <bool> x);
    if (m == 2) return (std::any_cast <int2048> x) != 0;
    if (m == 3) return (std::any_cast <double> x) != 0;
    if (m == 4) return (std::any_cast <std::string> x) != "";
}
std::string tostr(std::any x)
{
    int m = checktype(x); std::string s;
    if (m == 4) return (std::any_cast <std::string> x);
    if (m == 1) return (std::any_cast <bool> x) == true ? "true" : "false";
    if (m == 2) return trans(std::any_cast <int2048> x);
    if (m == 3)
    {
        double y = std::any_cast <std::string> x;
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
        return sjtu::int2048::read(s);
    for (i = k + 1; i < j; i++)
        if (s[i] != '0') {fl = 1; break;}
    s.erase(k - 1);
    return sjtu::int2048::read(s);
}
int2048 strtodouble(std::string s)
{
    double x;
    ss << s;
    ss >> x;
    return x;
}
int2048 toint(std::any x)
{
    int m = checktype(x);
    if (m == 2) return (std::any_cast <int2048> x);
    if (m == 1) return (std::any_cast <bool> x) == true ? 1 : 0;
    return strtoint(tostr(x));
}
double todouble(std::any x)
{
    int m = checktype(x);
    if (m == 3) return (std::any_cast <double> x);
    if (m == 1) return (std::any_cast <bool> x) == true ? 1 : 0;
    return strtodouble(tostr(x));
}