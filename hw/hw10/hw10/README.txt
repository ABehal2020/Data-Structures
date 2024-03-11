HOMEWORK 10:  PERFORMANCE & BIG O NOTATION


NAME:  < Aditya Behal >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Ali Lin, Dylan Walker >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 15 hours >



COMPLEXITY ANALYSIS
n = number of elements in the input
f = requested number of values in output (first sorted only)
l = maximum length of any string element

Neatly fill in the table below with the Big O Notation for running time.
Top is time complexity, and bottom is memory usage.

-------------------------------------------------------------------------------------------------------------------------
|                         |              | remove       |              | closest      | first f         | longest       |
|                         | sort         | dups         | mode         | pair         | sorted          | substr        | 
-------------------------------------------------------------------------------------------------------------------------
|                         | O(n*log(n))  | O(n^2)       | O(n*log(n))  | O(n*log(n))  | O(n*log(n))     | O(n^2*l^3)    |
| vector                  | O(n)         | O(n)         | O(n)         | O(n)         | O(n)            | O(n*l)        |
-------------------------------------------------------------------------------------------------------------------------
|                         | O(n*log(n))  | O(n^2)       | O(n*log(n))  | O(n*log(n))  | O(n*log(n))     | O(n^2*l^3)    |
| list                    | O(n)         | O(n)         | O(n)         | O(n)         | O(n)            | O(n*l)        |
-------------------------------------------------------------------------------------------------------------------------
|                         | O(n*log(n))  | O(n*log(n))  | O(n*log(n))  | O(n*log(n))  | O(n*log(n))     | O(n^2*l^3)    |
| bst (map)               | O(n)         | O(n)         | O(n)         | O(n)         | O(n)            | O(n*l)        |
-------------------------------------------------------------------------------------------------------------------------
|                         | O(n*log(n))  | X            | O(n*log(n))  | O(n*log(n))  | O(n + f*log(n)) | X             |
| pq                      | O(n)         |              | O(n)         | O(n)         | O(n)            |               |
-------------------------------------------------------------------------------------------------------------------------
|                         | X            | O(n)         | O(n)         | O(n^2)       | X               | O(n^2*l^3)    |
| hash (unordered_map)    |              | O(n)         | O(n)         | O(n)         | O(n)            | O(n*l)        |
-------------------------------------------------------------------------------------------------------------------------



RESULTS
For each data type and each operation, run several sufficiently large
tests and collect the operation time output by the program. Organize
these timing measurements in your README.txt file and estimate the
coefficients for the dominant term of your Big ‘O’ Notation.

< insert your performance measurements and coefficient estimates >

