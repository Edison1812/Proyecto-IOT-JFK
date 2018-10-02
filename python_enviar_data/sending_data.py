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
    
    while(1):
    	v= ArduinoSerial.readline() #read the serial data and print it as line
    	v=v.split()
        if running_status:
            values = {"S1": v[0],
            "S2": v[1],
            "S3": round(100*(1-float(v[2])/1023),1),
            "S4": round(100*(1-float(v[3])/1023),1),
            "S5": round(100*(1-float(v[4])/1023),1),
            "S6": 20,
            "rpm": "1.0"}
            success = device_client.publishEvent(
                "sensor",
                "json",
                {"d": values},
                qos=0,
                on_publish=my_on_publish_callback())
            #print data  
            time.sleep(0.33)
            if not success:
                print("Not connected to WatsonIoTP")

if __name__ == "__main__":
    try:
        device_file = "device.conf"
        device_options = ibmiotf.device.ParseConfigFile(device_file)
        device_client = ibmiotf.device.Client(device_options)
        device_client.connect()
        sendIOT()
    except Exception as e:
        print("Caught exception connecting device: %s" % str(e))
        sys.exit()
