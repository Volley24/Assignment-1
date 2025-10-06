Save/Restore Context Time 
[10ms, 20ms, 30ms]
=> More Overhead %,
=> More impactful for trace_io then trace_cpu

ISR activity time
[40ms - 200ms]
[40ms, 80ms, 200ms]

 - What this mean...?
 - I/O processing time...?
 - Wouldn't this literally be changing 'Y' in SYSCALL, Y, such that the ms is diff each time


How does the difference in speed of these steps affect the overall execution time of the process?
- Not sure what to write here... I guess I can can say for increase save/restore time it will impact I/O bound trace more since there's more SYS CALLS...


Ask yourselves other interesting questions and try to answer them through simulations.
For instance: what happens if we have addresses of 4 bytes instead of 2? What if we have a faster CPU
- Not sure.


---

10, 20, 30 (save_context)

40, 80, 200 (isr_activity)


3x3 = 9 diff things

9 x 3 = 27 simulations accross CPU and IO / Bound

