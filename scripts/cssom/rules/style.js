// import selectors from './selectors'
import values from "../value"

export default function rule(context)
{
    selector(context)
    declaration(context)

    context.sheet.rules.push(context.rule)
    context.state = 0
}

function selector(context)
{
    let index = context.find('{')

    if (index == 0 || index == -1)
    {
        throw new Error("no selector found")
    }

    context.rule = {
        selector: context.consume(index),     // TODO:后续再详细处理
        properties: [],
    }

    context.consume(1)                        //skip "{"
}

function declaration(context)
{
    let key_token = null
    let index = 0
    let repeat = true
    for (; repeat; index++)
    {
        const token = context.at(index)

        switch (token.value)
        {
            case ':':
                {
                    if (index == 0)
                    {
                        throw new Error("invalid property")
                    }
                    key_token = context.at(0)
                    context.consume(index + 1)
                }
                break
            case ';':
                {
                    if(index == 0 || key_token == null)
                    {
                        if (index == 0)
                        {
                            throw new Error("invalid property")
                        }
                    }
                    parse_value(context, key_token, index)
                    context.consume(1)

                    index = -1
                    key_token = null
                }
                break
            case '}':
                repeat = false
                break
            default:
                break
        }
    }
}

function parse_value(context, key_token, end)
{
    const value_tokens = context.consume(end)
    const parser = values[key_token.value]
    
    const value = parser(context, key_token, value_tokens)

    context.rule.properties.push({
        type:"style",
        key: key_token.value,
        value: value,
    })
}