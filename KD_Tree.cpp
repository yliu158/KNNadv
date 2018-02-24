#include <vector>
#include <iomanip>
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
using namespace std;

int dim_index = 0;

void printData(const vector<vector<double> >& data) {
  cout << endl;
  for (vector<double> v: data) {
    for (double d: v) {
      cout << left <<setfill(' ') << setw(10) << left << d;
    }
    cout << endl;
  }
  cout << endl;
}

bool compareFunc(const vector<double>& first, const vector<double>& second) {
  dim_index %= first.size();
  return first[dim_index] < second[dim_index];
}

void localSort(vector<vector<double> >& v, int begin, int end, int dimension) {
  dim_index = dimension;
  sort(v.begin()+begin, v.begin()+end+1, compareFunc);
}

void buildTreeHelper(vector<vector<double> >& data, int begin, int end, int dimension) {
  if (begin >= end) return;
  localSort(data, begin, end, dimension);
  int mid = (begin+end)/2;
  buildTreeHelper(data, begin, mid-1, dimension+1);
  buildTreeHelper(data, mid+1, end, dimension+1);
  return;
}

void buildTree(vector<vector<double> >& data) {
  buildTreeHelper(data, 0, data.size()-1, 0);
  return;
}

void printHelper(const vector<vector<double> >& data, int begin, int end, int dimension) {
  if (begin > end) return;
  if (begin == end) {
    for (int i = 0; i < dimension; ++i) {
      cout << "       ";
    }
    cout << data[begin][dimension%data[0].size()] << endl;
    return;
  }
  int mid = (begin+end)/2;
  printHelper(data, begin, mid-1, dimension+1);
  for (int i = 0; i < dimension; ++i) {
    cout << "       ";
  }
  cout << data[mid][dimension%data[0].size()] << endl;
  printHelper(data, mid+1, end, dimension+1);
  return;
}

double euclideanMetric(const vector<double>& first, const vector<double>& second) {
  assert(first.size() == second.size());
  double distance = 0;
  for (int i = 0; i < first.size(); ++i ) {
    distance += first[i]*first[i] + second[i]*second[i];
  }
  return sqrt(distance);
}

void traceBack(const vector<vector<double> >& tree, ) {

}

void query(const vector<vector<double> >& tree,
            int begin,
            int end,
            int dimension,
            const vector<double>& q,
            vector<double>& knn
            // int parent,
            // bool left
          ) {
  if (begin > end) return;
  if (begin == end) {
    double divideLine = tree[begin][dimension%tree[0].size()];
    cout << " " << divideLine << endl;
    knn.clear();
    knn.shrink_to_fit();
    double r = euclideanMetric(tree[begin], q);
    knn.push_back(r);
    // traceBack();
    return;
  }
  int mid = (begin+end)/2;
  double divideLine = tree[mid][dimension%tree[0].size()];
  cout << " " << divideLine << endl;
  if (q[dimension%tree[0].size()] <= divideLine) {
    query(tree, begin, mid-1, dimension+1, q, knn);
  } else {
    query(tree, mid+1, end, dimension+1, q, knn);
  }
  return;
}


void printTree(const vector<vector<double> >& data) {
  printHelper(data, 0, data.size()-1,0);
}



vector<vector<double> > randomData(int size_of_data, int dimension) {
  vector<vector<double> > v(size_of_data, vector<double>(dimension, 1));
  for (int i = 0; i < v.size(); ++i) {
    for (int j = 0; j < v[i].size(); ++j) {
      v[i][j] = (double)(rand()%20);
    }
  }
  return v;
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  vector<vector<double> > data = randomData(10, 2);
  printData(data);
  buildTree(data);
  printData(data);
  vector<double> p = {5, 11};
  vector<double> knn;
  query(data, 0, data.size()-1, 0, p, knn);
  printTree(data);
  return 0;
}

// void query(const vector<vector<double> >& tree,
//             int begin,
//             int end,
//             int dimension,
//             const vector<double>& q,
//             vector<double>& knn
//             // int parent,
//             // bool left
//           ) {
