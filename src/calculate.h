#ifndef CALCULATE_H
#define CALCULATE_H
# include "checktype.h"
# include "int2048.h"
# include "Scope.h"
# include <algorithm>
# include <utility>
using sjtu::int2048;
std::pair<std::any, std::any> change(std::any x, std::any y)
{
    int u = checktype(x), v = checktype(y), w = std::max(u, v);
    if (w == 1) return std::make_pair(tobool(x), tobool(y));
    if (w == 2) return std::make_pair(toint(x), toint(y));
    if (w == 3) return std::make_pair(todouble(x), todouble(y));
    if (w == 4) return std::make_pair(tostr(x), tostr(y));
}
std::any addany(std::any x, std::any y)
{
    auto p = change(x, y);
    std::any u = p.first, v = p.second; int m = checktype(u);
    if (m == 1) return (int2048)(tobool(u) + tobool(v));
    if (m == 2) return toint(u) + toint(v);
    if (m == 3) return todouble(u) + todouble(v);
    if (m == 4) return tostr(u) + tostr(v);
}
std::any subany(std::any x, std::any y)
{
    auto p = change(x, y);
    std::any u = p.first, v = p.second; int m = checktype(u);
    if (m == 1) return (int2048)(tobool(u) - tobool(v));
    if (m == 2) return toint(u) - toint(v);
    if (m == 3) return todouble(u) - todouble(v);
}
std::any mulany(std::any x, std::any y)
{
    auto p = change(x, y);
    std::any u = p.first, v = p.second; int m = checktype(u);
    if (m == 1) return (int2048)(tobool(u) * tobool(v));
    if (m == 2) return toint(u) * toint(v);
    if (m == 3) return todouble(u) * todouble(v);
}
double divany(std::any x, std::any y)
{
    return todouble(x) / todouble(y);
}
int2048 idivany(std::any x, std::any y)
{
    auto p = change(x, y);
    std::any u = p.first, v = p.second; int m = checktype(u);
    if (m == 1) return (int2048)(tobool(u) / tobool(v));
    if (m == 2) return toint(u) / toint(v);
    if (m == 3) return toint(todouble(u) / todouble(v));
}
std::any modany(std::any x, std::any y)
{
    auto p = change(x, y);
    std::any u = p.first, v = p.second; int m = checktype(u);
    return subany(x, mulany(y, idivany(x, y)));
}
bool lesany(std::any x, std::any y)
{
    auto p = change(x, y);
    std::any u = p.first, v = p.second; int m = checktype(u);
    if (m == 1) return tobool(u) < tobool(v);
    if (m == 2) return toint(u) < toint(v);
    if (m == 3) return todouble(u) < todouble(v);
    if (m == 4) return tostr(u) < tostr(v);
}
bool greany(std::any x, std::any y)
{
    auto p = change(x, y);
    std::any u = p.first, v = p.second; int m = checktype(u);
    if (m == 1) return tobool(u) > tobool(v);
    if (m == 2) return toint(u) > toint(v);
    if (m == 3) return todouble(u) > todouble(v);
    if (m == 4) return tostr(u) > tostr(v);
}
bool equany(std::any x, std::any y)
{
    auto p = change(x, y);
    std::any u = p.first, v = p.second; int m = checktype(u);
    if (m == 1) return tobool(u) == tobool(v);
    if (m == 2) return toint(u) == toint(v);
    if (m == 3) return todouble(u) == todouble(v);
    if (m == 4) return tostr(u) == tostr(v);
}
bool leeqany(std::any x, std::any y)
{
    auto p = change(x, y);
    std::any u = p.first, v = p.second; int m = checktype(u);
    if (m == 1) return tobool(u) <= tobool(v);
    if (m == 2) return toint(u) <= toint(v);
    if (m == 3) return todouble(u) <= todouble(v);
    if (m == 4) return tostr(u) <= tostr(v);
}
bool greqany(std::any x, std::any y)
{
    auto p = change(x, y);
    std::any u = p.first, v = p.second; int m = checktype(u);
    if (m == 1) return tobool(u) >= tobool(v);
    if (m == 2) return toint(u) >= toint(v);
    if (m == 3) return todouble(u) >= todouble(v);
    if (m == 4) return tostr(u) >= tostr(v);
}
bool noeqany(std::any x, std::any y)
{
    auto p = change(x, y);
    std::any u = p.first, v = p.second; int m = checktype(u);
    if (m == 1) return tobool(u) != tobool(v);
    if (m == 2) return toint(u) != toint(v);
    if (m == 3) return todouble(u) != todouble(v);
    if (m == 4) return tostr(u) != tostr(v);
}
#endif