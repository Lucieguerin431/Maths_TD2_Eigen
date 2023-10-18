#include "Polynomial.hpp"

#include <initializer_list>

#include <Eigen/Dense>


Polynomial::Polynomial(const std::initializer_list<double> &list)
	: m_coef(Eigen::VectorXd::Zero(list.size()))
{
	std::copy(list.begin(),list.end(), m_coef.data());
}


double Polynomial::operator()(const double &x) const{
	double b=m_coef(this->degree());
	for (int i=this->degree()-1;i>=0;i--){
		b= b * x + m_coef(i);
	}
	return b;
}


Polynomial Polynomial::polynomialFromRoot(const Eigen::VectorXd &roots){

	return Polynomial();
}


Eigen::VectorXd Polynomial::findRoots(const unsigned int nbIter) const{

  return Eigen::VectorXd();
}


Polynomial Polynomial::derivative() const{

	return Polynomial();
}


Eigen::VectorXd Polynomial::refineRoots(const Eigen::VectorXd &inputRoots, const int nbIter) const {

  return Eigen::VectorXd();
}



// product between 2 polynomials
Polynomial Polynomial::operator*(const Polynomial &p) const {

	Polynomial res(this->degree()+p.degree()+1);

    for(size_t i=0; i<size_t(m_coef.size()); ++i) {
        for(size_t j=0; j<size_t(p.m_coef.size()); ++j) {
            res.m_coef(i + j) += m_coef(i) * p.m_coef(j);
        }
    }

    return res;
}


std::ostream& operator<< (std::ostream& stream, const Polynomial &p){

	bool first_element = true;
	for(int i=p.degree(); i>=0; --i){
		if(std::abs(p.a(i)) > 1.0e-10){
			// sign
			if(p.a(i) < 0) stream << " - ";
			else if(!first_element) stream <<  " + ";
			first_element = false;  // don't print fist sign if it is '+'
			// coef
			if(((std::abs(p.a(i))-1.0) > 1.0e-10) || (i==0)) stream << std::abs(p.a(i));  // don't print coefficients '1' unless it is a scalar
			// power
			switch(i){
				case 0 : break;
				case 1 : stream << "x"; break;
				default : stream << "x^" << i; break;
			}
		}
	}
    return stream;
}