#include <iostream>
#include <vector>
#include <array>
#include <string>

using raw_container_type = std::vector<std::string>;
using string_array_type = std::vector<std::string>;
using parsed_container_type = std::vector<string_array_type>;
using code_type = std::string;
using query_type = std::string;


class Query
{
private:
    raw_container_type m_queries{};

public:
    Query(int numberOfQuery = 0)
    {
        m_queries = inputQueries(numberOfQuery);
    }

public:
    raw_container_type inputQueries(int numberOfQuery)
    {
        raw_container_type queries(numberOfQuery);
        for (int count{0}; count < numberOfQuery; ++count)
        {
            std::string query;
            std::getline(std::cin, query);
            queries[count] = query;
        }
        return queries;
    }

    void print() const
    {
        std::cout << '\n';
        for (const auto &query : m_queries)
        {
            std::cout << query << '\n';
        }
        std::cout << '\n';
    }

    raw_container_type getQueries() const
    {
        return m_queries;
    }
    
};


class SourceCode
{
private:
    raw_container_type m_sourceCode{};

public:
    SourceCode(int numberOfLines)
    {
        m_sourceCode = inputSourceCode(numberOfLines);
    }

public:
    raw_container_type inputSourceCode(int numberOfLines)
    {
        raw_container_type sourceCode(numberOfLines);
        for (int count{0}; count < numberOfLines; ++count)
        {
            std::string line;
            std::getline(std::cin, line);
            sourceCode[count] = line;
        }
        return sourceCode;
    }

    void print() const
    {
        std::cout << '\n';
        for (const auto &line : m_sourceCode)
        {
            std::cout << line << '\n';
        }
        std::cout << '\n';
    }

    raw_container_type getSourceCode() const
    {
        return m_sourceCode;
    }
    
};


// class ParsedCode
// {
// private:
//     parsed_container_type m_tagNamesArray{};
//     parsed_container_type m_attributeNamesArray{};

// public:
//     ParsedCode(const SourceCode &sourceCode)
//     {
//         m_tagNamesArray = getTagNames(sourceCode);
//         m_attributeNamesArray = getAttributeNames(sourceCode);
//     }
    
// public:
//     parsed_container_type getTagNamesArray(const SourceCode &sourceCode) const
//     {
//         raw_container_type rawCode{ sourceCode.getSourceCode() };

//         parsed_container_type tagNamesArray{};



//         return tagNamesArray;
//     }

//     parsed_container_type getAttributeNamesArray(const SourceCode &sourceCode) const
//     {
//         raw_container_type rawCode{ sourceCode.getSourceCode() };

//         parsed_container_type attributeNamesArray{};




//         return attributeNamesArray;
//     }

// };


class ParsedQuery
{
private:
    parsed_container_type m_queriesArray{};

public:
    ParsedQuery(const Query &query)
    {
        m_queriesArray = getQueriesArray(query);
    }

public:
    void print() const
    {
        for (const auto &stringArray : m_queriesArray)
        {
            for (const auto &tag : stringArray)
            {
                std::cout << tag << ' ';
            }
            std::cout << '\n';
        }
    }

    parsed_container_type getQueriesArray(const Query &query) const
    {
        parsed_container_type queriesArray{};
        raw_container_type rawQueries{ query.getQueries() };

        for (auto &rawQuery : rawQueries)
        {
            string_array_type stringArray{};

            while (true)
            {
                size_t pos{ rawQuery.find(".") };
                size_t pos2{ rawQuery.find("~") };

                if (pos != std::string::npos)
                {
                    // Extract the first rawQuery and push it in the array
                    std::string tagName { rawQuery.substr(0, rawQuery.length() - rawQuery.substr(pos).length()) };
                    stringArray.push_back(tagName);
                    // assign rawQuery the value of remaining unparsed rawQuery
                    rawQuery = rawQuery.substr(pos + 1);
                }
                else if (pos2 != std::string::npos)
                {
                    // Extract the first rawQuery and push it in the array
                    std::string tagName { rawQuery.substr(0, rawQuery.length() - rawQuery.substr(pos2).length()) };
                    stringArray.push_back(tagName);
                    // assign rawQuery the value of remaining unparsed rawQuery
                    rawQuery = rawQuery.substr(pos2 + 1);
                    stringArray.push_back(rawQuery);
                }
                else
                    break;
            }

            queriesArray.push_back(stringArray);
        }

        return queriesArray;
    }
    
};



