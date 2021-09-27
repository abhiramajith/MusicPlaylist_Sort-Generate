The following are the instructions to ensure the program works correctly.

First go to 'assignment|Debug' on the left of the run button and click 'Edit Configurations'.

In here enter the working directory as '$ProjectFileDir$' so the program will search for the 
text files in the project file directory.

If you wish you can save your text file of songs and artists on the same level as main.c and
to use it in the program simply enter the files name, (example : yourfilehere.txt), where it says 
'Program Arguments' in Edit Configurations.

Alternatively you can save your text file in the folder cmake-build-debug and execute the program
and your file in the commandline terminal situated at the bottom of the screen. Ensure you are in
the cmake-build-debug directory and if not cd into it using 'cd cmake-build-debug'.

Once in the directory simply enter the command as follows "assignment.exe yourfilehere.txt" to use 
your text file.