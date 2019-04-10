# Operating-System-Project
College Project involving Shortest Job First along with Priority Based Scheduling.

######OS PROJECT######

5. Consider a scheduling approach which is non pre-emptive similar to shortest job next in 
nature. The priority of each job is dependent on its estimated run time, and also the amount 
of time it has spent waiting. Jobs gain higher priority the longer they wait, which prevents 
indefinite postponement. The jobs that have spent a long time waiting compete against 
those estimated to have short run times. The priority can be computed as :
Priority = 1+ Waiting time / Estimated run time
Using the data given below compute the waiting time and turnaround time for each process 
and average waiting time and average turnaround time.

Process   Arrival_time  Burst_time
  P1        0              20
  P2        5              36
  P3        13             19
  P4        17             42
