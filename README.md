# Nautok 20 
Nautok 20 is a testing application created with C++ and Qt. It allows you to complete and create tests with multiple choice single or multiple select questions.


## How to run the application

1. Download nautok_20.zip from the latest release
2. Extract the content
3. Run nautok_20.exe

Unfortunately, there are no releases for UNIX-like operating systems. You can find source files at the main branch, so it is possible to run the app throw Qt Creator. 

## How to launch the test

1. Run the application
2. Select a test file with a file extension .test
3. Hit the run button

## How to create the test

All tests are should be formatted in exact way with .test file extension

1. Create an empty file with a file extension .test
2. Add questions following this format:
```
<type> <question> <number of right answers> <total number of answers> [right answer 1] [right answer 2] ... [right answer <last>] [wrong answer 1] [wrong answer 2] ...
```
Each question should be in exactly one line.

#### Type
There can be 2 types:
- "multi" used for multiple choice multi select questions.
- "radio" used for multiple choice single select questions.
Enter without quotes
#### Question
Any text in quotes that will be used as question text.

#### Answers
After putting number of right answers and total number of answers you should enter **all** right answers and then you should enter wrong answers. Total number of answers should not be exceeded.

Example: 

```
multi "x**2 = 9" 2 4 "x = 3" "x = -3" "x = 0" "x = 2"
radio "3 + 3 = ?" 1 4 "6" "7" "8" "9"
radio "5 + 3 = ?" 1 4 "8" "7" "6" "9"
radio "9 + 3 = ?" 1 4 "12" "7" "8" "9"
radio "11 + 3 = ?" 1 4 "14" "11" "8" "9"
radio "13 + 3 = ?" 1 4 "16" "17" "18" "19"
```

This test will have 4 single select questions and 1 multiple select question. You can find this in release archive with the name "algebra.test", so it is possible to run.

# Few details
By default, test answers and questions are randomly shuffled. Currently, it is impossible to turn of this function with getting into source files.
I am currently working on test constructor, so it will be easier to create and format tests.