Student STDOUT.txt
  1vector              sort               10,000 length 5 strings     0.0090 sec     3864 kb
  2vector              sort               50,000 length 5 strings     0.0472 sec     5328 kb
  3vector              sort              100,000 length 5 strings     0.0981 sec     7424 kb
  4vector              sort              500,000 length 5 strings     0.5235 sec    19688 kb
  5vector              remove_dups         5,000 length 3 strings     0.2489 sec     3576 kb
  6vector              remove_dups        10,000 length 3 strings     0.9220 sec     3808 kb
  7vector              remove_dups        20,000 length 3 strings     3.0915 sec     4192 kb
  8vector              remove_dups        50,000 length 3 strings    12.6827 sec     5316 kb
  9vector              mode               10,000 length 4 strings     0.0082 sec     3876 kb
 10vector              mode               50,000 length 4 strings     0.0455 sec     5332 kb
 11vector              mode              100,000 length 4 strings     0.0914 sec     7408 kb
 12vector              mode              500,000 length 4 strings     0.4868 sec    19524 kb
 13vector              closest_pair       10,000 8 digit integers     0.0067 sec     1984 kb
 14vector              closest_pair       50,000 8 digit integers     0.0353 sec     3484 kb
 15vector              closest_pair      100,000 8 digit integers     0.0737 sec     3892 kb
 16vector              closest_pair      500,000 8 digit integers     0.3926 sec     5280 kb
 17vector              first 50 sorted   10,0000 length 4 strings     0.0081 sec     3736 kb
 18vector              first 50 sorted   20,0000 length 4 strings     0.0429 sec     5276 kb
 19vector              first 50 sorted   50,0000 length 4 strings     0.0901 sec     7408 kb
 20vector              first 50 sorted  100,0000 length 4 strings     0.4828 sec    19732 kb
 21vector              longest_substring    500 length 20 strings     1.5559 sec     1864 kb
 22vector              longest_substring  1,000 length 20 strings     6.0871 sec     2032 kb
 23vector              longest_substring  2,000 length 20 strings    23.5215 sec     3460 kb
 24vector              longest_substring  3,000 length 20 strings    NOT IMPLEMENTED
 25
 26linked list         sort               10,000 length 5 strings     0.0134 sec     3748 kb
 27linked list         sort               50,000 length 5 strings     0.0761 sec     6420 kb
 28linked list         sort              100,000 length 5 strings     0.1549 sec     9364 kb
 29linked list         sort              500,000 length 5 strings     1.0328 sec    34424 kb
 30linked list         remove_dups         5,000 length 3 strings     0.4292 sec     3292 kb
 31linked list         remove_dups        10,000 length 3 strings     1.5777 sec     3672 kb
 32linked list         remove_dups        20,000 length 3 strings     5.2769 sec     4520 kb
 33linked list         remove_dups        50,000 length 3 strings    21.9187 sec     6392 kb
 34linked list         mode               10,000 length 4 strings     0.0125 sec     3740 kb
 35linked list         mode               50,000 length 4 strings     0.0703 sec     6324 kb
 36linked list         mode              100,000 length 4 strings     0.1625 sec     9592 kb
 37linked list         mode              500,000 length 4 strings     0.9637 sec    34296 kb
 38linked list         closest_pair       10,000 8 digit integers     0.0120 sec     3432 kb
 39linked list         closest_pair       50,000 8 digit integers     0.0668 sec     4620 kb
 40linked list         closest_pair      100,000 8 digit integers     0.1432 sec     6196 kb
 41linked list         closest_pair      500,000 8 digit integers     0.8224 sec    18616 kb
 42linked list         first 50 sorted   10,0000 length 4 strings     0.0124 sec     3676 kb
 43linked list         first 50 sorted   20,0000 length 4 strings     0.0682 sec     6388 kb
 44linked list         first 50 sorted   50,0000 length 4 strings     0.1523 sec     9532 kb
 45linked list         first 50 sorted  100,0000 length 4 strings     0.9147 sec    34296 kb
 46linked list         longest_substring    500 length 20 strings     1.7695 sec     1868 kb
 47linked list         longest_substring  1,000 length 20 strings     6.9282 sec     1864 kb
 48linked list         longest_substring  2,000 length 20 strings    27.1001 sec     3300 kb
 49linked list         longest_substring  3,000 length 20 strings    NOT IMPLEMENTED
 50
 51binary search tree  sort               10,000 length 5 strings     0.0130 sec     3892 kb
 52binary search tree  sort               50,000 length 5 strings     0.0736 sec     7200 kb
 53binary search tree  sort              100,000 length 5 strings     0.1590 sec    11116 kb
 54binary search tree  sort              500,000 length 5 strings     1.1619 sec    41520 kb
 55binary search tree  remove_dups         5,000 length 3 strings     0.0129 sec     3516 kb
 56binary search tree  remove_dups        10,000 length 3 strings     0.0139 sec     3824 kb
 57binary search tree  remove_dups        20,000 length 3 strings     0.0264 sec     4196 kb
 58binary search tree  remove_dups        50,000 length 3 strings     0.0593 sec     4572 kb
 59binary search tree  mode               10,000 length 4 strings     0.0121 sec     4084 kb
 60binary search tree  mode               50,000 length 4 strings     0.0648 sec     6864 kb
 61binary search tree  mode              100,000 length 4 strings     0.1439 sec    10320 kb
 62binary search tree  mode              500,000 length 4 strings     0.8776 sec    27004 kb
 63binary search tree  closest_pair       10,000 8 digit integers     0.0114 sec     3568 kb
 64binary search tree  closest_pair       50,000 8 digit integers     0.0623 sec     5412 kb
 65binary search tree  closest_pair      100,000 8 digit integers     0.1320 sec     7892 kb
 66binary search tree  closest_pair      500,000 8 digit integers     0.9052 sec    26720 kb
 67binary search tree  first 50 sorted   10,0000 length 4 strings     0.0115 sec     4036 kb
 68binary search tree  first 50 sorted   20,0000 length 4 strings     0.0649 sec     7188 kb
 69binary search tree  first 50 sorted   50,0000 length 4 strings     0.1441 sec    11164 kb
 70binary search tree  first 50 sorted  100,0000 length 4 strings     0.9881 sec    41380 kb
 71binary search tree  longest_substring    500 length 20 strings     2.3028 sec     1824 kb
 72binary search tree  longest_substring  1,000 length 20 strings     9.0903 sec     2056 kb
 73binary search tree  longest_substring  2,000 length 20 strings    NOT IMPLEMENTED
 74binary search tree  longest_substring  3,000 length 20 strings    NOT IMPLEMENTED
 75
 76priority queue      sort               10,000 length 5 strings     0.0156 sec     3748 kb
 77priority queue      sort               50,000 length 5 strings     0.0858 sec     5292 kb
 78priority queue      sort              100,000 length 5 strings     0.1814 sec     7440 kb
 79priority queue      sort              500,000 length 5 strings     1.0824 sec    19660 kb
 80priority queue      remove_dups         5,000 length 3 strings    NOT IMPLEMENTED
 81priority queue      remove_dups        10,000 length 3 strings    NOT IMPLEMENTED
 82priority queue      remove_dups        20,000 length 3 strings    NOT IMPLEMENTED
 83priority queue      remove_dups        50,000 length 3 strings    NOT IMPLEMENTED
 84priority queue      mode               10,000 length 4 strings     0.0148 sec     3812 kb
 85priority queue      mode               50,000 length 4 strings     0.0838 sec     5344 kb
 86priority queue      mode              100,000 length 4 strings     0.1768 sec     7432 kb
 87priority queue      mode              500,000 length 4 strings     1.0390 sec    19692 kb
 88priority queue      closest_pair       10,000 8 digit integers     0.0126 sec     1836 kb
 89priority queue      closest_pair       50,000 8 digit integers     0.0691 sec     3644 kb
 90priority queue      closest_pair      100,000 8 digit integers     0.1541 sec     3896 kb
 91priority queue      closest_pair      500,000 8 digit integers     0.7981 sec     5272 kb
 92priority queue      first 50 sorted   10,0000 length 4 strings     0.0051 sec     3884 kb
 93priority queue      first 50 sorted   20,0000 length 4 strings     0.0243 sec     5388 kb
 94priority queue      first 50 sorted   50,0000 length 4 strings     0.0485 sec     7384 kb
 95priority queue      first 50 sorted  100,0000 length 4 strings     0.2396 sec    19648 kb
 96priority queue      longest_substring    500 length 20 strings    NOT IMPLEMENTED
 97priority queue      longest_substring  1,000 length 20 strings    NOT IMPLEMENTED
 98priority queue      longest_substring  2,000 length 20 strings    NOT IMPLEMENTED
 99priority queue      longest_substring  3,000 length 20 strings    NOT IMPLEMENTED
