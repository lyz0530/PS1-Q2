//#pragma once
#include "util.h"

RowVectorXd split_line(const string& line)
{
	RowVectorXd v;
	vector<double> vec;

	stringstream s(line);
	string tok;
	while(s >> tok)
	{
		vec.push_back(stod(tok));
	}
	v = Map<VectorXd>(vec.data(), vec.size());
	return v;
}

VectorXd std2eig(const vector<double>& vec)
{
	return Map<const VectorXd>(&vec[0], vec.size());
}

vector<double> eig2std(const VectorXd& vec)
{
       	return vector<double>(vec.data(), vec.data() + vec.size()); 
}
