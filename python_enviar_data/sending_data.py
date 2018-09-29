# *****************************************************************************
# Copyright (c) 2018 Jose Avalos
# *****************************************************************************
#!/usr/bin/env python

import time
import sys
import uuid
import threading
import time
import signal
import os
import random
import ibmiotf.device
import math
import serial

running_status = True

def my_on_publish_callback():
    print("Confirmed received by WatsonIoTP")

def sendIOT():
    ArduinoSerial = serial.Serial('com3',9600) #Create Serial port object called arduinoSerialData  
    value= ArduinoSerial.readline() #read the serial data and print it as line
    while:
        if running_status:
            values = {'Temp': value[0],
                    'Presion': value[1],
                    'A0': value[2],
                    'A1': value[3],
                    'A2': value[4]}
            success = device_client.publishEvent(
                "sensor",
                "json",
                {'j': values},
                qos=0,
                on_publish=my_on_publish_callback())
            #print data  
            time.sleep(0.1)
            if not success:
                print("Not connected to WatsonIoTP")

    

if __name__ == "__main__":
    try:
        device_file = "device.conf"
        device_options = ibmiotf.device.ParseConfigFile(device_file)
        device_client = ibmiotf.device.Client(device_options)
        device_client.connect()
        rospy.init_node('listener', anonymous=True)
        sendIOT()
    except Exception as e:
        print("Caught exception connecting device: %s" % str(e))
        sys.exit()
