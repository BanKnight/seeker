//https://developer.mozilla.org/en-US/docs/Web/API/CSSImportRule
//https://developer.mozilla.org/en-US/docs/Web/CSS/@import
export default function rule(context)
{
    context.skip('@')
    context.skip('import')

    let value_token = null

    if(context.skip_if("url"))
    {
        context.skip("(")
        
        value_token = context.fetch()

        context.skip(")")
    }
    else
    {
        value_token = context.fetch()
    }

    context.next_line()

    context.sheet.rules.push({
        type:"import",
        value:value_token.value
    })
}