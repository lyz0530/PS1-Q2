#include <Eigen/Dense>
#include <vector>
using namespace std;
using namespace Eigen;

RowVectorXd split_line(const string& line);
VectorXd std2eig(const vector<double>&);
vector<double> eig2std(const VectorXd& vec);
