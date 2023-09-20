#include <iostream>
#include <iomanip>      // std::setprecision
#include <cstdlib>
#include <Eigen/Dense>
#include <ctime>
#include <cassert>

using namespace Eigen;


double dotProduct(const VectorXd &a, const VectorXd &b){

  assert(a.size() == b.size() && "dotProudct: error: the 2 vectors should have the same size");

  double result = 0.0;
  for(unsigned int i=0; i<a.size(); ++i)
    result += a(i)*b(i);	
	
  return result;	
}

MatrixXd matrixProduct(const MatrixXd &A, const MatrixXd B)
{
  assert(A.cols() == B.rows());
	
  MatrixXd C = MatrixXd::Zero(A.rows(),B.cols());
  
  for(unsigned int i=0; i<C.rows(); ++i)
    for(unsigned int j=0; j<C.cols(); ++j)
      C(i,j) = dotProduct(A.row(i),B.col(j));

  return C;
}

int main()
{
  srand(time(0));

  MatrixXd A = MatrixXd::Random(5,5);	
  MatrixXd B = MatrixXd::Random(5,5);	
  
  std::cout << "A :\n" << A << std::endl;
  std::cout << "B :\n" << B << std::endl;
  
  std::cout << "mine  : \n" << matrixProduct(A,B) << std::endl;
  std::cout << "eigen : \n " << A*B << std::endl;	
	
  return 0;
}



// g++ -Wall -I ~/eigen/  matrixProduct.cpp 
