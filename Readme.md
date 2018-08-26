# ![alt text](docs/inputs_logo.png "BeagleBoom Inputs")

# About this repository
This repository is part of the [BeagleBoom](https://github.com/beagleboom)-Sampler project developed by the academic working group "[Creative Technologies AG](http://www.creative-technologies.de/)" (ctag) at the [University of Applied Sciences Kiel](https://www.fh-kiel.de/).

# What is it used for?
The tool `IOSetup` sets up the GPIO-Pins needed for the Buttons and Rotary encoders used by the [BeagleBoom Snouts](https://github.com/BeagleBoom/Snouts).
`IOManager` watches the Buttons and Rotary Encoders and promotes the changes via the [BeagleQueue](https://github.com/BeagleBoom/BeagleQueue)-Lib.

# Prerequirements
- You need a version of cmake >= 3.5.2
- This project needs an compiled and installed version of the [BeagleQueue](https://github.com/BeagleBoom/BeagleQueue)-Lib
  - Thus you need an installed version of PocoLib which includes the JSON namespace.
- Another Prerequirement is a working overlay. You can see a detailed installation description [here](https://github.com/BeagleBoom/ADCManager/wiki/Overlays).

# Installation
If all requirements are met, just run
```
cmake .
make
```
Now you can find the binary files in the `bin/`-directory.

# How to run BeagleBoom Inputs
## How to run the IOSetup
To configure and initialize the GPIO pins, just run
```
cd bin
./IOSetup
```

## How to run the IOHandler
To run the IOHandler you need to pass the MessageQueue Recipient/"Channel Number" as parameter to the IOHandler. 
This is usually the channel of the BeagleBoom menu, which we define, when we start the [BeagleBoom Menu](https://github.com/BeagleBoom/Menu)

```
cd bin
./IOHandler 2
```


# Functionality
## GPIO Access
BeagleBoom Inputs accesses the GPIOs via the /sys/class/gpio/ device path.
To initialize and configure all these Inputs, you can use the IOSetup program.
This program exports all needed GPIO pins and sets their direction as "input".

Therefore it uses the io.json (/configs/io.json) and pins.json (configs/pins.json) files:

### pins.json
The pins.json file contains a collection of all Pinouts of the BeagleBone and it's internal Linux GPIO number, sorted by port.
This conduces as a mapping between the Port/Pin number and the Linux GPIO number.

Here's an excerpt of the pins.json file: 
``` json
{
  "port_8": {
    "pin_3": 38,
    "pin_4": 39,
    "pin_5": 34,
    "pin_6": 35,
    "pin_7": 66,
    "pin_8": 67,
    "pin_9": 69,
    ...
  },
  "port_9": {
    "pin_11": 30,
    "pin_12": 60,
    "pin_13": 31,
    "pin_14": 50,
    "pin_15": 48,
    "pin_16": 51,
    ...
  }
}
```

### io.json
The io.json file contains the assignment of all buttons and rotary encoder to the correct port/PIN. 
For each entry in the file, the corresponding Port/PIN will be parsed, exported and configured on the system.

Here is an excerpt of the io.json file: 
``` json
{
  "Buttons": [
    {
      "name": "BACK",
      "pin": 24,
      "header": 8
    },
    {
      "name": "A",
      "pin": 26,
      "header": 8
    },
    ...
  ],
  "RotaryEncoders": [
    {
      "name": "Z2",
      "state": {
        "header": 8,
        "pin": 18
      },
      "direction": {
        "header": 8,
        "pin": 22
      }
    },
    {
      "name": "R1",
      "state": {
        "header": 8,
        "pin": 5
      },
      "direction": {
        "header": 8,
        "pin": 7
      }
    },
    ...
  ]
}
```
The names of each defined input are sent as an indentifier in our event messages.

Every Rotary Encoder on the BeagleBoom PCB has two functionalites:
Rotation (left and right) and button press.
We do not distinguish between a button has been pressed or a rotary encoder has been pressed. Both are defined as a button.
To determine a rotation, the physical rotary Encoder gives two signals to the BeagleBone, the first signal shows whether it has been rotated (state_pin == HIGH) and the second signal indicates which direction was rotated (left or right). These two signal pins are defined in the JSON file as state and direction.


## GPIO Polling
The IOHandler is the main program, which generates the input Events, that are send over the [BeagleQueue](https://github.com/BeagleBoom/BeagleQueue).

To monitor all inputs, we use a polling mechanism, that checks every 10ms
all of our GPIO pins. Because we already have the buttons and rotary encoders defined in our io.json file, the program knows which pin belongs to which input and and can generate the respective events.

## Message Queue Events
For sending our events, we distinguish between four different types:

| EventType    	| Description                            	|
|--------------	|----------------------------------------	|
| BUTTON_UP    	| A Button has been pressed/was released 	|
| BUTTON_DOWN  	| A Button has been pressed down         	|
| ROTARY_LEFT  	| A Rotary Encoder was rotated to left   	|
| ROTARY_RIGHT 	| A Rotary Encoder was rotated to right  	|

On every event, the payload contains the device name as a string, like "BACK" for the back button. The device name is stored in the io.json file

Click [here for more information on the BeagleQueue](https://github.com/BeagleBoom/BeagleQueue).


# Kudos
- This project includes a modified version of @VegetableAvenger's [BBBIOlib](https://github.com/VegetableAvenger/BBBIOlib).

# License
The content and source code of this project itself is licensed under the [Creative Commons Attribution 4.0 International license](https://creativecommons.org/licenses/by/4.0/).