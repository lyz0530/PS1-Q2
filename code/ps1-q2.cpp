#include "Config.h"
#include "PlotFig.h"
#include <iostream>
#include <cassert>
using namespace std;

int main(int argNum, char** args)
{
	string trainX_path;
	string trainY_path;
	if(argNum > 2)
	{
	
		trainX_path = args[1];
		trainY_path = args[2];
	}
	else
	{
		cerr << "Usage: ps1-q2 X_path Y_path" <<endl;
		exit(1);
	}

	/*extract X and Y from data file to memory*/
	Config conf(trainX_path, trainY_path);
	conf.parse();
//	conf.print();

	/*compute theta */
	const double tau = 5;
/*	VectorXd x_query(2);
	x_query << 0.36, -0.77;
	double y;
	y = lwlr(conf.getX(), conf.getY(), x_query, tau);
	cout << "y: " << y << endl;
*/
	/*plot data*/
	const size_t& resolution = 200;
//	PlotFig::plotxy(conf.getX(), conf.getY(), x_query, y); //for one query point
	plot_lwlr(conf.getX(), conf.getY(), tau, resolution); //for grid points
}

