import { Context } from "./types"
import rules from "./rules"

export default function parse(source)
{
    const context = new Context(source)

    while (true)
    {
        if (context.tokens.length == 0 && next(context) == false)
        {
            break
        }

        //参考：https://developer.mozilla.org/zh-CN/docs/Web/API/CSSRule

        const parser = rules[context.state]

        parser(context)
    }

    return context.sheet
}
