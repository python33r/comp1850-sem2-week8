# Task 1: Student Record Management

This activity introduces the use of structures (`struct`) in C to manage related data as a single unit. 

You'll create a student record system that stores and manipulates student information.

## Learning Objectives

* Define and use structures in C
* Initialise structure variables
* Access and modify structure members
* Perform calculations with structure data
* Understand the difference between structure member access with dot notation (`.`) and arrow notation (`->`)

## Code structure

`student_record.h` - structure definition, function headers

`student_record.c` - function implementations

## The Task

1. Complete the implementation of a student record system using the provided stub code.
2. The student_record structure contains:
   - Name (as a character array)
   - ID number (as an integer)
   - Three module marks (as floating-point numbers)
3. Create and initialise a student variable
4. Calculate and display the average module mark

## Step-by-Step Instructions

1. Review the `struct student_record` definition provided in the files
2. Initialise a student variable with sample data
3. Implement the `calculate_average` function to compute the average of the three module marks
4. Print the student information

## Testing Your Implementation

As you implement each function, test it to ensure it works correctly:
- Verify that student information is correctly stored
- Check that the average calculation is accurate

## Tips for Working with Structures

* Access structure members using the dot operator (`.`) for structure variables
* When working with string data remember to use the `<string.h>` functions