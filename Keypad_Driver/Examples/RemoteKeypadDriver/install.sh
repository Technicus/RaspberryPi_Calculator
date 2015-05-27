#! /bin/sh

chmod +x RemoteKeypad
chmod +x RemoteKeypadDriver.sh

cp RemoteKeypadDriver.sh /etc/init.d/

update-rc.d RemoteKeypadDriver.sh defaults

