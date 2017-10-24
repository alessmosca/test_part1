# Description 
Develop a simple set of C++ classes for performing simple image processing tasks which elegantly exposes the image processing operations in a way that might be used within the larger project.
Develop a command line interface that allows execution of all operations of the interface from the command line


## Requirements
- OpenCV 2.X
- CMake > 2.8

## Installation 
```
git clone https://github.com/alessmosca/test_part1.git
cd test_part1
mkdir build && cd build 
cmake .. 
make 
```

## Usage
The user as to provide the input over the command line.
The possible choice are shown: 

Run the application:
```
./test_part1
```
Command line interface: 

```
std::cout <<"Welcome to the test1 -- Alessandro Mosca" << std::endl;
std::cout <<"Please chose your input. Possible choices: \n"
      " - test1.png\n"
      " - test2.png\n"
      " - test3.png\n"
      " - test4.jpg" << std::endl;
```
Choose what you want to do, and follow the instruction: 
```
std::cout <<"Welcome to the test1 -- Alessandro Mosca" << std::endl;
    std::cout <<"Please chose your input. Possible choices: \n"
		" [1] Visualize the image \n"
		" [2] Find Region\n"
		" [3] Find Perimeter\n"
		" [4] Save Image\n" 
		" [5] Exit "<< std::endl;
```


## References
