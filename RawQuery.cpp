#include "RawQuery.h"

RawQuery::RawQuery(int numberOfLines)
{
    m_rawQueryContainer = fillRawQueryContainer(numberOfLines);
}

RawQuery::rawQuery_container_type RawQuery::fillRawQueryContainer(int numberOfLines)
{
    rawQuery_container_type rawQueryContainer(numberOfLines);
    for (int count{0}; count < numberOfLines; ++count)
    {
        std::string rawQueryLine;
        std::getline(std::cin, rawQueryLine);
        rawQueryContainer[count] = rawQueryLine;
    }
    return rawQueryContainer;
}

void RawQuery::print() const
{
    std::cout << "\nThis is Raw-query:\n";
    for (const auto &rawQueryLine : m_rawQueryContainer)
    {
        std::cout << rawQueryLine << '\n';
    }
    std::cout << '\n';
}

RawQuery::rawQuery_container_type RawQuery::getRawQueryContainer() const
{
    return m_rawQueryContainer;
}