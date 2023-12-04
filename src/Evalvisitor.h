#pragma once
#ifndef PYTHON_INTERPRETER_EVALVISITOR_H
#define PYTHON_INTERPRETER_EVALVISITOR_H


#include "Python3ParserBaseVisitor.h"
#include "int2048.h"
#include "Exception.h"
#include "Scope.h"
#include "utils.h"
#include "None.h"
#include "checktype.h"
#include "calculate.h"
#include <utility>
//using int2048 = long long

Scope scope;

int continue_fl, break_fl, return_fl;

class EvalVisitor: public Python3BaseVisitor {

//todo:override all methods of Python3BaseVisitor
public:

    virtual std::any visitFile_input(Python3Parser::File_inputContext *ctx) override {           
		auto stmtArray = ctx->stmt();
		for (int i = 0; i < stmtArray.size(); i++)
			visitStmt(stmtArray[i]);
        return justnone;
    }//done

    virtual std::any visitFuncdef(Python3Parser::FuncdefContext *ctx) override {
        // no func def
        scope.sto_func(ctx->NAME()->getText(), ctx->suite());
        //std::pair<std::vector<std::string>, std::vector<std::any>> p;
        auto p = visitParameters(ctx->parameters());
        scope.sto_functfp(p.first);
        scope.sto_funcval(p.second);
        return justnone;
    }

    virtual std::any visitParameters(Python3Parser::ParametersContext *ctx) override {
        if (!ctx->typedargslist())
        {
            std::pair<std::vector<std::string>, std::vector<std::any>> p;
            return p;
        }
        return visitTypedargslist(ctx->typedargslist());
    }

    virtual std::any visitTypedargslist(Python3Parser::TypedargslistContext *ctx) override {
        auto array_tfpdef = ctx->tfpdef()->getText();
        auto array_val = ctx->test();
        std::vector<std::any> v;
        int x = array_tfpdef.size(), y = (ctx->test()).size();
        for (int i = 1; i <= x - y; i++) v.push_back(justnone);
        for (int i = 0; i < y; i++) v.push_back(visitTest(array_val[i]));
        return std::make_pair(array_tfpdef, v);
    }

    virtual std::any visitTfpdef(Python3Parser::TfpdefContext *ctx) override {
        return ctx->NAME()->getText();
    }

    virtual std::any visitStmt(Python3Parser::StmtContext *ctx) override {
        if (ctx->simple_stmt()) return visitSimple_stmt(ctx->simple_stmt());
        else return visitCompound_stmt(ctx->compound_stmt());
    }//done

    virtual std::any visitSimple_stmt(Python3Parser::Simple_stmtContext *ctx) override {
        return visitSmall_stmt(ctx->smallstmt());
    }

    virtual std::any visitSmall_stmt(Python3Parser::Small_stmtContext *ctx) override {
        if (ctx->expr_stmt()) return visitExpr_stmt(ctx->expr_stmt());
        else return visitFlow_stmt(ctx->flow_stmt());
//        return visitChildren(ctx);
    }//done

    virtual std::any visitExpr_stmt(Python3Parser::Expr_stmtContext *ctx) override {
        auto testlistArray = ctx->testlist();
        if (ctx->augassign()) {
            int2048 id = toint(visitAugassign(ctx->augassion()));
            std::any varData = visitTestlist(testlistArray[1]);
            std::string varName = testlistArray[0]->getText();
            std::any varData2 = scope.sco_que(varName);
            if (id == 1) {scope.sto_any(varName, addany(varData2, varData));}
            if (id == 2) {scope.sto_any(varName, subany(varData2, varData));}
            if (id == 3) {scope.sto_any(varName, mulany(varData2, varData));}
            if (id == 4) {scope.sto_any(varName, divany(varData2, varData));}//div(varData2, varData);
            if (id == 5) {scope.sto_any(varName, idivany(varData2, varData));}//整除
            if (id == 6) {scope.sto_any(varName, modany(var Data2, varData));}

//            throw Exception("", UNIMPLEMENTED);
            return justnone;
        }
        int m = testlistArray.size();
        if (m == 1) {
            visitTestlist(testlistArray[0]);
            return justnone;
        }
        std::any varData = visitTestlist(testlistArray[m - 1]);
        std::string varName;
        scope.sto_any(varName, varData[0]);
//        scope.varRegister(varName, varData);
        return justnone;
    }

