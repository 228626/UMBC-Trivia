/*****************************************************************************
 ** File: Trivia.cpp
 ** Project: CMSC 202 Project 5, Spring 2022
 ** Author:  Kush Shah and CMSC202
 ** Date:    04/05/2022
 ** Email:   k216@umbc.edu
 **
 Description: CPP file for Trivia class. Includes both class definition and
 class function definitions. Loads a file of trivia questions
*****************************************************************************/

#ifndef TRIVIA_CPP
#define TRIVIA_CPP
#include "Lqueue.cpp"
#include "Question.cpp"
#include <fstream>
#include <vector>
using namespace std;

const string DEFAULT_FILE = "proj5_string.txt";
const char DELIMITER = '|';

template <class T>
class Trivia {
public:
  // Name: Default Constructor
  // Desc: Displays the title, Loads Questions and calls menu
  // Indicates if the file was not loaded.
  // Precondition: None
  // Postcondition: User is prompted with assignment menus
  Trivia(string filename= DEFAULT_FILE)
  {
  	//Lqueue<Question<T>* >* m_questions;
  	m_questions = new Lqueue<Question<T>*>();
  	LoadQuestions(filename);
  	DisplayTitle();
  	MainMenu();
  	
  }
  // Name: Destructor
  // Desc: Deallocates memory allocated for the Questions and
  // resets all variables.
  // Precondition: A Trivia exists.
  // Postcondition: All dynamically allocated memory in Trivia is deleted.
  ~Trivia()
  {
  	m_questions->Clear();
  	delete m_questions;
  	m_subjects.clear();
  }
// Name: LoadQuestions
  // Desc: Each input file will be for a specific type of question (int, double, string)
  //       Reads in Questions from a file and stores them in anLqueue.
  //       An input file will be for exactly one type of question (int, double, string)
  // Precondition: None.
  // Postcondition: Returns true if file was read. Otherwise, it returns false.
  bool LoadQuestions(string filename)
  {
  	ifstream file(filename);
  	if(!file)
  		cout << "Error openning the file!\n";
  	
  	while(!file.eof())
  	{
  		string subject, question ,type, difficulty;
  		T answer;
  		
		getline(file ,subject, '|');
  		//cout << "Subject: " << subject << endl;
  		
  		if(subject.length() == 0)
  			break;
  		
		AddSubject(subject);
  		
		getline(file ,question, '|');
  		//cout << "Question: " <<question << endl;
  		
		  //cout << "Test1\n";
  		getline(file ,type, '|');
  		//cout <<"Type: " << type << endl;
  		
		getline(file ,difficulty, '|');
  		//cout <<"Difficulty: " << difficulty << endl;
  		
		file >> answer;
  		//cout <<"Answer: " << answer << endl;
  		
  		
		file.ignore(2, '\n');
		int diff = stoi(difficulty);
		//cout << diff <<  " TEST\n";
		
		Question <T> *temp = new Question<T>(subject, question, type, diff, answer);
		
		//cout << "HELLO\n";
		
		m_questions->Push(temp);
		
		//cout << "Size: "<< m_questions->GetSize() << endl;
	}
  }
  // Name: MainMenu
  // Desc: Presents user with menu options for showing subjects and allowing
  // user to work on a subject.
  // Precondition: None.
  // Postcondition: The main menu is presented.
  void MainMenu()
  {
  	while(1)
	{
	  	cout << "Choose an option.\n1. Display Subjects\n2. Start Subject\n3. Quit\n";
	  	int inp;
	  	cin >> inp;
	  	if(inp == 1)
	  	{
	  		DisplaySubjects();
		}
		else if(inp ==2)
		{
			StartSubject();
		}
		else if(inp == 3)
			break;
		else
			cout << "Invalid input, enter again.\n";
	}	
  }
  // Name: DisplaySubjects
  // Desc: Presents all Subjects with corresponding numerical identifiers.
  // Precondition: Subjects have been added.
  // Postcondition: All assignments are printed to the screen.
  void DisplaySubjects()
  {
  	for(int i =0; i<m_subjects.size(); i++)
  	{
  		cout << i+1 << ". " << m_subjects[i] << endl;
	  }
  }
  // Name: StartSubject
  // Desc: Starts working on a selected Subject.
  // Displays the number of questions in subject.
  // Starts at beginning and goes through each question.
  // After all questions have been answered:
  //       displays total correct, incorrect, and percentage correct
  // Precondition: m_questions has been populated
  // Postcondition: Returns to main menu
  void StartSubject()
  {
  	cout << "What subject would you like to attempt?\n";
  	int sub = ChooseSubject();
  	cout << "There are "<< QuestionsPerSubject(m_subjects[sub]) << " questions in this subject.\n";
  	int totalqs = QuestionsPerSubject(m_subjects[sub]);
  	int progress = 0;
  	int correct=  0;
  	string subject = m_subjects[sub];
  	for(int i = 0; i< m_questions->GetSize(); i++)
  	{
  		Question<T> *q = m_questions->At(i);
  		if(q->m_subject == subject)
  		{
  			cout << progress+1 << ". " << *q;
  			progress++;
  			T ans;
  			cin >> ans;
  			if(q->CheckAnswer(ans))
  			{
  				cout << "Correct\n";
  				correct++;
			}
			else
				cout << "Incorrect\n";
		}
	}
	cout << "You got " << correct << " answers correct.\nYou got " << totalqs-correct << " answers incorrect.\nWhich is a " << (double)((double)correct/(double)totalqs)*100 << "%.\n";
  }
// Name: AddSubject
  // Desc: Checks to see if a subject exists in m_subjects.
  //       If not, inserts subject into m_subjects.
  // Precondition: A Subject exists.
  // Postcondition: Add subject to m_subjects if new subject.
  void AddSubject(string subject)
  {
  	bool found = false;
  	for(int i = 0; i< m_subjects.size(); i++)
  	{
  		if(m_subjects[i] == subject)
  			found = true;
	}
	if(!found)
		m_subjects.push_back(subject);
	//cout << "Add Subject passed";
  }
  // Name: ChooseSubject
  // Desc: Allows a user to choose one of the subjects to work on. Lists all subjects
  // in m_subjects and allows use to choose one. Returns value - 1 (location in vector)
  // Precondition: A Subject exists.
  // Postcondition: Returns value entered minus one
  int ChooseSubject()
  {
  	cout << "Possible Subjects:\n";
  	DisplaySubjects();
  	cout << "Choose an option:\n";
  	while(1)
  	{
  		int i;
  		cin >>i;
  		if(i>=1 && i<= m_subjects.size())
  			return i-1;
  		else
  			cout << "Incorrect entry, enter again!\n";
	}
	return -1;
  }
  // Name: QuestionsPerSubject
  // Desc: Iterates over m_questions and counts how many questions match the subject
  // passed into function
  // Precondition: A Subject exists.
  // Postcondition: Returns number of questions of a particular subject
  int QuestionsPerSubject(string subject)
  {
  	int count;
  	for(int i =0; i<m_questions->GetSize(); i++)
  	{
  		if(m_questions->At(i)->m_subject == subject)
  			count++;
	  }
	  return count;
  }
  // Name: DisplayTitle
  // Desc: Displays opening Welcome message
  // Precondition: None.
  // Postcondition: Title is displayed.
  void DisplayTitle()
  {
  	cout << "Welcome to UMBC Trivia!\n";
  }
private:
  Lqueue<Question<T>* >* m_questions; // Holds questions using a specific data type
  vector<string> m_subjects; //Populated as file is loaded
};

//**********Implement Trivia Class Here***********



#endif

