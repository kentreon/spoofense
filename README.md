# Spoofense
This is a Lovense compatible platform, which enables users to make thair own attachments.
It is based on thew Arduino Uno, and can be coverted to most models.

# How to build:
Main Station:
  Parts:
    - 1 Arduino (uno in my case)
    - 1 HC-06 Bluetooth module
    - 1 USB plug of choice (must have solderable ends)
    - 2 NPN Transistors (I used TIP142)
    - 2 resistors (somewhere around 10kOhm should be fine. Not too important)
    - (optional): clamps to make modules detchable
    - (optional): Prototyping board to build it better
  Tools:
    - Soldering gear
    - some Wire (colors of choice)
    - PC
    - Arduino programming cable (USB-B for UNO)
  Circuit:
  ![image](https://user-images.githubusercontent.com/111907393/186235231-0e6f28f2-4289-4d49-939d-c6a6ac71a320.png)
  ![image](https://user-images.githubusercontent.com/111907393/186235382-99c658e0-a676-41e8-9cf2-c4ca2df3b379.png)
  Note: The gnd and vcc pin of the HC-06 board get connected respectively to the arduino, while TX gets hooked up to 4 and RX to 7 (May be switched up, but easily fixable in code).
  
  After the bluetooth module, and optionally the rest is installed, the setup code needs to be flashed. Afterwards, you will need to connect to the arduino via the Serial monitor. ![image](https://user-images.githubusercontent.com/111907393/186236168-5d724e68-371a-4312-acc0-0205e7cd7dbf.png)
  Note that you must not be connected to it via bluetooth yet. This is important.
  Now you will need to type "AT" in the command bar, and send it. If the response is "OK", everything is fine. Otherwise check the before steps, or consult google on "AT commands HC06 not working" or so.
  Assuming everything worked, you just paste the following command now: "AT+NAME=LVS-Edge10"; This will make the app think, that our device is a Edge 1 with the 1.0 Firmware. I chose it, because it has 2 control axis instead of one.
  Now you can flash the firmware, and you base station is done! Congratulations!
