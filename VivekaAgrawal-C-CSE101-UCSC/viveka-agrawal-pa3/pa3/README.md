# Programming Assignment 3 (pa3)

## Makefile 
This is the Makefile for this assignment that creates the executable binary file FindComponents.

## List.h
This header file contains all of the exported List function declarations. 

## List.c 
This file is the List module containing the List type and associated operations. 

## Graph.h
This header file contains all of the exported Graph function declarations. 

## Graph.c
This is the Graph module containing the Graph type and associated operations. 

## GraphTest.c
This file contains test cases for the Graph ADT. 

## FindComponents.c
This client program will find all the strongly connected components in the graph using Depth First Search and the Graph ADT. 

### Visit() Function
I used the second approach (let time be a local variable in DFS(), then pass the address of time to Visit(), making it an input-output variable to Visit()).
