export default class HTMLElement extends mixin(Element,ElementCSSInlineStyle)
{
    constructor()
    {
        super()

        this._accessKey = ""
        this._accessKeyLabel = ""
        this._autocapitalize = ""
        this._dir = ""
        this._draggable = false
        this._hidden = false
        this._innerText = ""
        this._lang = ""
        
        this._offsetHeight = 0
        this._offsetLeft = 0
        this._offsetParent = null
        this._offsetTop = 0
        this._offsetWidth = 0

        this._outerText = ""
        this._spellcheck = false
        this._title = ""
        this._translate = false
    }

    get accessKey()
    {
        return this._accessKey
    }
    set accessKey(value)
    {
        this._accessKey = value
    }

    get accessKeyLabel()
    {
        return this._accessKeyLabel
    }

    get offsetHeight()
    {
        return this._offsetHeight
    }
    get offsetLeft()
    {
        return this._offsetLeft
    }
    get offsetParent()
    {
        return this._offsetParent
    }
    get offsetTop()
    {
        return this._offsetTop
    }
    get offsetWidth()
    {
        return this._offsetWidth
    }
    get outerText()
    {
        return this._outerText
    }
    set outerText(value)
    {
        this._outerText = value
    }
    get spellcheck()
    {
        return this._spellcheck
    }
    set spellcheck(value)
    {
        this._spellcheck = value
    }

    get title()
    {
        return this._title
    }
    set title(value)
    {
        this._title = value
    }

    get translate()
    {
        return this._translate
    }
    set translate(value)
    {
        this._translate = value
    }

}