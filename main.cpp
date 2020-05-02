#include <iostream>
#include <vector>
#include <array>
#include <string>

class FindQuery;

class SourceCode
{
public:
    using sourceCode_container_type = std::vector<std::string>;

private:
    sourceCode_container_type m_sourceCodeContainer{};

public:
    SourceCode(int numberOfLines = 0);
    sourceCode_container_type fillSourceCodeContainer(int numberOfLines);
    void print() const;
    sourceCode_container_type getSourceCodeContainer() const;   

    friend class FindQuery;
};

class RawQuery
{
public:
    using rawQuery_container_type = std::vector<std::string>;

private:
    rawQuery_container_type m_rawQueryContainer{};

public:
    RawQuery(int numberOfLines = 0);
    rawQuery_container_type fillRawQueryContainer(int numberOfLines);
    void print() const;
    rawQuery_container_type getRawQueryContainer() const;
    
};

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

    // returns private members
    parsedQuery_container_type getParsedQueryContainer() const
    {
        return m_parsedQueryContainer;
    }

    // fills empty m_parsedQueryContainer with containers of tags
    parsedQuery_container_type fillparsedQueryContainer(const RawQuery &rawQuery) const;

    // make FindQuery class a friend
    friend class FindQuery;
};

class FindQuery
{
public:
    using sourceCode_container_type = std::vector<std::string>;
    using parsedQuery_container_type = std::vector<std::vector<std::string>>;
    using parsedCodeLines_container_type = std::vector<std::string>;
    
private:
    // contains the source-code
    sourceCode_container_type m_sourceCodeContainer{};
    // contains parsed query
    parsedQuery_container_type m_parsedQueryContainer{};

public:
    FindQuery(SourceCode &sourceCode, ParsedQuery &parsedQuery);
    parsedCodeLines_container_type findParsedCodeLines(const std::vector<std::string> &tagArray) const;
    std::string getAttrValue(const std::vector<std::string> &tagArray) const;
    void printAttrValues() const;
    
};

int main()
{
    int N{};
    int Q{};
    std::cin >> N >> Q;
    std::cin.ignore(32767, '\n');

    // Get the HRML Source code
    SourceCode sourceCode{ N };
    // Get the Raw-Queries
    RawQuery rawQuery{ Q };
    // Parse Query
    ParsedQuery parsedQuery{ rawQuery };
    // Find parsed-query in parsed-code
    FindQuery findQuery{ sourceCode, parsedQuery };
    // print answer
    findQuery.printAttrValues();
    
    return 0;
}

SourceCode::SourceCode(int numberOfLines)
{
    m_sourceCodeContainer = fillSourceCodeContainer(numberOfLines);
}

SourceCode::sourceCode_container_type SourceCode::fillSourceCodeContainer(int numberOfLines)
{
    sourceCode_container_type sourceCodeContainer(numberOfLines);
    for (int count{0}; count < numberOfLines; ++count)
    {
        std::string sourceCodeLine;
        std::getline(std::cin, sourceCodeLine);
        sourceCodeContainer[count] = sourceCodeLine;
    }
    return sourceCodeContainer;
}

void SourceCode::print() const
{
    std::cout << "\nThis is Source code:\n";

    for (const auto &sourceCodeLine : m_sourceCodeContainer)
    {
        std::cout << sourceCodeLine << '\n';
    }
    std::cout << '\n';
}

SourceCode::sourceCode_container_type SourceCode::getSourceCodeContainer() const
{
    return m_sourceCodeContainer;
}

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

FindQuery::FindQuery(SourceCode &sourceCode, ParsedQuery &parsedQuery)
{
    this->m_sourceCodeContainer = sourceCode.m_sourceCodeContainer;
    this->m_parsedQueryContainer = parsedQuery.m_parsedQueryContainer;
}

FindQuery::parsedCodeLines_container_type FindQuery::findParsedCodeLines(
                                                   const std::vector<std::string> &tagArray) const
{
    // this array contains sourceCodeLine with the tag (tagArray[second last element])
    parsedCodeLines_container_type parsedCodeLines{};
    // tag is second last element of the tagArary
    std::string tag{ "<" + tagArray[tagArray.size() - 2] };

    for (const auto &sourceCodeLine : m_sourceCodeContainer)
    {
        std::size_t pos{ sourceCodeLine.find(tag) };
        if (pos != std::string::npos)
        {
            parsedCodeLines.push_back(sourceCodeLine);
        }
    }
    
    return parsedCodeLines;
}

std::string FindQuery::getAttrValue(const std::vector<std::string> &tagArray) const
{
    std::string attrName{ tagArray.back() };

    std::vector<std::string> parsedCodeLines = findParsedCodeLines(tagArray);

    for (auto &line : parsedCodeLines)
    {
        std::size_t pos{ line.find(attrName) };         
        if (pos != std::string::npos)
        {
            line = line.substr(pos + attrName.size() + 4) ;
            std::size_t pos2{ line.find("\"") };
            if (pos2 != std::string::npos)
            {
                std::string attrValue{ line.substr(0, line.length() - line.substr(pos2).length()) };
                return attrValue;
            }
        }
    }
    return ""; 
}

void FindQuery::printAttrValues() const
{   
    std::string attrValue{};

    for (const auto &tagArray : m_parsedQueryContainer)
    {
        attrValue = getAttrValue(tagArray);

        if (attrValue == "")
            std::cout << "Not Found!\n";
        else
            std::cout << attrValue << '\n';
    }     
}
