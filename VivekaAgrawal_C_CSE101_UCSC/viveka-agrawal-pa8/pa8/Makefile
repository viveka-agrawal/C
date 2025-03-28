#------------------------------------------------------------------------------
#  Makefile
#  Makefile for CSE 101 Programming Assignment 8
#
#  Viveka Agrawal
#  viagrawa@ucsc.edu
#  pa8
# 
#  make                     makes WordFrequency
#  make DictionaryTest      makes DictionaryTest
#  make Order		    makes Order
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg.txt
#  make DictionaryCheck     runs DictionaryTest under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ADT_TEST       = $(ADT)Test
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

Order : Order.o Dictionary.o
	g++ -std=c++17 -Wall -o Order Order.o Dictionary.o 

Order.o : Dictionary.h Order.cpp
	g++ -std=c++17 -Wall -c Order.cpp

clean:
	$(REMOVE) $(MAIN) $(ADT_TEST) $(OBJECT) $(ADT_TEST).o $(ADT_OBJECT) Order Order.o

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) Gutenberg.txt

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)

