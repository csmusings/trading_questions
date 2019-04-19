all: question3 question1 question2

question3: question3.cpp 
	g++ question3.cpp -o question3 -std=c++14

question1: question1.cpp
	g++ question1.cpp -o question1 -std=c++14

question2: question2.cpp
	g++ question2.cpp -o question2 -std=c++14

	
