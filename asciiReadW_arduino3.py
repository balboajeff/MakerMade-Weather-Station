import requests
import json
import serial
import struct
import time
import random
from gpiozero import LED

# Set up the parameters we want to pass to the API.
# This is the latitude and longitude of Estes Park, CO.

ser=serial.Serial("/dev/ttyUSB0",9600) #change ACM number as found from 
#ls /dev/tty/ACM*
ser.baudrate=9600
    
while True:
# Make a get request with the parameters.
    response = requests.get("https://api.darksky.net/forecast/9d538331b3dd68f860627b9ad1976a89/40.377000,-105.521000")
    data = response.json()
    littleBit = data["currently"]
    print(littleBit["temperature"])
    print(littleBit["humidity"])
    print(littleBit["pressure"])
   #red value
    redVal = int(littleBit["temperature"]) #/250
    prtVal = str(redVal)
    #prtVal = str(random.randint(1,200))
    tempVal = str.encode(prtVal)

     #green value
    greenVal = int(littleBit["pressure"])
    grnInt = int((greenVal)/6)
    pressVal = str(grnInt)
    #humVal = str(random.randint(1,200))
    prtPress = str.encode(pressVal)

    #blue value
    blueVal = (littleBit["humidity"])
    blueInt = int(blueVal*100)
    print(type(blueVal))
    print(type(blueInt))
    print(blueInt)
    humVal = str(blueInt)
##    humVal = str(random.randint(35,85))
    prtHum = str.encode(humVal)

    ##### console print to confirm values
    print("RED=" + prtVal)
    print("GREEN=" + pressVal)
    print("BLUE=" + humVal)
    
    #charactor formatting
    comma = str.encode(',')
    newline = str.encode('\n')
    #serial output constructor
    ser.write(tempVal)
    ser.write(comma)
    ser.write(prtPress)
    ser.write(comma)
    ser.write(prtHum)
    ser.write(newline)
  
    time.sleep(60)
    
   

           
    
##    print(counterByte)
##    time.sleep(5)

