DESCRIPTION
===============
A simple and fast C program for reversing byte ordering, block-wise.

INSTALLATION
===============

Procedure for building code using CMake:

  [reverse\_byte\_ordering]$ mkdir build

  [reverse\_byte\_ordering]$ cd build

  [reverse\_byte\_ordering/build]$ cmake ..

  [reverse\_byte\_ordering/build]$ make

Note that the last two commands are executed inside the build directory.

Afterwards, your tree structure should look like this:

  [reverse\_byte\_ordering]$ tree -L 2
  .
  |-- CMakeLists.txt
  |-- README.txt
  |-- build
  |   |-- CMakeCache.txt
  |   |-- CMakeFiles
  |   |-- Makefile
  |   |-- cmake_install.cmake
  |   |-- src
  |-- src
      |-- CMakeLists.txt
      |-- reverse\_byte\_ordering.c

and you can execute the program in the build/src directory as follows:

  [masked_xcorr/build/src]$ ./reverse\_byte\_ordering

For more information on using CMake, check out http://www.cmake.org/cmake/help/cmake_tutorial.html

William Wu, 2013-05-20 10:04
	