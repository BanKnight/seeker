export class Position
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

export class Token
{
    constructor()
    {
        this.begin = new Position()
        this.end = new Position()
        this.value = null
    }
}

const ignore = ['\r']
const splits = [',', ':', '{', '}', '(', ')', '@']; //这几个会单独token化

export class Context
{
    constructor(source)
    {
        this.source = source
        this.state = 0
        this.sheet = {
            rules: [],
        }

        this.position = new Position()
        this.tokens = []
        this.current = null         //current token
    }

    /**
     * 生成下一个单词token
     * 注意：
     *      1 如果是双引号包含的字符串，那么这个token.value = 字符串
     *      2 如果是注释，那么忽略
     * @returns 
     */
    next()
    {
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

        if (count == 0)
        {
            return false
        }

        token.end = current.position.clone()
        token.value = this.source.substring(token.begin.offset, token.end.offset).toLowerCase()

        this.tokens.push(token)

        return true
    }

    prepare(count = 1)
    {
        while (this.tokens.length < count)
        {
            if (this.next() == false)
            {
                return false
            }
        }
        return true
    }

    consume(count = 1)
    {
        return this.tokens.splice(0, count)
    }
    at(index = 0)
    {
        if (this.prepare(index + 1) == false)
        {
            throw new Error("no enough data")
        }

        this.current = this.tokens[index]

        return this.current
    }

    touch(index = 0)
    {
        if (this.prepare(index + 1) == false)
        {
            return
        }

        this.current = this.tokens[index]

        return this.current
    }

    fetch(index = 0)
    {
        if (this.prepare(index + 1) == false)
        {
            throw new Error("no enough data")
        }

        this.current = this.tokens[index]
        this.consume(index + 1)

        return this.current
    }

    skip(ignore)
    {
        if (this.prepare(1) == false)
        {
            throw new Error("no enough data")
        }

        const first = this.fetch()

        if (first.value != ignore)
        {
            throw new Error("skip error:" + ignore)
        }
    }

    skip_if(ignore)
    {
        const first = this.touch()

        if (first == null || first.value != ignore)
        {
            return false
        }

        this.consume(1)

        return true
    }

    find(target, start = 0)
    {
        let index = start

        for (; ; index++)
        {
            const token = context.touch(index)

            if (token == null)
            {
                return -1
            }

            if (token.value == target)
            {
                return index
            }
        }
        return -1
    }

    next_line()
    {
        let line = this.current != null ? this.current.end.line : 0

        while(true)
        {
            const token = context.touch()
            if(token == null || token.begin.line != line)
            {
                break 
            }
            this.consume(1)
        }
    }

}

