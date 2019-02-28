# Arduino Writing Machine

![writing_machine](https://user-images.githubusercontent.com/35738310/53573718-5d57fe80-3b6e-11e9-8174-7d2ab71b477f.jpg)

The following project is a CNC machine with a polar coordinate system build on an Arduino.

## Components

* Arduino UNO R3 - The Most Complete Starter Kit
* 1 DVD - Player
* Pen
* Tape and some screws
* Some wood

## How it works

I am using the stepper motor and the servo motor of the Arduino Kit and the stepper motor of the DVD player.
The DVD stepper motor controls the radius and the the Arduino stepper motor the angle (polar coordinates).
On the DVD stepper I put some piece of wood, which I attached the servo motor and the pen on. The
steppers and the servo are controled by some Arduino libraries.
On top of these libraries I built my own functions in order to use the system properly.

Functions:
* print(String string, int font_size) -> takes a string of only uppercase letters, which I had to define by myself (see code); it automatically jumps into the next line, if written text >= 2 PI - some threshold

* penUp()

* penDown()

* movePos(int radius, int angle) -> moves position relative to its currentPos

* moveAt(int radius, int angle) -> moves absolute to the position

* draw(int radius, int angle) -> draws and moves position relative to its currentPos

* drawAt(int radius, int angle) -> draws and moves absolute to the position

* getDifference(int radius, int angle, String direction) -> updates x_diff and y_diff by the difference of the currentPos,                                                               targetPos and the direction, so either clockwise or counter                                                                   clockwise

* isRotated() -> checks if angle >= 2 Pi


![result](https://user-images.githubusercontent.com/35738310/53573731-65b03980-3b6e-11e9-8122-18a4bcb3e57e.jpg)
