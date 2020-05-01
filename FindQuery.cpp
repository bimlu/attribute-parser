#include "FindQuery.h"

FindQuery::FindQuery(ParsedCode &parsedCode, ParsedQuery &parsedQuery)
{
    m_parsedQueryContainer = parsedQuery.getParsedQueryContainer();
    m_tagNameContainer = parsedCode.getTagNameContainer();
    m_attrNameValuePairArrayContainer = parsedCode.getAttrNameValuePairArrayContainer();
}

std::string FindQuery::findAttrValue(const std::string &attrName) const
{
    std::string attrValue{};

    for (auto const &attrNameValuePairArray : m_attrNameValuePairArrayContainer)
    {
        for (auto const &attrNameValuePair : attrNameValuePairArray)
        {
            if (attrNameValuePair.attrName == attrName)
            {
                return attrNameValuePair.attrValue;
                break;
            }
        }
    }

    return "";
}

void FindQuery::printAttrValues() const
{
    std::string attrName{};
    std::string attrValue{};

    for (auto const &parsedQueryLine : m_parsedQueryContainer)
    {
        attrName = parsedQueryLine.back();
        attrValue = findAttrValue(attrName);

        if (attrValue == "")
            std::cout << "Not Found!" << '\n';
        else
            std::cout << attrValue << '\n';       
    }
}