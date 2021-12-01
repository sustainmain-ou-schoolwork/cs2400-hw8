#include <string>
#include <cctype>
#include <iostream>
#include "appointment.h"
using namespace std;

///constructors

Appointment::Appointment() {
    title = "N/A";
    year = 1;
    month = 1;
    day = 1;
    time = 0;
    duration = 1;
}

Appointment::Appointment(string appData) : Appointment() {
    int indices[7];    // contains the start indices of each parameter, plus another index so the length of the last parameter can be determined
    string params[6];  // contains each parameter from appData

    // determine starting indices of each parameter
    indices[0] = 0;    // first param starts at index 0
    for (int i = 1; i < 6; i++) {
        indices[i] = appData.find("|", indices[i - 1]) + 1;
    }
    indices[7] = appData.length();

    // parse appData into an array of parameters
    for (int i = 0; i < 6; i++) {
        params[i] = stripSpaces(appData.substr(indices[i], (indices[i + 1] - 1 - indices[i])));
    }
    
    // set each value based on its corresponding parameter if the parameter is valid
    // if the parameter is invalid, retain the default value
    setTitle(params[0]);
    if (containsInt(params[1])) {
        setYear(stoi(params[1]));
    }
    if (containsInt(params[2])) {
        setMonth(stoi(params[2]));
    }
    if (containsInt(params[3])) {
        setDay(stoi(params[3]));
    }
    setTime(standardToMilitary(params[4]));
    if (containsInt(params[5])) {
        setDuration(stoi(params[5]));
    }
}


///getters

string Appointment::getTitle() const {
    return title;
}

int Appointment::getYear() const {
    return year;
}

int Appointment::getMonth() const {
    return month;
}

int Appointment::getDay() const {
    return day;
}

int Appointment::getTime() const {
    return time;
}

int Appointment::getDuration() const {
    return duration;
}

string Appointment::getDate() const {
    string monthPadding = (month < 10) ? "0" : "";  // add a leading 0 if necessary so the month is always 2 digits
    string dayPadding = (day < 10) ? "0" : "";      // add a leading 0 if necessary so the day is always 2 digits

    return to_string(year) + "-" + monthPadding + to_string(month) + "-" + dayPadding + to_string(day);
}

string Appointment::getStandardTime() const {
    return militaryToStandard(time);
}

string Appointment::getAppointmentString() const {
    return title + "|" + to_string(year) + "|" + to_string(month) + "|" + to_string(day) + "|" + getStandardTime() + "|" + to_string(duration);
}


///setters

void Appointment::setTitle(string newTitle) {
    title = stripSpaces(newTitle);
}

void Appointment::setYear(int newYear) {
    if (newYear >= 0) {
        year = newYear;
    }
}

void Appointment::setMonth(int newMonth) {
    if (newMonth >= 1 && newMonth <= 12) {
        month = newMonth;
    }
}

void Appointment::setDay(int newDay) {
    if (newDay >= 1 && newDay <= 31) {
        day = newDay;
    }
}

void Appointment::setTime(int newTime) {
    if (newTime >= 0 && newTime < 2400) {  // ensure that hours are within bounds
        if (newTime % 100 < 60) {          // ensure that minutes are within bounds
            time = newTime;
        }
    }
}

void Appointment::setDuration(int newDuration) {
    if (newDuration >= 0) {
        duration = newDuration;
    }
}

void Appointment::setDate(int newYear, int newMonth, int newDay) {
    setYear(newYear);
    setMonth(newMonth);
    setDay(newDay);
}


///helpers

string Appointment::militaryToStandard(int time) const {
    string meridiem;                                  // AM or PM
    int minute = time % 100;
    string minutePadding = (minute < 10) ? "0" : "";  // add a leading 0 if necessary so the minute is always 2 digits
    int hour = (time - minute) / 100;

    if (time >= 1200) {
        meridiem = "PM";
    }
    else {
        meridiem = "AM";
    }

    if (hour >= 13) {      // handle 12-hour wraparound
        hour = hour - 12;
    }
    else if (hour == 0) {  // handle special case for midnight - 1AM
        hour = 12;
    }

    return to_string(hour) + ":" + minutePadding + to_string(minute) + meridiem;
}

int Appointment::standardToMilitary(string time) const {
    string meridiemIndexSearches[4] = {"a", "A", "p", "P"};  // all possible first characters of the meridiem
    int colonIndex = time.find(":");
    int meridiemIndex = -1;
    
    // try searching for each first character of the meridiem
    for (int i = 0; i < 4; i++) {
        if (meridiemIndex < 0) {
            meridiemIndex = time.find(meridiemIndexSearches[i]);
        }
        else {
            break;
        }
    }

    // set hour and minute to default values
    int hour = 0;
    int minute = 0;

    string hourString, minuteString;
    hourString = time.substr(0, colonIndex);
    minuteString = time.substr((colonIndex + 1), 2);

    // only convert if all parts of the time string were valid
    if (containsInt(hourString) && containsInt(minuteString) && meridiemIndex > -1) {
        hour = stoi(hourString);
        minute = stoi(minuteString);

        string meridiem = stringToUpper(time.substr(meridiemIndex, 2));

        if (meridiem == "PM" && hour < 12) {       // handle 12-hour wraparound
            hour += 12;
        }
        else if(meridiem == "AM" && hour == 12) {  // handle special case for midnight - 1AM
            hour = 0;
        }
    }

    return ((hour * 100) + minute);
}

string Appointment::stripSpaces(string input) const {
    int leftIndex = 0;
    int rightIndex = input.length() - 1;

    // find beginning of string
    for (int i = 0; i <= rightIndex; i++) {
        if (isspace(input.at(i))) {
            leftIndex++;
        }
        else {
            break;
        }
    }

    // find end of string
    for (int i = rightIndex; i >= leftIndex; i--) {
        if (isspace(input.at(i))) {
            rightIndex--;
        }
        else {
            break;
        }
    }

    return input.substr(leftIndex, (rightIndex - leftIndex + 1));
}

string Appointment::stringToUpper(string input) const {
    string output = "";
    for (size_t i = 0; i < input.length(); i++) {
        output += toupper(input.at(i));
    }

    return output;
}

bool Appointment::containsInt(string input) const {
    // scan through each character until a digit is found
    for (size_t i = 0; i < input.length(); i++) {
        if (isdigit(input[i])) {
            return true;
        }
    }

    return false;
}

/// friends

bool operator ==(const Appointment &first, const Appointment &second) {
    if (first.title != second.title) {
        return false;
    }
    else if (first.year != second.year) {
        return false;
    }
    else if (first.month != second.month) {
        return false;
    }
    else if (first.day != second.day) {
        return false;
    }
    else if (first.time != second.time) {
        return false;
    }
    else if (first.duration != second.duration) {
        return false;
    }
    else {
        return true;
    }
}