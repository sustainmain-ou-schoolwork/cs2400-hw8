/**
 *   @file: appointment_main.cc
 * @author: Josh Marusek
 *   @date: 2021-12-01
 *  @brief: Manages an agenda using an agenda file and command line arguments.
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <vector>
#include "appointment.h"

using namespace std;

int main(int argc, char const *argv[]) {
    vector<string> appointmentStrings;  // contains all the appointment strings from the appointment file
    vector<Appointment> appointments;   // contains all the appointments created from appointmentStrings

    ifstream appointmentFile;           // file with each appointment string on a separate line
    string lineIn;                      // holds a line from the appointment file

    // read appointments file
    appointmentFile.open("agenda.txt");
    if (appointmentFile.fail()) {
        cout << "Failed to open file." << endl;
        exit(0);
    }

    // load appointment strings line by line
    while (getline(appointmentFile, lineIn)) {
        appointmentStrings.push_back(lineIn);
    }
    appointmentFile.close();

    // load appointments from strings
    for (size_t i = 0; i < appointmentStrings.size(); i++) {
        Appointment newAppointment(appointmentStrings[i]);

        // only load if the line contains non-whitespace chars
        if (!newAppointment.stripSpaces(appointmentStrings[i]).empty()) {
            appointments.push_back(newAppointment);
        }
    }

    // parse arguments
    if (argc >= 2) {
        string argFlag = argv[1];
        if (argFlag == "-ps") {
           // print daily schedule sorted by starting time
        }
        else if (argFlag == "-p") {
            // print all appointments at the time specified by the next argument
        }
        else if (argFlag == "-a") {
            // add an appointment using the appointment data string specified by the next argument
        }
        else if (argFlag == "-dt") {
            // delete all appointments that match the title specified by the next argument
        }
        else if (argFlag == "-dm") {
            // delete all appointments that match the starting time specified by the next argument
        }
        else {
            cout << "Invalid arguments." << endl;
        }
    }
    else {
        cout << "Missing arguments." << endl;
    }

    return 0;
}// main