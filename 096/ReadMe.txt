READ ME

These three folders contain iterations (failed) of attempts to deal with issue of the Arduino resetting every time a pin interrupt (hall sensor) was triggered. It didn't seem to be a power-sag issue because the resetting issue didn't happen when I ran a simpler 1-file sketch with the same interrupts/sensors.

190607_Game_Engine_Template_MessedUp190607_Game_Engine_Template_not compiling190607_Game_Engine_Template_resetting on interrupt


After a bit go googling I found someone who had a similar issue and suggested the cause was related to passing a class member function to the attachPCINT() function, but the program not necessarily knowing which instance of the class the member function belonged to. Strange, because my program was compiling and running. Anyway, I tried to solve this issue and eventually found an idea by dpursell (https://community.particle.io/t/cpp-attachinterrupt-to-class-function-help-solved/5147) that worked (with a little tweaking and debugging! 
In the following version I finally got the pinInterrupts working (and not causing reset of Arduino). Now to troubleshoot next problem. :)

190607_Game_Engine_Template


One good thing is, I've learned more about the -> operator, and been reminded about scope issues.