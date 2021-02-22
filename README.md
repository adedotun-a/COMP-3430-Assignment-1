# COMP 3430 - Assignment 1 Adedotun Adeyemo 7784807

## Readme

### How to compile

---

cd to the directory of the submission and run the command "make"

### How to run

---

Use the command "./assignment1 x y"
where x is the total number of threads/processes and y is the number of conccurrent threads/processes

alternatively if the x and y values are missing the user is prompted to input them.

### Hypothesis

---

Threads should run faster than processes as a process has to copy the data from the parent process and this would take some resources and memory to acomplish. While on the other hand a threadonly needs the function it needs to run.

### Design Choices

---

The code is designed to run the first batch of y processes or threads first, then it will check if one of those threads of the current batch are complete so another processes or thread can be added to that batch.
For the threads a list of the currently running threads is kept, then it creates the first batch of y threads. It then loops till the total number of threads have been made while waiting for a thread from the current batch to finish to create a thread to take its place.

For the processes the code creates its first batch of y processes. It then loops till the total number of processes have been made while waiting for a thread from the current batch to finish to create a processes to take its place.