// ParsedQuery getParsedQuery(query_type query);
// std::string getLineWithQueryTag(container_type tagArray, container_type HRMLSourceCode);
// std::string getStringWithAttributValue(std::string attribute,
//                                                  std::string lineWithQueryTag);
// std::string getAttributeValue(ParsedQuery parsedQuery,
//                                                 container_type HRMLSourceCode);
// void printAttributeValues(container_type HRMLSourceCode, container_type queries);


int main()
{
    int N{};
    int Q{};
    std::cin >> N >> Q;
    std::cin.ignore(32767, '\n');

    // Get the HRML Source code
    SourceCode sourceCode{ N };
    sourceCode.print();

    // Get the Queries
    Query query{ Q };
    query.print();


    ParsedQuery parsedQuery{ query };
    parsedQuery.print();

    
    
    // container_type HRMLSourceCode {
    //                                 "<body>",
    //                                 "<div id = \"myDiv\">",
    //                                 "<h1 id = \"myHeading\">",
    //                                 "</h1>",
    //                                 "</div>",
    //                                 "</body>",

    //                                 "<tag1 value = \"HelloWorld\">",
    //                                 "<tag2 name = \"Name1\">",
    //                                 "</tag2>",
    //                                 "</tag1" 
    //                             };

    // container_type queries {
    //                         "div~id",
    //                         "body.div~id",
    //                         "h1~id",
    //                         "div.h1~id",
    //                         "body.div.h1~id",

    //                         "tag1~value",
    //                         "tag1.tag2~name" };

    // printAttributeValues(HRMLSourceCode, queries);
    
    return 0;
}


// ParsedQuery getParsedQuery(query_type query)
// {
//     
// }

// std::string getLineWithQueryTag(container_type tagArray, container_type HRMLSourceCode)
// {
//     std::string tag = tagArray.back();

//     int lineNumber{0};
//     for (auto codeLine : HRMLSourceCode)
//     {
//         std::size_t found{ codeLine.find(tag) };

//         if (found != std::string::npos)
//         {
//             return HRMLSourceCode[lineNumber];
//         }

//         ++lineNumber;
//     }

//     return " ";
// }

// std::string getStringWithAttributValue(std::string attribute,
//                                                   std::string lineWithQueryTag)
// {
//     std::size_t pos{ lineWithQueryTag.find(attribute) + attribute.size() + 4 };

//     std::string str{ lineWithQueryTag.substr(pos) };

//     str.erase(str.size() - 2);

//     return str;
// }

// std::string getAttributeValue(ParsedQuery parsedQuery,
//                                                 container_type HRMLSourceCode)
// {
//     std::string attribute{ parsedQuery.attribute };
//     container_type tagArray{ parsedQuery.tagArray };

//     std::string lineWithQueryTag { getLineWithQueryTag(tagArray, HRMLSourceCode) };

//     std::string stringWithAttributeValue{ 
//                        getStringWithAttributValue(attribute, lineWithQueryTag) };

//     return stringWithAttributeValue;
// }

// void printAttributeValues(container_type HRMLSourceCode, container_type queries)
// {
//     for (auto query : queries)
//     {

//         ParsedQuery parsedQuery { getParsedQuery(query) };
//         std::cout << getAttributeValue(parsedQuery, HRMLSourceCode) << '\n';
//     }
// }
