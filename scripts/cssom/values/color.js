//https://developer.mozilla.org/en-US/docs/Learn/CSS/Building_blocks/Values_and_units#color
export default function (context, key_token, value_tokens)
{
    const first = value_tokens[0]

    const ret = {}

    switch (first.value)
    {
        case '#':
            {
                ret.hex = value_tokens[1].value
            }
            break
        case "rgb": //rgb(2, 121, 139)
        case "rgba":
            {
                ret.rgb = []

                for (let i = 1; i < value_tokens.length; ++i)
                {
                    let token = value_tokens[i]
                    if (token.value == ",")
                    {
                        continue
                    }
                    ret.rgb.push(value)
                }
            }
            break
        case "hsl":
        case "hsla":
            {
                ret.hsl = []

                for (let i = 1; i < value_tokens.length; ++i)
                {
                    let token = value_tokens[i]
                    if (token.value == ",")
                    {
                        continue
                    }
                    ret.hsl.push(value)
                }
            }
            break
        default:
            ret.keywords = first.value
            break
    }

}