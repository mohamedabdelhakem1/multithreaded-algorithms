# multithreaded-algorithms
**1) Matrix Multiplication**

The algorithm implements two variations of this algorithm:

**a.** The computation of each element of the output matrix happens in a thread.

**b.** The computation of each row of the output matrix happens in a thread.

The program should read two input matrices in a certain format as mentioned in the &quot;matrix-readme.txt&quot; file associated with project (Output format is also mentioned).

**2) Merge Sort**

Merge sort is an O (n log n) comparison-based sorting algorithm. It is a divide and conquer algorithm.

Conceptually, a merge sort works as follows:

**1)** If the list is of length 0 or 1, then it is already sorted. Otherwise:

**2)** Divide the unsorted list into two sub-lists of about half the size.

**3)** Sort each sub-list recursively by re-applying the merge sort.

**4)** Merge the two sub-lists back into one sorted list.

the program is implemented using Pthreads. Each time the list is divided;two threads are created to do merge-sort on each half separately. This step is repeated recursively until each sub-list has only one element.
