export function mixin(...mixins) 
{
    let last = null
    for(let one of mixins)
    {
        last = class Mixin extends one
        {
            constructor(...args)
            {
                super(...args)
            }
        }
    }

    return last
}