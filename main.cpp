#include <handler.hpp>

int pixel_x, pixel_y;

// static void onMouse(int event, int x, int y, int f, void*){
//   pixel_x = x;
//   pixel_x = y;
//   std::cout << x << " " << y << std::endl;
// }

int main(int argc, char ** argv){
  
  std::string name;
  std::cout <<"Welcome to the test1 -- Alessandro Mosca" << std::endl;
  std::cout <<"Please chose your input. Possible choices: \n"
              " - test1.png\n"
	      " - test2.png\n"
	      " - test3.png\n"
	      " - test4.jpg" << std::endl;
  std::cin >> name;
  handler* hand = new handler("../Images/"+name);
  
  int choice = 0;
  
  while(true){
    std::cout <<"Welcome to the test1 -- Alessandro Mosca" << std::endl;
    std::cout <<"Please chose your input. Possible choices: \n"
		" [1] Visualize the image \n"
		" [2] Find Region\n"
		" [3] Find Perimeter\n"
		" [4] Save Image\n" 
		" [5] Exit "<< std::endl;
  
    std::cin >> choice;
    switch(choice)
    {
      case (1):
	hand->display_image();
	break;
      case (2):
	std::cout <<"Choose the values of the pixel" << std::endl;
	std::cout <<"max X: " <<  hand->row <<  " max Y: " <<  hand->col << "\n"
		<< std::endl;
	//cv::setMouseCallback("Input Image", onMouse, 0);
 	std::cout <<"set X: "; std::cin >> pixel_x;
 	std::cout <<"set Y: "; std::cin >> pixel_y;
	std::cout <<"set threshold (default 0.0):  "; std::cin >> hand->threshold;
	
	hand->find_region(pixel_x,pixel_y);
	break;
      case (3):
	hand->x_input = pixel_x;
	hand->y_input = pixel_y;
	hand->find_border();
	break;
      case (4):
	hand->save_image();
      case (5): 
	return -1;
    }
      
  }
  
  return 0;
}
