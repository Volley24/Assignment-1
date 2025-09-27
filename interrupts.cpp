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

    /******************************************************************/

    //parse each line of the input trace file
    while(std::getline(input_file, trace)) {
        auto [activity, duration_intr] = parse_trace(trace);
        // CPU, 50
        cout << "Activity: " << activity << " Duration: " << duration_intr << endl;

        /******************ADD YOUR SIMULATION CODE HERE*************************/

        //if (activity == "CPU")


        /************************************************************************/

    }

    input_file.close();

    write_output(execution);

    return 0;
}
