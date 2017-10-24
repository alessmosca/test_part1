#include <stdio.h>
#include <iostream>
#include <math.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include "opencv2/imgproc/imgproc.hpp"


class handler {

public: 
  cv::Mat3b _image;      // variable used for storing the loaded image 
  cv::Mat3b _image_alg;  // variable used for the algorithm process 
  std::string _image_path; // path to the image loaded
  int row, col;  // dimensions of the loaded image
  int x_input, y_input;
  double threshold;
  
  handler(std::string);
  ~handler();
  
  
  
  void display_image();
  void display_results(cv::Mat3b, std::string);
  void find_region(int, int);
  void find_boarder();
  void save_image();
  
private: 
  
  cv::Mat3b _black_image;   // supported matrix
  cv::Vec3b black;          // supported vector
  cv::Vec3b white;          // supported vector
  int norm_calculation(cv::Vec3b, cv::Vec3b);
  void flood_fill(cv::Mat3b, cv::Mat3b, int, int, int, int);
  void find_perimeter(cv::Mat3b , cv::Mat3b, int, int, int, int,cv::Mat3b*);
};