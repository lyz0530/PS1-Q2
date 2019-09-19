#include <Eigen/Dense>
#include <vector>
using namespace std;
using namespace Eigen;

class Comp
{
public:

	VectorXd theta;
		
	double weight(const VectorXd& x_query, const VectorXd& x_one, double toa);

	double sigma(const VectorXd& x_one);

	double Dii(const double& w, const double& h);

};

double lwlr(const MatrixXd& trainX, const VectorXd& trainY, const VectorXd& x_query, const double& tau);
