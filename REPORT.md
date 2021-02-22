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

# COMP 3430 - Assignment 1 Adedotun Adeyemo 7784807

## Report

## Result

---

| Total processes/threads | Concurrent processes/threads |    Threads time     |   Processes time    |
| :---------------------: | :--------------------------: | :-----------------: | :-----------------: |
|           100           |              4               | 0s & 369579090.4ns  | 0s & 381123424.8ns  |
|           100           |              8               |  0s & 185312009ns   | 0s & 191492170.4ns  |
|           100           |              32              |   0s & 46600654ns   |   0s 48038007.8ns   |
|          1000           |              4               |  6s & 848747099ns   | 6s & 958057010.4ns  |
|          1000           |              8               |  3s & 914938576ns   | 3s & 971958798.4ns  |
|          1000           |              32              |  1s & 477135432ns   | 1s & 493708639.8ns  |
|          10000          |              4               | 69s & 621026953.8ns | 69s & 727434261.6ns |
|          10000          |              8               | 35s & 281223097.6ns | 35s & 357548637.2ns |
|          10000          |              32              | 8s & 801217068.4ns  | 8s & 960027509.2ns  |

### Which is faster: threads or processes?

---

As seen in the table above threads run are faster than processes.

### Does your result match your hypothesis? Why do you think it does, or why do you think it does not?

---

Yes, the results match my hypothesis as threads are faster than processes with every combination of x and y value used. To ensure the results were accurate each combination of the x and y values were run 5 times, and the averages were used for the table. The result should be because of the time processes need to copy the data contained in the parent class, as was mentioned in the Hypothesis.

### Is there a point of diminishing returns on how many concurrent processes/threads are running?

---

There seem to be diminishing returns when there is a smaller amount of concurrent processes/threads are running concurrently.
