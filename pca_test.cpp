#include <iostream>
#include <fstream>
#include "pca.h"

#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;



int main(int argc, char* argv[])
{
	Eigen::Matrix<float, 10, 2> pca_data_matrix;
	Eigen::Matrix<float, 10, 2> pca_center_matrix;
	pca_data_matrix <<
		2.5, 2.4,
		0.5, 0.7,
		2.2, 2.9,
		1.9, 2.2,
		3.1, 3.0,
		2.3, 2.7,
		2.0, 1.6,
		1.0, 1.1,
		1.5, 1.6,
		1.1, 0.9;


	pca_t<float> pca;
	pca.set_input(pca_data_matrix);
	pca.compute();
	

	std::cout
		<< "Input Matrix:		\n" << pca.get_input_matrix() << std::endl << std::endl
		<< "Centered Matrix:	\n" << pca.get_centered_matrix() << std::endl << std::endl
		<< "Covariance Matrix:	\n" << pca.get_covariance_matrix() << std::endl << std::endl
		<< "Projection Matrix:	\n" << pca.get_projection_matrix() << std::endl << std::endl
		<< "Mean Matrix:		\n" << pca.get_mean() << std::endl << std::endl
		<< "Eigen Values:		\n" << pca.get_eigen_values() << std::endl << std::endl
		<< "Eigen Vectors:		\n" << pca.get_eigen_vectors() << std::endl << std::endl;

	
	const auto& reprojection = pca.reprojection();
	auto error = (pca_data_matrix - reprojection).norm();

	std::cout
		<< "Reprojected Matrix:	\n" << reprojection << std::endl << std::endl
		<< std::fixed
		<< "Error:				\n" << error << std::endl << std::endl;
	
	return EXIT_SUCCESS;
}