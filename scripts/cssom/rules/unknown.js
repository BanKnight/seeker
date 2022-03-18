export default function unknown(context)
{
    const first = context.touch()

    switch (first.value)
    {
        case '@':
            dot_rule(context)
            break
        case '/':       //comment
            break
        default:        //style
            context.state = 1
            break
    }
}

function dot_rule(context)
{
    const keyword = context.touch(1)

    switch (keyword.value)
    {
        case 'charset':
            context.state = 2
            break
        case 'import':
            context.state = 3
            break
        default:
            throw new Error('unknow dot rule:' + keyword.value)
            break
    }
}