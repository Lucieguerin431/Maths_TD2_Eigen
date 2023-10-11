#include <iostream>
#include <iomanip>
#include <functional>
#include <cmath>
#include <numbers>

#include "DualNumber.hpp"

double dichotomy(std::function<double(const double&)> &f, 
                  double lowerBound, 
                  double upperBound, 
                  const unsigned int nbIterations){
    int i=0;
    for (int i=0;i<nbIterations;i++){
        double c=(lowerBound+upperBound)/2;
        if (f(lowerBound)*f(c)<0){
            upperBound=c;
        }
        else lowerBound=c;
    }
    
    return (lowerBound + upperBound)*0.5;
}

unsigned int dichotomyNbIteration(const double &lowerBound, const double &upperBound, const double &precision){
    return 42;
}


double Newton(std::function<double(const double&)> &f, 
              std::function<double(const double&)> &derivative, 
              double &input,
              const double &threshold,
              int &maxIterations) // ref just to get back the number of iterations
{
    double x=input;
    unsigned int nbIterations = 0;
    while(f(x)<threshold){
        x=x-f(x)/derivative(x);
        nbIterations++;
        if(nbIterations>maxIterations)
            break;
    }
    
    return x;
}


void mainDichotomy()
{
    std::function<double(const double&)> f = [](const double&x){return std::cos(x) - 2*x;};
    const double precision = 1.0e-7;
    const unsigned int nbIterations = dichotomyNbIteration(-std::numbers::pi_v<double>,std::numbers::pi_v<double>,precision);

    std::cout << "requested precision  : " << precision << std::endl;
    std::cout << "suggested iterations : " << nbIterations << std::endl;
    double root = dichotomy(f,-std::numbers::pi_v<double>,std::numbers::pi_v<double>,nbIterations);
    std::cout << "dichotomy            : " << root << std::endl;
    std::cout << "f(root)              : " << f(root) << std::endl << std::endl;
}

void mainNewton()
{
    std::function<double(const double&)> f, derivative;
    // f = [](const double&x){return ((std::exp(x)-1.0)/(std::exp(x)+1.0)) + (3.0/4.0) ;};
    // derivative = [](const double&x){return 2.0*std::exp(x) / ((std::exp(x)+1.0)*(std::exp(x)+1.0)) ;};
    f = [](const double&x){return cos(x) - 2*x;};
    derivative = [](const double&x){return -sin(x) - 2;};

    const double precision = 1.0e-7;
    int maxIterations = 20;
    double x = 2;

    std::cout << "requested precision  : " << precision << std::endl;
    std::cout << "input estimattion    : " << x << std::endl;
    double root = Newton(f,derivative,x,precision,maxIterations);
    std::cout << "Newton               : " << root << std::endl;
    std::cout << "f(root)              : " << f(root) << std::endl;
    std::cout << "nb iterations        : " << maxIterations << std::endl;
}
DualNumber<double> NewtonDual(std::function<DualNumber<double>(const DualNumber<double>&)> &f, 
              const DualNumber<double> &input,
              const double &threshold,
              const int &maxIterations,
              int &nbIterationsToConverge){

    DualNumber<double> x = input;

    unsigned int nbIterations = 0;
    while(std::abs(f(x).real()) > threshold){
        DualNumber<double> value = f(x);
        x = x - ( value.real() / value.dual() );
        nbIterations++;
        if(nbIterations > maxIterations)
            break;
    }

    // just for information
    nbIterationsToConverge = nbIterations; 

    return x;
}

void mainNewtonDual()
{
    std::function<DualNumber<double>(const DualNumber<double>&)> f;
    // f = [](const DualNumber<double>&x){return ((DualNumber<double>::exp(x)-1.0)/(DualNumber<double>::exp(x)+1.0)) + (3.0/4.0) ;};
    f = [](const DualNumber<double>&x){return DualNumber<double>::cos(x) - 2*x;};

    const double precision = 1.0e-7;
    int maxIterations = 20;
    int nbIterationsToConverge = 0;
    const DualNumber<double> x(0.0,1.0);

    std::cout << "requested precision  : " << precision << std::endl;
    std::cout << "input estimation     : " << x.real() << std::endl;
    DualNumber<double> root = NewtonDual(f,x,precision,maxIterations,nbIterationsToConverge);
    std::cout << "Newton               : " << root.real() << std::endl;
    std::cout << "f(root)              : " << f(root).real() << std::endl;
    std::cout << "nb iterations        : " << nbIterationsToConverge << std::endl << std::endl;
}
int main()
{
    mainDichotomy();

    mainNewton();
        mainNewtonDual();
    return 0;
}

