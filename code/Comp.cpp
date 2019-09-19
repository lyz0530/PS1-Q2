#include "Comp.h"
#include "util.h"
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;
using namespace Eigen;

/*weight function*/
double Comp::weight(const VectorXd& x_query, const VectorXd& x_one, double toa)
{
	return exp(-((x_query-x_one).squaredNorm())/(2*toa*toa));
}

/*sigma function*/
double Comp::sigma(const VectorXd& x_one)
{
	return 1.0/(1+exp(-(theta.transpose())*x_one));
}

/*diag D*/
double Comp::Dii(const double& w, const double& h)
{
	return (-w*h*(1-h));
}

double lwlr(const MatrixXd& trainX, const VectorXd& trainY, const VectorXd& x_query, const double& tau)
{
	Comp* comp = new Comp();
	double w;
        double h;
        double D_ii;
        double Zi;
        const double lambda = 0.0001;

	const size_t num = trainX.rows();
        const size_t dim = trainX.cols();
	
	const double eps = 1e-6;
        const double theta_init = 1;
	
	double y_old;
        double y_new;
        double error_y;
        VectorXd theta_old;
        comp->theta = theta_init * MatrixXd::Ones(dim, 1);
        VectorXd x_one(dim);
        VectorXd Z(num);
        vector<double> Z_tmp;
        MatrixXd D = MatrixXd::Identity(num, num);
	
	for(size_t i = 0; i < num; ++i)
        {
                x_one = trainX.row(i);
                w = comp->weight(x_query, x_one, tau);
                h = comp->sigma(x_one);
                Zi = w*(trainY[i] - h);
                Z_tmp.push_back(Zi);
                D_ii = comp->Dii(w, h);
                D(i, i) = D_ii;
        }

        Z = std2eig(Z_tmp);
        const MatrixXd& trainX_T = trainX.transpose();
	
	do
        {
                y_old = comp->sigma(x_query);
                comp->theta = comp->theta - ((trainX_T * D * trainX - lambda * MatrixXd::Identity(dim, dim)).inverse()) * (trainX_T * Z - lambda * comp->theta);
                y_new = comp->sigma(x_query);
                error_y = abs(y_old - y_new);
//                cout << "theta is: " << comp->theta.transpose() << endl;
        }while(error_y > eps);

//	cout << "theta converges to: " << comp->theta.transpose() << endl;
	double y = comp->sigma(x_query);
	delete comp;
	
	return y;
}

