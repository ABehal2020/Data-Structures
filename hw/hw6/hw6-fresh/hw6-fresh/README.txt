HOMEWORK 6: CROSSWORD BLACKOUT


NAME:  < Aditya Behal >



COLLABORATORS AND OTHER RESOURCES:
List the names of everyone you talked to about this assignment
(classmates, TAs, ALAC tutors, upperclassmen, students/instructor via
LMS, etc.), and all of the resources (books, online reference
material, etc.) you consulted in completing this assignment.

< Srijan Srivatsa, Ali Lin, https://www.tutorialspoint.com/cplusplus-program-to-generate-all-possible-combinations-out-of-a-b-c-d-e >

Remember: Your implementation for this assignment must be done on your
own, as described in "Academic Integrity for Homework" handout.



ESTIMATE OF # OF HOURS SPENT ON THIS ASSIGNMENT:  < 35 hours >



ANALYSIS OF PERFORMANCE OF YOUR ALGORITHM:
(running time order notation & concise paragraph, < 200 words)
The dimensions of the board (w and h) 
The number of words in the dictionary (d)? 
The total number of spaces with a letter (l)?
The total number of blacked out spaces (b)? 
The number of constraints (c)? 
Etc.

My own additional variables:
The number of comments (starting with an !) in the puzzle input file (z)?
The length of the longest word in the dictionary (w)?
The number of found words in the crossword puzzle (f)?
The most number of constraints of a certain length (i.e. the frequency variable in my Constraints class) (x)?
The length of the longest word (note: it can be simplified to h or w, whichever one is larger - however, h > w or w > h depending on the scenario so we define a new variable that is equal to h or w (whichever one is larger)) (p)?

Please note that nCr denotes n choose r (i.e. the total number of combinations with a set of n elements and where we allowed to pick r elements at a time) and is given by the formula n!/((n-r)!*r!)

