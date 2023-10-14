#include "ini.h"

#include <iostream>
#include <string>
#include <unordered_map>

namespace Ini
{
    size_t Document::SectionCount() const
    {
        return data_storage.size();
    }

    const Section &Document::GetSection(const std::string &section) const
    {
        return data_storage.at(section);
    }

    Section &Document::AddSection(std::string section)
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
        std::string line{};
        Section *section = nullptr;
        while (getline(input, line))
        {
            if (!line.empty())
            {
                if (line[0] == '[')
                {
                    section = &result.AddSection(line.substr(1, line.length() - 2));
                }
                else
                {
                    const auto equality = line.find('=');
                    section->insert({line.substr(0, equality), line.substr(equality + 1)});
                }
            }
        }
        return result;
    }
}
