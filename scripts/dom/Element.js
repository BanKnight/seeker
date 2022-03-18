export default class Element extends Node
{
    constructor()
    {
        super()
        this._attributes = new NamedNodeMap();
        this.classList = [];
        this._className = ""
        this._id = ""
        this._tagName = ""
    }

    get clientHeight()
    {

    }

    get clientLeft()
    {

    }

    get clientTop()
    {

    }

    get clientWidth()
    {

    }

    get id()
    {
        return this._id
    }

    set id(value)
    {
        this._id = value
    }

    get tagName()
    {
        return this._tagName
    }

    getAttributeNode(qualifiedName)
    {
        return this._attributes.get(qualifiedName)
    }
    hasAttribute(qualifiedName)
    {
        return this._attributes.has(qualifiedName)
    }
    hasAttributes()
    {
        return !this._attributes.empty()
    }
    setAttribute(qualifiedName, value)
    {
        this._attributes.set(qualifiedName,value)
    }



}