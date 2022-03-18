
#if 0
#pragma once

#include <string>
#include <vector>
#include <variant>
#include <unordered_map>

// https://developer.mozilla.org/zh-CN/docs/Web/API/CSSRule

namespace seeker
{
    namespace css
    {
        enum SelectorType
        {
            ELEMENT = 0,
            ID = 1,
            CLASS = 2,
            ALL = 3,
        };

        enum PropertyType : int
        {
            ALIGN_CONTENT,
            ALIGN_ITEMS,
            ALIGN_SELF,
        };

        struct Position
        {
            int line = 1;
            int column = 1;
        };

        struct Comment
        {
            Position begin;
            Position end;

            std::string content;
        };

        struct Selector
        {
            Position begin;

            SelectorType type = SelectorType::ELEMENT;
            std::string name;
        };

        typedef std::variant<int, bool, float, std::string> Value; //

        struct Property
        {
            Position begin;
            std::unordered_map<int, Value> values;
        };

        struct RuleBase
        {

        };

        struct StyleRule : public RuleBase
        {
            std::vector<Selector> selectors;
            std::vector<Property> properties;
        };

        using Rule = std::variant<StyleRule>;
        using Rules = std::vector<Rule>;

        struct Sheet
        {
            Rules rules;
        };

        // https://github.com/csstree/csstree/blob/master/docs/ast.md
        void parse(const std::string &content,Sheet & sheet);
    }
}

#endif