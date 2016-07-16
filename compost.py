import boto.sns
import os
import sys
import mraa
import time
from pprint import pprint

if __name__ == "__main__":

    try:

        x = mraa.Aio(0)

        compostmsg = 'Compost Bucket at Location #1 is Ready for Pickup'

        conn = boto.sns.connect_to_region('us-west-2')

        while 1:

            tmp = float(x.read())

            if tmp <= 200:
                try:
                    pprint(compostmsg)
                    pub = conn.publish(topic=os.environ['TOPIC'], message=compostmsg)
                    time.sleep(30)
                except:
                    print("Unexpected error:", sys.exc_info()[0])

    except:
        pass