The big O notation of my algorithm is O((h + c + z)(c + w) + fCc(c*x + p + h*w*l^2*(w+h) + (fCc)^2*h*w + d*h*w*(w+h)).
I will present the big picture leading to this analysis out here. My program can be broken up into a few main parts (you can see these function calls in main.cpp as well):
1) parseDictionary which parses the dictionary input file using a while loop - O(d)
2) parsePuzzleInput - O((h + c + z)(c + w))
A while loop iterates over the whole puzzle input file. There are h lines of the crossword puzzle, c lines of constraints, and z lines of comments. There are two sequential for loops inside the outer while loop. The first outer for loop iterates c times, checking if a new line of the puzzle file which denotes a constraint is unique (e.g. if the input puzzle file had +3, +5, +5, after reading in the first two constraints, 3 and 5 would be added to constraints vector; when the third constraint of +5 is read in, by looping over the constraints, we determine that 5 is not unique and we increment 5's frequency to 2 since we have encountered 5 twice). Furthermore, the other for loop appends a new line of the crossword puzzle of length w characters (the for loop has to iterate w times) to the vector<vector<char>> representing the crossword puzzle. Finally, we sort constraints (hence the O(c*log(c)) cost). However, this gets discarded as a term c^2 appears when you simplify the expression (h + c + z)(c + w) as c^2 is bigger than c*(log c).
3) searchWords which searches the crossword puzzle to see which words in the dictionary are present - O(d*h*w*(w + h))
We must loop through the entire dictionary and the entire board in triply nested loops. Then, we call the searchAcross and the searchDown functions. The searchAcross function calls itself recursively approximately O(w) times in the worst case scenario (a word could be spanning the entire width of the board in the worst case). Similar logic applies for the searchDown function, but since it is a column wise search, its cost is O(h). Although the found words vector is sorted at the end, incurring a cost of f*log(f), we can discard this term as d*h*w*(w + h) dwarfs it. This is because the term h*w in the latter expression is greater than f^2, which is greater than f*log(f). The term h*w is greater than f^2 as h*w represents the total number of characters on the board while f^2 has the limitation that each word in the found vector according to the homework rules must at least be 3 characters long.
4) findWordCombinations - O(c*fCc*x + (fCc)^2/(c^2)*log(fCc)
The premise of this function is that it finds the combinations of words at multiple levels. After this algorithm splits words up by size, it then notes how many words of each size (based on the constraints) are allowed in the crossword puzzle solution. Then, it calls the combinations function. The combinations function is recursive, and we end up with all the combinations in the given set of elements. For instance, if we supplied a vector containing a, b, c, d, e to the combinations function and specified that the required length was 2 (i.e. each combination had to have exactly 2 characters in it), the combinations function would return a vector containing the combinations (ab, ac, ad, ae, bc, bd, be, cd, ce, de). The total number of combinations is given by the combinations formula (n!/((n-r)!*r!)) and is spoken of as n choose r, which we shall denote as nCr. First, we run the combinations algorithm on the found words vector, and we are allowed to pick at most x elements per combination at a time (where x represents the highest frequency in a combination). This algorithm has be run for each constraint (c) times. Then, we flatten the result of the combinations and combine them into a vector. We find the meta combinations among those elements. Considering the blackout1 example, the results of the initial combinations algorithm is ski, use, eke, sis and blues, flees in different vectors in a nested vector. Flattening results in all of them being in a one dimension vector containing ski, use, eke, sis, and bluesflees. Note that blues and flees have been merged into one word as a word combination as we need 2 five letter words as per the blackout_dict1 constraints in this example (the blackout_dict1 constraints need 1 three letter word and 2 five letter words to appear in the solution). Then, we find the meta combinations which is O(fCc) cost as we do this on a vector which is at most the size of the found vector [this would occur in a case where each constraint was of a unique length (i.e. constraints of the same length only appear once in the puzzle input file)]. We would have to pick c elements in this worst case scenario (hence the overall O(fCc) cost in the worst case). After filtering the meta combinations to remove erroneous combinations (e.g. ski, use can be generated by the combinations algorithm so we would discard this). We would want to keep combinations like ski, bluesflees as there is one 3 letter word and two 5 letter words (after bluesflees is split up into its component words). We have to loop over all the constraints to sum up their frequencies in order to calculate what the proper combination size is, so we incur an O(c) cost. We know what the proper combination size is now, and we accordingly use this information to split up combined words into their component words (like bluesflees into blues and flees as mentioned earlier) and combine it with an appropriate three letter word like ski to form a correct combination that is of the correct size (3 in this case) and follows the constraints (1 five letter words and 1 three letter word). Note, that the sorting algorithm is called as well (hence the log term). This gets thrown out when simplifying the terms for the overall algorithm cost as an (fCc)^3 term pops up in a subsequent step, which dwarfs the (fCc)^2*log(fCc) term.
5) createAnswerGrids - O(fCc*p + fCc*(l + h*w + c*log(c) + (fCc)^3*h*w + fCc*((d*h*w*(w + h) + f*log(f)) + fCc + fCc*(h*w*l^2*(w+h)))
The first step in this function is to combine several words' paths in subsets of the doubly nested vector allWordCombinations. This requires a cost of O(fCc*p) where p represents the longest word. As noted in the definition of the variable p, p is equal to h or w, whichever one is bigger. Then, there are nested loops iterating over these combined paths O(fCc) cost and then over each of these individual paths in the nested vector (O(l) total iterations where l represents the number of spaces with a letter in the solution board). Then, we proceed to black out the non-letter squares by iterating h*w times but only changing the squares that are not letters. We also end up sorting the words that each grid is supposed to have (each time the sort function is called in this manner, the cost is O(c*log(c)).
6) outputSolutions - O(fCc*h*w)
In the worst case scenario, we loop over all of the answer grids (which is of a maximum size of fCc as fCc represents the maximum number of combinations of size of found words choose size of constraints and at maximum there would be fCc answer grids if all such combinations were valid). We then loop over each of the boards in triply nested loops, incurring O(fCc*h*w) cost in total.
After adding up the Big O notation of each of these function calls and further simplifying by factoring and noting the terms which dwarf other terms, we are left with the above expression.
Please take a look at my main.cpp for more information on the detailed break down of my Big O notation analysis for each function. Please note that I further simplified out here. 


DESCRIPTION OF YOUR ADDTIONAL PUZZLES/DICTIONARIES:
Briefly explain the design of the puzzles or dictionaries and what
makes them "interesting" test cases (or why they aren't interesting).

I made 3 puzzles and 3 corresponding dictionaries. 

The first puzzle is invalid_constraints_test.txt, and its corresponding dictionary is invalid_constraints_test_dict.txt.
This puzzle's dictionary has one 5 letter word, one 4 letter word, and one 3 letter word. The constraints require two 5 letter words, one 4 letter word, and one 3 letter word. These constraints are invalid because the dictionary only has one 4 letter word, and the constraints require two 4 letter words. My code returns 0 solutions as expected.

Number of solution(s): 0

The second puzzle is overlap_test.txt, and its corresponding dictionary is overlap_test_dict.txt.
This puzzle tests multiple types of overlap corner cases. The first type of overlap corner cases is when two words are next to each other. DOG and POI are two 3 letter words that are right next to each other (DOGPOI is the second line of the crossword puzzle). Additionally, the puzzle requires one 3 letter word, one 4 letter word, and one 5 five letter word. The first line of the crossword puzzle is USERUM. The final column of the crossword puzzle is MINDS. My code accounts for all these corner cases and returns the only solution that is valid, which is shown below.

Number of solution(s): 1
Board: 
USER#M
#####I
H####N
U####D
M####S

The third puzzle is combo_test, and its corresponding dictionary is combo_test_dict.txt. When run in all_solutions mode, my code outputs all 21 solutions to this puzzle. It successfully generates all the combinations and rules out corner cases (e.g. words stacked on top of each other like CHAKRA and ABACUS (first 6 letters of last 2 lines of this crossword puzzle). When this puzzle and its corresponding dictionary is tested in one_solution mode, here is the one_solution mode output:

Number of solution(s): 1
AARDWOLVES
##########
JAZZIER###
##########
##########
ABAPTISTON
##########
##########
BEZZAZZ###
##########
##########
##########
##########
##########
ABACUS####



SUMMARY OF PERFORMANCE OF YOUR PROGRAM ON THE PROVIDED PUZZLES AND 
ON YOUR ADDITIONAL PUZZLES/DICTIONARIES:
# of solutions & approximate wall clock running time for different
puzzles / dictionaries for a single solution or all solutions. Be
specific about which puzzle/dictionary/parameters you were timing.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Dictionary                                     Grid File                               One Solution Run Time (s)                           All Solutions Run Time                          Total Number of Solutions
--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
reverse_ell_dict.txt                           reverse_ell1.txt                        0.003 s                                             0.006 s                                         1                                          
reverse_ell_dict.txt                           reverse_ell2.txt                        0.005 s                                             0.004 s                                         1
nyt_mini1_dict.txt                             nyt_mini1.txt                           0.006 s                                             0.006 s                                         1
nyt_mini1_dict.txt                             nyt_mini1_noblack.txt                   0.005 s                                             0.006 s                                         1
nyt_mini1_dict.txt                             nyt_mini2.txt                           0.006 s                                             0.006 s                                         0
nyt_mini1_dict.txt                             nyt1.txt                                0.004 s                                             0.005 s                                         0 
nyt_mini1_dict.txt                             nyt2.txt                                0.005 s                                             0.005 s                                         0 
blackout_dict1.txt                             blackout1.txt                           0.006 s                                             0.006 s                                         3
blackout_dict1.txt                             blackout2.txt                           0.005 s                                             0.006 s                                         1
blackout_dict1.txt                             blackout3.txt                           0.005 s                                             0.006 s                                         3
blackout_dict2.txt                             blackout1.txt                           0.006 s                                             0.006 s                                         3
blackout_dict2.txt                             blackout2.txt                           0.005 s                                             0.005 s                                         0
blackout_dict2.txt                             blackout3.txt                           0.004 s                                             0.005 s                                         3
sporcle1_dict1.txt                             sporcle1_constraintsA.txt               0.024 s                                             0.024 s                                         1
sporcle1_dict1.txt                             sporcle1_constraintsB.txt               0.025 s                                             0.028 s                                         40
sporcle1_dict2.txt                             sporcle1_constraintsA.txt               Takes too long                                      Takes too long                                  N/A
sporcle1_dict2.txt                             sporcle1_constraintsB.txt               0.038 s                                             0.034 s                                         20
sporcle1_dict3.txt                             sporcle1_constraintsA.txt               Takes too long                                      Takes too long                                  N/A
sporcle1_dict3.txt                             sporcle1_constraintsB.txt               0.027 s                                             0.026 s                                         20
sporcle1_dict4.txt                             sporcle1_constraintsA.txt               Takes too long                                      Takes too long                                  N/A
sporcle1_dict4.txt                             sporcle1_constraintsB.txt               0.004 s                                             0.005 s                                         20
combo_test_dict.txt                            combo_test_dict.txt                     0.278 s                                             0.285 s                                         21
overlap_test_dict.txt                          overlap_test.txt                        0.008 s                                             0.008 s                                         1
invalid_constraints_text_dict.txt              invalid_constraints_text.txt            0.004 s                                             0.005 s                                         0


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)


