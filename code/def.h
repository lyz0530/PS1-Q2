#include <cassert>
#include <iostream>
#include <limits>
#include <vector>
#include <functional>
using namespace std;

#define MYASSERT(x)						\
	if(!(x))						\
	{							\
		cerr << "Assertion failed: " << #x << endl;	\
		cerr << "\tFile: " << __FILE__ << endl;		\
		cerr << "\tLine: " << __LINE__ << endl;		\
		cerr << "\tFunc: " << __func__ << endl;		\
		exit(1);					\
	}								
