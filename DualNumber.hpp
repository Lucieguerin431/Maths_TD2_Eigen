#pragma once

#include <fstream>
#include <cmath>

template <typename T>
class DualNumber{

	private : 
		T m_real;
		T m_dual;

	public :

		// default constructor
		DualNumber() = default;

		// constructor by value
		DualNumber(const T& real, const T &dual) : m_real(real), m_dual(dual) {};

		// convert a scalar into a dual number		
		DualNumber(const T &value) : m_real(value), m_dual(static_cast<T>(0)) {}; 

		// copy constructor
		DualNumber(const DualNumber &dn) = default;

		// destructor
		~DualNumber() = default;

		// getter / setter
		inline T & real() {return m_real;};
		inline T & dual() {return m_dual;};
		inline const T & real() const {return m_real;};
		inline const T & dual() const {return m_dual;};


		// some operators
		DualNumber operator*(const DualNumber &dn) const;
		DualNumber operator+(const DualNumber &dn) const;
		DualNumber operator-(const DualNumber &dn) const;
		DualNumber operator/(const DualNumber &dn) const;
		inline DualNumber operator/(const T &value) const {return DualNumber(m_real / value, m_dual/value);}
		inline friend DualNumber operator*(const T &value, const DualNumber &dn) {return dn * value;}
		inline friend DualNumber operator/(const T &value, const DualNumber &dn) {return DualNumber(value)/dn;};
		inline friend DualNumber operator-(const DualNumber &dn) {return DualNumber(-dn.m_real,-dn.m_dual);}; // unary minus


		static DualNumber sin(const DualNumber & dn);	
		static DualNumber cos(const DualNumber & dn);
		static DualNumber tan(const DualNumber & dn);
		static DualNumber exp(const DualNumber & dn);
		static DualNumber log(const DualNumber & dn);
		static DualNumber abs(const DualNumber & dn);
		static DualNumber pow(const DualNumber & dn, const T &n);
		static DualNumber sqrt(const DualNumber & dn);

		template<typename U>
        friend std::ostream& operator<< (std::ostream& stream, const DualNumber<U> &dn);
};


template<typename T>
std::ostream& operator<< (std::ostream& stream, const DualNumber<T> &dn){
	stream << "(" << dn.m_real << ", " << dn.m_dual << ")";
    return stream;
}


template <typename T>
DualNumber<T> DualNumber<T>::operator*(const DualNumber<T> &dn) const {
	return DualNumber<T>(this->m_real * dn.m_real, this->m_dual*dn.m_real + this->m_real*dn.m_dual);
}

template <typename T>
DualNumber<T> DualNumber<T>::operator+(const DualNumber<T> &dn) const {
    return DualNumber<T>(this->m_real+dn.m_real, this->m_dual+dn.m_dual);
}

template <typename T>
DualNumber<T> DualNumber<T>::operator-(const DualNumber<T> &dn) const {
    return DualNumber<T>(this->m_real-dn.m_real, this->m_dual-dn.m_dual);
}

template <typename T>
DualNumber<T> DualNumber<T>::operator/(const DualNumber<T> &dn) const {
	return DualNumber<T>(this->m_real / dn.m_real, this->m_dual/dn.m_real - (this->m_real/dn.m_dual) / (dn.m_real*dn.m_real));
}

template <typename T>
DualNumber<T> DualNumber<T>::sin(const DualNumber<T> & dn){
	return DualNumber<T>(std::sin(dn.m_real),dn.m_dual*std::cos(dn.m_real));
}

template <typename T>
DualNumber<T> DualNumber<T>::cos(const DualNumber<T> & dn){
	return DualNumber<T>(std::cos(dn.m_real),dn.m_dual*std::sin(dn.m_real));
}

template <typename T>
DualNumber<T> DualNumber<T>::tan(const DualNumber<T> & dn){
	return DualNumber<T>::sin(dn.m_real+dn.m_dual),dn.m_dual*DualNumber<T>::sin(dn.m_real);
}

template <typename T>
DualNumber<T> DualNumber<T>::exp(const DualNumber<T> & dn){
	return DualNumber<T>(std::exp(dn.m_real),dn.m_dual*std::exp(dn.m_real));
}

template <typename T>
DualNumber<T> DualNumber<T>::log(const DualNumber<T> & dn){
	return DualNumber<T>(std::log(dn.m_real),dn.m_dual/dn.m_real);
}

template <typename T>
DualNumber<T> DualNumber<T>::abs(const DualNumber<T> & dn){
    int sign;
    if (dn.m_real >=0)
        sign=1;
    else 
        sign=-1;
    
    return DualNumber<T>(std::abs(dn.m_real),dn.m_dual*sign);
}

template <typename T>
DualNumber<T> DualNumber<T>::pow(const DualNumber<T> & dn, const T &n){
	return DualNumber<T>(std::pow(dn.m_real,n),n*dn.m_dual*std::pow(dn.m_real,n-1));
}

template <typename T>
DualNumber<T> DualNumber<T>::sqrt(const DualNumber<T> & dn){
	return DualNumber<T>(std::sqrt(dn.m_real),dn.m_dual/(2*std::sqrt(dn.m_real)));
}
