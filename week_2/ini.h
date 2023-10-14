#pragma once

#include <iostream>
#include <string>
#include <unordered_map>

namespace Ini
{
    using Section = std::unordered_map<std::string, std::string>;

    class Document
    {
    public:
        explicit Document() = default;

        size_t SectionCount() const;
        const Section &GetSection(const std::string &section) const;
        Section &AddSection(std::string section);

    private:
        std::unordered_map<std::string, Section> data_storage;
    };

    Document Load(std::istream &input);
}
