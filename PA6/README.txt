#################################################################
# PA6 Test case Descriptions
# Author: Fereydoon
# Date: April 23, 2015
#################################################################

# Test1: 10 pts if compiles without error
make clean; make

# Test2: 20pts //given the keypoint, should behave similar to PA5
# Comparison based on 2.pgm 
pa6 Dog.pgm DogFade.pgm keypoint2

# Test3: 20pts //given the keypoint, should behave similar to PA4
# Comparison based on 3.pgm
pa6 negative1.pgm negative2.pgm keypoint3

# Test4: 20pts //Comparison based on 3.pgm
pa6 fereydoon.pgm bruce.pgm keypoint4

# Test5: 20pts //Comparison based on 3.pgm
pa6 bruce.pgm fereydoon.pgm keypoint5

# Test6 - Valgrind: 10pts  if no memory leaks and no error in Valgrind report
valgrind --leak-check=full ./pa6 girl1.pgm girl2.pgm keypoint3
