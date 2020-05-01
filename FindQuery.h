#ifndef FIND_QUERY_H
#define FIND_QUERY_H

#include "ParsedQuery.h"
#include "ParsedCode.h"

#include <iostream>
#include <vector>
#include <array>
#include <string>

class FindQuery
{
public:
    using parsedQuery_container_type = std::vector<std::vector<std::string>>;
    using tagName_container_type = std::vector<std::string>; 
    using attrNameValuePairArray_container_type = 
                                std::vector<std::vector<ParsedCode::AttrNameValuePair>>;

private:
    // contains parsed query
    parsedQuery_container_type m_parsedQueryContainer{};
    // contains tagNames
    tagName_container_type m_tagNameContainer{};
    // contains arrays of attribute name-value pairs
    attrNameValuePairArray_container_type m_attrNameValuePairArrayContainer{};

public:
    FindQuery(ParsedCode &parsedCode, ParsedQuery &parsedQuery);

    std::string findAttrValue(const std::string &attrName) const;

    void printAttrValues() const;
    
};

#endif