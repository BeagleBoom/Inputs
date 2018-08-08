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

# Kudos
- This project includes a modified version of @VegetableAvenger's [BBBIOlib](https://github.com/VegetableAvenger/BBBIOlib).