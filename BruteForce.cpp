#include "KD_Tree.cpp"
#include <limits.h>

int size_of_data = 200;
int dimension = 20;
int n = 50;

void knn(const vector<vector<double> >& data, const vector<double>& p, vector<pair<double, double> >& res) {
  for (int i = 0; i < size_of_data; ++i) {
    double d = euclideanMetric(p, data[i]);
    if (res.back().first > d) {
      res.back().first = d;
      res.back().second = (double)i;
      sort(res.begin(), res.end());
    }
  }
  return;
}



int main(int argc, char const *argv[]) {
  srand(time(NULL));
  vector<vector<double> > data = randomData(size_of_data, dimension);
  Node* root = buildTree(data);
  printData(data);
  printTree(data, root);

  vector<double> p;
  for (int i = 0; i < dimension; ++i) {
    double in = (double)(rand()%20);
    p.push_back(in);
    cout << in << " ";
  }
  cout << endl;

  vector< pair<double, double> > res_bf(n,pair<double, double>(numeric_limits<double>::max() , 0));
  vector< pair<double, Node*> > res_kd(n, pair<double, Node*>(numeric_limits<double>::max() , NULL));
  knn(data, p ,res_bf);
  query(data, root, p, res_kd);
  for (int i = 0; i < res_bf.size(); ++i) {
    cout << "BF" <<res_bf[i].first  << "  [" << res_bf[i].second << "]" << endl;
    cout << "KD" <<res_kd[i].first  << "  [" << res_kd[i].second->index << "]" << endl;
    if (res_bf[i].first != res_kd[i].first || res_bf[i].second != res_kd[i].second->index) {
      cout << "Wrong Answer!!! \n";
      break;
    }
  }
  return 0;
}
