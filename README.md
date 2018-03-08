[![Build status](https://ci.appveyor.com/api/projects/status/mtf9dxn6tweovo47/branch/master?svg=true)](https://ci.appveyor.com/project/martymcflywa/scrabbledictionary/branch/master)


# CSP2104 Assignment

## Overview
- Create an app which loads an English dictionary
- Perform certain tasks using that dictionary
- Worth 40%
- Contains tasks of varying complexity
- Expected to consult sources outside of unit materials in order to accomplish goals

### Marks and due dates
- Part 1
    - 10 marks
    - Due 2018-04-23 17:00
- Part 2
    - 30 marks
    - Due 2018-05-25 17:00

### Learning outcomes
- Formulate computer algorithms using
    - Operations
    - Control structures
    - Classes
- Write, test and debug computer programs written in C++
- Design / implement class library as an abstraction
    - Using facilities of C++ and environment
- Implement efficient exception handling mechanisms in user defined classes

### Submission
- Penalties apply for late submissions
- Single zipped file containing entire **Visual Studio 2017** project
- Filename: `<surname>_<studentid>.zip`
- Must be submitted via Blackboard

# Part 1

## Acceptance criteria
- Parse dictionary file `dictionary2018.txt`
- Load each record into a new instance of a `Word` class
- Add each instance of `Word` to a collection contained in a `Dictionary` class
- Display a menu of tasks the app can perform
    1. Enter a word
        - If exact word is found in dictionary
            - Prepend with type
                - `Noun (n.)`
                - `Verb (v.)`
                - `Adverb (adv.)`
                - `Adjective (adj.)`
                - `ProperNoun (pn.)`
                - `NounAndVerb (n. v.)`
                - `Preposition (prep.)`
                - `MiscWords (misc.)`
            - Print word's definition
        - If word is not in dictionary, print `word not found`
    2. Find the longest word in the dictionary
    3. Find the word(s) which end in `logy` and `length <= 7`

## Classes
- Must follow strict naming convention

### `Word` class
- Fields
    - `string word`
        - The word in the dictionary
    - `enum type`
        - The word type, ie. noun
    - `string definition`
- Methods
    - Getters for `word`, `type`, and `definition`
    - `printDefinition`
        - Print the word's definition to console in accordance with acceptance criteria above

### `Dictionary` class
- Maintains an appropriate `STL` container of `Word` objects
- Loads the dictionary file into its collection of `Word` objects
- Performs the tasks needed for this assignment
- Methods
    - `loadDictionary()`
    - Other appropriate methods to implement requirements