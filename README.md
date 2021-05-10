# Motorized Camera Slider
This motorized camera slider moves a DSLR camera smoothly along a slider to take cinematic time-lapses and videos. At the heart of the project is the software on the MSP432P401R that takes input from a keypad, displays information on an LCD, and controls a stepper motor mounted on the slider with a stepper motor driver module. The user has control over the mode (either time-lapse or video) as well as the number of images (also called frames) in a time-lapse and the duration in seconds between the beginning of each frame. In time-lapse mode, Timer A0 and interrupts are used to wake up the system from low power mode so it can push the camera carriage forward a certain amount over the user-determined interval. In terms of power, the stepper motor is powered by an external 12 V battery pack with 8 AA batteries and the MSP432 is powered by a 5 V portable power bank for portability.

<div align="center">
<img src="https://github.com/cameronapriest/motorizedcameraslider/blob/main/schematic.png" width="800">

**System Schematic**
</div>

<img src="https://github.com/cameronapriest/motorizedcameraslider/blob/main/Slider%20In%20Action.JPG" width="500">

<img src="https://github.com/cameronapriest/motorizedcameraslider/blob/main/Slider%20In%20Action%202.JPG" width="500">

