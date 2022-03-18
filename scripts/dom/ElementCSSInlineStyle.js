
class CSSStyleDeclaration
{
    constructor()
    {
        this._items 
    }

    getPropertyValue(property)
    {
        return this[property];
    } 

    setPropertyValue(property, value)
    {
        this[property] = value;
    }
}

export default class ElementCSSInlineStyle
{
    constructor()
    {
        this._style = new CSSStyleDeclaration()
    }

    get style()
    {
        return this._style
    }
}