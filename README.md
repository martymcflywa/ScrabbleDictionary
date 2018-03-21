| CI/CD    | Build status |
|----------|--------------|
| AppVeyor | [![appveyor](https://ci.appveyor.com/api/projects/status/mtf9dxn6tweovo47/branch/master?svg=true)](https://ci.appveyor.com/project/martymcflywa/scrabbledictionary/branch/master) |

# Implementation overview

## Part 1
- During dictionary parsing, answers for tasks are evaluated and cached in the same extraction loop
    - No need for lookups, extra loops later on when requesting what the longest word is, etc.

## Part 2
- After dictionary is loaded, glossary is generated on a separate thread
    - Allows user to interact and recall results for part 1
- Any attempts to select the glossary menu item before glossary task is finished are denied
- User is notified when glossary is generated
    - User can then select glossary menu item

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

# Part 2
- An extension of Part 1
- Implement these additional tasks and add them to the menu

## Basic tasks
1. Prompt user for a word and report all words that rhyme
    - Last 3 letters must be the same
2. Print a word's scrabble score following its definition
    - Does not need its own menu
    - Can be implemented as part of definition search in part 1
    - See appendix for calculating scrabble score

## Intermediate tasks
1. Prompt user for a word and report all words that are anagrams of it
2. Let user enter a string of letters and return the word with the highest scrabble score

## Advanced tasks
Create a glossary generator.

1. Parse `many_english_works.txt` one word at a time
    - Every time a word is found that exists in the dictionary, increment `usageFrequency`
2. Parse `new_work.txt` one word at a time
    - For every word that is in the dictionary and is `rareWord()`, print word and definition
    - Do not print the same word twice
3. Save glossary to text file