100
101hash table          sort               10,000 length 5 strings    NOT IMPLEMENTED
102hash table          sort               50,000 length 5 strings    NOT IMPLEMENTED
103hash table          sort              100,000 length 5 strings    NOT IMPLEMENTED
104hash table          sort              500,000 length 5 strings    NOT IMPLEMENTED
105hash table          remove_dups         5,000 length 3 strings     0.0108 sec     3560 kb
106hash table          remove_dups        10,000 length 3 strings     0.0099 sec     3728 kb
107hash table          remove_dups        20,000 length 3 strings     0.0178 sec     3936 kb
108hash table          remove_dups        50,000 length 3 strings     0.0361 sec     4460 kb
109hash table          mode               10,000 length 4 strings     0.0066 sec     4036 kb
110hash table          mode               50,000 length 4 strings     0.0318 sec     6748 kb
111hash table          mode              100,000 length 4 strings     0.0657 sec     9672 kb
112hash table          mode              500,000 length 4 strings     0.4091 sec    25804 kb
113hash table          closest_pair       10,000 8 digit integers     2.4144 sec     3668 kb
114hash table          closest_pair       50,000 8 digit integers    NOT IMPLEMENTED
115hash table          closest_pair      100,000 8 digit integers    NOT IMPLEMENTED
116hash table          closest_pair      500,000 8 digit integers    NOT IMPLEMENTED
117hash table          first 50 sorted   10,0000 length 4 strings    NOT IMPLEMENTED
118hash table          first 50 sorted   20,0000 length 4 strings    NOT IMPLEMENTED
119hash table          first 50 sorted   50,0000 length 4 strings    NOT IMPLEMENTED
120hash table          first 50 sorted  100,0000 length 4 strings    NOT IMPLEMENTED
121hash table          longest_substring    500 length 20 strings     1.9120 sec     1876 kb
122hash table          longest_substring  1,000 length 20 strings     7.5667 sec     1984 kb
123hash table          longest_substring  2,000 length 20 strings    NOT IMPLEMENTED
124hash table          longest_substring  3,000 length 20 strings    NOT IMPLEMENTED
125


