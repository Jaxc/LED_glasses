# Python testing of effects
Using the code in this folder it is possible to develop effects without access to the hardware itself!
## Basic information
The effects are developed in C. The resources on the MCU is currently very limited, so avoid much data in the effect.
The CPU power is also quite limited so avoid complex calculations if possible. 
If an effect is too slow it will be detected and the MCU will stop safely.

A pattern is a combination of a colour effect and a light effect.
The colour effect outputs a colour which can then be dimmed using a light effect.
One example of this is that a strobe light effect can be used with any colour effect.

## Tools needed
To be able to develop you will need some kind of editor for the C code.
You will also need the following programs installed and in PATH:
* GCC
* Make
* Python 3

I highly recommend the following tool as well:
* GDB for debugging the effect of the C code

## How effects works
The effects have a set of functions that will be called during execution.
An template for the effects can be found in `effects/colours/template_colours.c` and `effects/lights/template_lights.c` respectively.
The callouts available are described below
### Generate frame
This is the main function for generating and assigning values to each separate LED.
In this function you will need to iterate over all LEDs inside of this function. 
For the colour generate frame function the array consists of 3 values for each LED due the LEDs are supporting 3 colours of 8 bits per colour.
Do note that the colour scheme is Green, Red, Blue (as opposed to the usual Red, Green, Blue).

### Beat start
This function is called when a beat has been detected. 
Use this to give an indication to the Generate Frame function that a beat has occurred.

## Creating a pattern for your effect
The process of installing the pattern is quite honestly a bit annoying, but this was the most reasonable way I could figure out.
1. Add your effect to `Inc/colour.h` and/or `Inc/lights.h`. You will need to create a new `#define` for your effect and name it to something descriptive. Easiest is to just copy one of the others effects and change as needed. If you are not using any of functions you can assign it to `&do_nothing`.
2. Figure out a good name for your effect and add last (just before `N_EFFECTS`) it to the `typedef enum patterns {}` in `Inc/pattern_generate.h`
3. Create a new row at the end of `const struct Presets presets[N_EFFECTS]` struct. Here you will use the define(s) you created in step 1.