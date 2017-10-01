#################################################################
# PA4 Test case descriptions
# Author: Fereydoon
# Date: March 21, 2015
#
# Notice that you were required to output ASCII pgm files with
#.pgm not .pgma! If this is your mistake, you may want to make
# a private resubmission in Piazza.
#################################################################

# Test1Compile: 10 pts if compiles without error

# Test2: 10pts // n=0 comparison on 1.pgm
pa4 Cat01.pgm Dog02.pgm 0

# Test3Error: 10pts  if returns -1 // mismatch in width and height
pa4 Cat01B.pgm Dog02B.pgm 3

# Test4: 10pts // n=20 comparison on 10.pgm
pa4 emma1.pgm emma2.pgm 20

# Test5: 10pts // n=5 comparison on 3.pgm
pa4 girl1.pgm girl2.pgm 5

# Test6: 10pts // n=5 comparison on 3.pgm, second image is binary, i.e. negative2.pgm
pa4 negative1.pgm negative2.pgm 5

# Test7: 10pts // n=5 comparison on 3.pgm
pa4 george1.pgm george2.pgm 5

# Test8: 10pts // n=5 comparison on 3.pgm
pa4 3D1.pgm 3D2.pgm 5

# Test9Error: 10pts  if returns -1 //invalid n=1.6
pa4 vader1.pgm vader2.pgm 1.6

# Test10Valgrind: 10pts  if no memory leaks and no error in Valgrind report // n=2
valgrind --leak-check=full pa4 vader1.pgm vader2.pgm 2
