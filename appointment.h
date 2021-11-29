#ifndef APPOINTMENT_H
#define APPOINTMENT_H
using namespace std;

class Appointment {
    public:
        /** Default constructor
         * @brief Construct a new Appointment object
         * 
         * Initializes title as "N/A", year as 1, month as 1, day as 1, time as 0, and duration as 1.
         */
        Appointment();
        /**
         * @brief Construct a new Appointment object from appData
         * 
         * @param appData the string containing all the appointment details, separated by barlines
         */
        Appointment(string appData);

        /**
         * Function: getTitle
         * @brief Gets the title of the appointment.
         * 
         * @return title of the appointment
         */
        string getTitle() const;

        /**
         * Function: getYear
         * @brief Gets the year of the appointment.
         * 
         * @return year of the appointment
         */
        int getYear() const;

        /**
         * Function: getMonth
         * @brief Gets the month of the appointment.
         * 
         * @return month of the appointment
         */
        int getMonth() const;

        /**
         * Function: getDay
         * @brief Gets the day of the appointment.
         * 
         * @return day of the appointment
         */
        int getDay() const;

        /**
         * Function: getTime
         * @brief Gets the time of the appointment.
         * 
         * @return time of the appointment
         */
        int getTime() const;

        /**
         * Function: getDuration
         * @brief Gets the duration of the appointment.
         * 
         * @return duration of the appointment
         */
        int getDuration() const;

        /**
         * Function: getDate
         * @brief Gets the full date of the appointment in YYYY-MM-DD format.
         * 
         * @return date of the appointment in YYYY-MM-DD format
         */
        string getDate() const;

        /**
         * Function: getStandardTime
         * @brief Gets the time of the appointment in standard format.
         * 
         * @return time of the appointment in standard format
         */
        string getStandardTime() const;
        

        /**
         * Function: setTitle
         * @brief Sets the title of the appointment.
         * 
         * @param newTitle the new title
         */
        void setTitle(string newTitle);

        /**
         * Function: setYear
         * @brief Sets the year of the appointment.
         * 
         * @param newYear the new year
         */
        void setYear(int newYear);

        /**
         * Function: setMonth
         * @brief Sets the month of the appointment.
         * 
         * @param newMonth the new month
         */
        void setMonth(int newMonth);

        /**
         * Function: setDay
         * @brief Sets the day of the appointment.
         * 
         * @param newDay the new day
         */
        void setDay(int newDay);

        /**
         * Function: setTime
         * @brief Sets the time of the appointment.
         * 
         * @param newTime the new time
         */
        void setTime(int newTime);

        /**
         * Function: setDuration
         * @brief Sets the duration of the appointment.
         * 
         * @param newDuration the new duration
         */
        void setDuration(int newDuration);

        /**
         * Function: setDate
         * @brief Sets the year, month, and day of the appointment.
         * 
         * @param newYear the new year
         * @param newMonth the new month
         * @param newDay the new day
         */
        void setDate(int newYear, int newMonth, int newDay);


        /**
         * Function: militaryToStandard
         * @brief converts a time from military to standard format.
         * 
         * @param time the time in military format
         * @return the time in standard format
         */
        string militaryToStandard(int time) const;

        /**
         * Function: standardToMilitary
         * @brief converts a time from standard to military format.
         * 
         * @param time the time in standard format
         * @return the time in military format
         */
        int standardToMilitary(string time) const;


        /**
         *  Function: stripSpaces
         *  @brief Compares two Appointment objects.
         * 
         *  @param otherAppointment the string to be stripped
         *  @return the string with no leading or trailing spaces
         */
        
        
        /**
         *  Function: stripSpaces
         *  @brief Strips leading and trailing spaces from a string.
         * 
         *  @param input the string to be stripped
         *  @return the string with no leading or trailing spaces
         */
        string stripSpaces(string input) const;
        
        /**
         *  Function: stringToUpper
         *  @brief Converts an entire string to uppercase.
         * 
         *  @param input the string to be converted
         *  @return the string in uppercase
         */
        string stringToUpper(string input) const;


        /**
         * Operator: ==
         * @brief Compares two Appointment objects.
         * 
         * @param first the first appointment
         * @param second the seocnd appointment
         * @return true if the objects contain all the same values
         * @return false if the objects do not contain all the same values
         */
        friend bool operator ==(const Appointment &first, const Appointment &second);
    private:
        string title;  // the title of the appointment
        int year;      // the year of the appointment's starting date
        int month;     // the month of the appointment's starting date
        int day;       // the day of the appointment's starting date
        int time;      // the starting time of the appointment
        int duration;  // the duration of the appointment
};

#endif