import httplib
import urllib2
import time
import serial
import json
import datetime

arduino = serial.Serial('/dev/ttyUSB0', baudrate=9600, timeout=1.0)
time.sleep(5)
httplib.HTTPConnection.debuglevel = 1

while True:
	date = datetime.datetime.fromtimestamp(time.time()).strftime('%Y-%m-%d %H:%M:%S')
	try:
		#request = urllib2.Request('https://blockchain.info/es/ticker')
		request = urllib2.Request('http://api.coindesk.com/v1/bpi/currentprice.json')
		opener = urllib2.build_opener()
		data = opener.open(request).read()
		jdata = json.loads(data)
		print(date+": "+jdata["bpi"]["USD"]["rate"])
		arduino.write(str(int(float(jdata["bpi"]["USD"]["rate"].replace(',',''))))+" ")
		#arduino.write(str(int(jdata["USD"]["buy"]))+" ")
		#print(date+": "+str(jdata["USD"]["buy"]))
	except Exception, error:
		arduino.write("10000 ")
		print(date+": "+str(error))
	finally:
		time.sleep(5)
