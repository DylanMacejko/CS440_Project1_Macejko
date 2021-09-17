# CS440_Project1_Macejko

The test.cpp file compiles with the proper compilation command, with absolutely no
warnings. This then produces an a.out executable which runs accordingly.

There are two lines that do not run properly in the test.cpp file and they are as
shown below:
	line135: assert(sizeof deq.type_name == 14)
	line255: assert(sizeof deq.type_name == 10)
Prior to converting over to the macro, I had implemented the Deque as if it was just
going to accomodate integers, and line 255 actually ran accordingly there, producing
an output of 10. However, after the macro conversion, this seemed to then fail.

Considering for both instances of the typename, the sizeof produces a result of 8,
I am assuming that the sizeof is just measuring the size of a pointer somehow. With
more time, I would look into manipulating this to produce the actual result and 
delve into why the sizeof is not recognizing the length of the string, whether it
has to due with the form that the string is taking in the program.


Additionally, while the code is completely functional and will run through the
length of test.cpp, it seems that it will only do this in a reasonable amount of
time if the for loop on line522 is decreased drastically with respect to the 
amount of iterations it covers. I found that with 1000 iterations, the whole 
program was able to complete in about one minute. However, once the iterations 
increased, the running time would be significantly larger to the point where it 
seemed like the computer could have ran for at least a half hour without producing
an answer.

A reasonable explanation for this discrepancy could just be the speed of my sort,
but I am not exactly sure how that could be the case, considering I chose Quick
Sort as my go to sorting method, which has asymptotic complexity of nlogn. I 
attempted to speed up the process of sorting by checking if the array was already
sorted to begin with to determine if sorting was even necessary. That definitely
helped with the speed to a degree but once again, even this improvement would've 
taken an excess amount of time to fulfill 1'000'000 iterations as previously 
listed in the test file. With more time, I would more appropriately manage the 
amount of unnecessary swaps or rearrangements of the deque that may be made.

While I am happy to have learned a lot from this assignment, I do look to learn
from these mistakes in the future and potentially develop a solution to them. 
Nonetheless, with the exceptions listed above, the program still compiles 
and is functional to the point where the deque itself works completely as expected.


