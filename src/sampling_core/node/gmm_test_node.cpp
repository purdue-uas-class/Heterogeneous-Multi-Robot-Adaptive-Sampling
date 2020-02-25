#include <ros/ros.h>
#include <stdlib.h> /* srand, rand */
#include <iostream>

#include "sampling_core/gmm.h"

float RandomFloat(float a, float b) {
  float random = ((float)rand()) / (float)RAND_MAX;
  float diff = b - a;
  float r = random * diff;
  return a + r;
}

int main(int argc, char **argv) {
  ros::init(argc, argv, "centralized_sampling");
  const int num_gau = 2;
  const double eps = 0.1;
  const int max_iteration = 100;
  float a = 3;
  float b = 10;
  Eigen::VectorXd samples(1000);
  for (int i = 0; i < 1000; ++i) {
    samples(i) = RandomFloat(a, b);
  }
  sampling::GMM_CV::GaussianMixtureModel gmm(num_gau, max_iteration, eps);
  gmm.Train(samples);
  Eigen::MatrixXd means = gmm.GetMeans();
  for (int i = 0; i < means.rows(); ++i) {
    for (int j = 0; j < means.cols(); ++j) {
      std::cout << means(i, j) << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
