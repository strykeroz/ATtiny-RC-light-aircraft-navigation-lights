ATtiny-RC-light-aircraft-navigation-lights
==========================================

ATtiny85 RC aircraft navigation lights, using Arduino core.

This project adds wingtip navigation lights, headlights, and a flashing tail beacon to RC light aircraft using an ATtiny85.  The ATtiny85 initially checks for daylight using an LDR, and if it is bright powers off entirely so flight time in daylight is not impacted by additional power consumption.  Since RC flights are typically under 20mins it was preferable to save battery power by shutting down rather than keeping running to monitor for the light fading.

If the LDR reports it's sufficiently dark, the ATtiny powers down the LDR and runs the lights.  The LDR is only tested once.

Of course, if you want to run with lights during the day, cover the LDR with your finger when you turn your plane's power on or connect the battery.

Operation
---------
5sec after power on, all lights are flashed 3 times for visual confirmation of operation.  If the LDR reports daylight, the lights then are flashed 3 times quickly before the ATtiny85 shuts down.  If the LDR reports darkness, lights and strobe are turned on and the LDR is powered off to conserve battery.  Disconnecting and reconnecting power will restart the process.

ATtiny85 pin assignments 
------------------------
(legs numbered 1..8 counterclockwise from leg marked with dot)  
1. Reset pin, no connection
2. LDR sensor reading (connected to one leg of LDR, and the end of a 10kR resistor which is connected to GND)
3. LDR power (connected to the other end of the LDR). Only powered while LDR readings are needed
4. GND.  Connected to ground.
5. Wingtip navigation lights.  Connected to red & green LEDs in parallel through correct current limiting resistors
6. Tail strobe.  Connected to a red LED through a current limiting resistor
7. Headlights.  Connected to a pair of white LEDs in parallel, through correct current limiting resistors
8. VCC, in this case most likely 3.7V, so ATtiny will run without additional regulation

Code
----
Written using the Arduino IDE, the target to select is the ATtiny85 @ 8MHz (internal oscillator, BOD disabled).  Look up how to program the ATtiny using Arduino, and programming it using Arduino as an IDE.  There are no external libraries used.  The only dependency is included with the IDE (avr/sleep.h).

Tested installation
-------------------
This has been tested in a Parkzone Ultra Micro T-28 Trojan.  We ran 3mm LEDs for the tail strobe and wingtips with a pair of 5mm white LEDs for the headlights.

Remember to use current limiting resistors to ensure the lights don't chew heaps of power from your aircraft.  We set ours with a goal of 10mA or less based on 3.7V for supply from the LiPo.  (http://ledcalc.com/ is handy!).

Power for the ATtiny was taken by splicing directly into the power lead to the battery.  We soldered all the components onto a DIP8 socket so if we need to upgrade the software in future, we can pull the ATtiny.  The IC sits inverted with the resistors above, and wires leading out from there.

The LDR pokes out through the join in the side of the fuselage, so when the aircraft is all taped up, it helps hold the ATtiny in place.

BoM as tested:  
	1x ATtiny85-20PU  
	1x 8 pin DIP IC Socket (optional, you might be confident soldering direct to the ATtiny to reduce weight)  
	2x 3mm red LEDs  
	1x 3mm green LED  
	2x 5mm white LED  
	1x Light dependent resistor  
	1x 10kR resistor (voltage divider, for LDR)  
	2x 100R resistor (current limiting, headlights)  
	3x 220R resistor (current limiting, wingtips & strobe)  
	Thin, light wire (we pulled apart an IDE cable for ours)  
	
  
Enjoy : ) 