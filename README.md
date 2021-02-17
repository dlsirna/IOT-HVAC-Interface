# IOT-HVAC-Interface
 Online thermostat controller
 

 
 <img src="https://github.com/dlsirna/IOT-HVAC-Interface/blob/main/prototype%20of%20thermostat.png" alt="drawing" width="500" height= "600"/>
  
 The application interface is currently protyped using Blynk https://blynk.io/
 the blynk library allows for easy use of virtual pins withint he blynk library, as well as a scheduling interface, an RTC module.
 This all culminates to a thermostat scheduler.
 
  This interface may look a little funny because I originally designed the system to be complementary to the existing thermostat interface to reduce the need for incorporating a screen into the device, by powering the micro controller and relays through the fan wire, when the original thermostat interface was used to turn on heat or ac the fan line would being cutoff would shut off the micro controller to prohibit any adverse complications in logic (most importantly turning both the ac and heat on at the same time which can strain the power line especially in old houses so I am told), unfortunatly the micro controller was responding in an odd way, upon investigation it turns out that an esp8266 can pull around a max of 400mA of power and my signal lines were operating at 28V AC at about 300mA.
 So at the moment it is powered via usb, further research into electronics is need to figure out if there is a possible work around, to achieve my idea of a complementary mobile iot thermostat that is complementary to an existing system. 
 note: I have heard that nest gets around this low amperage issue by using a battery and periodically charging it up via the fan line, so that may be worth learning about.
 

 
 <img src="https://github.com/dlsirna/IOT-HVAC-Interface/blob/main/Blynk%20interface.png" alt="drawing" width="300" height= "600"/>
 <header>
 Challenge:

 
 
 
 


**hope you enjoyed lokking at this project, there is risk in using a hvac interface especially with small children, some issue may cause the heat to be stuck or any other number of things could happen, YOU SHOULD NOT IMPLEMENT THIS PROJECT. For educational purposes only. Thank you!


