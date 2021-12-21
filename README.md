# CFS-scheduler


The Linux CFS Scheduler is a non-realtime scheduler, with non-realtime guarantees being given to processes. 
You need to add a soft real-time requirement to a process – say something like each process, that requires soft real-time guarantees must receive atleast x units of time-slice. 
Every time the scheduler is called, you need to check if the real-time guarantees of process with soft- realtime requirements are being met or not. 
You would give higher priority to a processes soft-realtime requirement compared to the vruntime that is normally considered.
You would thus need to modify the scheduler in such a way that when everytime a process is selected through the RB-tree, you you need to compare to all other process with 
soft-realtime requirements and see which one of those require the CPU more urgently than the one selected through the regular RB- tree. 
The one that urgently requires CPU time need to be scheduled before the one selected through CFS. You would additionally require a system call to modify the tasks soft-realtime requirements – say rtnice, 
which takes argument the PID and the realtime guarantees needed. rtnice can have a corresponding user program with the same name which should actually do the system 
call rtnice to perform the said operation with the supplied PID. To test the correct functionality of the modified scheduler, 
you need to run tasks requiring realtime guarantees. You would need to set the guarantees through the rtnice program. 
You would need to show execution time of the process with and without the soft realtime guarantees. This should demonstrate to you if the modified scheduler is functioning or not.
