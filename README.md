24pwm_controller
=============

Software PWM Controller based on ATMega16

Building
-----------

Cloning repo:

	$ git clone https://github.com/threedeyes/24pwm_controller

Building 24pwm_controller:

	$ make

Uploading
-------------
	For example:

	$ avrdude -c stk500v2 -P avrdoper -p atmega16 -U flash:w:'pwm.hex'

Using
-------
	1. UART baudrate is 38400
	2. Servo named by capital latin symbols (from A to X).
	3. Range PWM values: 0 - 99 (from 0 to 180 equivalently)
	4. For enable / disable pwm timer used #E and #D codes

	Set Servo named "A" to 30 degrees position for example:
	
	unsigned char value = 17; // 17*180/100 = 30 degrees
	Serial.begin(38400); // Baudrate = 38400
	Serial.print("#E"); // Enable pwm controller
	Serial.write("A"); // Select "A" servo (pin 40)
	Serial.write(value); //Set pwm value
