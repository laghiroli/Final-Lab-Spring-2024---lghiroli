#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <iostream>
#include "Student.h"

using namespace std;

class Course 
{
// Public
public:
  // Constructor
  Course(const string& subject, const string& courseNumber,
  const string& section, const string& description,
  const int& hours, const string& CRN, const string& term,
  const string& instructor, const vector<string>& meetingTimes,
  const string& time); 

  // Getters
  string getSubject() const { return subject_; }
  string getCourseNumber() const { return courseNumber_; }
  string getSection() const { return section_; }
  string getDescription() const { return description_; }
  int getHours() const { return hours_; }
  string getCRN() const { return CRN_; }
  string getTerm() const { return term_; }
  string getInstructor() const { return instructor_; }
  const vector<string>& getMeetingTimes() const { return meetingTimes_; }
  string getTime() const { return time_; }

  // Setters
  bool isScheduled() const { return scheduled_; }
  void setScheduled(bool scheduled) { scheduled_ = scheduled; }
  

 // Overloading the << operator for Course class
 friend ostream& operator<<(ostream& os, const Course& course) {
   os << "Subject: " << course.subject_ << endl;
   os << "Course Number: " << course.courseNumber_ << endl;
   os << "Section: " << course.section_ << endl;
   os << "Description: " << course.description_ << endl;
   os << "Hours: " << course.hours_ << endl;
   os << "CRN: " << course.CRN_ << endl;
   os << "Term: " << course.term_ << endl;
   os << "Instructor: " << course.instructor_ << endl;

   // Used to print the meeting times of the course
   os << "Meeting Times: ";
   string meetingTimesString;
   for (const string& meetingTime : course.meetingTimes_) {
     meetingTimesString += meetingTime + ", ";
   }
   // For formatting, using pop_back to remove the trailing comma and space
   meetingTimesString.pop_back();
   meetingTimesString.pop_back();
   os << meetingTimesString << endl;

   return os;
}

// Private (including student.h vector)
private:
  string subject_;
  string courseNumber_;
  string section_;
  string description_;
  int hours_;
  string CRN_;
  string term_;
  string instructor_;
  vector<string> meetingTimes_;
  string time_;
  bool scheduled_ = false;
  vector<Student> enrolledStudents_;
};

// Course functions used in Course.cpp
vector<Course> readCourses(const string& filename);
void generateProfessorList(const vector<Course>& courses, const string& outputFilename);
void showCoursesFor(const vector<Course>& courses, const string& instructorName);
void createScheduleGrid(const vector<Course>& courses); 
void scheduleCourse(const Course& course, const vector<string>& days, const vector<string>& timeSlots, vector<vector<string>>& scheduleGrid);

#endif
