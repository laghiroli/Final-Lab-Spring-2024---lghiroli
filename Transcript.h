#ifndef TRANSCRIPT_H
#define TRANSCRIPT_H

#include <vector>
#include "Course.h" 
#include "Student.h"

using namespace std;

// Forward declaration
class Course; 
class Transcript 
{ 
// Public
public:
  // Default constructor
  Transcript(); 
  // Setters and Getters
  void addCourse(const string& grade);
  vector<Course> getCourses() const { return courses_; } 
  double getGPA() const; 

// Private
private:
  vector<Course> courses_; 
  vector<char> grades_; 
};

#endif
