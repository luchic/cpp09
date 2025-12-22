# Ford-Johnson algorithm

## Origin sequence:
 2 3 18 19 8 14 6 9 21 16 5 10 23 15 1 11 17 20 12 22 13 7 4

### First step divison of sorting

#### Recursion level 1:
##### Before sorting
[2 3] [18 19] [8 14] [6 9] [21 16] [5 10] [23 15] [1 11] [17 20] [12 22] [13 7] 4

##### After sorting
[2 3] [18 19] [8 14] [6 9] [16 21] [5 10] [15 23] [1 11] [17 20] [12 22] [7 13] 4

We just swap a cuple of numbers in pairs.

#### Recursion level 2:
##### Before sorting
{[2 3] [18 19]} {[8 14] [6 9]} {[16 21] [5 10]} {[15 23] [1 11]} {[17 20] [12 22]} [7 13] 4
##### After sorting
{[2 3] [18 19]} {[6 9] [8 14]} {[5 10] [16 21]} {[1 11] [15 23]} {[17 20] [12 22]} [7 13] 4

We compare the biggest element in the pair to decide if we need to swap the two pairs.

#### Recursion level 3:
##### Before sorting
[{[2 3] [18 19]} {[6 9] [8 14]}] [{[5 10] [16 21]} {[1 11] [15 23]}] {[17 20] [12 22]} [7 13] 4
##### After sorting
[{[6 9] [8 14]} {[2 3] [18 19]}] [{[5 10] [16 21]} {[1 11] [15 23]}] {[17 20] [12 22]} [7 13] 4

#### Recursion level 4:
##### Before sorting
{[{[6 9] [8 14]} {[2 3] [18 19]}] [{[5 10] [16 21]} {[1 11] [15 23]}]} {[17 20] [12 22]} [7 13] 4
##### After sorting
[{[6 9] [8 14]} {[2 3] [18 19]}] [{[5 10] [16 21]} {[1 11] [15 23]}] {[17 20] [12 22]} [7 13] 4


## Insertion step of algorithm
### Back to level 4
##### Starting sequence
[6 9 8 14 2 3 18 19] [5 10 16 21 1 11 15 23] | [17 20 12 22 7 13 4]

##### Non-participating
[17 20 12 22 7 13 4]

##### Pend
[ empty ]

##### Main
[6 9 8 14 2 3 18 19] [5 10 16 21 1 11 15 23]

### Back to level 3:
##### Starting sequence
[6 9 8 14]b1 [2 3 18 19]a1 [5 10 16 21]b2 [1 11 15 23]a2 [17 20 12 22]b3 | [7 13] 4

##### Non-participating
[7 13] 4

##### Pend 
{5 10 16 21}b2 {17 20 12 22}b3

##### Main
{6 9 8 14}b1 {2 3 18 19}a1 {1 11 15 23}a2

now begin with b3 to compare b1 a1 and a2, b3 less the a2 and bigger then a1, that why we insert b3 between a1 and a2

#### Insertion
##### Pendin
{5 10 16 21}b2

##### Main
{6 9 8 14}b1 {2 3 18 19}a1 {17 20 12 22}b3 {1 11 15 23}a2

Now we know that b2 connected to a2. I don't need to compare with a2 that I need to compare only with (b1 a1 and b3)
#### Insertion

##### Pendin
{ empty }

##### Main
{6 9 8 14}b1 {2 3 18 19}a1 {5 10 16 21}b2 {17 20 12 22}b3 {1 11 15 23}a2

#### Secuence after level 3
{6 9 8 14} {2 3 18 19} {5 10 16 21} {17 20 12 22} {1 11 15 23} [7 13] 4

### Back to level 2
####  Starting sequence
{6 9}b1 {8 14}a1 {2 3}b2 {18 19}a2 {5 10}b3 {16 21}a3 {17 20}b4 {12 22}a4 {1 11}b5 {15 23}a5 {7 13}b6 | 4

##### Non-participating
4
##### Pend
{2 3}b2 {5 10}b3 {17 20}b4 {1 11}b5 {7 13}b6

##### Main
{6 9}b1 {8 14}a1 {18 19}a2 {16 21}a3 {12 22}a4 {15 23}a5

Begin wiht b3 (This special numbers) Begin compare with a2, because b3 is connectied to a3 and can't be bigger then this number.
##### Insertion

##### Pend
{2 3}b2 {17 20}b4 {1 11}b5 {7 13}b6

##### Main
{6 9}b1 {5 10}b3 {8 14}a1 {18 19}a2 {16 21}a3 {12 22}a4 {15 23}a5

##### Insertion
On this level b2 is lower then a2 and begin compare with a1.
##### Pend
{17 20}b4 {1 11}b5 {7 13}b6

##### Main
{2 3}b2  {6 9}b1 {5 10}b3 {8 14}a1 {18 19}a2 {16 21}a3 {12 22}a4 {15 23}a5

##### Insertion
Now we have jacobsthal number 5: And that why we begining to insert with b5
##### Pend
{17 20}b4 {7 13}b6

