# multithreaded-algorithms
**1) Matrix Multiplication**

The algorithm implements two variations of this algorithm:

<p>**a.** The computation of each element of the output matrix happens in a thread.</p>

<p>**b.** The computation of each row of the output matrix happens in a thread.</p>

The program should read two input matrices in a certain format as mentioned in the &quot;matrix-readme.txt&quot; file associated with project (Output format is also mentioned).

**2) Merge Sort**

Merge sort is an O (n log n) comparison-based sorting algorithm. It is a divide and conquer algorithm.

Conceptually, a merge sort works as follows:

<p>**1)** If the list is of length 0 or 1, then it is already sorted. Otherwise:</p>

<p>**2)** Divide the unsorted list into two sub-lists of about half the size.</p>

<p>**3)** Sort each sub-list recursively by re-applying the merge sort.</p>

<p>**4)** Merge the two sub-lists back into one sorted list.</p>

the program is implemented using Pthreads. Each time the list is divided;two threads are created to do merge-sort on each half separately. This step is repeated recursively until each sub-list has only one element.
