#ifndef RAW_QUERY_H
#define RAW_QUERY_H

#include <iostream>
#include <vector>
#include <array>
#include <string>

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

#endif