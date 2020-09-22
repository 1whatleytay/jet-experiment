# jet - An HDL languge experiment.

I am really proud of this HDL.
I made this when I was really into engineering, and I was making CPU's etc. and it took me a lot of time to wire.
Unfortunately, there was supposed to be an interpreter but I never made it.
The interpreter was going to be pretty complicated, so I should've probably spent more time thinking it through.

## Theory Syntax

It has been a while since I wrote this, so I am just going to write what I remember the syntax to be like.

```
// Comments don't exist yet, but I'll be using them.

// [c = 0] is a constant, you can use math to make chips of different sizes, chip is like a function.
// For example, the input and output wire are the same constant size.
chip Memory[c = 300](in inputWire[c], out outputWire[c], in combineLine) { // array of wires
  inputWire = otherWire // use = to wire stuff together

  thing = not (outputWire xor combineLine) // single wire and expressions

  // declare math expressions with const
  const z = c + 8

  // Declare other chips, access output wire with .
  otherWire[z] = OtherChip[z](thing).lastWire


}

chip OtherChip[p](b[p], out lastWire[p]) {
  // ...
}
```