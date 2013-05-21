# Car Driver Shield #

This is a library for [Elechouse](http://www.elechouse.com/) [Car Driver Shield]() , 

## Instruction ##

### Files ###

- CarDriverShield.h - library header file
- CarDriverShield.cpp - library source file
- exmples - samples folder.
	- car\_driver\_shield\_sample0.ino - sample
- image - some related images
- keywords.txt - Add keywords Arduino key words list, this benefits your developing.

### Functions ###
***CarDriverShield*** - library class name, use to declare a user class for using library.

***begin(int led_num)*** - CarDriverShield initial function. Must be called in **setup()** of arduino. `led_num`=**-32768** means no LED is needed.

***forward()*** - car run forward

***backward()*** - car run backward

***decelerate()*** - car run decelerate

***accelerate()*** - car run accelerate

***turn_left()*** - car run turn_left

***turn_right()*** - car run turn_right

***evt_loop()*** - CarDriverShield event loop, handle speed refreshing and LED control.
******

## How to ##

*This is a quick start guide, which aims to teach you how to use this **CarDriverShield** library and tell you what you need prepare for using.*

### Prepare ###

- [Arduino Nano board](http://arduino.cc/en/Main/ArduinoBoardNano)
- [Car Driver Shield](http://www.elechouse.com)
- A toy car board with four motors(2 motors a group), [like this](http://www.emartee.com/product/42135/4WD%20Robot%20Raider%20Car%20Kits)

### Assemble ###

1. Plug your **Arduino Nano** into **Car Driver Shield**.
2. Fix **Car Driver Shield** in your **Toy Car**.
3. Parallel connect the two left side wheels, anode to anode, cathode to cathode, then connect the **anode(+)** of the left wheels to the **OUTA-1** and the **cathode(-)** to **OUTA-2** 
4. Just do as **part 3**, parallel connect the two right side wheels, anode to anode, cathode to cathode. Then connect the **anode(+)** of the right wheels to the **OUTB-1** and the **cathode(-)** to **OUTB-2**.
5. Connect the battery.

### Upload ###

1. Download CarDriverShield.

		#get through GIT tools :
		git clone https://github.com/elechouse/CarDriverShield.git

	or
		
		#download zip file
1. Extract the zip file if you download the zip format file. Copy CarDriverShield  to **$ArduinoSketch/libraries** .
		
	Note: **$ArduinoSketch** means your **Arduino sketchbook location**, you can find it by opening *ArduinoIDE->File->Preferences* or shortcut **Ctrl+comma**
1. Restart your Arduino IDE.
1. Open car\_driver\_shield\_sample0. (ArduinoIDE->File->Examples->CarDriverShield->car\_driver\_shiled\_sample0)
1. Connect your [Arduino Nano](http://arduino.cc/en/Main/ArduinoBoardNano) to PC, select exact **Serial Port**, select exact arduino Board.
1. Hit **upload** button, wait to be uploaded.
1. Now you can control you **Toy Car** through serial port(_Default : 115200,8,N,1_),

Most people may need to control your car by **wireless way**, here is some recommended way:

- [Wifi Car](https://github.com/elechouse/wifi-car) (*Strongly recommended*)
- Bluetooth Car (see this [Serial Bluetooth Module](http://www.elechouse.com/elechouse/index.php?main_page=product_info&cPath=90_91&products_id=1385)
- 2.4GHz Car (see this [2.4GHz Module](http://www.elechouse.com/elechouse/index.php?main_page=product_info&cPath=90_92&products_id=2218))
- may be more ...

### Run your car ###
Control your car by sending these characters:

- w --> forward; 
- s --> backward; 
- a --> turn left; 
- d --> turn right;
- e --> accelerate; 
- c --> decelerate; 
- z --> stop;

## **Buy** ##
[![elechouse](./image/elechouse.png) ](http://www.elechouse.com) 






