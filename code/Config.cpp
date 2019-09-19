//#pragma once
#include <string>
#include "Config.h"
#include "util.h"
#include "def.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
using namespace std;
using namespace Eigen;

//constructor
Config::Config(string trainX_path, string trainY_path) : _x_path(trainX_path), _y_path(trainY_path){}

//parse the data path and get the train set
void Config::parse()
{
	ifstream x_f; //for trainX
	ifstream y_f; //for trainY
	x_f.open(_x_path);
	y_f.open(_y_path);
	MYASSERT(x_f.is_open() && !x_f.fail());
	MYASSERT(y_f.is_open() && !y_f.fail());
	string x_line;
	string y_line;
	vector<RowVectorXd> tmp_RowVec; //Vector in Vector constructs 2D matrix
	vector<double> y;
	
	while(getline(x_f, x_line))
	{
		VectorXd v_row = split_line(x_line);
		tmp_RowVec.push_back(v_row);
	}
	x_f.close();
	if(!tmp_RowVec.empty())
	{
		const size_t dim = tmp_RowVec[0].size();
		MatrixXd trainX(tmp_RowVec.size(), dim);
		for (size_t i = 0; i < tmp_RowVec.size(); ++i)
		{
			if((size_t)tmp_RowVec[i].size() != dim)
			{
				cerr << "Rows' dimension in data file mismatchs!" << endl;
				exit(1);
			}
			trainX.row(i) = tmp_RowVec[i];
		}
		_x = trainX;
	}
	else
	{
		cerr << "Empty matrix in file " << _x_path << endl;
		exit(1);
	}

	while(getline(y_f, y_line))
	{
		double tmp_y;
		stringstream ss(y_line);
		ss >> tmp_y;
		y.push_back(tmp_y);
	}

	_y  = std2eig(y);

	y_f.close();
}

//print the train data
void Config::print()
{
	cout << "Train X path: " << _x_path << endl;
	cout << "Train Y path: " << _y_path << endl;
	const size_t _x_dim = _x.cols(); //dimensions of X
	const size_t _x_num = _x.rows(); //# of train data
	cout << setiosflags(ios::right);
	for(size_t i = 0; i < _x_dim; ++i)
		cout << setw(12) << "x" << i+1;
	cout << setw(6) << "y" << endl;
	for(size_t i = 0; i < _x_num; ++i)
	{
		for(size_t j = 0; j < _x_dim; ++j)
		{
			cout << setw(13) << _x(i,j);

		}
		cout << setw(6) << _y[i] << endl;
	}
}

MatrixXd Config::getX()
{
	return _x;
}

VectorXd Config::getY()
{
	return _y;
}
