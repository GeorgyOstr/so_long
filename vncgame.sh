export DISPLAY=:1
#Xvfb $DISPLAY -screen 0 "1792x1024x24" &
Xvfb $DISPLAY -screen 0 "6792x3024x24" &
sleep 1
./so_long maps/8.ber &
sleep 1
x11vnc -display :1 -nopw -forever &
~/noVNC/utils/novnc_proxy --vnc localhost:5900 --listen 6080
#http://dell:6080/vnc.html?autoconnect=1&resize=scale&quality=9&compression=9
