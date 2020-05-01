#ifndef PARSED_QUERY_H
#define PARSED_QUERY_H

#include "RawQuery.h"

#include <iostream>
#include <vector>
#include <array>
#include <string>

class ParsedQuery
{
public:

    using rawQuery_container_type = std::vector<std::string>;
    using parsedQuery_container_type = std::vector<std::vector<std::string>>;

private:
    // contains contaiers of tags
    parsedQuery_container_type m_parsedQueryContainer{};

public:
    // Constructor initializes m_parsedQueryContainer
    ParsedQuery(const RawQuery &rawQuery);

    // prints all the elements in m_parsedQueryContainer
    void print() const;

    // fills empty m_parsedQueryContainer with containers of tags
    parsedQuery_container_type fillparsedQueryContainer(const RawQuery &rawQuery) const;
};

#endif