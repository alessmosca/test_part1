#include <handler.hpp>

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
  int pixel_x, pixel_y;
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
	
	std::cin >> pixel_x;
	std::cin >> pixel_y;
	hand->find_region(pixel_x,pixel_y);
	break;
      case (3):
	hand->find_boarder();
	break;
      case (4):
	return - 3;
      case (5): 
	return -1;
    }
      
  }
  
  return 0;
}
