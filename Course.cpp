#include "Course.h"
#include <sstream>
#include <fstream>
#include <iostream> 
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include "Student.h"

using namespace std;

Course::Course(const string& subject, const string& courseNumber,
               const string& section, const string& description,
               const int& hours, const string& CRN, const string& term,
               const string& instructor, const vector<string>& meetingTimes,
               const string& time)
  : subject_(subject), courseNumber_(courseNumber), section_(section),
    description_(description), hours_(hours), CRN_(CRN), term_(term),
    instructor_(instructor), meetingTimes_(meetingTimes), time_(time) {}

// Function to read courses from a tab-delimited file
vector<Course> readCourses(const std::string& filename) 
{
  vector<Course> courses;
  ifstream file(filename);
  if (!file.is_open()) 
  {
    cerr << "Error: Could not open file " << filename << std::endl;
    return courses;
  }

  // Skip header line
  string line;
  getline(file, line);

  while (getline(file, line)) 
  {
    stringstream ss(line);
    string subject, courseNumber, section, description;
    int hours;
    string CRN, term, instructor;
    vector<string> meetingTimes;
    string time;

    // Extract fields based on tab delimiters
    getline(ss, subject, '\t');
    getline(ss, courseNumber, '\t');
    getline(ss, section, '\t');
    getline(ss, description, '\t');
    string hoursString;
    getline(ss, hoursString, '\t');
    getline(ss, CRN, '\t');
    getline(ss, term, '\t');
    getline(ss, instructor, '\t');

    // Get times, separated by commas
    getline(ss, time);
    istringstream meetingTimeStream(time);
    string meetingTime;
    while (getline(meetingTimeStream, meetingTime, ',')) 
    {
      meetingTimes.push_back(meetingTime);
    }

    courses.push_back(Course(subject, courseNumber, section, description,
                             hours, CRN, term, instructor, meetingTimes, time));
  }

  file.close();
  return courses;
}

// Function to generate professor list and save to a file
void generateProfessorList(const vector<Course>& courses, const string& filename) 
{
map<string, string> professors; 
for (const Course& course : courses) 
  {
    professors[course.getInstructor()] = course.getCRN();
  }

ofstream file(filename);
if (file.is_open()) 
{
  file << "Professor Name, CRN" << endl;
  for (auto it = professors.begin(); it != professors.end(); ++it) 
  {
    const string& name = it->first;
    const string& crn = it->second;
    file << name << ", " << crn << endl;
  }
  
  file.close();
  cout << "Professor list saved to: " << filename << endl;
} 
else 
{
  cerr << "Error: Could not open file: " << filename << endl;}
}

//Function to find courses for a specific instructor
void showCoursesFor(const vector<Course>& courses, const string& instructorName) 
{
  cout << "**Courses for " << instructorName << "**" << endl;
  // Extract last name from instructor name 
  string lastName;
  size_t commaPos = instructorName.find(',');
  if (commaPos != string::npos) 
  {
    lastName = instructorName.substr(commaPos + 1); 
    lastName.erase(lastName.size() - 1); 
  } 
  else 
  {
    lastName = instructorName; // Use entire name if no comma found
  }

// Convert instructor last name and course instructor names to lowercase 
string lowercaseName = lastName;
transform(lowercaseName.begin(), lowercaseName.end(), lowercaseName.begin(), ::tolower);

bool foundMatch = false; 

for (const Course& course : courses) 
{
  string lowercaseInstructor = course.getInstructor();
  transform(lowercaseInstructor.begin(), lowercaseInstructor.end(), lowercaseInstructor.begin(), ::tolower);

  // Search for last name within instructor name 
  if (lowercaseInstructor.find(lowercaseName) != string::npos) 
  {
    // If a match is found :)
    foundMatch = true;
    cout << "Course: " << course.getSubject() << " " << course.getCourseNumber() << endl;
    cout << "Instructor: " << course.getInstructor() << endl;  // Display full instructor name
    cout << "CRN: " << course.getCRN() << endl;  // Display CRN
  }
}
  if (!foundMatch) 
    {
      cout << "No courses found for instructor: " << instructorName << endl;
    }
  }

// !!This function was used to create the course schedule grid, however this wasn't included in my final project because I couldn't get the courses to populate the grid!!
void createScheduleGrid(const vector<Course>& courses) 
{

  // Initializing the schedule grid
  const vector<string> days = {" M ", " T ", " W ", " Th ", " F "};
  const vector<string> timeSlots = {"8:30 AM", "10:00 AM", "11:30 AM", "1:00 PM",
                                   "2:30 PM", "4:00 PM", "5:30 PM"};
  vector<vector<string>> scheduleGrid(days.size(), vector<string>(timeSlots.size(), ""));

  // Grid borders
  const string topBorder = "+----------+----------+----------+----------+----------+";
  const string rowSeparator = "| | | | | |";
  const string bottomBorder = "+----------+----------+----------+----------+----------+";

  // Printing header row 
  cout << topBorder << endl;
  cout << " ";
  for (const string& timeSlot : timeSlots) 
  {
    cout << timeSlot << " ";
  }
  cout << endl << topBorder << endl;

  for (const Course& course : courses) 
  {
    // Parsing meeting times (error parsing I think)
    stringstream ss(course.getTime());
    string meetingTime;
    while (getline(ss, meetingTime, ',')) 
    {
      // Extract day and time from meeting time
      string day = meetingTime.substr(0, 2);
      string startTime, endTime;
      stringstream timeStream(meetingTime.substr(3));
      getline(timeStream, startTime, '-');
      getline(timeStream, endTime);

      // Find corresponding indices in the schedule grid
      int dayIndex = find(days.begin(), days.end(), day) - days.begin();
      int startTimeIndex = lower_bound(timeSlots.begin(), timeSlots.end(), startTime) - timeSlots.begin();
      int endTimeIndex = lower_bound(timeSlots.begin(), timeSlots.end(), endTime) - timeSlots.begin();
      string courseInfo = course.getSubject() + " " + course.getCourseNumber() + " " + course.getSection();

      // Check if course is scheduled and update cell content accordingly
      if (course.isScheduled()) 
      {
        courseInfo = "[*] " + courseInfo; 
      }

      // Loop through time slots and handle displaying multiple courses 
      // Also also print course info if the cell is not empty ??
      for (int i = startTimeIndex; i < endTimeIndex; ++i)
        {
          if (!scheduleGrid[dayIndex][i].empty()) {
          scheduleGrid[dayIndex][i] += "\n  " + courseInfo;
        } 
        else 
        {
          scheduleGrid[dayIndex][i] = courseInfo;
        }
      }
    }
  }
}
