#include <handler.hpp>

handler::handler(std::__cxx11::string input)
{
  _image_path = input;
  _image = cv::imread(_image_path,CV_LOAD_IMAGE_COLOR);
  _image_alg = _image.clone();
  black.zeros();
  white[0] = 255;
  white[1] = 255;
  white[2] = 255;
  std::cout << white << std::endl;
  row = _image.rows;
  col = _image.cols;
  _black_image.zeros(row, col);
  threshold = .0;
  
}

handler::~handler()
{

}

/**
 * Function for displaying the original image loaded
 */

void handler::display_image()
{ 
  cv::namedWindow("Input Image", CV_WINDOW_NORMAL);
  cv::imshow("Input Image", _image);
  cv::waitKey(0);
}

/**
 * Function for desplaying the result 
 */

void handler::display_results(cv::Mat3b image, std::string name)
{
  cv::namedWindow(name, CV_WINDOW_NORMAL);
  cv::imshow(name, image);
  cv::waitKey(0);
}

/**
 * Function for running the algorithm for finding the boarder from the output of the find_region function  
 * the border is shown in white!
 */
void handler::find_border()
{
  
  std::vector<int> temp_pixel;
  temp_pixel.resize(2);
  cv::Mat3b temp2 = _image_alg.clone();
  find_perimeter(_image_alg, temp2, x_input, y_input, row, col);
  
  for(int i=0; i< row; i++){
    for(int j=0; j< col; j++){
      cv::Vec3b _bgr_image = _image_alg.at<cv::Vec3b>(i,j);
      cv::Vec3b _bgr_temp = temp2.at<cv::Vec3b>(i,j);
      if(norm_calculation(_bgr_image, white) == 0){
	temp2.at<cv::Vec3b>(i,j) = white;
	temp_pixel[0] = i;
	temp_pixel[1] = j;
	perimeter_x.push_back(i);
	perimeter_y.push_back(j);
	perimeter_pixel.push_back(temp_pixel);
	
      }
    } 
  }
  
  display_results(temp2, "Result Contour Image_after");
  
  
}

/**
 * Function for running the algorithm for finding the region 
 * accroding to the output of the flood fill algorithm the region will be shown. 
 * the other regions are set with black color
 */
void handler::find_region(int x, int y)
{
  // creating a copy for the flood fill algorithm 
  cv::Mat3b temp = _image.clone();
  flood_fill(_image_alg, temp, x, y, row, col);
  //accroding to the output of the flood fill algorithm the region will be shown. 
  //the other regions are set with black color
  for(int i=0; i< row; i++){
    for(int j=0; j< col; j++){
      cv::Vec3b _bgr_image = _image_alg.at<cv::Vec3b>(i,j);
      cv::Vec3b _bgr_temp = temp.at<cv::Vec3b>(i,j);
      if(norm_calculation(_bgr_temp, black) != 0){
	_image_alg.at<cv::Vec3b>(i,j) = black;
      }
    } 
  }
  
  display_results(_image_alg, "Result Region Image");
  filtered = _image_alg.clone();
  filtered = computeFiltering();
  display_results(filtered, "Result Filtered Image");
  
  
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
    if(this->norm_calculation(_bgr_original, original.at<cv::Vec3b>(x+1,y)) <= threshold){
      flood_fill(original, copy, x+1, y, row_max, col_max);
    }
  }
  if(x-1 >= 0){
    if(this->norm_calculation(_bgr_original, original.at<cv::Vec3b>(x-1,y)) <= threshold){
      flood_fill(original, copy, x-1, y, row_max, col_max);
    }
  }
  if(y+1 < col_max){
    if(this->norm_calculation(_bgr_original, original.at<cv::Vec3b>(x,y+1)) <= threshold){
      flood_fill(original, copy, x, y+1, row_max, col_max);
    }
  }
  if(y-1 >= 0){
    if(this->norm_calculation(_bgr_original, original.at<cv::Vec3b>(x,y-1)) <= threshold){
      flood_fill(original, copy, x, y-1, row_max, col_max);
    }
  }
}

/**
 * The perimeter function recognize the border point of the region 
 */
