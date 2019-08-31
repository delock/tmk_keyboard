sleep 4
sudo avrdude -patmega32u4 -cavr109 -b57600 -Uflash:w:$1 -P/dev/ttyACM0