    virtual std::any visitAugassign(Python3Parser::AugassignContext *ctx) override {
        if (ctx->ADD_ASSIGN()) return 1;
        if (ctx->SUB_ASSIGN()) return 2;
        if (ctx->MULT_ASSIGN()) return 3;
        if (ctx->DIV_ASSIGN()) return 4;
        if (ctx->IDIV_ASSIGN()) return 5;
        if (ctx->MOD_ASSIGN()) return 6;
        return visitChildren(ctx);
    }

    virtual std::any visitFlow_stmt(Python3Parser::Flow_stmtContext *ctx) override {
        if (ctx->break_stmt()) return visitBreak_stmt(ctx->break_stmt());
        if (ctx->continue_stmt()) return visitContinue_stmt(ctx->break_stmt());
        if (ctx->return_stmt()) return visitReturn_stmt(ctx->return_stmt());
        return visitChildren(ctx);
    }

    virtual std::any visitBreak_stmt(Python3Parser::Break_stmtContext *ctx) override {
        break_fl = 1;
        return justnone;
    }

    virtual std::any visitContinue_stmt(Python3Parser::Continue_stmtContext *ctx) override {
        continue_fl = 1;
        return justnone;
    }

    virtual std::any visitReturn_stmt(Python3Parser::Return_stmtContext *ctx) override {
        return_fl = 1;
        if (ctx->testlist()) return visitTestlist(ctx->testlist());
        return justnone;
    }

    virtual std::any visitCompound_stmt(Python3Parser::Compound_stmtContext *ctx) override {
        if (ctx->if_stmt()) return visitIf_stmt(ctx->if_stmt());
        if (ctx->while_stmt()) return visitWhile_stmt(ctx->while_stmt());
        if (ctx->funcdef()) return visitFuncdef(ctx->funcdef());
    }

    virtual std::any visitIf_stmt(Python3Parser::If_stmtContext *ctx) override {
        auto arraytest = ctx->test();
        auto arraysuite = ctx->suite();
        for (int i = 0; i < arraytest().size(); i++)
        {
            bool b = tobool(visitTest(arraytest[i]));
            if (b == true) return visitSuite(arraysuite[i]);
        }
        if (ctx->ELSE()) return visitSuite(arraysuite[arraysuite().size() - 1]);
    }

    virtual std::any visitWhile_stmt(Python3Parser::While_stmtContext *ctx) override {
        std::any x;
        while(1)
        {
            x = visitTest(ctx->test());
            if (tobool(x) == false) break;
            visitSuite(ctx->Suite());
            if (break_fl)
            {
                break_fl = 0;
                return justnone;
            }
            if (continue_fl)
            {
                continue_fl = 0;
                return justnone;
            }
            if (return_fl)
                return x;
        }
        return justnone;
    }

    virtual std::any visitSuite(Python3Parser::SuiteContext *ctx) override {
        if (ctx->simple_stmt()) return visitSimple_stmt(ctx->simple_stmt());
        auto arraystmt = ctx->stmt();
        std::any x;
        for (int i = 0; i < arraystmt().size(); i++)
        {
            x = visitStmt(arraytest[i]);
            if (return_fl)
                return x;
            if (break_fl)
                return justnone;
            if (continue_fl)
                return justnone;
        }
        return justnone;
    }

    virtual std::any visitTest(Python3Parser::TestContext *ctx) override {
        return visitOr_test(ctx->or_test());
    }

    virtual std::any visitOr_test(Python3Parser::Or_testContext *ctx) override {
        auto array = ctx->and_test();
        if (array.size() == 1)
            return visitAnd_test(array[0]);
        int x = 0;
        for (int i = 0; i < array.size(); i++)
            x = x | (visitAnd_test(array[i]));
        if (x) return true;
        else return false;
    }

