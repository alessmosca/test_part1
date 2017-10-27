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
Run the application:
```
cd build 
./test_part1
```
The user as to provide the input over the command line.
The possible choice are shown: 
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
## Gaussian Blur 
Honestly my backgroud about image processing is not really wide. I tried anyway to achieve some results, without completing the project. 
The choice of the Gaussian Blur, is due to my tiny knowledge from the university. I tried to blur the image in order to achieve a better edge detection, but seems not working 


## Implementation
Implement a proper perimeter smoothing operator. 
Since my knoledge is not really high, i tried to study a bit the possible implementation, and as far as I understood, one of the best solution was to apply the Bezier curves algotithm 
(i tried without good results)


## References

Flood fills
https://www.codeproject.com/Articles/6017/QuickFill-An-efficient-flood-fill-algorithm


