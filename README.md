# **TownOfSalem2Simulator**
A program that simulates the generation of role lists in Town of Salem 2.

# **Introduction**
This program provides 3 main functionalities:
* Generate a single role list.  
* Simulate a large number of games and gather faction, alignment, and role frequency data.  
* Profile the performance of your PC.

Note that, for now, this only works on Windows.

# **How to use it**
1. Download the "main.exe" file from the release. Your antivirus might not like this: you can disable it or allow this specific program to run.
2. Drop main.exe into whatever directory you like. In the same directory, create a .txt file called "main_config".

Depending on which of the above functionalities you wish to use, you will need to fill out main_config.txt differently.

## **1. Simulate a large number of games**
To do this, populate main_config.txt as follows. Make sure there are no spaces at the end of any of the lines.
1. Write "0" in the first line. This tells the program you are generating a large number of games.
2. Put the number of games you wish to generate on the second line. This can be written normally (like 1000), or in scientific notation (like 1E+3).
3. Write the slots in the gamemode you wish to generate, comma separated, without spaces (like "Any,Any,Any")
4. Write the filename for the factions data to be stored in on the next line.
5. Write the filename for the alignemnts data to be stored in on the next line.
6. Write the filename for the roles data to be stored in on the next line.
7. Write the folder for the data to be written into on the next line.
8. Write the subfolder for the factions data to be written to on the next line.
9. Write the subfolder for the alignments data to be written to on the next line.
10. Write the subfolder for the roles data to be written to on the next line.
11. Write any roles you would like to exclude on the next line, comma separated without spaces (like "Pirate,Hex Master,Vigilante").
12. Write "0" on the final line.

Make sure the folders you wrote into main_config.txt already exist - the program will not create them.
Once this has been done, save main_config.txt, and run main.exe. A terminal will open up displaying the information in main_config.txt. Your CPU usage will stay at 100% until the program is finished.
When the program is finished, the terminal will automatically close. You will find CSV files like "numRoles0.csv" in the folders you specified. This is the output data.

On a mid-range system (Ryzen 2700X), around 10 million games per second is possible with this program.

Example file:
```
1
100000000
Any,Any,Any,Any,Any,Any,Any,Any,Any,Any,Any,Any,Any,Any,Any,
numFactions
numAlignments
numRoles
G:/test_output/
factions
alignments
roles
Poisoner,
0
```

## **2. Generating a single role list.**
1. Write "1" in the first line. This tells the program you are generating a single game.
2. Write the slots in the gamemode you wish to generate, comma separated, without spaces (like "Any,Any,Any")
3. Write any roles you would like to exclude on the next line, comma separated without spaces (like "Pirate,Hex Master,Vigilante")

Example file:
```
0
Any,Any,Any,Any,Any,Any,Any,Any,Any,Any,Any,Any,Any,Any,Any,
Plaguebearer,
```

A terminal will pop up for a brief second. You will find the generated roles in a file called "main_output.txt" in the same directory as main.exe.

## **3. Profiling your PC's performance**
For this, all you need to do is write "2" at the top of main_config.txt, and then run main.exe. You will get an output file called "profiler_data.csv".
In the first column of profiler_data.csv, the number of games generated is shown. On the second column, the amount of time, in microseconds, taken to do so is shown.

Currently, you have to do your own linear regression to estimate the time - this will be done for you when the UI is finished.
