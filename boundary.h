#ifndef BOUNDARY_H
#define BOUNDARY_H
#include<string>
#include<vector>
#include"course.h"

std::istream &operator>>(std::istream &is,Grade  &g);
std::ostream &operator<<(std::ostream  &os,const Grade &g);

void readCouseGrades(Course &course,std::string path);
void outputCourseGrades(Course  &course);
#endif // BOUNDARY_H
