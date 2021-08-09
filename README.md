# Howdy!
## Intro
This is a simple database implementation that works with pairs. It can select and delete events that meet a given condition, as well as dividing its code into several files.
<br><br>
Link to [C++ : Yellow Belt] - [Final Task](https://www.coursera.org/learn/c-plus-plus-yellow/programming/n1Nbg/kursovoi-proiekt)
<br><br>
In more detail, our program is able to process a set of commands:
<hr />
- **Add dateevent** — add a pair to the database (date, event);
<br>
- **Print** — output the entire contents of the database;
<br>
- **Find condition** — output all records contained in the database that meet the **condition**;
<br>
- **Del condition** — delete all records from the database that meet the **condition**;
<br>
- **Last date** — output a record with the last event that occurred no later than this date.
<hr />
The conditions in the Find and Del commands impose certain restrictions on dates and events, for example:
<hr />
- **Find date < 2017-11-06** — find all events that happened earlier than November 6, 2017;
<br>
- **Del event != "holiday"** — delete all events from the database except "holiday";
<br>
- **Find date >= 2017-01-01 AND date < 2017-07-01 AND event == "sport event"** — find all the "sport event" events that happened in the first half of 2017;
<br>
- **Del date < 2017-01-01 AND (event == "holiday" OR event == "sport event")** — delete all "holiday" and "sport event" events that occurred before 2017 from the database.
<hr /> 
In both types of commands, the conditions can be empty: all events fall under this condition.
<br>

## Program structure

Below are the descriptions for the project files.
<hr />
- condition_parser.h/cpp — contain an implementation of an abstract syntax tree for arithmetic expressions. The implementation of this algorithm for parsing conditions in the **Find** and **Del** commands is contained in the ParseCondition function, declared and fully implemented in the condition_parser.h/cpp files;p;
<br>
 - token.h/cpp — contain a ready-made tokenizer that is used in the ParseCondition function;
<br>
- database.h/cpp - these files contain the declaration and definition of the Database class;
<br>
- node.h/cpp — these files contain declarations and definitions of the Node class, as well as all its descendants (see above), which are nodes of an abstract syntax tree formed by the ParseCondition function;
<br>
- date.h/cpp — these files contain declarations and definitions of the Date class, the parseDate function, and the output operator to the stream for the Date class;
<br>
- test_runner.h/cpp - these files contain the implementation of a custom test framework.
<br>
- condition_parser_test.cpp - tests...
<br>
- main.cpp — contains a ready-made main function.
<hr />
## Input and output format
The standard input contains commands for working with the database, one command per line. Our program should read them and output the processing results to standard output. The rules for processing commands are given below.
<br>
### Add command

After encountering the **Add dateevent** command, our program should add a pair (**date**, **event**) to the database and then show it when searching (the **Find** command) or printing (the **Print** command). The same events that occurred on the same day do not need to be saved: adding an existing pair (**date**, **event**) to the database should be ignored. Many different events can occur on the same date, the database should be able to save them all.
<br><br>
It is guaranteed that the **date** field in the **Add** command has the format *"Year-Month-Day"*, where the *Year* is an integer from 0 to 9999, the *Month* is the number of the month from 1 to 12 inclusive, the *Day* is the number of the day from 1 to 31 inclusive. The date must be followed by a space separating it from the event. Examples of correct dates: **2017-11-07**, **0-2-31**.
<br><br>
The rest of the line in the **Add** command sets the event. It can contain spaces, so it is convenient to use the getline function to read it. At the same time, it is guaranteed that the event name cannot contain a quotation mark character (**"**). Thus, this character can only occur in the condition in the **Find** and **Del** commands, being the limiter of the event name.
<br><br>
Example
<br><br>
For the **Add 2017-11-07 big sport event**, the program must add a pair (**2017-11-07**, **big sport event**) to the database.

### Del command

After encountering the **Del condition** command, our program should delete all events from the database that satisfy the **condition**, and output the number of deleted records **N** in the format "**Removed N entries**"to standard output. If the condition is empty, the result of executing the command should be clearing the entire database.
<br><br>
Example
<br><br>
Input
```
Add 2017-06-01 1st of June
Add 2017-07-08 8th of July
Add 2017-07-08 Someone's birthday
Del date == 2017-07-08

``` 
Output
```
Removed 2 entries
```
### Print command

After encountering the **Print** command, our program should output all the pairs (*date, event*) that are currently contained in the database. Pairs should be output one per line. They should be sorted by date in ascending order. Events within the same date must be displayed in the order of addition (with the exception of already deleted ones and attempts to add repetitions).
<br><br>
Dates should be output in the format **YYYY-MM-DD**, where G, M, D are the digits of the numbers of the year, month and day, respectively. If a number has fewer digits than necessary, it should be supplemented with zeros, for example: **0001-01-01** — the first of January of the first year.
<br><br>
Example
<br><br>
Input
```
Add 2017-01-01 Holiday
Add 2017-03-08 Holiday
Add 2017-1-1 New Year
Add 2017-1-1 New Year
Print
```
Output
```
2017-01-01 Holiday
2017-01-01 New Year
2017-03-08 Holiday
```
*Note that the "New Year" event is displayed only once, despite the fact that it was added twice. As stated in the description of the Add command, you do not need to save the same events that occurred on the same day.*

### The Find command
After encountering the **Find condition** command, our program should output all the pairs (date, event) that are currently contained in the database and satisfy the **condition**. The output format is similar to the **Print** command. A search with an empty condition is equivalent to the **Print** command. At the end, the command should output the string **Found** _**N**_ **entries**, where _**N**_ is the number of pairs found.
<br><br>
Example
<br><br>
Input
```
Add 2017-01-01 Holiday
Add 2017-03-08 Holiday
Add 2017-01-01 New Year
Find event != "working day"
Add 2017-05-09 Holiday
```
Output
```
2017-01-01 Holiday
2017-01-01 New Year
2017-03-08 Holiday
Found 3 entries
```

### The Last command

Using the Last date command, you need to output the last of the events that occurred by the date. More formally:<br>
among all the available event dates, you need to find the largest one that does not exceed date;
from all events with this date, select the last one added and output it in a format similar to the format of the Print command;
if the date is less than all the available dates, it is necessary to output "No entries".
<br><br>
Example
<br><br>
Input
```
Add 2017-01-01 New Year
Add 2017-03-08 Holiday
Add 2017-01-01 Holiday
Last 2016-12-31
Last 2017-01-01
Last 2017-06-01
Add 2017-05-09 Holiday
```
Output
```
No entries
2017-01-01 Holiday
2017-03-08 Holiday
```

### Example

Input
```
Add 2017-11-21 Tuesday
Add 2017-11-20 Monday
Add 2017-11-21 Weekly meeting
Print
Find event != "Weekly meeting"
Last 2017-11-30
Del date > 2017-11-20
Last 2017-11-30
Last 2017-11-01
```
Output
```
2017-11-20 Monday
2017-11-21 Tuesday
2017-11-21 Weekly meeting
2017-11-20 Monday
2017-11-21 Tuesday
Found 2 entries
2017-11-21 Weekly meeting
Removed 2 entries
2017-11-20 Monday
No entries
```