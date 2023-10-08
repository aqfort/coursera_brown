#include "ini.h"

#include <iostream>
#include <string>
#include <unordered_map>

namespace Ini
{
    const size_t Document::SectionCount() const
    {
        return data_storage.size();
    }

    const Section &Document::GetSection(const std::string &section) const
    {
        return data_storage.at(section);
    }

    Section &Document::AddSection(const std::string &section)
    {
        return data_storage[section];
    }

    // [секция 1]
    // ключ1=значение1
    // ключ2=значение2

    // [секция 2]
    // ключ3=значение3
    // ключ4=значение4

    Document Load(std::istream &input)
    {
        Document result{};
        return result;
    }
}
