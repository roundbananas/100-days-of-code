#include "Arduino.h"

class Teacher
{
private:
    String m_name;
 
public:
    Teacher(String name)
        : m_name(name)
    {
    }
 
    String getName() { return m_name; }
};
 
class Department
{
private:
    Teacher *m_teacher; // This dept holds only one teacher for simplicity, but it could hold many teachers
 
public:
    Department(Teacher *teacher = nullptr)
        : m_teacher(teacher)
    {
    }
};

void setup()
{
  Serial.begin (9600);
}

void loop()
{
    // Create a teacher outside the scope of the Department
    Teacher *teacher = new Teacher("Bob"); // create a teacher
    {
        // Create a department and use the constructor parameter to pass
        // the teacher to it.
        Department dept(teacher);
 
    } // dept goes out of scope here and is destroyed
 
    // Teacher still exists here because dept did not delete m_teacher
 
    Serial.print (teacher->getName()); Serial.println(" still exists!");
 
    delete teacher;
 
}
