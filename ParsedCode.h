#ifndef PARSED_CODE_H
#define PARSED_CODE_H

#include "SourceCode.h"
#include <iostream>
#include <vector>
#include <array>
#include <string>

class FindQuery;

class ParsedCode
{
private:
    // AttrNameValuePair contains attribute name-value pair
    struct AttrNameValuePair
    {
        std::string attrName{};
        std::string attrValue{};
    };

public:
    using sourceCode_container_type = std::vector<std::string>;
    using tagName_container_type = std::vector<std::string>; 
    using attrNameValuePairArray_container_type = std::vector<std::vector<AttrNameValuePair>>;

private:
    // contains tagNames
    tagName_container_type m_tagNameContainer{};
    // contains arrays of attribute name-value pairs
    attrNameValuePairArray_container_type m_attrNameValuePairArrayContainer{};

public:
    // constructor initializes member variables
    ParsedCode(const SourceCode &sourceCode);
    // prints tag-names and attribute name-value pairs
    void print() const;
    // initializes m_tagNameContainer
    tagName_container_type fillTagNameContainer(const SourceCode &sourceCode) const;
    // initializes m_tagNameContainer
    attrNameValuePairArray_container_type fillAttrNameValuePairArrayContainer(
                                                     const SourceCode &sourceCode) const;

    // returns m_attrNameValuePairArrayContainer
    tagName_container_type getTagNameContainer() const
    {
        return m_tagNameContainer;
    }

    // returns m_attrNameValuePairArrayContainer
    attrNameValuePairArray_container_type getAttrNameValuePairArrayContainer() const
    {
        return m_attrNameValuePairArrayContainer;
    }

    friend class FindQuery;
};

#endif