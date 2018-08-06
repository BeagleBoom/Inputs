# About this repository
This repository is part of the [BeagleBoom](https://github.com/beagleboom)-Sampler project developed by the academic working group "[Creative Technologies AG](http://www.creative-technologies.de/)" (ctag) at the [University of Applied Sciences Kiel](https://www.fh-kiel.de/).

For a detailed documentation, have a look at the [Wiki](https://github.com/BeagleBoom/ADCManager/wiki).

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