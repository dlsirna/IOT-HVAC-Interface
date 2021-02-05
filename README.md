# IOT-HVAC-Interface
 Online thermostat controller
 
  This project came from a need for a thermostat capable of complex scheduling, to save money my roomates and I prefer to keep the heat off, however it proved impossible to get out of bed and enter the frigid wasteland that was our house, so i set out to build something to fix our problem.
  I knew it was relatively possible because the nest thermostat exists, and my next thought was "can I do that?", after an amazing learning experience later (HVAC I/O and relays, soldering, learning about NTP, learning about juggling I/O and listeners on a single-core mircro controller(esp 8266)) this what I have come up with.
 
 The application interface is currently protyped using Blynk https://blynk.io/ 
 the blynk library allows for easy use of virtual pins withint he blynk library, as well as a scheduling interface, an RTC module.
 This all culminates to a thermostat scheduler
 
 ![alt text](https://mail.google.com/mail/u/0?ui=2&ik=03b31984a7&attid=0.1&permmsgid=msg-f:1690871685760134751&th=17772ed6ee7fae5f&view=fimg&sz=s0-l75-ft&attbid=ANGjdJ8pis7LAuDX68zWHJ7Ghby36S4v7kV1ZVGqKrxEDZvAtcy7rj3vNH0zht6759JZcVJz_vxXX0Hjvv2UsbFNc76YBg56OQESliKCNm5nMLiYdVmcSkNxnw1iK4c&disp=emb)
 
 
 
 
 //TODO
Houskeeping: (1)refactor the c++ code(very hard to read)  (2)migrate from prototyping platform to a custom android app to learn more about building apps and TCP/IP, networking, interfacing with microcontrollers.
Future features: a money saving feature that turns the heat/ac low when known mobile devices have left the network(no one is home).


