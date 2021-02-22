# COMP 3430 - Assignment 1 Adedotun Adeyemo 7784807

## Report

## Result

---

| Total processes/threads | Concurrent processes/threads | Threads time (nanoseconds) | Processes time (nanoseconds) |
| :---------------------: | :--------------------------: | :------------------------: | :--------------------------: |
|           100           |              4               |        369579090.4         |         381123424.8          |
|           100           |              8               |         185312009          |         191492170.4          |
|           100           |              32              |          46600654          |          48038007.8          |
|          1000           |              4               |         848747099          |         958057010.4          |
|          1000           |              8               |         914938576          |         971958798.4          |
|          1000           |              32              |         477135432          |         493708639.8          |
|          10000          |              4               |        621026953.8         |         727434261.6          |
|          10000          |              8               |        281223097.6         |         857548637.2          |
|          10000          |              32              |        801217068.4         |         960027509.2          |

### Which is faster: threads or processes?

---

As seen in the table above threads seem to run are faster than processes.

### Does your result match your hypothesis? Why do you think it does, or why do you think it does not?

---

Yes, the results match my hypothesis as threads are faster than processes with every combination of x and y value used. To ensure the results were accurate each combination of the x and y values were run 5 times, and the averages were used for the table. The result should be because the of the time proceesses need to copy the data contained in the parent class, as was mentioned in the Hypothesis.

### Is there a point of diminishing returns on how many concurrent processes/threads are running?
I tried running the code for casses with more processes and threads than those suggested to check for ,ore prooof of diminishingreturns and came across a bug in the timespec diff function. The results seem to break after a certain point and i belive this is a result of the limits of what can be stored in a long.