    virtual std::any visitAnd_test(Python3Parser::And_testContext *ctx) override {
        auto array = ctx->not_test();
        if (array.size() == 1)
            return visitNot_test(array[0]);
        int x = 1;
        for (int i = 0; i < array.size(); i++)
            x = x & (visitNot_test(array[i]));
        if (x) return true;
        else return false;
    }

    virtual std::any visitNot_test(Python3Parser::Not_testContext *ctx) override {
        if (ctx->not_test()) return !(tobool(visitNot_test(ctx->not_test())));
        return visitComparison(ctx->comparison());
    }

    virtual std::any visitComparison(Python3Parser::ComparisonContext *ctx) override {
        auto arrayari = ctx->arith_expr();
        auto arrayop = ctx->comp_op();
        if (arrayari.size() == 1) return visitArith_expr(ctx->arith_expr);
        std::vector< std::any > v;
        for (int i = 0; i < arrayari.size(); i++)
            v.push_back(visitArith_expr(arrayari[i]));
        int fl = 1;
        for (int i = 0; i < arrayari.size() - 1; i++)
        {
            int2048 m = toint(arrayari[i]);
            if (m == 1) fl = fl & lesany(v[i], v[i + 1]);
            if (m == 2) fl = fl & greany(v[i], v[i + 1]);
            if (m == 3) fl = fl & equany(v[i], v[i + 1]);
            if (m == 4) fl = fl & leeqany(v[i], v[i + 1]);
            if (m == 5) fl = fl & greqany(v[i], v[i + 1]);
            if (m == 6) fl = fl & noeqany(v[i], v[i + 1]);
        }
        return fl;
    }

    virtual std::any visitComp_op(Python3Parser::Comp_opContext *ctx) override {
        if (ctx->LESS_THAN()) return 1;
        if (ctx->GREATER_THAN()) return 2;
        if (ctx->EQUALS()) return 3;
        if (ctx->LE_EQ()) return 4;
        if (ctx->GR_EQ()) return 5;
        if (ctx->NOT_EQ_2()) return 6;
        return justnone;
    }//<, >, =, <=, >=, !=

    virtual std::any visitArith_expr(Python3Parser::Arith_exprContext *ctx) override {
        auto termArray = ctx->term();
        auto opArray = ctx->addorsub_op();
        std::any x = visitTerm(termArray[0]);
        for (int i = 1; i < termArray.size(); i++) {
            int m = toint(visitAddorsub_op(opArray[i - 1]));
            if (m == 1) x = addany(x, visitTerm(termArray[i]));
            if (m == 2) x = subany(x, visitTerm(termArray[i]));
        }
        return x;
    }

    virtual std::any visitAddorsub_op(Python3Parser::Addorsub_opContext *ctx) override {
        if (ctx->ADD()) return 1;
        if (ctx->MINUS()) return 2;
        return justnone;
    }

    virtual std::any visitTerm(Python3Parser::TermContext *ctx) override {
        auto factorArray = ctx->factor();
        auto opArray = ctx->muldivmod_op();
        std::any x = visitFactor(factorArray[0]);
        for (int i = 1; i < factorArray.size(); i++) {
            int m = toint(visitMuldivmod_op(opArray[i - 1]));
            if (m == 3) x = mulany(x, visitFactor(factorArray[i]));
            if (m == 4) x = divany(x, visitFactor(factorArray[i]));
            if (m == 5) x = idivany(x, visitFactor(factorArray[i]));
            if (m == 4) x = modany(x, visitFactor(factorArray[i]));
        }
        return x;
    }

    virtual std::any visitMuldivmod_op(Python3Parser::Muldivmod_opContext *ctx) override {
        if (ctx->STAR()) return 3;
        if (ctx->DIV()) return 4;
        if (ctx->IDIV()) return 5;
        if (ctx->MOD()) return 6;
        return justnone;
    }

    virtual std::any visitFactor(Python3Parser::FactorContext *ctx) override {
        if (ctx->atom_expr()) return visitAtom_expr(ctx->atom_expr());
        if (ctx->MINUS()) return subany(false, visitFactor(ctx->factor()));
        if (ctx->ADD()) return visitFactor(ctx->factor());
        return justnone;
    }

