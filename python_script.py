#!/usr/bin/env python
# -*- coding: utf-8 -*-
# lsusb to check device name
#dmesg | grep "tty" to find port name

import mysql.connector
import sys
import serial,time
from picamera import PiCamera
from time import sleep
camera = PiCamera()
conn = mysql.connector.connect(host="IP", 
                                  user="root", password="", 
                                  database="freetool")
cursor = conn.cursor()

if __name__ == '__main__':
        with serial.Serial("/dev/ttyACM0", 9600, timeout=1) as arduino:
        time.sleep(0.1) #wait for serial to open
        if arduino.isOpen():
            print("{} connected!".format(arduino.port))
            try:
                while True:
                    time.sleep(0.1) #wait for arduino to answer
                    while arduino.inWaiting()==0: pass
                    if  arduino.inWaiting()>0: 
                        answer=arduino.readline()
                        fichier = open("data.txt", "a")
                        fichier.write(answer)
                        fichier.write(" ")
                        fichier.close()
                        identification= answer
                        content=answer
                        if identification == "1x1":
                            cursor.execute("""UPDATE tools SET Tool="Outil Disponible" WHERE id=1""")
                        id1= identification[:-2]
                        if id1=="1x3":
                            cont1=content[4:]
                            reference = ("Retour de l'Outil dans: ", cont1, " jours.")
                            cursor.execute("""UPDATE tools SET Tool=%s, %s, %s WHERE id=1""", reference)
                        id2= identification[:-11]
                        if id2=="1x2":
                            cont2=content[4:]
                            reference = ("Retour de l'Outil le : ", cont2)
                            cursor.execute("""UPDATE tools SET Tool=%s, %s WHERE id=1""", reference)
                        if identification=="0x3":
                            camera.capture(str(datetime.datetime.now())+'intruder'+'.jpg')
                        if identification=="0x4":
                            camera.capture(str(datetime.datetime.now())+'user'+'.jpg')