void handler::find_perimeter(cv::Mat3b original, cv::Mat3b copy, int x, int y , int row_max, int col_max)
{
  //sleep(1);
  cv::Vec3b _bgr_original = original.at<cv::Vec3b>(x,y);
  cv::Vec3b _bgr_copy = copy.at<cv::Vec3b>(x,y);

  if(this->norm_calculation(black,_bgr_copy) == 0){
    return;
  }
  copy.at<cv::Vec3b>(x,y) = black;
  
  if(x+1 < row_max && this->norm_calculation(white,original.at<cv::Vec3b>(x+1,y)) != 0){
    if(this->norm_calculation(_bgr_original, original.at<cv::Vec3b>(x+1,y)) <= threshold){
      find_perimeter(original, copy, x+1, y, row_max, col_max);
    }else{
      original.at<cv::Vec3b>(x,y) = white;
      return;
    }
  }
  if(x-1 >= 0 && this->norm_calculation(white,original.at<cv::Vec3b>(x-1,y)) != 0){
    if(this->norm_calculation(_bgr_original, original.at<cv::Vec3b>(x-1,y)) <= threshold ){
      find_perimeter(original, copy, x-1, y, row_max, col_max);
    }else{
      original.at<cv::Vec3b>(x,y) = white;
      return;
    }
  }
  if(y+1 < col_max && this->norm_calculation(white,original.at<cv::Vec3b>(x,y+1)) != 0){
    if(this->norm_calculation(_bgr_original, original.at<cv::Vec3b>(x,y+1)) <= threshold ){
      find_perimeter(original, copy, x, y+1, row_max, col_max);
    }else{
      original.at<cv::Vec3b>(x,y) = white;
      return;
    }
  }
  if(y-1 >= 0 && this->norm_calculation(white,original.at<cv::Vec3b>(x,y-1)) != 0){
    if(this->norm_calculation(_bgr_original, original.at<cv::Vec3b>(x,y-1)) <= threshold ){
      find_perimeter(original, copy, x, y-1, row_max, col_max);
    }else{
      original.at<cv::Vec3b>(x,y) = white;
      return;
    }
  }
}

std::vector <std::vector< double> > handler::getGaussian(int row, int col, double sigma)
{
  std::vector <std::vector< double> > kernel(row);
  for(int i=0; i<row; i++){
    kernel[i].resize(col);
  }
  double total=0;
  int kernalWidth = row;
  int kernalHeight = col;
 //calculate each relavant value to neighour pixels and store it in 2d array
 for(int row=0;row<kernalWidth;row++){

  for(int col=0;col<kernalHeight;col++){

   float value=(1/(2*M_PI*pow(sigma,2)))*exp(-(pow(row-kernalWidth/2,2)+pow(col-kernalHeight/2,2))/(2*pow(sigma,2)));

   kernel[row][col]=value;

   total+=value;
  }
 }

 //Scale value in 2d array in to 1
 for(int row=0;row<kernalWidth;row++){
  for(int col=0;col<kernalHeight;col++){

   kernel[row][col]=kernel[row][col]/total;

  }
 }
return kernel;
}


cv::Mat3b handler::computeFiltering(){
 const int kernalWidth=200;
 const int kernalHeight=200;
 std::vector<std::vector<double> > kernel = getGaussian(kernalWidth,kernalHeight,5);
 
 int verticleImageBound=(kernalHeight-1)/2;
 int horizontalImageBound=(kernalWidth-1)/2;
 
 for(int rows=0+verticleImageBound;rows<row-verticleImageBound;rows++){

  for(int cols=0+horizontalImageBound;cols<col-horizontalImageBound;cols++){

   float value=0.0;

   for(int kRow=0;kRow<kernalHeight;kRow++){
    for(int kCol=0;kCol<kernalWidth;kCol++){
     
     float pixel=_image_alg.at<uchar>(kRow+rows-verticleImageBound,kCol+cols-horizontalImageBound)*kernel[kRow][kCol];
     value+=pixel;
    }
   }
   filtered.at<uchar>(rows,cols)=cvRound(value);
  }
 }
  return filtered;
}




void handler::save_image()
{
  cv::imwrite( "../Images/image_test.png", _image_alg);
  std::cout << "Image saved in: ../Images/image_test.bmp" << std::cout;
}