# Automata

### DFA Minimization
This program takes DFA as input and transforms it into another DFA with minimum number of states.

**Input**
```
   n k a           n = total number of states , k = total number of transitions , a = total number of final states
   a1,a2,a3...     final states
   from,sybmol,to 
   s1...........   first transition
   .............
   .............
   sk...........   kth transition

```
**Algorithm : Partition Method**
 
- Use of binary sequences to store different parition.
- First store final states in one variable using binary operation **OR** so that every 1 in 
  sequence is a symbol of final state.
- Then Store total states in another variable using same method as previous step. After this we use DFS to find only the recachable
  states and do **AND** with both variables to eliminate the non reachable states.
- Store the two sequences in an array named parition and start checking if there is any pair in any of parition who goes to different partition's states after taking same symbol.
  If this happens then we make different partition and split those states and continue the operation.
- After this, we get final partitions which are going to be new states and the partitions which include
  previous final states are going to be final state for this new DFA also. 
- The we analyze the transitions and make the appropriate transitions seeing the previous transitions.

**Output**

 Similiar to the input format but with new number of states and transitions , and the state number is representing the 
 partition number.


### Regx to NFA

The program takes a regular expression as input and forms a corresponding NFA table.
The regex alphabet will only consist of lower-case letters (a − z). The operators that will be used are:
1. '+' for union
2. '*' for closure
3. Continuous letters will signify concatenation
4. () for grouping expressions

NFA table will be in same format as previous for DFA
```
   n k a           n = total number of states , k = total number of transitions , a = total number of final states
   a1,a2,a3...     final states
   from,sybmol,to 
   s1...........   first transition
   .............
   .............
   sk...........   kth transition

```
