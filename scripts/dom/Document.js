import Node from './Node';

export default class Document extends Node 
{
    constructor()
    {
        super();

        this._head = null
        this._body = null
        this._documentElement = null

    }

    get URL()
    {
        return ""
    }
    get documentURI()
    {

    }
    get compatMode()
    {

    }
    get characterSet()
    {

    }
    get charset()
    {

    }
    get inputEncoding()
    {

    }
    get contentType()
    {

    }

    get head()
    {
        return this._head
    }

    get body()
    {
        return this._body
    }

    get documentElement()
    {
        return this.documentElement
    }

    createElement(tagName,options)
    {

    }

    getElementById(id)
    {
        
    }

}