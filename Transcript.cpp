#include "Transcript.h"
#include <algorithm> 

using namespace std; 
Transcript::Transcript() {}

void Transcript::addCourse(const string& grade) 
{
  // Add the grade to the grades_ vector
  grades_.push_back(grade[0]);
}

double Transcript::getGPA() const 
{
  // Handle empty grades
  if (grades_.empty()) 
  {
    return 0.0; 
  }

  // Calculate GPA using the formula: GPA = sum of grades / number of grades
  double gpa = 0.0;
  for (auto it = grades_.begin(); it != grades_.end(); ++it) 
  {
    char firstChar = *it;  
    switch (firstChar) 
    {
      case 'A':
        gpa += 4.0;
        break;
      case 'B':
        gpa += 3.0;
        break;
      case 'C':
        gpa += 2.0;
        break;
      case 'D':
        gpa += 1.0;
        break;
      case 'F':  
        gpa += 0.0;
        break;
      default:
        // Handle incorrect grades (troubleshooting)
        cerr << "Warning: Unrecognized grade: " << *it << endl;
        break; 
    }
  }
  return gpa / grades_.size();
}
