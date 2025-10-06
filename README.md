# SYSC 4001-A Assignment 1

Student 1: Maxim Creanga 101298069
Student 2: Braedy Gold Colin 

**NOTE**: Most of the git commits come from my account (Student 1, Maxim) as Braedy was having environment setup issues. However, we both equally collaborted on the assignment in person, using my computer.

There are three trace files, meant to simulate three types of programs being ran:
1. CPU-bound programs, where there are more CPU bursts then I/O operations.
2. IO-bound programs, where there are more I/O device calls then CPU bursts.
3. mixed programs, where we have a balance of the two.


Note that the CPU-bound trace files utilize a SYSCALL X, where X is a value not found in device_table.txt but found in vector_table.txt. This means that that system call is not associated with an I/O device, but rather is a CPU system call, which takes less time then an I/O system call.

The execution files are split up by whichever trace file was used (see the `/` folder: `trace_cpu.txt`, `trace_io.txt`, and `trace_mixed.txt`), and each folder has the following cases:
- Context switch is 10ms, 20ms or 30ms.
- ISR activity time is 40ms, 80ms, 140ms, or 200ms.
