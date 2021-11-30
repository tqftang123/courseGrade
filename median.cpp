#include"median.h"  //包含自己的头文件，为了做一致性检查

#include<algorithm>
#include<stdexcept>
#include<vector>

using std::domain_error;
using std::sort;
using std::vector;

double median(vector<double> vec)
{
    // check if vec is empty
    auto size = vec.size();
    if (size == 0)
        throw domain_error{"median of an empty vector"};

    // sort the grades
    sort(vec.begin(), vec.end());

    // compute the median homework grade
    auto mid = size / 2;

    double median = (size % 2 == 0 ? (vec[mid] + vec[mid - 1]) / 2 : vec[mid]);
    return median;
}
