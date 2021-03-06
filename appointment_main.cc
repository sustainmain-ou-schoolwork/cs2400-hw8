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

/**
 * Function: isInt
 * @brief Checks if a string contains a valid int.
 * 
 * @return true if the string contains a valid int
 */
bool isInt(string input);

/**
 * Function: writeAppointments
 * @brief Writes all the appointments to the appointment file.
 * 
 * @param appointments vector containing all the appointments
 */
void writeAppointments(const vector<Appointment> appointments);

const string AGENDA_FILE_NAME = "agenda.txt";


int main(int argc, char const *argv[]) {
    vector<string> appointmentStrings;  // contains all the appointment strings from the appointment file
    vector<Appointment> appointments;   // contains all the appointments created from appointmentStrings

    ifstream appointmentFile;           // file with each appointment string on a separate line
    string lineIn;                      // holds a line from the appointment file

    // read appointments file
    appointmentFile.open(AGENDA_FILE_NAME);
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
            size_t originalSize = appointments.size();
            for (size_t i = 0; i < originalSize; i++) {
                int minIndex = 0;
                int min = appointments[minIndex].getTime();
                for (size_t j = 0; j < appointments.size(); j++) {
                    if (appointments[j].getTime() < min) {
                        minIndex = j;
                        min = appointments[minIndex].getTime();
                    }
                }
                cout << appointments[minIndex].getAppointmentString() << endl;
                appointments.erase(appointments.begin() + minIndex);
            }
        }
        else if (argFlag == "-p") {
            // print all appointments at the time specified by the next argument
            if (argc >= 3) {  // check if next argument exists
                if (isInt(argv[2])) {  // check if next argument contains an int
                    int time = stoi(argv[2]);

                    // print all matches
                    for (size_t i = 0; i < appointments.size(); i++) {
                        if (appointments[i].getTime() == time) {
                            cout << appointments[i].getAppointmentString() << endl;
                        }
                    }
                }
                else {
                    cout << "Invalid time." << endl;
                }
            }
            else {
                cout << "No time given." << endl;
            }
        }
        else if (argFlag == "-a") {
            // add an appointment using the appointment data string specified by the next argument
            if (argc >= 3) {  // check if next argument exists
                Appointment newAppointment(argv[2]);
                appointments.push_back(newAppointment);
            }

            // save appointments to file
            writeAppointments(appointments);
        }
        else if (argFlag == "-dt") {
            // delete all appointments that match the title specified by the next argument
            if (argc >= 3) {  // check if next argument exists
                // remove all matches
                for (size_t i = 0; i < appointments.size(); i++) {
                    if (appointments[i].getTitle() == argv[2]) {
                        appointments.erase(appointments.begin() + i);
                        i--;
                    }
                }

                // save appointments to file
                writeAppointments(appointments);
            }
            else {
                cout << "No title given." << endl;
            }
        }
        else if (argFlag == "-dm") {
            // delete all appointments that match the starting time specified by the next argument
            if (argc >= 3) {  // check if next argument exists
                if (isInt(argv[2])) {  // check if next argument contains an int
                    int time = stoi(argv[2]);

                    // remove all matches
                    for (size_t i = 0; i < appointments.size(); i++) {
                        if (appointments[i].getTime() == time) {
                            appointments.erase(appointments.begin() + i);
                            i--;
                        }
                    }

                    // save appointments to file
                    writeAppointments(appointments);
                }
                else {
                    cout << "Invalid time." << endl;
                }
            }
            else {
                cout << "No time given." << endl;
            }
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

bool isInt(string input) {
    // scan through each character until a digit is found
    for (size_t i = 0; i < input.length(); i++) {
        if (isdigit(input[i])) {
            return true;
        }
    }

    return false;
}

void writeAppointments(const vector<Appointment> appointments) {
    ofstream appointmentFile;
    appointmentFile.open(AGENDA_FILE_NAME);
    for (size_t i = 0; i < appointments.size(); i++) {
        appointmentFile << appointments[i].getAppointmentString() << endl;
    }
    appointmentFile.close();
}