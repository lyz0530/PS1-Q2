#define _USE_MATH_DEFINES
#include <iostream>
#include "util.h"
#include "matplotlibcpp.h"
#include "Comp.h"
#include <map>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;
namespace plt = matplotlibcpp;

class PlotFig
{
public:

	void plotxy(const MatrixXd& trainX, const VectorXd& trainY, const VectorXd& x_query, const double& y);
	void plotxy(const MatrixXd& gridX, const vector<double>& gridY);
	MatrixXd genGrid(const map<string, double>& gridInfo, const size_t& res);
};

void plot_lwlr(const MatrixXd& trainX, const VectorXd& trainY, const double& tau, const size_t& res)
{
	const size_t num = trainX.rows();
        const size_t dim = trainX.cols();
	
	const size_t num_grid = res * res;
	const map<string, double> gridInfo = {{"x1_db", -1}, {"x1_range", 2}, {"x2_db", -1}, {"x2_range", 2}};

	PlotFig* fig = new PlotFig();
	MatrixXd grid(num_grid, dim);
        grid = fig->genGrid(gridInfo, res);

	VectorXd grid_x_one(dim);
//	vector<double> grid_y(num_grid);
	vector<double> grid_y;
	double grid_y_one;

	/*compute y of every grid point*/
	for(size_t i = 0; i < num_grid; ++i)
	{
		grid_x_one = grid.row(i);
		grid_y_one = lwlr(trainX, trainY, grid_x_one, tau);
		if(grid_y_one > 0.5)
		{
			grid_y_one = 1;

		}
		else
		{
			grid_y_one = 0;

		}
		grid_y.push_back(grid_y_one);
//		cout << grid_y_one << endl;
	}
//	fig->plotxy(trainX, trainY);
//	cout << grid_y[0] << endl;
	fig->plotxy(grid, grid_y);

	delete fig;

}

/*generate grid points*/
MatrixXd PlotFig::genGrid(const map<string, double>& gridInfo, const size_t& res)
{
	const size_t num = res * res;
	const size_t dim = 2;
	MatrixXd grid(num, dim); 

	size_t cou_x1 = 1;
	size_t cou_x2 = 1; //count grid points number
	const double del_x1 = gridInfo.at("x1_range")/(res + 1);
	const double del_x2 = gridInfo.at("x2_range")/(res + 1);
	
	for(size_t i = 0; i < num - 1;)  //generate row by row
	{
		cout << "i: " << i << endl;
                cou_x2 = 1; //reset

		grid(i, 0) = gridInfo.at("x1_db") + cou_x1 * del_x1; // x1 of the grid point
		grid(i, 1) = gridInfo.at("x2_db") + cou_x2 * del_x2; // x2 of the grid point
//		cout << "grid_x1: " << grid(i, 0) << " grid_x2: " << grid(i, 1) << endl;
		size_t old_i = i;
		while(cou_x2 < res)
		{
			++i;
			++cou_x2;
			grid(i, 0) = grid(old_i, 0); // x1 of the grid point
			grid(i, 1) = gridInfo.at("x2_db") + cou_x2 * del_x2; // x2 of the grid point
//                        cout << "grid_x1: " << grid(i, 0) << " grid_x2: " << grid(i, 1) << endl;

//			cout << "cou: " << cou_x2 << endl;
		}
		++cou_x1;
		++i;
	}

	return grid;
}

/*plot scattering figure*/
void PlotFig::plotxy(const MatrixXd& trainX, const VectorXd& trainY, const VectorXd& x_query, const double& y)
{
        const size_t num = trainX.rows();
        const size_t dim = trainX.cols();
	
	vector<double> t1_x1, t1_x2, t2_x1, t2_x2;
	vector<double> x_query_x1;
        x_query_x1.push_back(x_query(0));
	vector<double> x_query_x2;
        x_query_x2.push_back(x_query(1));

	for(size_t i = 0; i < num; ++i)
	{
		if(trainY(i) == 0)
		{
			t1_x1.push_back(trainX(i, 0));
			t1_x2.push_back(trainX(i, 1));
		}
		else
		{
			t2_x1.push_back(trainX(i, 0));
			t2_x2.push_back(trainX(i, 1));
		}
	}
    // Set the size of output image = 1200x780 pixels
        plt::figure_size(1200, 780);

    // PlotFig points from given x and y data. Color is selected automatically.
	plt::plot(t1_x1, t1_x2, "b*");
        plt::plot(t2_x1, t2_x2, "ro");
	
	cout << "x_querey: " << x_query.transpose() << endl;
	cout << "y: " << y << endl;
    // Plot x_query and corresponding predictation y
    	if(y <= 0.5) //t1 type
		plt::plot(x_query_x1, x_query_x2, "bx");
	else
		plt::plot(x_query_x1, x_query_x2, "rx");

    // Set x-axis to interval [-1,1]
        plt::xlim(-1, 1);

    // Add graph title
        plt::title("Training Data figure");

    // Set legend
    	plt::named_plot("red=1\n blue=0", x_query_x1, x_query_x2);

    // Enable legend.
        plt::legend();
	
    // save figure
    	const char* filename = "./ps1-q2-one_query.png";
    	std::cout << "Saving result to " << filename << std::endl;;
    	plt::save(filename);

}

/*reload plotxy()*/
void PlotFig::plotxy(const MatrixXd& gridX, const vector<double>& gridY)
{
        const size_t num = gridX.rows();
        const size_t dim = gridX.cols();
	
	vector<double> t1_x1, t1_x2, t2_x1, t2_x2; //t1: blue; t2:red.

	for(size_t i = 0; i < num; ++i)
	{
		if(gridY[i] == 0)
		{
			t1_x1.push_back(gridX(i, 0));
			t1_x2.push_back(gridX(i, 1));
		}
		else
		{
			t2_x1.push_back(gridX(i, 0));
			t2_x2.push_back(gridX(i, 1));
		}
//		cout << gridY[i] << endl;
//		cout << "x1: " << gridX(i, 0) << " x2: " << gridX(i, 1) << endl;
	}
    // Set the size of output image = 1200x780 pixels
        plt::figure_size(1200, 780);

    // PlotFig points from given x and y data. Color is selected automatically.
	plt::plot(t1_x1, t1_x2, "b*");
        plt::plot(t2_x1, t2_x2, "ro");
	

    // Set x-axis to interval [-1,1]
        plt::xlim(-1, 1);

    // Add graph title
        plt::title("Training Data figure");

    // Set legend
//    	plt::named_plot("red=1\n blue=0", t1_x1, t1_x2);

    // Enable legend.
        plt::legend();
	
    // save figure
    	const char* filename = "./ps1-q2-grid.png";
    	std::cout << "Saving result to " << filename << std::endl;;
    	plt::save(filename);

}
