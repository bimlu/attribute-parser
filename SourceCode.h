#ifndef SOURCE_CODE_H
#define SOURCE_CODE_H

#include <iostream>
#include <vector>
#include <array>
#include <string>

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
};

#endif