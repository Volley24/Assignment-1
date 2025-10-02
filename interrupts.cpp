/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 *
 */
#include<interrupts.hpp>
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

	int current_time = 0;

    /******************************************************************/

	// Utility function to avoid having to manually add a line to the execution and set the time
	auto print = [&](string output, int duration) {
		execution += std::to_string(current_time) + ", " + std::to_string(duration) + ", " + output + "\n";
		current_time += duration;
	};

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace); // CPU, 50 or SYSCALL, 7

		cout << "Activity: " << activity << "  Duration/Device ID: " << duration_intr << endl;
        
        /******************ADD YOUR SIMULATION CODE HERE*************************/

        if (activity == "CPU") {
			print("CPU burst", duration_intr);

		}else if (activity == "SYSCALL") {
			auto [exec_output, new_time] = intr_boilerplate(current_time, duration_intr, 2, vectors);
			
			current_time = new_time;
			execution += exec_output;

			print("call device driver", delays.at(duration_intr));

			print("Switch to user mode", 1);
			print("IERT", 1);

		}else if (activity == "END_IO") {
			print("End of I/O " + std::to_string(duration_intr) + ": interrupt" , 1);
		}
    }

    input_file.close();

    write_output(execution);

    return 0;
}