compile-pro:
	arduino-cli compile --fqbn arduino:avr:pro ../src/main.ino
	mv ./../src/main.ino.arduino.avr.pro.elf ./build.arduino.avr.pro.elf 
	mv ./../src/main.ino.arduino.avr.pro.hex ./build.arduino.avr.pro.hex
	mv ./../src/main.ino.arduino.avr.pro.with_bootloader.hex ./build.arduino.avr.pro.with_bootloader.hex

upload-pro:
	arduino-cli upload -p /dev/cu.usbmodem14101 --fqbn arduino:avr:pro
	chmod +x serial.command
	open serial.command

build-pro:
	make compile-pro
	make upload-pro

compile-uno:
	arduino-cli compile --fqbn arduino:avr:uno ../src/main.ino
	mv ./../src/main.ino.arduino.avr.uno.elf ./build.arduino.avr.uno.elf 
	mv ./../src/main.ino.arduino.avr.uno.hex ./build.arduino.avr.uno.hex
	mv ./../src/main.ino.arduino.avr.uno.with_bootloader.hex ./build.arduino.avr.uno.with_bootloader.hex

upload-uno:
	arduino-cli upload -p /dev/cu.usbmodem14101 --fqbn arduino:avr:uno
	chmod +x serial.command
	open serial.command

build-uno:
	make compile-uno
	make upload-uno

quit:
	screen -S serialmonitor -X kill
