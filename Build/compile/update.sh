#/!bin/bash

# rsync -avz -e "ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null" --progress Technician@192.168.0.1:'/run/media/Technician/Work/Work/Newark/TBHS/Episodes/Episode_Files/Episode\ 189\ -\ Raspberry\ Pi\ Compute\ Calculator/Software/Calculator/' /home/pi/Calculator/Software/;
rsync -avz -e "ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null" --progress Technician@192.168.2.3:'/run/media/Technician/Work/Work/Newark/TBHS/Episodes/Episode_Files/Episode\ 189\ -\ Raspberry\ Pi\ Compute\ Calculator/Software/Calculator/' /home/pi/Calculator/Software/;
# rsync -avz -e "ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null" --progress Technician@192.168.1.132:'/run/media/Technician/Work/Work/Newark/TBHS/Episodes/Episode_Files/Episode\ 189\ -\ Raspberry\ Pi\ Compute\ Calculator/Software/Calculator/' /home/pi/Calculator/Software/;


sudo cp /home/pi/Calculator/Software/Build/boot/*.* /boot;
sudo cp /home/pi/Calculator/Software/Build/etc/*.* /etc;
sudo cp /home/pi/Calculator/Software/Build/etc/udev/rules.d/*.* /etc/udev/rules.d;

exec "/home/pi/Calculator/Software/Build/compile/compile.sh";