import json
import sys
import serial
import time
import boto.sns
import os

from pprint import pprint
import serial.tools.list_ports

def serial_ports():
    result = ''
    for port in list(serial.tools.list_ports.comports()):
        try:
            s = serial.Serial(port.device, baudrate=9600, timeout=2)
            test = s.read(1)
            if test != '':
                s.close()
                result = port.device
                return result
        except (OSError, serial.SerialException):
            pass
    return result


if __name__ == "__main__":

    compostmsg = 'Compost Bucket at Location #1 is Ready for Pickup'

    ttyusb = serial_ports()
    ser = serial.Serial(ttyusb, 9600, timeout=2)
    conn = boto.sns.connect_to_region('us-west-2')

    while 1:

        tmp = ser.readline()[:-2]

        if tmp == '1':
            try:
                pprint(compostmsg)
                pub = conn.publish(topic=os.environ['TOPIC'], message=compostmsg)
                time.sleep(1)
            except:
                print("Unexpected error:", sys.exc_info()[0])
