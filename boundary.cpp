
#include<iostream>
#include<fstream>
#include"boundary.h"
#include"course.h"
#include <sstream>

using std::cerr;
using std::getline;
using std::ifstream;
using std::istream;
using std::istringstream;
using std::ostream;
using std::string;
using std::vector;
using std::cout;
using std::endl;
istream &operator>>(istream &is, Grade  &g)
{
    // read and store the student'name and midterm and final exam grade
    is >> g.m_name >> g.m_midterm >> g.m_final;
    // read and store all the student's homework grades
    // followed by terminator-string "the end"
    if (is) {
        g.m_homework.clear();
        double x;
        while (is >> x)
            g.m_homework.push_back(x);
        is.clear();
    }
    return is;
}

 std::ostream  &operator<<(std::ostream  &os, const Grade &g)
{

    os<< g.score()<<"\t\t\t\t"<<g.m_name<<"   \n";
    return os;
}



 void readCourseGrades(Course &course,std::string path)
 {
     ifstream ifs{path};
     string line;
     while (getline(ifs, line)) {
         istringstream iss{line};
         iss >> std::ws;
         Grade *g = new Grade;
         if (iss >> *g) {
             course._grades.push_back(g);
         }
     }
     if (course._grades.size() != 0) {
         cerr << "Reading successfully!\n\n";
     } else {
         cerr << "There are some errors in the grade data.\n"
                 "The program will exit.\n";
         exit(EXIT_FAILURE);
     }
 }

 void outputCourseGrades(Course &course)
 {
     cout << "SBI total grades:" << std::endl << std::showpoint;
     for(std::vector<Grade*>::size_type i=0;i<course._grades.size();i++)
     {
         //std::ofstream os;
         //os.open("./abc.xtx");
         cout<<*course._grades[i];   //
         //cout<<"1";
     }
 }