These coefficients are with units of 1*10^-9 seconds.

Vector coefficients:

Sort: 60.7
Remove dups: 6.23
Mode: 84.2
Closest pair: for 75.4
First f sorted: 25.3
Longest substr: 13.9

List coefficients:

Sort: 132
Remove dups: 8.54
Mode: 112
Closest pair: 96.4
First f sorted: 49.9
Longest substr: 13.5

Bst coefficients:

Sort: 112
Remove dups: 78.7
Mode: 83.5
Closest pair: 90.6
First f sorted: 49.3
Longest substr: 13.5

Pq coefficients:

Sort: 138
Mode: 119
Closest pair: 108
First f sorted: 790

Hash coefficients:

Remove dups: 732
Mode: 692
Closest pair: 15.8
First f sorted: 486
Longest substr: 17.5

DISCUSSION
Do these measurements and the overall performance match your predicted
Big ‘O‘ Notation for the data type and operation? Did you update your
initial answers for the Big ‘O‘ Notation of any cell in the table?

Compare the relative coefficients for different data types that have
the same Big ‘O’ Notation for a specific operation. Do these match
your intuition? Are you surprised by any of the results? Will these
results impact your data structure choices for future programming
projects?

Use well-written, complete sentences.  Approximately 250-500 words.  


< insert your discussion of the results, including your answers to the
above questions >

I was able to correctly ascertain the time and memory complexity of most of the data structures and operations before hand. One exception was the priority queue's first f sorted. I thought it would be n*log(n), but I realized that it takes O(n) to build a priority queue. Removal is log n cost and occurs f times for this particular operation using this data structure. Vector coefficients overall were lower than lists as I expected. The continuous blocks of memory and quick random access operations makes vectors pretty powerful. I thought maps and priority queues would have lower coefficients, but as they have to maintain their order, this could raise the coefficient values. Hash table coefficients were really high. I was pretty surprised by this. Perhaps it has to do with the hashing function and the map structure (both a key and a value must be stored). It was interesting to note that vectors performed overall really well (better than any other data structure coefficient wise) for the sort operation in particular. In my future programming projects, I definitely will think more carefully about deciding whether more complicated data structures like lists, maps, unordered_maps, and priority queues are really necessary as the simplicity of vectors along with their surprisingly good performance makes them a good data structure for a lot of use cases. I will think twice about using a hash table. Although it is really nice to have O(1) operations on average, their coefficients are really high, and I will have to make sure I use a speedy hash function that churns out a good distribution.



MISC. COMMENTS TO GRADER:  
Optional, please be concise!
