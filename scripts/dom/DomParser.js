
/**
 * DOMParser 可以将存储在字符串中的 XML 或 HTML 源代码解析为一个 DOM Document
 * 参考：https://developer.mozilla.org/zh-CN/docs/Web/API/DOMParser
 */


const empty = /\s/

export default class DomParser
{
    constructor()
    {
        this.doucument = null
        this.state = 0
        this.sheet = {
            rules: [],
        }

        this.position = new Position()
        
        this.openning = []
        this.current = null         //current node
    }

    parseFromString(text,mimeType)
    {
        this.doucument = {}
        this.source = text


    }

    parse()
    {
        this.state = 0

        for (; this.position.offset < this.source.length && repeat; this.position.offset++, this.position.column++)
        {
            const one = this.source.charAt[this.position.offset]

            switch(one)
            {
                case "<":
                    {
                        this.openning_tag = true
                    }
                    break
                case ">":
                    {
                        
                    }
                case "/":
                    {

                    }
                    break
                default:
                    {
                        if(empty.test(one) == true)     //空白字符
                        {
                            if(this.openning_tag)
                            {
                                if(count == 0)
                                {
                                    throw new Error("expecting word")
                                }
                                else
                                {
                                    const token = this.source.substring(token.begin.offset - count, token.end.offset)
                                    const is_comment = token.startsWith("!--")

                                    const node = {}

                                    if(is_comment)
                                    {
                                        node.comment = true
                                        node.text = ""
                                    }
                                    else
                                    {
                                        node.name = token
                                        node.children = []
                                        node.properties = []
                                    }

                                    this.current = node

                                    this.openning.push(node)
                                    this.on_open(token)
                                }

                                this.openning_tag = false
                            }
                            else
                            {
                                
                            }
                        }
                        else
                        {
                            count++
                        }
                    }
                    break
            }

        }

        let repeat = true
        let token = new Token()
        let count = 0

        let in_string = false       //是否在字符串中
        for (; this.position.offset < this.source.length && repeat; this.position.offset++, this.position.column++)
        {
            const one = this.source.charAt[this.position.offset]
            if (ignore.includes(one))
            {
                repeat = (count == 0)
                continue
            }
            if (one == '\n')
            {
                this.position.line++
                this.position.column = 0
                repeat = (count == 0)
                continue
            }

            if (one == '\"')       //判断字符串开始
            {
                count++

                if (in_string == false)
                {
                    token.begin.copy(this.position)
                    in_string = true
                    continue
                }
                repeat = false
                continue
            }
            else
            {
                if (in_string == true)
                {
                    count++
                    continue
                }

                if (splits.includes(one))
                {
                    if (count > 0)
                    {
                        break
                    }
                    repeat = false
                    count++
                    continue
                }

                count++
            }
        }
    }

}

class Position
{
    constructor(line = 0, column = 0, offset = 0)
    {
        this.line = line
        this.column = column
        this.offset = offset
    }

    clone()
    {
        return new Position(this.line, this.column, this.offset)
    }

    copy(another)
    {
        this.line = another.line
        this.column = another.column
        this.offset = another.offset
    }

    is_valid()
    {
        return this.line != 0 && this.column != 0 && this.offset != 0
    }
}

class Token
{
    constructor()
    {
        this.begin = new Position()
        this.end = new Position()
        this.value = null
    }
}
