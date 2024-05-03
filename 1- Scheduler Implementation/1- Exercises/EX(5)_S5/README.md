- In the previous example, we used Printf to identify the schedualer behavoiur.

- This time will implement GpioToggle function in each task will pulling delay.

Using the logic analyser:

<img src="Logic 2 [Logic - Connected] [Session 0] 5_3_2024 6_15_21 PM.png" alt="debug configurations" width="1920" height="1051">\


we noticed that the time is multiplied by 4 which is the tasks number.

So in scheduler we should not use blocking delay (busy waiting). 

We can use timer instead

or another option is to check if the task in is blocking state so do not run it.