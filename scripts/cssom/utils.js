const dignities = ['0','1','2','3','4','5','6','7','8','9']


export function find_last_dignities(content)
{
    let last = -1
    for(let offset = content.length - 1; offset >= 0; offset--)
    {
        const one = content.charAt(offset)
        if(dignities.includes(one))
        {
            last = index
            continue
        }
        break
    }
    return last
}