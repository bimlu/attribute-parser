#include "RawQuery.h"
#include "SourceCode.h"
#include "ParsedQuery.h"
#include "ParsedCode.h"
#include "FindQuery.h"

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
    SourceCode sourceCode{ N };
    // // print the Source code
    // sourceCode.print();

    // Get the Raw-Queries
    RawQuery rawQuery{ Q };
    // // Print the Raw-Queries
    // rawQuery.print();

    // Parse Query
    ParsedQuery parsedQuery{ rawQuery };
    // // Print parsed query
    // parsedQuery.print();

    // Parse source-code
    ParsedCode parsedCode{ sourceCode };
    // // print source-code
    // parsedCode.print();

    // Find parsed-query in parsed-code
    FindQuery findQuery{ parsedCode, parsedQuery };
    // print answer
    findQuery.printAttrValues();


    
    return 0;
}