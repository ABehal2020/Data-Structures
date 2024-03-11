HOMEWORK 9: MINIBLAST


NAME:  < Aditya Behal >


COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Srijan Srivatsa, Ali Lin >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 10 hours >


HASH FUNCTION DESCRIPTION
I got the hash function from the Lecture 20.14, which got it from http://www.partow.net/programming/hashfunctions/.
The hash function relies on looping through the string and doing left and right bitwise shifting to produce a hash value. Taking the modulus of this value yields the index that the entry should be placed in or found at in the hash table.

HASH TABLE IMPLEMENTATION
The normal hash table is implemented using a vector<pair<string, list<int>>>. The vector is a good choice for the outermost data structure to enable quick random access. The hash function is also fast enabling rapid find and insert operations for the hash table on average. Constructor, copy constructor, assignment operator, and destructors were implemented for this hash table. The constructor initializes the size and load fraction to the default values, and the updateConfigs function updates these parameters if the user wants to provide custom values. The size function returns the current size of the hash table. Linear probing using the method of open addressing is used to deal with collisions.

The pair<string, list<int>> keeps track of the kmer and the various positions at which it was found using the list of ints. The insert function works by hashing the kmer and finding if it already exists in the table. If it does, we append the position to the list of ints. If it doesn't, then we create a new hash table entry with the kmer and its position. To account for collisions (two different strings can hash to the same index), linear probing is used to find the next empty spot. The program steps through each index sequentially after the original calculated index. If we reach the end of the hash table, then the index's value becomes 0, and we continue sequentially stepping through the table. Whenever the load fraction exceeded the default or custom value, the table was resized.

The find method uses the same principle as insert except that it checks whether the index contains the kmer or not. Linear probing accounts for collisions.

The print method steps through all non empty entries of the hash table and prints out the key and values. This was useful for debugging the program.

The resize method is a private helper function. It makes a copy of the current table before clearing the current table and resizing it to a size of 2x + 1 where x was the original size of the table. We loop through the original table and for each non empty entry, we rehash the key to a new index in the new table, copying over the entry from the old table to its new location in the new table.


ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(order notation & concise paragraph, < 200 words)

L = length of the genome sequence
q - query length
p - number of different locations where key is found
k - key size (k-mer size)

How much memory will the hash table data structure require (order notation for memory use)?
O((L*(k + p)) - There will be roughly L entries in the table (assume L is very large like 1,000,000 and k = 10). There will be nearly a million entries in the table. However, L only accounts for the number of entries in the vector. We must use multiply L by k + p. P tells us the number of different locations locations where the key is found as the list<int> associated with each kmer will on average length p. K tells us what the maximum key size is. We cannot assume k < p or that p < k because k could be very big and occur only in a few locations or k could be very small and appear in a lot of locations.


What is the order notation for performance (running time) of each of
the commands? What about for the hash table's insert, find, and resize?

UPDATE 
Constructing the hash table: O(L*k)
Using nested loops, we loop through the length of the string containing of the genome O(L) and then construct kmers, which is O(k) cost as we have to append each character of each kmer to a new string. Calling insert L times will have O(k) cost on average. 

Matching a single query of length q: O(k + pq)
Finding the list of positions matching up to a query is O(k + p) on average. Evaluating the list of positions matching up to that query is p*q cost due to two nested loops (the outer loop runs through the list of positions and the inner loop runs up to q times checking for mismatches.

Insert:
Average Case (no resize): O(k)
We have to calculate hash value and copy the kmer into the hash table, which is O(k).
Worst Case (no resize): O(k + L)
We will have to loop through the entire hash table in the worst case scenario with linear probing in the event of a collision.
Worst case (resize occurs): O(L*(k + p))

Find: 
Average Case: O(k) in theory - my implementation is O(k + p) due to the following reasons:
Hashing the key takes O(k) time as the hash function loops over the whole string. We also take the substring of the query which takes O(k) time. Returning a copy of the list is O(p). We cannot return it by constant reference in the event that the kmer does not exist in the hash map as we will have to return a copy of an empty list to indicate that the kmer could not be found.
Worst Case: O(k + L + p)
We will have to loop through the entire hash table in the worst case scenario with linear probing in the event of a collision.

Resize: O(L*(k + p)) - We loop through the old table which has L entries. Resize is called by default when the table is half full, so L/2 entries have to be run through the hash function (O(k) cost per call to the hash function since it has to loop through the whole string which is of size k). We assume that hash collisions are rare (roughly a constant number of times) and takes O(L) time to resolve it in the worst case. L*k*(k + p) dwarfs c*L where c is a constant number.

EXTRA CREDIT
Add a new command to implement the database using one of the other
 data structures that we have covered so far in the course: 
vectors, lists, arrays etc. 

Compare the performance your alternative method to the homework method
by making a table of run times for each of the genomes and query 
sets provided with the homework  and compare the times to build
the index and the times to process the queries. 
Document any new commands you have added in your README file.

I implemented the extra credit using lists instead of vectors.

The program is normally run using the following command:
./main.out < input_small.txt > code_output.txt

The program can be run in extra credit mode using the command below.
./main.out extra_credit < input_small.txt > code_output.txt

--------------------------------------------------------------------------------------------------------------------------------------------
Input File                                     Normal Hash Map Run Time (s)                               Extra Credit Hash Map Run Time (s)
--------------------------------------------------------------------------------------------------------------------------------------------
input_small.txt                                0.034 s                                                    0.487 s
input_medium.txt                               0.101 s                                                    0.134 s
input_large.txt                                0.119 s                                                    1.636 s
input_larger.txt                               0.955 s                                                    16.43 s



MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


