
import { find_last_dignities } from "../utils"

//https://developer.mozilla.org/en-US/docs/Web/CSS/length
//https://developer.mozilla.org/en-US/docs/Learn/CSS/Building_blocks/Values_and_units
export default function(context,key_token,value_tokens)
{
    if(value_tokens.length == 0)
    {
        throw new Error("invalid integer")
    }

    const token = value_tokens[0]

    let last_dignities = find_last_dignities(token.value)

    let value = parseFloat(value.substr(0,last_dignities + 1))
    let unit = value.substr(last_dignities + 1)

    return {
        value,
        unit
    }
}