    virtual std::any visitAtom_expr(Python3Parser::Atom_exprContext *ctx) override {
        if (!ctx->trailer()) return visitAtom(ctx->atom());
        auto functionName = ctx->atom()->getText();
        auto argsArray = visitTrailer(ctx->trailer());
        if (functionName == "bool") return tobool(argsArray[0]);
        if (functionName == "int") return toint(argsArray[0]);
        if (functionName == "float") return todouble(argsArray[0]);
        if (functionName == "str") return toint(argsArray[0]);
        if (functionName == "print") {
            int i, m;
            for (i = 0; i < argsArray.size(); i++)
            {
                m = checktype(argsArray[i]);
                if (m == 1)
                {
                    bool x = std::any_cast <bool> argsArray[i];
                    if(x == true) std::cout << "True ";
                    else std::cout << "False ";
                    continue;
                }
                if (m == 2)
                {
                    int2048 x = std::any_cast <int2048> argsArray[i];
                    std::cout << x << ' ';
                }
                if (m == 3)
                {
                    double x = std::any_cast <double> argsArray[i];
                    std::cout << std::fixed << std::setprecision(6) << x;
                    std::cout << ' ';
                }
                if (m == 4)
                {
                    std::string x = std::any_cast <std::string> argsArray[i];
                    std::cout << x << ' ';
                }
            }
            std::cout << std::endl;
            return justnone;
        }
        std::vector<std::string> arraytfp = str2functfp[varName];
        std::vector<std::any> arrayval = str2funcval[varName];
        for (int i = 0; i < argsArray.size(); i++)
            arrayval[i] = argsArray[i];
        for (int i = 0; i < arraytfp.size(); i++)
            scope.sto_any(arraytfp[i], arrayval[i]);
        return visitSuite(Scope.str2func[varName]);
    }//内置函数在此

    virtual std::any visitTrailer(Python3Parser::TrailerContext *ctx) override {
        if (ctx->arglist()) return visitArglist(ctx->arglist());
        return std::vector<std::any>();
    }

    virtual std::any visitAtom(Python3Parser::AtomContext *ctx) override {
        if (ctx->NUMBER())
        {
            std::string s = ctx->NUMBER()->getText();
            int m = s.length(), fl = 0;
            for (i = 0; i < m; i++) if (s[i] == '.') {fl = 1; break;}
            if (fl) return stringToDouble(s);
            else return stringToInt(s);
        }
        else if (ctx->NAME())
            return scope.sco_que(ctx->NAME()->getText());
        else if (ctx->STRING())
        {
            auto array = ctx->STRING();
            std::string s = "";
            for (int i = 0; i <= array.size(); i++)
                s += array[i]->getText();
            return s;
        }
        else if (ctx->NONE())
            return justnone;
        else if (ctx->TRUE())
            return (bool)true;
        else if (ctx->FALSE())
            return (bool)false;
        else if (ctx->test()) return visitTest(ctx->test());
        //throw Exception("", UNIMPLEMENTED);
    }

    virtual std::any visitTestlist(Python3Parser::TestlistContext *ctx) override {
        std::vector<std::any> v;
        auto arraytest = ctx->test();
        for (int i = 0; i < arraytest.size(); i++)
            v.push_back(visitTest(arraytest[i]));
        return v;
    }

    virtual std::any visitArglist(Python3Parser::ArglistContext *ctx) override {
        auto argumentArray = ctx->argument();
        std::vector<std::any> retArray;
        for (int i = 0; i < argumentArray.size(); i++) {
            retArray.push_back(visitArgument(argumentArray[i]));
        }
        return retArray;
    }

    virtual std::any visitArgument(Python3Parser::ArgumentContext *ctx) override {
        auto arraytest = ctx->test();
        if (arraytest.size() == 1) return visitTest(arraytest[0]);
        std::string s = tostring(visitTest(arraytest[0]));
        std::any x = visitTest(arraytest[1]); int m = checktype(x);
        if (m == 1) sco.sto_bool(tobool(x));
        if (m == 2) sco.sto_int(toint(x));
        if (m == 3) sco.sto_double(todouble(x));
        if (m == 4) sco.sto_str(tostr(x));
        return x;
    }
};


#endif//PYTHON_INTERPRETER_EVALVISITOR_H
