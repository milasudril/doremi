#Makefile generated by wand

all:doremi.exe doremi.o midiport.o 

doremi.o:.\doremi.cpp .\doremi.h .\midiport.h D:\torbjorr\program\herbs\application.h D:\torbjorr\program\herbs\array.h D:\torbjorr\program\herbs\chartype.h D:\torbjorr\program\herbs\intformat.h D:\torbjorr\program\herbs\memblock.h D:\torbjorr\program\herbs\memory.h D:\torbjorr\program\herbs\messageprinter.h D:\torbjorr\program\herbs\messageprinterstdio.h D:\torbjorr\program\herbs\reference.h D:\torbjorr\program\herbs\runnable.h D:\torbjorr\program\herbs\streamspec.h D:\torbjorr\program\herbs\string.h D:\torbjorr\program\herbs\stringbase.h D:\torbjorr\program\herbs\stringformat.h
	g++ ".\doremi.cpp" -Wall -c -std=c++11 -g -municode -I"." -I"D:\torbjorr\program" -I"D:\msys-win64\include" -I"." -o "doremi.o"

doremi.exe:D:\torbjorr\program\herbs\win32\messageprinterstdio.o D:\torbjorr\program\herbs\win32\chartype.o D:\torbjorr\program\herbs\win32\memory.o D:\torbjorr\program\herbs\win32\textconverter.o D:\torbjorr\program\herbs\win32\stringsys.o D:\torbjorr\program\herbs\win32\application.o .\doremi.o D:\torbjorr\program\herbs\win32\stringformat.o D:\torbjorr\program\herbs\win32\intformat.o D:\torbjorr\program\herbs\win32\maindefault.o D:\torbjorr\program\herbs\win32\exceptionsystem.o D:\torbjorr\program\herbs\win32\seh.o D:\torbjorr\program\herbs\win32\floatformat.o D:\torbjorr\program\herbs\win32\memoryin.o D:\torbjorr\program\herbs\win32\filein.o D:\torbjorr\program\herbs\win32\tokenizer.o D:\torbjorr\program\herbs\win32\dirspellreader.o D:\torbjorr\program\herbs\win32\streamin.o D:\torbjorr\program\herbs\win32\textdecoder.o D:\torbjorr\program\herbs\win32\directory.o D:\torbjorr\program\herbs\win32\dirspellwriter.o D:\torbjorr\program\herbs\win32\textencoder.o D:\torbjorr\program\herbs\win32\streamout.o D:\torbjorr\program\herbs\win32\exceptionfilecreat.o D:\torbjorr\program\herbs\win32\exceptionmissing.o D:\torbjorr\program\herbs\win32\path.o D:\torbjorr\program\herbs\win32\fileout.o .\doremi-main.cpp .\doremi.h D:\torbjorr\program\herbs\application.h D:\torbjorr\program\herbs\chartype.h D:\torbjorr\program\herbs\maindefault.h D:\torbjorr\program\herbs\messageprinter.h D:\torbjorr\program\herbs\messageprinterstdio.h D:\torbjorr\program\herbs\reference.h D:\torbjorr\program\herbs\runnable.h D:\torbjorr\program\herbs\streamspec.h
	g++ ".\doremi-main.cpp" "D:\torbjorr\program\herbs\win32\messageprinterstdio.o" "D:\torbjorr\program\herbs\win32\chartype.o" "D:\torbjorr\program\herbs\win32\memory.o" "D:\torbjorr\program\herbs\win32\textconverter.o" "D:\torbjorr\program\herbs\win32\stringsys.o" "D:\torbjorr\program\herbs\win32\application.o" ".\doremi.o" "D:\torbjorr\program\herbs\win32\stringformat.o" "D:\torbjorr\program\herbs\win32\intformat.o" "D:\torbjorr\program\herbs\win32\maindefault.o" "D:\torbjorr\program\herbs\win32\exceptionsystem.o" "D:\torbjorr\program\herbs\win32\seh.o" "D:\torbjorr\program\herbs\win32\floatformat.o" "D:\torbjorr\program\herbs\win32\memoryin.o" "D:\torbjorr\program\herbs\win32\filein.o" "D:\torbjorr\program\herbs\win32\tokenizer.o" "D:\torbjorr\program\herbs\win32\dirspellreader.o" "D:\torbjorr\program\herbs\win32\streamin.o" "D:\torbjorr\program\herbs\win32\textdecoder.o" "D:\torbjorr\program\herbs\win32\directory.o" "D:\torbjorr\program\herbs\win32\dirspellwriter.o" "D:\torbjorr\program\herbs\win32\textencoder.o" "D:\torbjorr\program\herbs\win32\streamout.o" "D:\torbjorr\program\herbs\win32\exceptionfilecreat.o" "D:\torbjorr\program\herbs\win32\exceptionmissing.o" "D:\torbjorr\program\herbs\win32\path.o" "D:\torbjorr\program\herbs\win32\fileout.o" "-liconv" "-lmidiport.o" -Wall -std=c++11 -g -municode -I"." -I"D:\torbjorr\program" -I"D:\msys-win64\include" -I"." -o "doremi.exe"

midiport.o:.\midiport.cpp .\midiport.h D:\torbjorr\program\herbs\array.h D:\torbjorr\program\herbs\chartype.h D:\torbjorr\program\herbs\memblock.h D:\torbjorr\program\herbs\memory.h D:\torbjorr\program\herbs\string.h D:\torbjorr\program\herbs\stringbase.h
	g++ ".\midiport.cpp" -Wall -c -std=c++11 -g -municode -I"." -I"D:\torbjorr\program" -I"D:\msys-win64\include" -I"." -o "midiport.o"

