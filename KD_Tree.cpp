#include <vector>
#include <iomanip>
#include <iostream>
using namespace std;

int dim_index = 0;

bool compareFunc(const vector<double>& first, const vector<double>& second) {
  dim_index %= first.size();
  return first[dim_index] < second[dim_index];
}

void localSort(vector<vector<double> >& v, int begin, int end) {
  sort(v.begin()+begin, v.begin()+end, compareFunc);
  ++ dim_index;
}

void buildTreeHelper(vector<vector<double> >& data, int begin, int end, int dim_index) {

}

void buildTree(vector<vector<double> >& data, int begin, int end) {

}

int main(int argc, char const *argv[]) {
  vector<double> a = {1, 3, 5, 7, 9};
  vector<double> b = {2, 4, 6, 8, 10};
  vector<double> c = {9, 2, 6, 5, 1};
  vector<vector<double> > v;
  v.push_back(a);
  v.push_back(b);
  v.push_back(c);

  for (int i = 0; i < a.size();++i) {
    localSort(v, 0, 3);
    for (vector<double> ve: v) {
      for (double d: ve) {
        cout << setfill(' ') << setw(6) << left << d;
      }
      cout << endl;
    }
    cout << endl;
  }
  return 0;
}
