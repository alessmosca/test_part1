#include <handler.hpp>

handler::handler(std::__cxx11::string input)
{
  _image_path = input;
   _image = cv::imread(_image_path,CV_LOAD_IMAGE_COLOR);
  _image_alg = _image.clone();
  black.zeros();
  row = _image.rows;
  col = _image.cols;
  _black_image.zeros(row, col);
  
}

handler::~handler()
{

}

/**
 * Function for displaying the original image loaded
 */

void handler::display_image()
{ 
  cv::namedWindow("Input Image", CV_WINDOW_AUTOSIZE);
  cv::imshow("Input Image", _image);
  cv::waitKey(0);
}

/**
 * Function for desplaying the result 
 */

void handler::display_results(cv::Mat3b image)
{
  cv::imshow("Result Image", image);
  cv::waitKey(0);
}

/**
 * Function for running the algorithm for finding the boarder from the output of the find_region function  
 */
void handler::find_boarder()
{
}

/**
 * Function for running the algorithm for finding the region 
 */
cv::Mat3b handler::find_region(int x, int y)
{
  cv::Mat3b temp = _image.clone();
  flood_fill(_image_alg, temp, x, y, row, col);
  for(int i=0; i< row; i++){
    for(int j=0; j<col; j++){
      cv::Vec3b _bgr_image = _image_alg.at<cv::Vec3b>(i,j);
      cv::Vec3b _bgr_temp = temp.at<cv::Vec3b>(i,j);
      if(norm_calculation(_bgr_temp, black) != 0){
	_image_alg.at<cv::Vec3b>(i,j) = black;
      }
    }
  }
  
  display_results(_image_alg);
  return _image_alg;
}

/**
 * this function is used in order to define a metric for the comparison between the color of the pixel
 * 
 */
int handler::norm_calculation(cv::Vec3b a, cv::Vec3b b)
{
return sqrt(pow((int)a[0] - (int)b[0],2) + pow((int)a[1] - (int)b[1],2) + pow((int)a[2] - (int)b[2],2));
}

/**
 * The flood_fill function lets to recognize in the images region similar
 */
void handler::flood_fill(cv::Mat3b original, cv::Mat3b copy, int x, int y, int row_max, int col_max)
{
  cv::Vec3b _bgr_original = original.at<cv::Vec3b>(x,y);
  cv::Vec3b _bgr_copy = copy.at<cv::Vec3b>(x,y);
  
  if(this->norm_calculation(black,_bgr_copy) == 0){
    return;
  }
  copy.at<cv::Vec3b>(x,y) = black;
  if(x+1 < row_max){
    if(this->norm_calculation(_bgr_original, original.at<cv::Vec3b>(x+1,y)) == 0){
      flood_fill(original, copy, x+1, y, row_max, col_max);
    }
  }
  if(x-1 >= 0){
    if(this->norm_calculation(_bgr_original, original.at<cv::Vec3b>(x-1,y)) == 0){
    
      flood_fill(original, copy, x-1, y, row_max, col_max);
    }
  }
  if(y+1 < col_max){
    if(this->norm_calculation(_bgr_original, original.at<cv::Vec3b>(x,y+1)) == 0){
    
      flood_fill(original, copy, x, y+1, row_max, col_max);
    }
  }
  if(y-1 >= 0){
    if(this->norm_calculation(_bgr_original, original.at<cv::Vec3b>(x,y-1)) == 0){
    
      flood_fill(original, copy, x, y-1, row_max, col_max);
    }
  }

}


void handler::save_image()
{
  cv::imwrite( "image_test.png", _image_alg);
}
