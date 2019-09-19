#include <string>
#include <vector>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

class Config
{
	string	_x_path;
	string	_y_path;
	
	MatrixXd _x;
	VectorXd _y;

public:
	explicit Config(string trainX_path, string trainY_path);
	

	void parse();

	void print();
	
	MatrixXd getX();
	VectorXd getY();
};
