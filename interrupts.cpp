/**
 *
 * @file interrupts.cpp
 * @author Sasisekhar Govind
 *
 */
#define KERNEL_MODE 0
#define USER_MODE 1
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

    bool mode = USER_MODE;
	int current_time = 0;

    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace); // CPU, 50 or SYSCALL, 7
        
        cout << "Activity: " << activity << " Duration: " << duration_intr << endl;

        /******************ADD YOUR SIMULATION CODE HERE*************************/

        if (activity == "CPU") {
            // 
            execution += std::to_string(current_time) + ", " + std::to_string(1) + ", do some CPU shit for " + std::to_string(duration_intr) + "\n";

		}else if (activity == "SYSCALL") {
			auto [exec_output, new_time] = intr_boilerplate(current_time, duration_intr, 2, vectors);
			
			current_time = new_time;
			execution += exec_output;
		}else if (activity == "END_IO") {
			
		}


        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}
