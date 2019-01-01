# Import required libraries
import time, sched, datetime, csv
import RPi.GPIO as GPIO
from multiprocessing import Pool

pool = Pool() #Multithreading

### TODO RECORD MEANINGFUL DATA TODO ###
he_recs = [] #For recodation of data
counter = 0 #Revolution count, used to calculate RPM



def getRevPer():
	### TODO WRITE INTO FILE IN TIME INTERVALS; PREVENT DATA LOSS TODO ###
	while(True):
		### TODO CALCULATE RPM PER SECOND TODO ###
		'''
			To calculate RPM in seconds:
			 -Measure RPM then divide by 60(?)
		'''
		perSec = sched.scheduler(time.time, time.sleep)

		def revPerSec(x): #@x is perSec passed by value
			global counter
			rps = ((counter / 60.0) / 60.0)

			if(counter > 0):
				print("RPS (Rev. per sec.):", rps)
				counter = 0 #Reset rev count
			else:
				print("RPS (Rev. per sec.): 0.0")
				counter = 0 #Reset rev count

			csvfile = open('he_results.csv', 'a')
			#with open('he_results.csv', 'w', newline='') as csvfile:
			with csvfile:
				fieldNames = ['Rev. per sec.', 'Time']
				writer = csv.DictWriter(csvfile, fieldnames = fieldNames)

				writer.writeheader()
				writer.writerow({'Rev. per sec.': str(rps), 'Time':\
				 ### TODO COMPUTE PROPER TIME TODO ###
				 str(datetime.timedelta(time.time() / 52.14 / 24 / 60 / 60))})

			perSec.enter(1, 1, revPerSec, (x, )) #TODO Figure out parameters of `.enter(...)`

		perSec.enter(1, 1, revPerSec, (perSec, ))
		perSec.run()



def sensorCallback(channel):
	global counter
 
	###Measuring magnet's top/bottom
	### TODO RECORD MEANINGFUL DATA TODO ###
	if GPIO.input(channel):
		### Write to file ###
		#print("Sensor HIGH " + stamp)
		#he_recs.append(str(stamp))

		###XXX DEPRECATED XXX
		#he_recs.append(str(counter) + "\t")

		print("Count: ", str(counter)) #Just to keep track of revolution count
		counter += 1



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
	### Async time tracker and rev counter
	pool.apply_async(getRevPer())
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
