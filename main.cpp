 //Project: coursegrades-sf
//
// Author: stardust (open-src@qq.com)
// Date: 2021-10-31
// Version: 0.1.0
//
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// coursegrades: A Program that computes all grades of a course. This is the
// version of single source file.
// =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
//
// Main module
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cerr;
using std::cin;
using std::cout;
using std::domain_error;
using std::endl;
using std::ifstream;
using std::istream;
using std::setprecision;
using std::sort;
using std::string;
using std::vector;

struct Grade {
    string name;
    double midterm;
    double final;
    vector<double> homework;
    double total;
};

vector<Grade> courseGrades; //全局变量

void readCourseGrades();
void computeAndSortCourseGrades();
void outputCourseGrades();

int main()
{
    readCourseGrades();
    computeAndSortCourseGrades();
    outputCourseGrades();

    return 0;
}


istream &operator>>(istream &is, Grade &g)         //重载操作符>>
{
    // read and store the student'name and midterm and final exam grade
    is >> g.name >> g.midterm >> g.final;
    // read and store all the student's homework grades
    // followed by terminator-string "the end"
    if (is) {
        g.homework.clear();   //清除上一次的数据
        double x;
        while (is >> x)
            g.homework.push_back(x);
        is.clear();
    }
    return is;
}

void readCourseGrades()         //read函数的实现
{
    cout << "Reading all grades information (name midterm final homework)"
            "from a file...\n";
    ifstream ifs{"../coursegrades-sf/coursegrades.dat"};
    // read and store all the grades
    for (Grade g; ifs >> g;) {
        courseGrades.push_back(g);
    }
    if (courseGrades.size() != 0) {
        cerr << "Reading successfully!\n\n";
    } else {
        cerr << "There are some errors in the grade data.\n"
                "The program will exit.\n";
        exit(EXIT_FAILURE);
    }
}


// void readCourseGrades(vector<Grade> &cg)
//{
//    cout << "Reading all grades information (name midterm final homework)"
//            "from a file...\n";
//    ifstream ifs{"../coursegrades/coursegrades.dat"};
//    // read and store all the grades
//    for (Grade g; ifs >> g;) {  //假定能够进行ifs >> g读取操作
//        cg.push_back(g);
//    }
//    //对cg进行错误处理
//}


double median(vector<double> vec)
{
     //check if vec is empty
  auto size = vec.size();
   if (size == 0)
        throw domain_error{"median of an empty vector"};

    //sort the grades
    sort(vec.begin(), vec.end());

     //compute the median homework grade
  auto mid = size / 2;

    double median = (size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid]);
   return median;
}

double score(const Grade &g)
{
    if (g.homework.size() == 0)
        throw domain_error{"Student has done no homework. "};
    return 0.2 * g.midterm + 0.4 * g.final + 0.4 * median(g.homework);
}
bool compare(const Grade &g1, const Grade &g2) { return g1.total < g2.total; }

void computeAndSortCourseGrades()
{
    try {
        for (auto &g : courseGrades)
            g.total = score(g);
        sort(courseGrades.begin(), courseGrades.end(), compare);
    } catch (domain_error &e) {
        cout << e.what();
    }
}

void outputCourseGrades()
{
    cout << "SBI total grades:" << endl << std::showpoint;
    // output the grade report
    auto prec = cout.precision(3);
    for (const auto &g : courseGrades) {
        cout << g.total << string(20, ' ') << g.name << '\n';
    }
    cout.precision(prec);
}




