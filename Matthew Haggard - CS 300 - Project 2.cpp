// Matthew Haggard - CS 300 - Project 2.cpp
// 6/19/2022

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <algorithm>

using namespace std;

// Create a custom type
struct Course {
    string courseNumber;
    string courseName;
    vector<string> coursePreReq; // This needs to be a vector

    Course(string courseNumber, string courseName) {
        this->courseNumber = courseNumber;
        this->courseName = courseName;
    }
    
    // Default constructor
    Course() {

    }
};

// Create a vector list of type course to hold courses.
vector<Course> courses;

void loadData(string fileName) {

    // make a temp course object
    Course tempCourses;

    string tempNumber, tempName;
    vector<string> tempPreReq;

    // read the data in from the file.
    fstream inFile;

    // open the file
    inFile.open(fileName);

    // in case the file doesn't exist
    if (!inFile) {
        cout << endl << "No such file exists...back to the main menu" << endl << endl;
    }

    else {

        // declare variables to read from the file
        vector<string> row;
        vector<string> tmpHolder;
        string line;
        int loop = 0;

        if (inFile.is_open()) {
            while (getline(inFile, line)) {

                if (line != "") {
                    row.push_back(line);
                }
            }
        }

        size_t pos = 0;
        string delimiterChar = ",";
        string token;
        vector<string> tempVector;
    
        // read all of the elements of row into a temp vector
        for (int i = 0; i < row.size(); i++) {
            while ((pos = row.at(i).find(delimiterChar)) != string::npos) {
                token = row.at(i).substr(0, pos);

                tempVector.push_back(token);
                row.at(i).erase(0, pos + delimiterChar.length());
            }
            // add the final string to the temp vector
            tempVector.push_back(row.at(i));

            // add the values of temp vector to the temp courses
            for (int j = 0; j < tempVector.size(); j++) {

                // the first item in the vector is the course number
                if (j == 0) {
                    tempCourses.courseNumber = tempVector.at(j);
                }

                // the second item in the vector is the course name
                else if (j == 1) {
                    tempCourses.courseName = tempVector.at(j);
                }

                // anything after that is a pre-requisite for the course
                else {
                    tempCourses.coursePreReq.push_back(tempVector.at(j));
                }
            }

            // add the tempCourses to the courses list
            courses.push_back(tempCourses);

            // clear the tempVector and coursePreReq vector
            tempVector.clear();
            tempCourses.coursePreReq.clear();
        }

        cout << endl << "Courses added successfully... " << endl << endl;
    }

    // close the file
    inFile.close();
    
}

void printCourseList() {
    // print a sample schedule with the pre-requisites first
    vector<Course> sampleSchedule;

    // add the courses to the sample schedule. Not necessary, but prevents messing with the original courses object
    for (int i = 0; i < courses.size(); i++) {
        sampleSchedule.push_back(courses.at(i));
    }

    // Using lambda expressions to sort the data
    sort(sampleSchedule.begin(), sampleSchedule.end(), [](const Course& lhs, const Course& rhs) {
        return lhs.courseNumber < rhs.courseNumber;
        });

    
    
    cout << endl << "- Course List -" << endl;

    for (int y = 0; y < sampleSchedule.size(); y++) {
        cout << "Course Number: " << sampleSchedule.at(y).courseNumber << " | Course Name: " << sampleSchedule.at(y).courseName;

        cout << " | PreReq: ";

        for (int j = 0; j < sampleSchedule.at(y).coursePreReq.size(); j++) {
            cout << sampleSchedule.at(y).coursePreReq.at(j) << " ";
        }

        cout << endl;
    }

    // this just adds a break between the information that is printed and the menu.
    cout << endl;
}

void printCourseInfo(string selectedCourse) {
    // print relavent course information
    int selection = -1;

    // check to see if the course exists in the vector
    for (int i = 0; i < courses.size(); i++) {
        if (courses.at(i).courseNumber.compare(selectedCourse) == 0) {

            // if yes, assign the current value of i to selection
            selection = i;
        }
    }

    // print the appropriate course information
    if (selection > -1) {
        cout << endl << courses.at(selection).courseNumber << " - " << courses.at(selection).courseName << endl;

        cout << "Pre-requisites: " << endl;
        for (int i = 0; i < courses.at(selection).coursePreReq.size(); i++) {
            cout << courses.at(selection).coursePreReq.at(i) << " ";

            for (int j = 0; j < courses.size(); j++) {
                if (courses.at(selection).coursePreReq.at(i).compare(courses.at(j).courseNumber) == 0) {
                    cout << courses.at(j).courseName << endl;

                }
            }

            
        }

        cout << endl << endl;
    }

    // if course doesn't exist in the vector, tell the user
    else {
        cout << "That course does not exist in that catalogue... Returning to the main menu." << endl;
    }
}

int main(){

    // variable for user input
    int userInput = 0;

    // program title
    cout << " - Welcome to the course planner - \n";

    // while loop to handle menu
    while (userInput != 9) {

        // display menu options
        cout << "1. Load Data" << endl;
        cout << "2. Print course list" << endl;
        cout << "3. Print course" << endl;
        cout << "9. Exit the application" << endl;
        
        // get menu input from the user
        cout << "Enter your selection: ";
        cin >> userInput;

        if (userInput == 1) {

            string fileName;
            cout << "Which file would you like to read data from?: ";
            cin >> fileName;

            // call the load data function with the specified filename
            loadData(fileName);
        }

        else if (userInput == 2) {
            // call the print course list function
            printCourseList();
        }

        else if (userInput == 3) {

            // variable to hold selected course
            string selectedCourse;

            // get course information from the user
            cout << "What course do you want to know about?: ";
            cin >> selectedCourse;
            
            // call to the printCourseInfo function
            printCourseInfo(selectedCourse);
        }

        // This is to handle if the user enters an invalid menu entry
        else if (userInput != 1 && userInput != 2 && userInput != 3 && userInput != 9) {
            
            cout << endl << "That is not a valid selection" << endl << endl;
        }

    }



    return 0;
}