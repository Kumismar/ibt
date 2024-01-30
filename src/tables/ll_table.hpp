#pragma once

#include "nonterminal.hpp"
#include "table_index.hpp"
#include "token.hpp"
#include <vector>

class LLRowAccessor
{
private:
    const std::vector<LLTableIndex>& row;

public:
    LLRowAccessor(const std::vector<LLTableIndex>& r)
        : row(r)
    {
    }

    LLTableIndex operator[](const Token& t) const;
};

class LLTable
{
private:
    const std::vector<std::vector<LLTableIndex>> table = {
        //                       if       while     for      return      ;       elseif     else       (         )          {        }      function   fName       :      variable     +         -         *         /         .         !         &&        ||        ==        !=         >         <        >=        <=      constant     ,        int      float     string     bool
        /*    program    */ { { 1, 1 }, { 1, 1 }, { 1, 1 }, { 1, 1 }, { 1, 1 }, { 0, 0 }, { 0, 0 }, { 1, 1 }, { 0, 0 }, { 1, 1 }, { 0, 0 }, { 1, 2 }, { 1, 1 }, { 0, 0 }, { 1, 1 }, { 1, 1 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 1, 1 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 1, 1 }, { 0, 0 }, { 1, 1 }, { 1, 1 }, { 1, 1 }, { 1, 1 } },
        /* statementList */ { { 1, 3 }, { 1, 3 }, { 1, 3 }, { 1, 3 }, { 1, 3 }, { 0, 0 }, { 0, 0 }, { 1, 3 }, { 0, 0 }, { 1, 3 }, { 0, 0 }, { 1, 4 }, { 1, 3 }, { 0, 0 }, { 1, 3 }, { 1, 3 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 1, 3 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 1, 3 }, { 0, 0 }, { 1, 3 }, { 1, 3 }, { 1, 3 }, { 1, 3 } },
        /*   statement   */ { { 2, 1 }, { 2, 2 }, { 2, 3 }, { 2, 5 }, { 2, 7 }, { 0, 0 }, { 0, 0 }, { 2, 4 }, { 0, 0 }, { 2, 6 }, { 0, 0 }, { 0, 0 }, { 2, 4 }, { 0, 0 }, { 2, 4 }, { 1, 1 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 1, 1 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 2, 4 }, { 0, 0 }, { 2, 4 }, { 2, 4 }, { 2, 4 }, { 2, 4 } },
        /*      if2      */ { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 2, 8 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
        /*   returnExp   */ { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 2, 11 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 2, 11 }, { 0, 0 }, { 2, 11 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 2, 11 }, { 0, 0 }, { 2, 11 }, { 2, 11 }, { 2, 11 }, { 2, 11 } },
        /*  functionDef  */ { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 3, 1 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
        /*    params     */ { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 3, 2 }, { 3, 2 }, { 3, 2 }, { 3, 2 } },
        /*    params2    */ { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 3, 4 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
        /*    funcType   */ { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 3, 5 }, { 3, 5 }, { 3, 5 }, { 3, 5 } },
        /*   expression  */ { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
        /*     args      */ { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 4, 7 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 4, 7 }, { 0, 0 }, { 4, 7 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 4, 7 }, { 0, 0 }, { 4, 7 }, { 4, 7 }, { 4, 7 }, { 4, 7 } },
        /*     args2     */ { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 4, 9 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 } },
        /*   codeBlock   */ { { 5, 2 }, { 5, 2 }, { 5, 2 }, { 5, 2 }, { 5, 2 }, { 0, 0 }, { 0, 0 }, { 5, 2 }, { 0, 0 }, { 5, 1 }, { 0, 0 }, { 0, 0 }, { 5, 2 }, { 0, 0 }, { 5, 2 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 5, 2 }, { 0, 0 }, { 5, 2 }, { 5, 2 }, { 5, 2 }, { 5, 2 } },
        /*   statements  */ { { 5, 3 }, { 5, 3 }, { 5, 3 }, { 5, 3 }, { 5, 3 }, { 0, 0 }, { 0, 0 }, { 5, 3 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 5, 3 }, { 0, 0 }, { 5, 3 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 5, 3 }, { 0, 0 }, { 5, 3 }, { 5, 3 }, { 5, 3 }, { 5, 3 } },
        /*      type     */ { { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }, { 6, 1 }, { 6, 1 }, { 6, 1 }, { 6, 1 } },
    };

public:
    LLRowAccessor operator[](const Nonterminal& nt) const;
};