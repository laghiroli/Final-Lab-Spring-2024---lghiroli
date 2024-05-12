#ifndef UNIVERSITYMEMBER_H
#define UNIVERSITYMEMBER_H

#include <string>
using namespace std;

class UniversityMember 
{
// Public
public:
    // Constructor
    UniversityMember(const string& name, const string& id);

    // Getters and Setters
    string getName() const { return name_; }
    string getID() const { return id_; }

    void setName(const string& name) { name_ = name; }
    void setID(const string& id) { id_ = id; }

// Private
private:
    string name_;
    string id_;
};

#endif
