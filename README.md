Trinket Rover
============
STEM / STEAM curriculum is gaining momentum in k-12 education. It's exciting, but there are some significant obstacles to manage: not all teachers have the technical expertise (or time) to generate curriculum, cost of materials can be prohibitive, and sourcing good quality components can be time consuming.

The aim of this project is to provide a low-cost but high-quality open software / open hardware platform for teaching robotics to students of all ages.


Instructions
============

Build instructions for the original rover are at:
https://learn.adafruit.com/trinket-powered-rover/red-rover

The Hack Manhattan version is beefed up a little by replacing the Trinket with an Arduino Nano, which is not much bigger and provides full Arduino functionality and digital pins, for only a couple of dollars more than the Trinket. 
We are using a different sonar module too, the HC-SR04, which has separate trigger and echo pins.

The wiring diagram is slightly different for the Nano version, see the /source folder.

Connections
===========

Sonar Trig Pin - 			Nano Pin D13
Sonar Echo Pin - 			Nano Pin D12
Right Servo Data Pin - 			Nano Pin D4
Left Servo Data Pin - 			Nano Pin D2
Power: 4xAA 1.2V NiMH Rechargeables  	Nano 5V/GND    (NB do NOT connect regular alkaline AA batteries directly to 5V, you could fry the Arduino due to the higher voltage!)


We sourced continuous rotation servo motors for almost the same price as regular ones, so you don't have to modify your own! They will still use the Adafruit Softservo library, so be sure to install it to your Arduino IDE hardware folder:
https://github.com/adafruit/Adafruit_SoftServo

You can 3D print your own chassis, using the STLs found here, or design your own! Rick made the originals in TinkerCAD, so bonus points for anyone who makes a parametric version in OpenSCAD!


####What's next?
------
Here are a few items that need attention...

 [ ] One-click configuration for Trinket 
 
 [ ] Manufacture continuous rotation servo (Turnigy requires a minimum order)
 
 [ ] Reduce cost of sonar to < $5
 

The target price for all electronics / hardware is ~ $25. Plastic parts can be produced on-site for ~ $2 each if the school has a 3D printer.



#####3D Printing
------
 * Chassis (small / large)
 * Front Free-spinning Wheels
 * Rear Drive Wheels
 * Sonar Clip
 * Mustache - not optional...

#####Electronics
------
 * Adafruit 3.3v Trinket
 * Parallax Ping))) Ultrasonic Sensor
 * Grove Ultrasonic Ranger
 * Continuous Rotation Micro Servos
 * Female / Male Jumpers

#####Hardware
------
 * 3X M3 10mm Screws
 * 1X M3 Hex Nut
 