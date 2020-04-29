#include <iostream>
#include <vector>
#include <array>
#include <string>

using container_type = std::vector<std::string>;
using line_type = std::string;
using query_type = std::string;

struct ParsedQuery
{
    query_type tag{};
    query_type attribute{};
};

struct ParsedTags
{
    container_type tagArray;
};

container_type getHRMLSourceCode(int numberOfLines);
void printHRMLSourceCode(container_type HRMLSourceCode);
container_type getQueries(int numberOfQuery);
void printQueries(container_type queries);
ParsedQuery getParsedQuery(query_type query);
ParsedTags getParsedTags(std::string tag);
void printParsedTags(ParsedTags parsedTags);
std::string getLineWithQueryTag(std::string tag, container_type HRMLSourceCode);
std::string getStringWithAttributValue(std::string attribute,
                                                 std::string lineWithQueryTag);
std::string getAttributeValue(ParsedQuery parsedQuery,
                                                container_type HRMLSourceCode);
void printAttributeValues(container_type HRMLSourceCode, container_type queries);

int main()
{
    // int N{};
    // int Q{};
    // std::cin >> N >> Q;
    // std::cin.ignore(32767, '\n');

    // // Get the HRML Source code
    // container_type HRMLSourceCode{ getHRMLSourceCode(N) };

    // // Get the Queries
    // container_type queries{ getQueries(Q) };

    
    
    container_type HRMLSourceCode {
                                    "<tag1 value = \"HelloWorld\">",
                                    "<tag2 name = \"Name1\">",
                                    "</tag2>",
                                    "</tag1" };
    container_type queries {
                            "<tag1~value",
                            "<tag2~name" };


    ParsedTags parsedTags{ getParsedTags("tag1.tag2.tag3~value") };
    printParsedTags(parsedTags);


    // printAttributeValues(HRMLSourceCode, queries);
    
    return 0;
}

container_type getHRMLSourceCode(int numberOfLines)
{
    container_type HRMLSourceCode(numberOfLines);
    for (int count{0}; count < numberOfLines; ++count)
    {
        std::string line;
        std::getline(std::cin, line);
        HRMLSourceCode[count] = line;
    }

    return HRMLSourceCode;
}

void printHRMLSourceCode(container_type HRMLSourceCode)
{
    std::cout << '\n';
    for (auto line : HRMLSourceCode)
    {
        std::cout << line << '\n';
    }
    std::cout << '\n';
}

container_type getQueries(int numberOfQuery)
{
    container_type queries(numberOfQuery);
    for (int count{0}; count < numberOfQuery; ++count)
    {
        std::string query;
        std::getline(std::cin, query);
        queries[count] = query;
    }

    return queries;
}

void printQueries(container_type queries)
{
    std::cout << '\n';
    for (auto query : queries)
    {
        std::cout << query << '\n';
    }
    std::cout << '\n';
}

ParsedQuery getParsedQuery(query_type query)
{
    ParsedQuery parsedQuery{};

    parsedQuery.tag = query.substr(0, query.find("~"));
    parsedQuery.attribute = query.substr(query.find("~") + 1);

    return parsedQuery;
}

ParsedTags getParsedTags(std::string tag)
{
    ParsedTags parsedTags;

    while (true)
    {
        size_t pos{ tag.find(".") };
        size_t pos2{ tag.find("~") };

        if (pos != std::string::npos)
        {
            // Extract the first tag and push it in the array
            std::string parsedTag { tag.substr(0, tag.length() - tag.substr(pos).length()) };
            parsedTags.tagArray.push_back(parsedTag);
            // assign tag the value of remaining unparsed tag
            tag = tag.substr(pos + 1);
        }
        else if (pos2 != std::string::npos)
        {
            // Extract the first tag and push it in the array
            std::string parsedTag { tag.substr(0, tag.length() - tag.substr(pos2).length()) };
            parsedTags.tagArray.push_back(parsedTag);
            // assign tag the value of remaining unparsed tag
            tag = tag.substr(pos2 + 1);
        }
        else
            break;
    }
    
    return parsedTags;
}

void printParsedTags(ParsedTags parsedTags)
{
    std::cout << '\n';
    for (auto parsedTag : parsedTags.tagArray)
    {
        std::cout << parsedTag << '\n';
    }
    std::cout << '\n';
}

std::string getLineWithQueryTag(std::string tag, container_type HRMLSourceCode)
{
    // ParsedTag parsedTag{ getParsedTag(tag) };

    for (auto codeLine : HRMLSourceCode)
    {
        int lineNumber{0};

        std::size_t found{ codeLine.find(tag) };

        if (found!=std::string::npos)
        {
            return HRMLSourceCode[lineNumber];
        }

        ++lineNumber;
    }

    return " ";
}

std::string getStringWithAttributValue(std::string attribute,
                                                  std::string lineWithQueryTag)
{
    std::size_t pos{ lineWithQueryTag.find(attribute) + attribute.size() + 4 };

    std::string str{ lineWithQueryTag.substr(pos) };

    str.erase(str.size() - 2);

    return str;
}

std::string getAttributeValue(ParsedQuery parsedQuery,
                                                container_type HRMLSourceCode)
{
    std::string tag{ parsedQuery.tag };
    std::string attribute{ parsedQuery.attribute };

    std::string lineWithQueryTag { getLineWithQueryTag(tag, HRMLSourceCode) };

    std::string stringWithAttributeValue{ 
                       getStringWithAttributValue(attribute, lineWithQueryTag) };

    return stringWithAttributeValue;
}

void printAttributeValues(container_type HRMLSourceCode, container_type queries)
{
    for (auto query : queries)
    {
        ParsedQuery parsedQuery { getParsedQuery(query) };
        std::cout << getAttributeValue(parsedQuery, HRMLSourceCode) << '\n';
    }
}
