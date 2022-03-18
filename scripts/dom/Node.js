

export default class Node extends EventTarget
{
    constructor()
    {
        super()
        
        this._name = ""
        this._value = ""
        this._childs = []
        this._prev = null
        this._next = null
    }
    /**
     * 
     */
    get baseURI()
    {
        return ""
    }

    get childNodes()
    {
        return this._childs
    }

    get firstChild()
    {
        return this._childs[0]
    }
    get lastChild()
    {
        if(this._childs.length == 0)
        {
            return
        }
        return this._childs[this._childs.length - 1]
    }

    get nextSibling()
    {
        return this._next
    }

    get previousSibling()
    {
        return this._prev
    }

    appendChild(node)
    {
        const last = this.lastChild
        if(last)
        {
            last._next = node
            node._prev = last
        }
        this.childNodes.push(node)

        return node
    }

    cloneNode()
    {

    }

    contains(other)
    {
        return this.childNodes.includes(other)
    }

    insertBefore(node,child)
    {
        if(node == null)
        {
            this.appendChild(node)
            return
        }

        const index = this._childs.indexOf(child)
        if(index == -1)
        {
            return
        }

        this._childs.splice(index,0,node)

        const prev = child._prev
        if(prev)
        {
            prev._next = node
            node._prev = prev
        }
        node._next = child
        child._prev = node

        return node
    }

    removeChild(child)
    {
        const index = this._childs.indexOf(child)
        if(index == -1)
        {
            return
        }
        
        const deleted = this._childs.splice(index,1)

        return deleted[0]
    }

    replaceChild(node,child)
    {
        const index = this._childs.indexOf(child)
        if(index == -1)
        {
            return
        }
        
        const deleted = this._childs.splice(index,1,node)

        return deleted[0] 
    }
}