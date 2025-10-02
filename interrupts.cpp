/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 *
 */
#include<interrupts.hpp>
#include <iostream>

using namespace std;

std::pair<std::string, int> print_line (string output, int time, int current_time);

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

	auto print = [&](string output, int duration) {
		auto [output_str, new_time] = print_line(output, duration, current_time);
		execution += output_str;
		current_time = new_time;
	};

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace); // CPU, 50 or SYSCALL, 7

		cout << "Activity: " << activity << "  Duration/Device ID: " << duration_intr << endl;
        
        /******************ADD YOUR SIMULATION CODE HERE*************************/

        if (activity == "CPU") {
			print("### Do CPU stuff for " + std::to_string(duration_intr), duration_intr);

		}else if (activity == "SYSCALL") {
			auto [exec_output, new_time] = intr_boilerplate(current_time, duration_intr, 2, vectors);
			
			current_time = new_time;
			execution += exec_output;

			print("do some device stuff", delays.at(duration_intr)); // 			delays[duration_intr]

			print("Switch to user mode", 1);
			print("IERT", 1);

		}else if (activity == "END_IO") {
			print("end of I/O " + std::to_string(duration_intr) + ": interrupt" , 1);
		}


        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}

std::pair<std::string, int> print_line (string output, int time, int current_time) {
	std::string execution = "";
	execution += std::to_string(current_time) + ", " + std::to_string(time) + ", " + output + "\n";
	current_time += time;

	return make_pair(execution, current_time);
}