/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 *
 */
#include <interrupts.hpp>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    //vectors is a C++ std::vector of strings that contain the address of the ISR
    //delays  is a C++ std::vector of ints that contain the delays of each device
    //the index of these elemens is the device number, starting from 0
    auto [vectors, delays] = parse_args(argc, argv);
    std::ifstream input_file(argv[1]);

    std::string trace;      //!< string to store single line of trace file
    std::string execution;  //!< string to accumulate the execution output

    /******************ADD YOUR VARIABLES HERE*************************/

    int save_context_time = 10; // Varied from 10, 20, 30ms
    int isr_activity_time = 200; // Varied from 40 - 200ms

	int current_time = 0; // Global timestamp of the program execution

    /******************************************************************/

	// Utility function to avoid having to manually add a line to the execution and set the time
    // This appends the current timestamp, duration of the operation, and output to the execution string and it increments the global duration time
	auto print = [&](string output, int duration) {
		execution += std::to_string(current_time) + ", " + std::to_string(duration) + ", " + output + "\n";
		current_time += duration;
	};

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace); // CPU, 50 or SYSCALL, 7
        
        /******************ADD YOUR SIMULATION CODE HERE*************************/

        if (activity == "CPU") {
			print("CPU burst", duration_intr); 

		}else if (activity == "SYSCALL") {

            //duration_intr is either the device number or duration. If activity is SYSCALL, then, it
            //must be a device number. We then simply check if duration_intr>=vectors.size()
            //if the device number does not index a address in the vector table, then we know we have an issue.
            if (duration_intr >= vectors.size()){
                print("ERROR: INVALID VECTOR TABLE INDEX: The I/O device does not have a ISR (corrupted)", 0);
            }else {
                auto [exec_output, new_time] = intr_boilerplate(current_time, duration_intr, save_context_time, vectors);
                current_time = new_time;  //increment current time
                execution += exec_output; //this is like our print function except intr_boilerplate does it for us.


                // If there is no delay time associated with a device number
                // then the system call is not from an I/O device, but from the CPU.
                if (duration_intr < delays.size()){
                    print("ISR work", isr_activity_time);
                    print("call device driver", delays.at(duration_intr));
                }else {
                    print("CPU System Call ISR", isr_activity_time);
                }

                // Switch back to user mode after device finished executing then Interrupt Return 
                print("Switch to user mode", 1);
                print("IERT", 1);
            }
		}else if (activity == "END_IO") {
			print("End of I/O " + std::to_string(duration_intr) + ": interrupt" , 1);
		}
    }

    input_file.close();

    write_output(execution);

    return 0;
}


//to run this code in wsl:
//./bin/interrupts trace.txt vector_table.txt device_table.txt
