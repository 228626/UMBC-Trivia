/*****************************************************************************
 ** File: Question.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Kush Shah and CMSC202
 ** Date:    04/05/2022
 ** Email:   k216@umbc.edu
 **
 Description: CPP file for Question class. Includes both class definition and
 class function definitions.
*****************************************************************************/

#ifndef QUESTION_CPP
#define QUESTION_CPP
#include <iostream>
#include <string>
using namespace std;

// Global constants for number of types
const int NUM_TYPES = 6;
const string KNOWN_TYPES[NUM_TYPES] = { "int", "double", "bool", "char", "string"};

template <class T>
class Question {
public:
  // Name: Overloaded Constructor
  // Desc: Constructs a question object given all fields.
  // Precondition: Question must be templated by the data type passed in as an argument.
  // Postcondition: A new Question object is created for use.
  Question(string subject, string question, string datatype, int difficulty, T answer)
  {
  	this->m_subject = subject;
  	this->m_question = question;
  	this->m_datatype = datatype;
  	this->m_difficulty = difficulty;
  	this->m_answer = answer;
  }
  // Name: Copy Constructor
  // Desc: Makes a copy of an existing Question object
  // Precondition: A Question object exists.
  // Postcondtion: A new populated Question exists
  Question(const Question&obj)
  {
  	m_subject = obj.m_subject;
  	m_question = obj.m_question;
  	m_datatype = obj.m_datatype;
  	m_difficulty = obj.m_difficulty;
  	m_isAnswered = obj.m_isAnswered;
  	m_answer = obj.m_answer;
  }
  // Name: Destructor
  // Desc: Resets variables and deallocates dynamically allocated memory
  // Precondition: A Question object exists.
  // Postcondtion: All dynamically allocated memory is destroyed.
  ~Question()
  {
  	
  }
// Name: CheckAnswer
  // Desc: Compares passed value with m_answer
  // Precondition: A Question object exists.
  // Postcondtion: Returns true if value passed matches m_answer else false.
  bool CheckAnswer(T submission)
  {
  	return(submission == m_answer);
  }
  // Name: Overloaded insertion operator
  // Desc: Returns ostream object for the question prompt. Presents
  // question and answer data type.
  // Precondition: Question object exists
  // Postcondition: Returns ostream of question prompt.
  template<class Y> //As friend function, has to use different templated variable
  friend ostream& operator<< (ostream& output, Question<Y>&q);

  //Member variables (all public)
  string m_subject; //Subject for question
  string m_question; // Question
  string m_datatype; // What type of data used for answer
  int m_difficulty; // Difficulty Rating (1 - 5)
  T m_answer; // Answer to question
  bool m_isAnswered; // True once question is answered. Otherwise, false.
};
template<class Y> //As friend function, has to use different templated variable
   ostream& operator<< (ostream& output, Question<Y>&q)
  {
  	output << "Question: " << q.m_question << "\nPlease answer with a(n) " << q.m_datatype <<".\n";
  }
//**********Implement Question Class Here***********

#endif

