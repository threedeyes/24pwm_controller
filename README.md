24pwm_controller
==========

Software PWM Controller based on ATMega16

Building
--------

Cloning repo:

	$ git clone https://github.com/threedeyes/24pwm_controller

Building 24pwm_controller:

	$ make

Uploading
----------
	For example:

	$ avrdude -c stk500v2 -P avrdoper -p atmega16 -U flash:w:'pwm.hex'

