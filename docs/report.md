
For this project, we chose to divide the work among team members and proceed individually after holding an initial meeting to assign tasks. We successfully met all project specifications. Since the project was developed in parallel, we organized our work into three main fronts, each focusing on different sets of specifications. Below is a summary of the approach, challenges, and results for each front.

Front 1: 6 and 3

Specification 6:
	The tricky part was implementing built-in commands in a way that affected the shell itself, not just child processes, other than that it was pretty straight forward.

Specification 3:
The main challenge was ensuring correct background execution while maintaining proper job control. I had to make sure the shell stayed responsive while background tasks were running, and signals such as Ctrl + C only affected the intended processes.

Do you have any feedback for improving the lab materials? 
No, the instructions were clear.

Did you find the automated tests useful? 
I tested manually.

Do you feel that there is any test case missing? 
No, the coverage seemed sufficient.

Front 2: 2 and 4

Specification 2:
 I had challenges understanding the concept of fork and execute and what kinds of resources I had to keep track of when creating child processes. I overcame this by learning more about the Operating system's process model to understand how to properly manage child processes.

Specification 4:
 When trying to implement piping I had an issue with a race condition regarding the group process ID. Since I was setting the PGID in the child, it meant that the order of execution of the children was arbitrary. This messed up who was the leader of the process group which in turn caused the processes to be assigned to the wrong groups. I solved this by instead managing the process grouping in the parent process. 

Do you have any feedback for improving the lab materials? 
No.

Did you find the automated tests useful? 
Yes, they helped provide an idea on how to test the shell .

Do you feel that there is any test case missing? 
No.

Front 3: 1, 7, 8 and 4

Specification 1:
No challenges, just had to handle the case where we get the input NULL.

Specification 7 & 8:
This was a little difficult since i have not worked with interrupts on an OS before, only on bare metal, so it took some googling to find how to set custom interrupt handlers, other than that both 7 and 8 just use flags/interrupts in a similar fashion to kill/remove a process.

Specification 4:
The most difficult thing here was that before I could start working I had to understand the other people's code, but it wasn't too bad, they had a very readable solution to the problems. Other than that it was just some pretty standard file descriptor.

Do you have any feedback for improving the lab materials?
No, it was pretty easy to follow along.

Did you find the automated tests useful?
I personally never ran any of the automated tests because i didn't bother setting it up, so I just tested manually.

Do you feel that there is any test case missing?
Couldn't say.
