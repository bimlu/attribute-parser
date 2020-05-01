#include "ParsedCode.h"

ParsedCode::ParsedCode(const SourceCode &sourceCode)
{ 
    // initialize member variables
    m_tagNameContainer = fillTagNameContainer(sourceCode);
    m_attrNameValuePairArrayContainer = fillAttrNameValuePairArrayContainer(sourceCode);
}

void ParsedCode::print() const
{
    // print tagNames
    std::cout << "\nThis is Parsed-Code:-->\n";
    std::cout << "\nTag-Names:\n";
    for (const auto &tagName : m_tagNameContainer)
    {
        std::cout << tagName << '*';
    }

    // print attribute name-value pair
    std::cout << "\nAttribute name-value Pair:\n";
    for (const auto &attrNameValuePairArray : m_attrNameValuePairArrayContainer)
    {
        for (const auto &attrNameValuePair : attrNameValuePairArray)
        {
            std::cout << "(" << attrNameValuePair.attrName << "," <<
                                             attrNameValuePair.attrValue << ")*";
        }
        std::cout << '\n';
    }
}

ParsedCode::tagName_container_type ParsedCode::fillTagNameContainer(const SourceCode &sourceCode) const
{
    // tagNameContainer contains all the tagNames found in sourcCode
    tagName_container_type tagNameContainer{};

    // sourceCodeContainer is array of strings
    // it contains all the source code
    sourceCode_container_type sourceCodeContainer{ sourceCode.getSourceCodeContainer() };

    // extract all tags from each sourceCodeLine
    for (auto &sourceCodeLine : sourceCodeContainer)
    {
        // find the end position of the tagName
        size_t pos{ sourceCodeLine.find(" ") };

        // if pos found extract tagName
        if (pos != std::string::npos)
        {
            std::string tagName{ sourceCodeLine.substr(1, sourceCodeLine.length() - 
                                            sourceCodeLine.substr(pos).length() - 1) };

            // push tagName in tagNameContainer
            tagNameContainer.push_back(tagName);
        }
        else
        {
            // if sourceCode line doesn't have " " then alleast extract the only tagName
            std::string tagName{ sourceCodeLine.substr(1, sourceCodeLine.length() - 2 ) };

            tagNameContainer.push_back(tagName);
        }    
    }

    // return tagNameContainer to the caller
    return tagNameContainer;
}

ParsedCode::attrNameValuePairArray_container_type ParsedCode::fillAttrNameValuePairArrayContainer(
                                                            const SourceCode &sourceCode) const
{
    // attrNameValuePairArrayContainer contains attrNameValuePairArray
    // (each attrNameValuePairArray contains all the attrNameValuePair extracted from single sourceCodeLine)
    attrNameValuePairArray_container_type attrNameValuePairArrayContainer{};

    // sourceCodeContainer is array of strings
    // it contains all the source code
    sourceCode_container_type sourceCodeContainer{ sourceCode.getSourceCodeContainer() };

    // extract attrNameValuePairArray from each sourceCodeLine
    for (auto &sourceCodeLine : sourceCodeContainer)
    {
        // attrNameValuePairArray contains all the attrNameValuePair extracted from single sourcCodeLine
        std::vector<AttrNameValuePair> attrNameValuePairArray{};

        size_t pos1{ sourceCodeLine.find(" ") };
        if (pos1 != std::string::npos)
        {
            // cut initial part of string upto pos
            // now sourceCodeLine is pos+1 to end
            sourceCodeLine = sourceCodeLine.substr(pos1 + 1);
        }
        else{
            // if pos1 not found then skip this line and continue from next sourcCodeLine
            continue;
        }            

        // extract all the attrNameValuePair in single sourceCodeLine
        while (true)
        {
            // attrNameValuePair struct contains attrName, and attrValue as data member
            AttrNameValuePair attrNameValuePair{};

            // find position of attrName
            size_t pos2{ sourceCodeLine.find(" ") };
            
            // if pos2 found in sourceCodeLine
            if (pos2 != std::string::npos)
            {
                // Extract attribute-name from sourceCodeLine and store it in attrName variable
                std::string attrName { sourceCodeLine.substr(0, sourceCodeLine.length() - 
                                                    sourceCodeLine.substr(pos2).length()) };
                // push the attrName in attrNameValuePair
                attrNameValuePair.attrName = attrName;

                // assign sourceCodeLine the value of remaining unextracted string
                sourceCodeLine = sourceCodeLine.substr(pos2 + 4);

                // find end position of the attrValue
                size_t pos3{ sourceCodeLine.find("\"") };

                // Extract attribute-value from sourceCodeLine and store it in attrValue variable
                std::string attrValue { sourceCodeLine.substr(0, sourceCodeLine.length() - 
                                                    sourceCodeLine.substr(pos3).length()) };

                // push the attrValue in attrNameValuePair
                attrNameValuePair.attrValue = attrValue;
                
                // assign sourceCode the value of remaining unextracted string pointing to next attrName
                sourceCodeLine = sourceCodeLine.substr(pos3 + 2);
            }
            else
            {
                // if pos2 was not found in sourcCodeLine
                // break this loop and move to next sourceCodeLine
                break;
            }

            // push the attrNameValuePair in attrNameValuePairArray
            attrNameValuePairArray.push_back(attrNameValuePair);

        }

        // push attrNameValuePairArray in the attrNameValuePairArrayContainer
        attrNameValuePairArrayContainer.push_back(attrNameValuePairArray);
    }

    // return attrNameValuePairArrayContainer to the caller
    return attrNameValuePairArrayContainer;
}