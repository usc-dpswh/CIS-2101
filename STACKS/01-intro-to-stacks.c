// Stacks apply to INSERTION and DELETION. Think of a stack as inserting CDs. If you want to insert a CD, you can only insert at the very top. If you want to take out a CD or DELETE, you can also take out from the top. If you wanted to take out the very first CD from a huge stack of CDs, you need to take out all the CDs first before you can access the very first CD.

// We can use ARRAY and LINKED LISTS in stack.

// LAST IN, FIRST OUT principle for STACK for insertion and deletion. (LIFO or FILO)

// Insertion  ==>   Push
// Deletion   ==>   Pop

//* Operations on Stack Data Structure

//? push(x)
// You can only insert data of similar datatypes.

//? pop()
// You don't need to pass anything as you just pop or remove the element from the TOP.

//? peek()/top()
// Return top most element of the stack WITHOUT removing it from the stack.

//? isEmpty()
// Return TRUE if data is present in stack.

//? isFull()
// Return TRUE if data is full in stack.

//* Implementing a Stack
// First, we allocate memory using static/dynamic memory allocation for stack. If static, we use ARRAYS. If dynamic, we use LINKED LISTS.

// top = -1 we assume. Underflow condition (??)

//? push(x)
// We use top++

//? pop()
// We use top--

//* Application of Stack

//? Reverse a String
// abcd   =>  dcba

//? Undo mechanism
// abcde  =>  abcd

//? Recursion/function call
// Stored in stack.

//? { } of curly braces