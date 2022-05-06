# CS5780 Mini Project

Team Members: Niles McNabb, John Michaels, Brian Cottle

# Project Goal
High level description: Using the discovery board and approximately 7 buttons, we will produce
a mini “piano” with five keys and some limited recording and looping functionality. The discovery
board will communicate with five buttons which will be hidden below 3D printed piano keys (or
something similar). These buttons will produce interrupts which cause predetermined tones to
play over a speaker connected to the board. An additional button will determine a period over
which the “key” presses will be recorded and then played back on a loop, enabling different
patterns of sounds to be played over top of one another. A third functionality will produce an
export of the information necessary to reproduce the musical tones on a separate device, or at a
different time. Additionally, we will include a potentiometer that alters the saved frequency
values for the tones produced by each key, enabling “tuning” of the keys to produce a larger
variety of music.

# Hardware 
This project uses the following hardware:

STM32F072 Discovery kit
8 push buttton switches
HiLetgo PAM8403 Mini Digital Power Amplifier Board (https://www.amazon.com/dp/B00LODGV64)
uxcell a15080600ux0275 Metal Shell Round Internal Magnet Speaker (https://www.amazon.com/dp/B0177ABRQ6)

# Compliation 
Required software: Keil uvision 5, stlink drivers

Open PainoKeys.uvprojx in Keil uvision 5, located in PainoKeys -> MDK-ARM 

Allow Keil uvision 5 to install any missing packages

Build and load program on to the device

# Instruction 

Buttons connected to pin PB2 through PB6 will play different tones when activated

Button connected to PB9 will start a recording 
Any tones played after starting the record will be stored in memory 
Starting a new recording will overwrite the old one

Button connected to PB8 will playback the current recording 

Button connected to PB7 will transmit data about the current recording over a UART serial connection
