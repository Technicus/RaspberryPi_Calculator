RemoteKeypad
============
Linux driver for a Microsoft XBox ChatPad, Sony PSP Joystick or a keypad of switches connected to the GPIO pins, of a Raspberry Pi computer. The driver is configurable to allow each switch to be assigned a function. Functions can be text macros, key-presses, character selection, horizontal and vertical scrolling, pointer movement, mouse clicks and other operations. LED indicators can be used to display the currently selected keypad mode.

The driver has been tested with termianl mode, LXDE on Raspbian and Window Maker on Arch Linux. It simulates keyboard and mouse operations and is intended to be configured and used with various applications running under the Linux Kernel.

The configuration file can be modified while the driver is in use, and the driver will automatically read the configuration file if it is altered.


The following files are distributed in the package:

README.txt            - Information about the package.
License.txt           - User license agreement.
License.dat           - License file.
RemoteKeypad          - Linux driver application.
RemoteKeypad.ini      - Driver configuration file.
install.sh            - Install script.
uninstall.sh          - Uninstall script.
RemoteKeypadDriver.sh - Driver start-up script.


Install
=======
Copy the driver software to the Raspberry Pi from a remote computer, or download the driver directly onto the Raspberry Pi from a web browser:
scp RemoteKeypadDriver.tar.gz root@[IP_ADDRESS]:/root/

Login to the Raspberry Pi, either locally or remotely:
ssh root@[IP_ADDRESS]

Unpack the driver:
gunzip RemoteKeypadDriver.tar.gz
tar -xf RemoteKeypadDriver.tar

Run the install script:
cd /root/RemoteKeypadDriver/
chmod +x install.sh
./install.sh

Reboot the Raspberry Pi to activate the driver:
reboot


Uninstall
=========
Run the uninstall script:
cd /root/RemoteKeypadDriver/
chmod +x uninstall.sh
./uninstall.sh

