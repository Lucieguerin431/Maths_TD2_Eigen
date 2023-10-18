#pragma once

#include <iostream>
#include <fstream>
#include <initializer_list>

#include <Eigen/Dense>


/// \brief very simple polynomial class
class Polynomial {

private :
	Eigen::VectorXd m_coef;

public :

	// constructor with the number of coefficients of the polynomial
	Polynomial(const size_t size) : m_coef(Eigen::VectorXd::Zero(size)) {}

	// constructor with the list of coeff of the polynomial
	Polynomial(const std::initializer_list<double> &list);

	// other constructors and destructor
	Polynomial(const Eigen::VectorXd &coef) : m_coef(coef) {}
	Polynomial()  = default;
	~Polynomial() = default;

	// getters, setters
	inline int degree() const {return m_coef.size()-1;}

	// polynomial coefficient setter / getter
	inline double &a(const size_t &index) {return m_coef(index);}
	inline const double &a(const size_t &index) const {return m_coef(index);}

	// evaluate the polynomial at value 'x'
	double operator()(const double &x) const;

	// arithmetic operators over polynomials
	Polynomial operator+(const Polynomial &p) const {return Polynomial(m_coef + p.m_coef);}
	Polynomial operator-(const Polynomial &p) const {return Polynomial(m_coef - p.m_coef);}
	Polynomial operator-() const {return Polynomial(-m_coef);}
	Polynomial operator*(const double &value) const {return Polynomial(m_coef*value);}
	Polynomial operator*(const Polynomial &p) const;
	friend Polynomial operator*(const double &value, const Polynomial &p) {return Polynomial(p.m_coef*value);}

	// polynomial tools
	Polynomial derivative() const;
	static Polynomial polynomialFromRoot(const Eigen::VectorXd &roots);
	Eigen::VectorXd findRoots(const unsigned int nbIter = 10) const;
	Eigen::VectorXd refineRoots(const Eigen::VectorXd &roots, const int nbIter) const;

	// print
	friend std::ostream& operator<< (std::ostream& stream, const Polynomial &p);

};

