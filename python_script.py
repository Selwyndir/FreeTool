#!/usr/bin/env python
# -*- coding: utf-8 -*-
# lsusb to check device name
#dmesg | grep "tty" to find port name

import serial,time
from picamera import PiCamera
from time import sleep
camera = PiCamera()


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
                            fichier=open('state_tools_1.txt','w')#pour un fichier texte, sinon, mettre 'wb' au lieu de "w"
                            fichier.write('Outil Disponible')#on peut maintenant écrire
                            fichier.close()#ne pas oublier pour libérer l'accès.
                            fichier=open('state_d_tools_1.txt','w')#pour un fichier texte, sinon, mettre 'wb' au lieu de "w"
                            fichier.write(" ")
                            fichier.close()#ne pas oublier pour libérer l'accès.
                        id1= identification[:-2]
                        if id1=="1x3":
                            cont1=content[4:]
                            fichier=open('state_d_tools_1.txt','w')#pour un fichier texte, sinon, mettre 'wb' au lieu de "w"
                            fichier.write("Retour de l'Outil dans: ")
                            fichier.write(cont1)#on peut maintenant écrire
                            fichier.write(" jours.")#on peut maintenant écrire
                            fichier.close()#ne pas oublier pour libérer l'accès.
                        id2= identification[:-11]
                        if id2=="1x2":
                            cont2=content[4:]
                            fichier=open('state_tools_1.txt','w')#pour un fichier texte, sinon, mettre 'wb' au lieu de "w"
                            fichier.write("Retour de l'Outil le : ")#on peut maintenant écrire
                            fichier.write(cont2)#on peut maintenant écrire
                            fichier.close()#ne pas oublier pour libérer l'accès.
                        if identification=="0x3":
                            camera.capture(str(datetime.datetime.now())+'intruder'+'.jpg')
                        if identification=="0x4":
                            camera.capture(str(datetime.datetime.now())+'user'+'.jpg')

