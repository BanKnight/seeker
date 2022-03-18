export default class NamedNodeMap
{
    constructor()
    {
        this._attributes = []
        this._named = {}
    }

    get length()
    {
        return this._attributes.length
    }
    getNamedItem(qualifiedName)
    {
        return this._named[qualifiedName]
    }
    getNamedItemNS(namespace, localName)
    {

    }
    item(index)
    {
        return this._attributes[index]
    }
    removeNamedItem(qualifiedName)
    {
        const attr = this._named[qualifiedName]
        if(attr == null)
        {
            return 
        }

        delete this._named[qualifiedName]

        const index = this._attributes.indexOf(attr)

        this._attributes.splice(index, 1)

        return attr
    }
    removeNamedItemNS(namespace, localName)
    {

    }
    setNamedItem(attr)
    {
        this.removeNamedItem(attr.name)
        
        this._attributes.push(attr)

        this._named[attr.name] = attr

        return attr
    }
    setNamedItemNS(attr)
    {

    }
    
}