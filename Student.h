#ifndef STUDENT_H
#define STUDENT_H
#include "UniversityMember.h"
#include "Course.h"

class Transcript;

class Student : public UniversityMember 
{
// Public
public:
    // Constructor
    Student(const string& name, const string& id, const string& studentID);

    // Getters/Setters
    string getStudentID() const { return studentID_; }
    void setStudentID(const string& studentID) { studentID_ = studentID; }

// Private 
private:
    string studentID_;

};

#endif
