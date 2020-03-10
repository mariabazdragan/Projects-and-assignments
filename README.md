# Projects-and-assignments

#2cc

You have two queues at your disposal. You have to introduce a list of letters and "sort" it in a given order only using the two queues.
Observations: pop eliminates the first character in a queue, push adds a character at the end of the queue.

Operations:

'character' -> the character is pushed into the first queue
1 -> pop character from the first queue and push it into the second queue
2 -> pop character from the second queue and push it into the first queue
I_1 -> pop character from the first queue and print it
I_2 -> pop character from the second queue and print itYou have two queues at your disposal. You have to introduce a list of letters
and "sort" it in a given order only using the two queues.
Observations: pop eliminates the first character in a queue, push adds a character at the end of the queue.

Initially, we have two lists: shuffled_data and data. We are to order elements in shuffled data in the order given in data. 
For simplicity, let Q1 be the first queue, and Q2 the second. 
We introduce the elements from shuffled_data into Q1, and we cycle through it using a counter, checking at every step if the current 
element is the same as Q1's front; if so, we pop it from Q1 and we add it into an array of solutions and we continue with the next element 
in data; if not, we pop it from Q1 and push it into Q2. 
We repeat these steps for Q2: compare Q2's front with current element in data, if they're equal, pop it from Q2 and add it into the vector 
of solutions, and go to the next element in data; if not, pop it from Q2 and push it into Q1. 
To save time, the algorithm can start after adding a single element to Q1, but we need more checks so we won't try to pop an empty queue.

