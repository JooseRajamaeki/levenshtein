This repository implements computing Levenshtein distance and matching words using it.

The application files are in the folder "src". The application has no outside dependencies apart from the standard library of C++. The application consists of the files:
levenshtein.cpp
levenshtein.hpp
main.cpp

Some tests are performed in the file test.cpp, which is located in the folder "test". The folder "test" also includes the sample of how to use the application from command line. This sample is in the file test.cmd.

The application is run on command line using the following syntax.
```
program_name --vocabulary vocabulary.txt --words word_list.txt --output output.txt
```
Each line of word_list.txt is matched to a line in vocabulary.txt using Levenshtein distance. The outputs are written to output.txt.