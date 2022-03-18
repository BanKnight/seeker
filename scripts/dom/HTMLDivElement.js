export default class HTMLDivElement extends HTMLElement  
{
    constructor()
    {
        super();

        this._align = ""    //这是一个 DOMString 表示一个指示元素内容相对于周围内容的对齐方式的可枚举属性。可取的值有 "left"，"right"，"justify"，和 "center"。
    }

    get align()
    {
        return this._align
    }
    set align(value)
    {
        this._align = value
    }
}