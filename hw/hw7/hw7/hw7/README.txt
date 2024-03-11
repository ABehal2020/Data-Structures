HOMEWORK 7: HALLOWEEN COSTUME MAPS


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



ORDER NOTATION ANALYSIS (ORIGINAL VERSION W/MAPS):
of each of the costume shop operations (please be concise!)

Variables provided by the HW handout:
n = number of different costumes in the shop
m = maximum number of copies of a given costume
c = number of customers who visit the shop

addCostume: O(log n) because we use the map operator [] to find the appropriate costume (log n) and increment its number of copies appropriately

rentCostume: O(m + log n + log c) because we find the correct key in the costume shop and then update the frequencies of the costumes accordingly using the maps [] operator and then loop over the list up to m times and remove the person from the previously held costume if applicable

lookup: O(m + log n) because we have to find the correct key-value pair in the costume_shop map (log n) and then iterate over each of the customers in the list in the value for the corresponding correct costume key up to m times in a loop

printPeople: O(c) because we have to iterate c times in a loop to print out the customers and their corresponding costumes from the people map


EXTRA CREDIT (W/O MAPS)
What alternate data structures did you use?  What is the order
notation of each operation without maps?  What is the expected
performance difference?  Summarize the results of your testing.

I used only lists instead.

Variables provided by the HW handout:
n = number of different costumes in the shop
m = maximum number of copies of a given costume
c = number of customers who visit the shop

addCostumeList: O(n) because you have to iterate through the whole list of costumes checking to see if the costume is already there (if not, you then have to push_back a new costume and its frequency)

rentCostumeList: O(n + m + c) because you have to iterate through the whole list of customers to find out which customer's costume to change (if the customer is a returning customer), iterate through the whole list of costumes to find which costumes' frequencies to update, and then iterate through the list of customers m times to erase the customer from the old corresponding costume's list

lookupList: O(c + m) because you have to iterate through the whole list of customers to check if the costume is in the inventory and then iterate through the list<People> corresponding to a costume up to m times to erase the person if the person is returning an old costume before renting a new one

printPeopleList: O(c) because you have to iterate through the whole list of customers to print them out and their corresponding costumes

The wall clock times for the large_input.txt with both versions for the large_input.txt was 0.005 seconds.

Running it on the custom_large.txt test case that I made, the map version ran in 1.786 seconds while the list version ran in 3.490 seconds.


MISC. COMMENTS TO GRADER:  
(optional, please be concise!)






