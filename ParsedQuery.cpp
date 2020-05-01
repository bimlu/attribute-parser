#include "ParsedQuery.h"

ParsedQuery::ParsedQuery(const RawQuery &rawQuery)
{
    // initialize member variable
    m_parsedQueryContainer = fillparsedQueryContainer(rawQuery);
}

// print parsed query
void ParsedQuery::print() const
{
    std::cout << "\nThis is Parsed-Query:\n";
    for (const auto &parsedQueryLine : m_parsedQueryContainer)
    {
        for (const auto &tag : parsedQueryLine)
        {
            std::cout << tag << '*';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

ParsedQuery::parsedQuery_container_type ParsedQuery::fillparsedQueryContainer(const RawQuery &rawQuery) const
{
    // parsedQueryContainer contains tagArray
    // (each tagArray contains all the tags extracted from single rawQueryLine)
    parsedQuery_container_type parsedQueryContainer{};

    // rawQueryContainer is array of strings
    // it contains all the raw queries
    rawQuery_container_type rawQueryContainer{ rawQuery.getRawQueryContainer() };

    for (auto &rawQueryLine : rawQueryContainer)
    {
        // tagArray contains all tags (including attribute name after ~ sign) in rawQueryLine
        std::vector<std::string> tagArray{};

        while (true)
        {
            size_t pos1{ rawQueryLine.find(".") };
            size_t pos2{ rawQueryLine.find("~") };

            if (pos1 != std::string::npos)
            {
                // Extract tagNames from rawQueryLine and store it in tag variable
                std::string tag { rawQueryLine.substr(0, rawQueryLine.length() - 
                                                        rawQueryLine.substr(pos1).length()) };
                // push the tag in tagArray
                tagArray.push_back(tag);
                // assign rawQueryLine the value of remaining unparsed rawQueryLine
                rawQueryLine = rawQueryLine.substr(pos1 + 1);
            }
            else if (pos2 != std::string::npos)
            {
                // Extract tagNames from rawQueryLine and store it in tag variable
                std::string tag { rawQueryLine.substr(0, rawQueryLine.length() - 
                                                        rawQueryLine.substr(pos2).length()) };
                // push the tag in tagArray
                tagArray.push_back(tag);
                // assign rawQueryLine the value of remaining unparsed rawQueryLine
                rawQueryLine = rawQueryLine.substr(pos2 + 1);
            }
            else
            {   
                // rawQueryLine contains the last tag atfter ~ sign
                // push it in the tagArray too
                tagArray.push_back(rawQueryLine);
                break;
            }
        }

        // push tagArray in the parsedQueryContainer
        parsedQueryContainer.push_back(tagArray);
    }
    return parsedQueryContainer;
}  