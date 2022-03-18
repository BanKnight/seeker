import {Event,EventTarget} from "./EventTarget.js"

const target = new EventTarget();

if(target)
{
    console.log("new target")
}

console.log("start in boot bootstrap")
console.log("scriptArgs",scriptArgs)

