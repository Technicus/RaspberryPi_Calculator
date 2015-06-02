#/!bin/bash

#rsync -avz -e "ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null" --progress Technician@10.42.0.1:'/run/media/Technician/Work/Work/Newark/TBHS/Episodes/Episode_Files/Episode\ 189\ -\ Raspberry\ Pi\ Compute\ Calculator/Software/Calculator/Keypad_Driver/' /home/pi/Calculator/Software/Keypad_Driver/;
rsync -avz -e "ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null" --progress Technician@192.168.2.3:'/run/media/Technician/Work/Work/Newark/TBHS/Episodes/Episode_Files/Episode\ 189\ -\ Raspberry\ Pi\ Compute\ Calculator/Software/Calculator/Keypad_Driver/' /home/pi/Calculator/Software/Keypad_Driver/;
#rsync -avz -e "ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null" --progress Technician@192.168.1.132:'/run/media/Technician/Work/Work/Newark/TBHS/Episodes/Episode_Files/Episode\ 189\ -\ Raspberry\ Pi\ Compute\ Calculator/Software/Calculator/Keypad_Driver/' /home/pi/Calculator/Software/Keypad_Driver/;

sudo cp /home/pi/Calculator/Software/Keypad_Driver/Build/boot/*.* /boot;
sudo cp /home/pi/Calculator/Software/Keypad_Driver/Build/etc/*.* /etc;
sudo cp /home/pi/Calculator/Software/Keypad_Driver/Build/etc/udev/rules.d/*.* /etc/udev/rules.d;

#g++ -Wall -o /home/pi/Calculator/Software/Keypad_Driver/Build/bin/Keypad_Driver /home/pi/Calculator/Software/Keypad_Driver/Build/source/Keypad_Driver.cpp -lwiringPi;
#g++ -Wall -o /home/pi/Calculator/Software/Keypad_Driver/Build/bin/Keypad_Driver /home/pi/Calculator/Software/Keypad_Driver/Build/source/Keypad_Driver_V01.cpp -lwiringPi;
#g++ -Wall -o /home/pi/Calculator/Software/Keypad_Driver/Build/bin/Keypad_Driver /home/pi/Calculator/Software/Keypad_Driver/Build/source/Keypad_Driver_V02.cpp -lwiringPi;
g++ -Wall -o /home/pi/Calculator/Software/Keypad_Driver/Build/bin/Keypad_Driver /home/pi/Calculator/Software/Keypad_Driver/Build/source/Keypad_Driver_V04.cpp -lwiringPi;

sudo kill `pgrep Keypad_Driver`;

sudo cp /home/pi/Calculator/Software/Keypad_Driver/Build/bin/Keypad_Driver /usr/local/bin/Keypad_Driver;

sudo /usr/local/bin/Keypad_Driver &
# 
# profile="Technician";
# passphrase="";
# ip_address="10.24.0.1";
# 
# # Keyboard source
# source_directory_1="/run/media/Technician/Work/Work/Newark/TBHS/Episodes/Episode_Files/Episode\ 189\ -\ Raspberry\ Pi\ Compute\ Calculator/Software/Calculator/Keypad_Driver/Build";
# source_file_1="Keypad_Driver.cpp";
# destination_directory_1="";
# destination_file_1="Keypad_Driver.cpp";
# build_file="/usr/local/bin/Keypad_Driver";
# 
# # Kernel Driver
# kernel_Keypad_Driver_file="/usr/local/bin/Keypad_Driver";
# 
# # Startup script
# source_directory_2="";
# source_file_2="rc.local";
# destination_directory_2="";
# destination_file_2="rc.local";
# 
# # Compile script
# source_directory_3="";
# source_file_3="compile.sh";
# destination_directory_3="";
# destination_file_3="compile.sh";
# 
# sftp Technician@10.42.0.1:"/run/media/Technician/Work/Work/Newark/TBHS/Episodes/Episode_Files/Episode\ 189\ -\ Raspberry\ Pi\ Compute\ Calculator/Software/Calculator/Keypad_Driver/Build/"simple_keypad_v03.cpp simple_keypad_v03.cpp;
# sftp Technician@10.42.0.1:"/run/media/Technician/Work/Work/Newark/TBHS/Episodes/Episode_Files/Episode\ 189\ -\ Raspberry\ Pi\ Compute\ Calculator/Software/Calculator/Keypad_Driver/Build/"compile_v01.sh compile_v01.sh;
# sftp Technician@10.42.0.1:"/run/media/Technician/Work/Work/Newark/TBHS/Episodes/Episode_Files/Episode\ 189\ -\ Raspberry\ Pi\ Compute\ Calculator/Software/Calculator/Keypad_Driver/Build/"auto_run.sh "/home/pi/Calculator/Utilities/Scripts/AutoRun/"auto_run.sh;
# 
# #sftp $profile@$ip_address:${source_directory_1}/$source_file_1 $destination_file_1;
# #sftp $profile@$ip_address:"$source_directory_1/$source_file_2" "$destination_file_2";
# #sftp $profile@$ip_address:"$source_directory_1/$source_file_3" "$destination_file_3";
# 
# g++ -Wall -o $build_file $source_file_1 -lwiringPi;
# 
# sudo kill `pgrep kernel_Keypad`
# 
# #cp $build_file $kernel_Keypad_Driver_file
# sudo cp $build_file $kernel_Keypad_Driver_file
# 
# sudo ./$build_file;

