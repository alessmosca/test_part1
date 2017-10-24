#include <handler.hpp>

int main(int argc, char ** argv){
  
  std::string path(argv[1]);
  handler* hand = new handler(path);
  
  hand->find_region(0,0);
  
  return 0;
}
