#include <iostream>
#include <vector>
#include <string>
#include "Course.h" 
#include "Student.h"
#include "Transcript.h"
#include <sstream>
#include <fstream>

using namespace std;

// These lines were being used to create the schedule grid 

//const vector<string> days = {" M ", " T ", " W ", " Th ", " F "};
//const vector<string> timeSlots = {"8:00 AM", "8:30 AM", "...", "12:45 PM",
//"1:00 PM", "1:30 PM", "...", "5:30 PM"};

int main() 
{
  // Defining the filename for the course data 
  const string filename = "Courses2023.xlsx"; 
  // Reading courses from the file
  vector<Course> courses = readCourses(filename);
  // Generating professor list and save to a file (a)
  generateProfessorList(courses, "professors.txt");
  // Showing courses for a specific instructor (b)
  string instructorName = "Trovato";
  showCoursesFor(courses, instructorName);

  // This function was originally used to create a schedule grid to display the final schedule, however I was unable to get the courses to populate inside the created grid. THe code does run, just creates an empty grid.
  // createScheduleGrid(courses); 

  // A function that allows the user to create a new course
  cout << "**Generating a New Course**" << endl;
  Course myCourse("C++ Programming", "CS 4200", "R1", "Introduction to R Programming",
  3, "55555", "Fall 2024", "Professor Trovato", {"T/F 10:00 AM"}, "T/F");
 
  cout << myCourse << endl;

  // Next, I wanted to be able to read a student's transcript, and calculate their GPA based on their grades
  // Define the filename for the transcript data 

  // Defining the filename for the transcript data 
  const string transcriptFilename = "Transcript.xlsx";
  // Reading transcript from the file
  ifstream transcriptFile(transcriptFilename);

  if (!transcriptFile.is_open()) 
  {
    // Used because was having errors opening the file
    cerr << "Error: Could not open transcript file " << transcriptFilename << endl;
  } 
  else 
  {
    vector<string> grades; // Save the grades
    string line;

    // Skip the header line 
    getline(transcriptFile, line); 

    // Process lines in the transcript file
    while (getline(transcriptFile, line)) 
    {
        // Skip empty lines
        if (line.empty()) continue;

        // Extract the grade, coursename, and studentname
        istringstream iss(line);
        string studentName, courseName, grade;
        iss >> studentName;
        iss >> courseName;  
        iss >> grade;        

        // Print the extracted grade (used to troubleshoot errors getting just the grade)
        cout << "**Calculating Student GPA from Transcript**" << endl;"
        cout << "Extracted Student Grade: " << grade << endl;

        // Add the grade to the vector
        grades.push_back(grade);
    }

  transcriptFile.close();

    Transcript myTranscript;

      // Add grades to the Transcript object
      for (const string& grade : grades) 
        {
          myTranscript.addCourse(grade);
        }

      // Calculate and display GPA using Transcript.cpp
      double gpa = myTranscript.getGPA();
      cout << "Calculated Student GPA: " << gpa << endl;
    }
  return 0;
}
