#include <iostream>

#include "Polynomial.hpp"

// g++ -Wall -O2 -std=c++11 -I /usr/include/eigen3 main.cpp Polynomial.cpp -o poly

int main()
{
	std::cout << std::endl << "define polynomial:" << std::endl;
	Polynomial p({3,2,1});
	std::cout << "p(x) = " << p << std::endl;

	std::cout << std::endl << "operators:" << std::endl;
	std::cout << " -p(x)  = " << -p << std::endl;
	std::cout << "3.p(x)  = " << 3*p << std::endl;
	// std::cout << "  p'(x) = " << p.derivative() << std::endl; 
	std::cout << "  p.p   = " << p*p << std::endl;
	
	std::cout << std::endl << "estimator:" << std::endl;
	std::cout << "p(0)  = " << p(0) << std::endl;
	std::cout << "p(1)  = " << p(1) << std::endl;
	std::cout << "p(-2) = " << p(-2) << std::endl;

	// std::cout << std::endl << "solver:" << std::endl;
	// Eigen::VectorXd roots(3);
	// roots << 1,2,3;
	// std::cout << "roots = " << roots.transpose() << std::endl;

	// Polynomial q = Polynomial::polynomialFromRoot(roots);
	// std::cout << "q(x) = " << q << std::endl;
	// for(unsigned int i=0; i<roots.size(); ++i)
	// 	std::cout << "q(" << roots(i) << ") = "  << q(roots(i)) << std::endl;

	// Eigen::VectorXd primaryRoots = q.findRoots(5*roots.size());
	// std::cout << "primary roots : " << primaryRoots.transpose() << std::endl;
	// std::cout << "refined roots : " << q.refineRoots(primaryRoots,20).transpose() << std::endl;

	return 0;
}