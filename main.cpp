#include <iostream>
#include <iomanip>      // std::setprecision
#include <Eigen/Dense>
#include <chrono>

double dot_product(const Eigen::VectorXd &v1, const Eigen::VectorXd &v2){
    double resultat=0;
    for (size_t i = 0; i < v1.size(); i++)
    {
        resultat+=v1(i)*v2(i);
    }
    return resultat;
}

int main()
{
  // build a seed
  unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
  srand(seed);

  // vectors dynamic size
  Eigen::VectorXd v1(5);
  v1 << 1, 2, 3, 4, 5;
  v1(2) = 42;
  std::cout << "v1 size : " << v1.size() << std::endl;
  std::cout << "v1[2]   : " << v1(2) << std::endl;
  std::cout << "v1 : " << v1.transpose() << std::endl << std::endl;

  Eigen::VectorXd v2(5);
  v2 << 2, 9, 3, 8, 5;
  std::cout << "v1 size : " << v1.size() << std::endl;
  std::cout << "v1[2]   : " << v1(2) << std::endl;
  std::cout << "v1 : " << v1.transpose() << std::endl << std::endl;
    // produit sca
    std::cout << "produit scalaire: " << dot_product(v1,v2) << std::endl;
    std::cout << "produit scalaire corrigé: " << v1.dot(v2) << std::endl;
  // vector static size
  Eigen::Vector4f v3 = Eigen::Vector4f::Zero();


  std::cout << "v3 : " << v3.transpose() << std::endl << std::endl;

  v3 = Eigen::Vector4f::Ones();
  std::cout << "v3 : " << v3.transpose() << std::endl << std::endl;

  Eigen::Vector4f v4 = Eigen::Vector4f::Random();
  std::cout << "v4 : " << v4.transpose() << std::endl << std::endl;
  v4 = v4 + v3;
  std::cout << "v4 : " << v4.transpose() << std::endl << std::endl;

  // matrices dynamic size
  Eigen::MatrixXd A = Eigen::MatrixXd::Random(3,4);
  std::cout << "A size : " << A.rows() << " x " << A.cols() << std::endl;
  std::cout << "A(1,2) : " << A(1,2) << std::endl;
  std::cout << "A :\n" << A << std::endl << std::endl;

  // matrices static size
  Eigen::Matrix4d B = Eigen::Matrix4d::Random();  
  std::cout << "B :\n" << B << std::endl << std::endl;

  // time computation
  const unsigned int iter = 10000;
  Eigen::MatrixXd C(3,4);
  auto start = std::chrono::steady_clock::now();
  for(unsigned int i=0; i<iter; ++i)
      C = A*B;
  auto stop = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = stop-start;
  std::cout << "temps calcul du produit matriciel: " << elapsed_seconds.count() << " s" << std::endl;
  
//   //time machin
//   const unsigned int iter = 10000;
//     auto start = std :: chrono :: steady_clock :: now ();
//     for ( unsigned int i =0; i < iter ; ++ i )
//     dot_product();
//     auto end = std :: chrono :: steady_clock :: now ();
//     std :: chrono :: duration <double > elapsed_seconds = end - start ;
//     std :: cout << " temps fonction : " << elapsed_seconds . count () << " s" << std :: endl ;

  
  auto start2 = std::chrono::steady_clock::now();
  for(unsigned int i=0; i<iter; ++i)
      dot_product(v1,v2);
  auto end2 = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds2 = end2-start2;
  std::cout << "temps calcul du produit matriciel: " << elapsed_seconds2.count() << " s" << std::endl;
  
  // print samples
  std::cout << "A + 2*A :\n" << A + 2*A << std::endl << std::endl;
  std::cout << "A * B :\n" << A * B << std::endl << std::endl;





  return 0;
}



// linux  : g++ -Wall -O2 -I /usr/include/eigen3 eigen_sample.cpp -o eigen_sample
// mac    : g++ -Wall -O2 -Wno-unknown-warning-option -std=c++11 -I /usr/local/include/eigen3 eigen_sample.cpp -o eigen_sample
// mac M1 : g++ -Wall -O2 -I /opt/homebrew/include/eigen3 eigen_sample.cpp -o eigen_sample

