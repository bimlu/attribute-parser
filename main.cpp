#include "RawQuery.h"
#include "SourceCode.h"
#include "ParsedQuery.h"
#include "ParsedCode.h"

#include <iostream>
#include <vector>
#include <array>
#include <string>

int main()
{
    int N{};
    int Q{};
    std::cin >> N >> Q;
    std::cin.ignore(32767, '\n');

    // Get the HRML Source code
    // SourceCode sourceCode{ N };
    // sourceCode.print();

    // Get the Queries
    RawQuery rawQuery{ Q };
    // rawQuery.print();

    ParsedQuery parsedQuery{ rawQuery };
    parsedQuery.print();

    // ParsedCode parsedCode{ sourceCode };
    // parsedCode.print();
    
    return 0;
}