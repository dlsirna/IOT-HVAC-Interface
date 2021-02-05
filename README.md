# IOT-HVAC-Interface
 Online thermostat controller
 
  This project came from a need for a thermostat capable of complex scheduling, to save money my roomates and I prefer to keep the heat off, however it proved impossible to get out of bed and enter the frigid wasteland that was our house, so i set out to build something to fix our problem.
  I knew it was relatively possible because the nest thermostat exists, and my next thought was "can I do that?", after an amazing learning experience later (HVAC I/O and relays, soldering, learning about NTP, learning about juggling I/O and listeners on a single-core mircro controller(esp 8266)) this what I have come up with.
 
 <img src="https://github.com/dlsirna/IOT-HVAC-Interface/blob/main/prototype%20of%20thermostat.png" alt="drawing" width="500" height= "600"/>
  
 The application interface is currently protyped using Blynk https://blynk.io/) 
 the blynk library allows for easy use of virtual pins withint he blynk library, as well as a scheduling interface, an RTC module.
 This all culminates to a thermostat scheduler
 

 
 <img src="https://github.com/dlsirna/IOT-HVAC-Interface/blob/main/Blynk%20interface.png" alt="drawing" width="300" height= "600"/>
 <header>
 Challenge:
 This interface may look a little funny because I originally designed the system to be complementary to the existing thermostat interface to reduce the need for incorporating a screen into the device, by powering the micro controller and relays through the fan wire, when the original thermostat interface was used to turn on heat or ac the fan line would being cutoff would shut off the micro controller to prohibit any adverse complications in logic (most importantly turning both the ac and heat on at the same time which can strain the power line especially in old houses so I am told), unfortunatly the micro controller was responding in an odd way, upon investigation it turns out that an esp8266 can pull around a max of 400mA of power and my signal lines were operating at 28V AC at about 300mA.
 So at the moment it is powered via usb, further research into electronics is need to figure out if there is a possible work around, to achieve my idea of a complementary mobile iot thermostat that is complementary to an existing system.
 
 
 
 
 //TODO
Houskeeping: (1)refactor the c++ code(very hard to read)  (2)migrate from prototyping platform to a custom android app to learn more about building apps and TCP/IP, networking, interfacing with microcontrollers.
Future features: a money saving feature that turns the heat/ac low when known mobile devices have left the network(no one is home).


