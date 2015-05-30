Userspace Input Device - uinput
----------------------

T. Egbert endeavoured to create a user-space mouse input device and
posted some source code:
http://www.mail-archive.com/linux-usb-devel@lists.sourceforge.net/msg20432.html
He describes difficulties with the code "not working" but does not follow
up with a post indicating whether he was successful or not.

Following chmodding of permissions on /dev/input/uinput to allow
non-root users to open the uinput device, examination of /dev/input/*
contents and examination of /var/log/syslog shows that T. Egbert's
original code _is_ actually successfully creating an input device.

After examining the userspace input source code for the wiimote (wminput)
I was able to make corrections which resulted in the code working as expected,
i.e. actually making the mouse move.  Bizarrely, the missing initialisation
ioctl was actually the _keyboard_ ioctl:
    ioctl(fd,UI_SET_EVBIT,EV_KEY)

Prior to that, although the user-space device appeared as /dev/input/inputNN
and could be read from, indicating that mouse-events were successful,
the device was not picked up as an additional mouse device by the rest of the
linux infrastructure until it was also told to look like a keyboard as well.
If asked to hazard a guess as to why this would be the case, interaction
with udev would seem like the reasonable place to investigate.

The EV_SYN events are _not_ required for the sole purpose of successfully
sending key or mouse events, but are added for completeness and for the
sheer hell of it, following the advice outlined in the above archived
message.

