#include <stdio.h>
#include <iostream>
#include <math.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>


class handler {
  cv::Mat3b _image;
  cv::Mat3b _image_alg;
  std::string _image_path;
  int row, col;
  
  
  cv::Vec3b black; 
public: 
  handler(std::string);
  ~handler();
  
  void display_image();
  void display_results(cv::Mat3b);
  cv::Mat3b find_region(int, int);
  void find_boarder();
  
private: 
  int norm_calculation(cv::Vec3b, cv::Vec3b);
  void flood_fill(cv::Mat3b, cv::Mat3b, int, int, int, int);
  
};