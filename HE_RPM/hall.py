# Import required libraries
import time
import datetime
import RPi.GPIO as GPIO
from multiprocessing import Pool
#import threading

pool = Pool() #Multithreading

he_recs = [] #For recodation of data
counter = 0 #Revolution count, used to calculate RPM
startTime = time.time() #Record start time, used to calculate RPM
trigger = True #Keep track of multiple zero values



def getTime():
	while(True):
		global counter
		global startTime
		global trigger
	
		endTime = time.time()

		#print("startTime:", startTime, "\tendTime:", endTime,\
		# "\tMin?", int(((endTime - startTime) % 60)))

		if((int((endTime - startTime) % 60) == 0) & trigger):
			trigger = False
			print("A minute has passed.")
			print("RPM:", (counter / 60.0))
			startTime = endTime
			counter = 0

		elif(int((endTime - startTime) % 60) & (not trigger)): #Reset zero value trigger
			trigger = True
	
		#if((counter > 0) & (((endTime - startTime) % 60.0) == 0)):
		#	rpm = (counter /  60.0) #Divide by 60 for sec
		#	startTime = endTime
		#	print("RPM:", str(rpm))
		#	counter = 0 #Reset revolution count
		#else:
		#	print("RPM:", str(0))



def sensorCallback(channel):
	global counter

	###Called if sensor output changes
	###XXX POSSIBLY DEPRECATED XXX
	#timestamp = time.time()
	#stamp = datetime.datetime.fromtimestamp(timestamp)\
	# .strftime('%H:%M:%S')

 
	###Measuring magnet's top/bottom
	if GPIO.input(channel):
		### Write to file ###
		#print("Sensor HIGH " + stamp)
		#he_recs.append(str(stamp))

		print("Count: ", str(counter))
		###XXX DEPRECATED XXX
		#he_recs.append(str(counter) + "\t")
		counter += 1

	###Measuring magnet's sides
	else:
		### Write to file ###
		#print("Sensor LOW " + stamp)
		#he_recs.append(str(stamp))

		print("Not counted, count is still: ", str(counter))
		###XXX DEPRECATED XXX
		#he_recs.append(str(counter) + "\t")

	#print("sensorCallback(channel) is running asynchronously.")


def record():
	###Get initial reading from GPIO 17
	sensorCallback(17)

	###File name
	f_name = "he_results.csv"
	test_file = open(f_name, "w")
	
	try:
		###Loop until users quits with CTRL-C
		while(True):
			time.sleep(0.0)
	
	except KeyboardInterrupt:
		print("Interrupt from keyboard")
		test_file.write(str(he_recs) + "\t")
		test_file.close()

		###Reset GPIO settings
		GPIO.cleanup()



def main():
	#global time
	#time = time.time()

	###XXX Possibly deprecated XXX
	#res1 = pool.apply_async(getTime())
	#res2 = pool.apply_async(record())
	#ans1 = res1.get(timeout=10)
	#ans2 = res2.get(timeout=10)
	#print("ans1:", str(ans1), "\nans2:", str(ans2))

	###XXX OG XXX
	#record()

	###XXX TEST XXX
	pool.apply_async(getTime())
	pool.apply_async(record())



#Tell GPIO library to use GPIO references
GPIO.setmode(GPIO.BCM)

print("Setup GPIO pin as input on GPIO17")

#Set Switch GPIO as input
#Pull high by default
GPIO.setup(17 , GPIO.IN, pull_up_down=GPIO.PUD_UP)
GPIO.add_event_detect(17, GPIO.BOTH, callback=sensorCallback, bouncetime=200)



### TODO Use data recorded and convert to RPM ###
if __name__=="__main__":
	main()
