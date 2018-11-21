# wolfMqttDemo

1.build
arm-linux-gnueabihf-gcc -o nbclient nbclient.c mqttnet.c mqttexample.c -I./ -I./include ./lib/libwolfmqtt.a ./lib/libwolfssl.a -lm
