#ifndef SCOPE_H
#define SCOPE_H

#include <map>
#include <any>
#include <vector>
#include <string>
#include "None.h"
#include "int2048.h"
#include "checktype.h"
#include "Python3ParserBaseVisitor.h"
//using int2048 = long long;
using sjtu::int2048;

class Scope {

    private:
        std::map<std::string, int> strtyp;
        std::map<std::string, bool> str2bool;
        std::map<std::string, int2048> str2int;
        std::map<std::string, double> str2double;
        std::map<std::string, std::string> str2str;
        std::map<std::string, NONE> str2none;
    public:
        std::map<std::string, Python3Parser::SuiteContext *> str2func;
        std::map<std::string, std::vector<std::string>> str2functfp;
        std::map<std::string, std::vector<std::any>> str2funcval;
        int op;

        void sto_none(const std::string& varName) {
            str2none[varName] = justnone;
            strtyp[varName] = 0;
            return;
        }

        void sto_bool(const std::string& varName, bool varData) {
            str2bool[varName] = varData;
            strtyp[varName] = 1;
            return;
        }
        
        void sto_int(const std::string& varName, int2048 varData) {
            str2int[varName] = varData;
            strtyp[varName] = 2;
            return;
        }

        void sto_double(const std::string& varName, double varData) {
            str2double[varName] = varData;
            strtyp[varName] = 3;
            return;
        }
        
        void sto_str(const std::string& varName, std::string varData) {
            str2str[varName] = varData;
            strtyp[varName] = 4;
            return;
        }

        void sto_func(const std::string& varName, Python3Parser::SuiteContext* varData) {
            str2func[varName] = varData;
            strtyp[varName] = 5;
            return;
        }

        void sto_functfp(const std::string& varName, std::vector<std::string> v)
        {
            str2functfp[varName] = v;
            return;
        }

        void sto_funcval(const std::string& varName, std::vector<std::any> v)
        {
            str2funcval[varName] = v;
            return;
        }

        void sto_any(const std::string& varName, std::any varData)
        {
            int m = checktype(varData);
            if (m == 1) sto_bool(varName, tobool(varData));
            if (m == 2) sto_int(varName, toint(varData));
            if (m == 3) sto_double(varName, todouble(varData));
            if (m == 4) sto_str(varName, tostr(varData));
            return;
        }

        std::any sco_que(std::string varName){
            int x = strtyp[varName];
            if (x == 0) return str2none[varName];
            if (x == 1) return str2bool[varName];
            if (x == 2) return str2int[varName];
            if (x == 3) return str2double[varName];
            if (x == 4) return str2str[varName];
            if (x == 5) return str2func[varName];
            return justnone;
        }
};

#endif //APPLE_PIE_SCOPE_H
