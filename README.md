# ledpru

WS2812 PRU driver, tested on Beaglebone Black kernel 4.19

Since Beaglebone moved away from the PRU uio / kernel overlays, libraries
like LEDscape no longer work.

This library is a minimal working example tested on a PRU rproc kernel (4.19).


## Installing

Disable HDMI and reboot
```
sed -i 's/#disable_uboot_overlay_video=1/disable_uboot_overlay_video=1/' /boot/uEnv.txt
reboot
```

Build and install the PRU driver
```
cd pru && make && sudo make install
```
This copies our ledpru-fw to /lib/firmware.


Configure our pin to be a PRU output:
```
config-pin P9_31 pruout
```


Start the PRU driver:
```
sudo make config    # Tells the kernel about our new firmware
sudo make run       # just sends "start" to the rproc and starts our PRU program
```

Plug in the LED strip you want to P9\_31 header pin on the Beaglebone.



Build the ledpru userspace driver library
```
cd ../
make
```

Maybe run a test pattern if ya want
```
make test
sudo ./test
```

Happy hacking!

TODO: support multiple channels. Should be able to get ~16 or so from each PRU. Probably
use https://github.com/fyhertz/epilepsia if you want to get serious though. This is just a
quick and dirty hack to get a single strand working.
