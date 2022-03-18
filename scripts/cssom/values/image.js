//https://developer.mozilla.org/en-US/docs/Learn/CSS/Building_blocks/Values_and_units#images
//https://developer.mozilla.org/en-US/docs/Web/CSS/image
export default function (context, key_token, value_tokens)
{
    //
    let url = ""

    if (skip_if(value_tokens, 0, "url"))
    {
        skip(value_tokens, 1, "(")
        for (let i = 2; i < value_tokens.length - 2; i++)
        {
            url += value_tokens[i].value
        }
        skip(value_tokens, value_tokens.length - 1, ")")
    }
    else
    {
        for (let i = 0; i < value_tokens.length - 1; i++)
        {
            url += value_tokens[i].value
        }
    }
}

function skip(value_tokens, index, ignore)
{
    const target = value_tokens[index]

    if(target.value != ignore)
    {
        throw new Error("must be:"+ignore)
    }
}

function skip_if(value_tokens, index, ignore)
{
    const target = value_tokens[index]

    return target.value != ignore
}