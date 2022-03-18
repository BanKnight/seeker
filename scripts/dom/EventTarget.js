console.log("this is event target")
// Listener types
const CAPTURE = 1;
const BUBBLE = 2;
const ATTRIBUTE = 3;

class Event
{
    constructor(type)
    {
        this.type = String(type)
        this.currentTarget = null
        this.canceled = false,
        this.stopped = false,
        this.immediateStopped = false,
        this.passiveListener = null,
        this.timeStamp = Date.now()
    }
}

class EventTarget
{
    constructor()
    {
        this.listeners = {}
    }
    /**
     * 
     * @param {string} type 
     * @param {function} listener 
     * @param {boolean|{capture?:boolean,passive?:boolean,once?:boolean}} options 
     * @returns {void}
     */
    addEventListener(type, listener, options)
    {
        if (listener == null)
        {
            return
        }

        let exists = this.listeners[type]
        if (exists == null)
        {
            exists = []
            this.listeners[type] = exists
        }

        const isObject = typeof (options) == "object"
        const capture = isObject
            ? Boolean(options.capture)
            : Boolean(options);

        const listenerType = capture ? CAPTURE : BUBBLE;

        exists.push({
            type: listenerType,
            listener,
            passive: isObject && Boolean(options.passive),
            once: isObject && Boolean(options.once),
        })

    }
    /**
     * Remove a given listener from this event target.
     * @param {string} type The event name to remove.
     * @param {Function} listener The listener to remove.
     * @param {boolean|{capture?:boolean,passive?:boolean,once?:boolean}} [options] The options for this listener.
     * @returns {void}
     */
    removeEventListener(type, listener, options)
    {
        if (listener == null)
        {
            return
        }
        let exists = this.listeners[type]
        if (exists == null)
        {
            return
        }

        const capture = typeof (options) == "object"
            ? Boolean(options.capture)
            : Boolean(options);

        const listenerType = capture ? CAPTURE : BUBBLE;

        let index = this.listeners.find((value) =>
        {
            return value.listener == listener && value.type == listenerType
        })

        if (index == null)
        {
            return
        }

        this.listeners.splice(index, 1)
    }

    /**
     * Dispatch a given event.
     * @param {Event|{type:string}} event The event to dispatch.
     * @returns {boolean} `false` if canceled.
     */
    dispatchEvent(event)
    {
        if (typeof event !== 'object')
        {
            throw new TypeError('Argument 1 of EventTarget.dispatchEvent is not an object.');
        }
        if (!(event instanceof Event))
        {
            throw new TypeError('Argument 1 of EventTarget.dispatchEvent does not implement interface Event.');
        }

        let exists = this.listeners[type]
        if (exists == null)
        {
            return true
        }

        event.target = this

        for(let i = 0;i < exists.length;)
        {
            const curr = exists[i]
            if(curr.once)
            {
                exists.shift(i,1)
            }
            else
            {
                i++
            }

            try 
            {
                curr.listener.call(this, event);
            } 
            catch (err) 
            {
                console.error(err);
            }
            if(event.immediateStopped)
            {
                break
            }
        }
        return !event.defaultPrevented
    }
}

export
{
    Event,
    EventTarget
}