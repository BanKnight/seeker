#if 0
#include <algorithm>
#include <stdexcept>
#include "css/parser/index.h"

namespace seeker
{
    namespace css
    {

        bool is_newline(unsigned char one)
        {
            return one == '\n' || one == '\r';
        }

        bool is_punctuation(unsigned char one)
        {
            return one != '-' && one != '_' && std::ispunct(one);
        }

        bool is_word(unsigned char one)
        {
            return std::isalnum(one) || one == '-' || one == '_' || std::ispunct(one);
        }

        static const std::vector<unsigned char> splits = {',', ':', '{', '}', '(', ')', '\"'}; //这几个会单独token化

        enum State
        {
            WAITING = 0,
            SELECTOR = 1,
            PROPERTY = 2,
            PROPERTY_NAME = 3,
            PROPERTY_VALUE = 4,
            ERROR,
        };

        enum TokenType
        {
            IDENTIFIER = 0,
            PUNCTUATION = 1,
        };

        struct Token
        {
            TokenType type = TokenType::IDENTIFIER;
            Position position;
            std::string value;
        };

        struct Context
        {
            State state = State::WAITING;
            int offset = 0;
            std::string content;
            Position position;
            std::vector<Token> tokens;
            Rules rules;
        };

        bool next(Context &context) noexcept
        {
            Token token;

            auto count = 0;
            auto repeat = true;
            for (; context.offset < context.content.length() && repeat; context.offset++, context.position.column++)
            {
                auto one = (unsigned char)context.content[context.offset];
                if (is_newline(one))
                {
                    context.position.line++;
                    context.position.column = 0;
                    repeat = false;
                    continue;
                }

                if (std::find(splits.begin(), splits.end(), one) != splits.end())
                {
                    count++;
                    repeat = false;
                    token.type = TokenType::PUNCTUATION;
                    continue;
                }
                if (is_word(static_cast<unsigned char>(one)) == false)
                {
                    repeat = false;
                    continue;
                }
                count++;
            }

            if (count == 0)
            {
                return false;
            }

            token.position = {context.position.line, context.position.column - count},
            token.value = context.content.substr(context.offset - count, count);

            std::transform(token.value.begin(), token.value.end(), token.value.begin(), ::tolower);

            context.tokens.push_back(token);

            return true;
        }

        void prepare(Context &context, int count = 1)
        {
            while (context.tokens.size() < count)
            {
                if (next(context) == false)
                {
                    throw std::runtime_error("size is not enough");
                }
            }
        }

        void consume(Context &context, int count = 1)
        {
            context.tokens.erase(context.tokens.begin(), context.tokens.begin() + count);

            if (context.tokens.empty())
            {
                next(context);
            }
        }

        void skip(Context &context, const std::string &ignore)
        {
            prepare(context, 1);

            auto &first = context.tokens.front();

            auto result = first.value == ignore;

            if (!result)
            {
                throw std::runtime_error("skip error");
            }

            consume(context, 1);
        }

        void parse_waiting(Context &context)
        {
            context.state = State::SELECTOR;
        }

        void parse_rule(Context &context)
        {
            auto rule = Rule();

            context.rules.push_back(rule);
        }

        void parse_selector(Context &context)
        {
            auto &rules = context.rules;

            auto &rule = *rules.rbegin();
            auto selector = Selector();

            auto first = context.tokens[0];

            auto first_char = first.value[0];

            switch (first_char)
            {
            case '.':
            {
                selector.type = SelectorType::CLASS;
                selector.name = first.value.substr(1);
            }
            break;
            case '#':
            {
                selector.type = SelectorType::ID;
                selector.name = first.value.substr(1);
            }
            break;
            default:
            {
                selector.name = first.value;
            }
            }

            selector.begin = first.position;

            rule.selectors.push_back(selector);

            consume(context, 1);

            prepare(context, 1);

            first = context.tokens[0];

            if (first.value == ",")
            {
                consume(context, 1);
            }
            else if (first.value == "{")
            {
                consume(context, 1);

                context.state = State::PROPERTY_NAME;
            }
            else
            {
                throw std::runtime_error("unsupport selector yet");
            }
        };

        void parse_property(Context &context)
        {
            prepare(context, 5); //key:value;}

            auto &rules = context.rules;

            auto &rule = *rules.rbegin();
            auto key_token = context.tokens[0];

            consume(context, 1);

            skip(context, ":");

            Property property;

            property.begin = key_token.position;
            // property.name = key_token.value;

            while (true)
            {
                prepare(context, 1);

                auto current = context.tokens[0];

                if (current.value == "}" || current.value == ";")
                {
                    break;
                }

                // property.values.push_back(current.value);

                consume(context, 1);
            }

            rule.properties.push_back(property);

            auto last = context.tokens[0];

            consume(context, 1);            //skip:;/{

            if (last.value == "}")
            {
                context.state = State::WAITING;
            }
        };

        void parse(const std::string &content,Sheet & sheet)
        {
            Context context;

            context.content = content;

            while (true)
            {
                if (context.tokens.empty() && next(context) == false)
                {
                    break;
                }
                switch (context.state)
                {
                case State::WAITING:
                {
                    parse_waiting(context);
                }
                break;
                case State::SELECTOR:
                {
                    parse_selector(context);
                }
                break;
                case State::PROPERTY:
                {
                    parse_property(context);
                }
                break;
                }
            }

            return context.rules;
        }

    }
}

#endif
