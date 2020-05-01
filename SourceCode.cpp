#include "SourceCode.h"

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