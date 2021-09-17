# CS440_Project1_Macejko

The test.cpp file compiles with the proper compilation command, with absolutely no
warnings. This then produces an a.out executable which runs accordingly.

While the code is completely functional and will run through the length of test.cpp,
it seems that it will only do this in a reasonable amount of
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
from this potential mistake in the future to potentially develop a solution to them 
Nonetheless, with the exception listed above, the program still compiles 
and is functional to the point where the deque itself works completely as expected
to produce the correct output.

(P.S. I created a duplicate copy of my Deque.hpp code prior to macro translation,
labled premacroDeque.hpp. This is included in the directory).