##### Main
{2 3}b2  {6 9}b1 {5 10}b3 {1 11}b5 {8 14}a1 {18 19}a2 {16 21}a3 {12 22}a4 {15 23}a5

##### Insertion
Now we have {7 13}b6 and jacobsthal number 5 is run out: Now we just take this element and insert in reverse way. But if we insert b3 in this way, the area of search still doesn't include a3 and further. In this case, it's an odd element, so there is no corresponding bound element. 
##### Pend

##### Main
{2 3}b2  {6 9}b1 {5 10}b3 {1 11}b5 {7 13}b6 {8 14}a1 {18 19}a2 {17 20}b4 {16 21}a3 {12 22}a4 {15 23}a5

##### Out on level 2
{2 3} {6 9} {5 10} {1 11} {7 13} {8 14} {18 19} {17 20} {16 21} {12 22} {15 23} 4


### Back to level 1

#### Starting sequence
2b1 3a1 6b2 9a2 5b3 10a3 1b4 11a4 7b5 13a5 8b6 14a6 18b7 19a7 17b8 20a8 16b9 21a9 12b10 22a10 15b11 23a11 4b12

##### Insertion (3)
So begin with b3
##### Pend
6b2 1b4 7b5 8b6 18b7 17b8 16b9 12b10 15b11 4b12
##### Main
2b1 3a1 5b3 9a2 10a3 11a4 13a5 14a6 19a7 20a8 21a9 22a10 23a11 

##### Insertion (3)
And now b2
##### Pend
1b4 7b5 8b6 18b7 17b8 16b9 12b10 15b11 4b12
##### Main
2b1 3a1 5b3 6b2 9a2 10a3 11a4 13a5 14a6 19a7 20a8 21a9 22a10 23a11 

##### Insertion (5)
All numbers run out that why begin with b5
##### Pend
1b4 8b6 18b7 17b8 16b9 12b10 15b11 4b12
##### Main
2b1 3a1 5b3 6b2 7b5 9a2 10a3 11a4 13a5 14a6 19a7 20a8 21a9 22a10 23a11 

##### Insertion (5)
Go to b4
##### Pend
8b6 18b7 17b8 16b9 12b10 15b11 4b12
##### Main
1b4 2b1 3a1 5b3 6b2 7b5 9a2 10a3 11a4 13a5 14a6 19a7 20a8 21a9 22a10 23a11 

##### Insertion (11)
Go to b11
##### Pend
8b6 18b7 17b8 16b9 12b10 4b12
##### Main
1b4 2b1 3a1 5b3 6b2 7b5 9a2 10a3 11a4 13a5 14a6 15b11 19a7 20a8 21a9 22a10 23a11 

##### Insertion (11)
Go to b10
##### Pend
8b6 18b7 17b8 16b9 4b12
##### Main
1b4 2b1 3a1 5b3 6b2 7b5 9a2 10a3 11a4 12b10 13a5 14a6 15b11 19a7 20a8 21a9 22a10 23a11 

##### Insertion (11)
Go to b9
##### Pend
8b6 18b7 17b8 4b12
##### Main
1b4 2b1 3a1 5b3 6b2 7b5 9a2 10a3 11a4 12b10 13a5 14a6 15b11 16b9 19a7 20a8 21a9 22a10 23a11 

##### Insertion (11)
Go to b8
##### Pend
8b6 18b7 4b12
##### Main
1b4 2b1 3a1 5b3 6b2 7b5 9a2 10a3 11a4 12b10 13a5 14a6 15b11 16b9 17b8 19a7 20a8 21a9 22a10 23a11 

##### Insertion (11)
Go to b7
##### Pend
8b6 4b12
##### Main
1b4 2b1 3a1 5b3 6b2 7b5 9a2 10a3 11a4 12b10 13a5 14a6 15b11 16b9 17b8 18b7 19a7 20a8 21a9 22a10 23a11 

##### Insertion (11)
Go to b6
##### Pend
4b12
##### Main
1b4 2b1 3a1 5b3 6b2 7b5 8b6 9a2 10a3 11a4 12b10 13a5 14a6 15b11 16b9 17b8 18b7 19a7 20a8 21a9 22a10 23a11 

##### Insertion (??)
Again no this specila number. For example I had smth like b12 and b13 i should begin with b13 and then b12. But now i have only one element, that why insert element b12.
##### Pend
##### Main
1b4 2b1 3a1 4b12 5b3 6b2 7b5 8b6 9a2 10a3 11a4 12b10 13a5 14a6 15b11 16b9 17b8 18b7 19a7 20a8 21a9 22a10 23a11 

#### Final sequence
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 


## Conclusion:
First step I need sort pairs of pairs, when go down of recursion. 
When go up, i should make insertion and be tolerant with insertion, and during this step I need implement special binary search, to now what numbers i have.
Don't forget about main and pendig elemetns.

?? How calculate Jacob number??
?? And i need some how to now till what number i need to looking for.