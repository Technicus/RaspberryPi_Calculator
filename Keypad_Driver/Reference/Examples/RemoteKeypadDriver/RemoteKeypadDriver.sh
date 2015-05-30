#! /bin/sh

case "$1" in
   start)
      cd /root/RemoteKeypadDriver
      ./RemoteKeypad &
      ;;
   stop)
      cd /root/RemoteKeypadDriver
      rm running.dat
      ;;
   *)
      exit 1
      ;;
esac

exit 0

