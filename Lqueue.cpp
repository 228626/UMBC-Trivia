#ifndef LQUEUE_CPP
#define LQUEUE_CPP
#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//Templated node class used in templated linked list
template <class T>
class Node {
   public:
  Node( const T& data ); //Constructor
  T& GetData(); //Gets data from node
  void SetData( const T& data ); //Sets data in node
  Node<T>* GetNext(); //Gets next pointer
  void SetNext( Node<T>* next ); //Sets next pointer
private:
  T m_data;
  Node<T>* m_next;
};

//Overloaded constructor for Node
template <class T>
Node<T>::Node( const T& data ) {
   m_data = data;
   m_next = NULL;
}

//Returns the data from a Node
template <class T>
T& Node<T>::GetData() {
   return m_data;
}

//Sets the data in a Node
template <class T>
void Node<T>::SetData( const T& data ) {
   m_data = data;
}

//Gets the pointer to the next Node
template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

//Sets the next Node
template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

template <class T>
class Lqueue {
	public:
  // Name: Lqueue() (Linked List Queue) - Default Constructor
  // Desc: Used to build a new linked queue (as a linked list)
  // Preconditions: None
  // Postconditions: Creates a new lqueue where m_head and m_tail point to nullptr
  // Required
  Lqueue()
  {
  	m_size = 0;
  }
 // Name: ~Lqueue() - Destructor
  // Desc: Used to destruct a Lqueue
  // Preconditions: There is an existing lqueue with at least one node
  // Postconditions: An lqueue is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
  // Required
 ~Lqueue()
 {
 	Clear();
 }
  // Name: Lqueue (Copy Constructor)
  // Preconditions: Creates a copy of existing LQueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue(const Lqueue& obj){
  	
  	Node<T> *temp = obj.m_head;
  	Node <T> *temp2 = new Node<T>(temp->GetData());
  	this->m_size = obj.m_size;
  	m_head = temp2;
	for(int i =0; i< obj.m_size-1; i++)
	{
		temp2->SetNext(new Node<T>(temp->GetNext()->GetData()));
		temp = temp->GetNext();
		temp2 = temp2->GetNext();
	}
  	m_tail = temp2;
  }
  // Name: operator= (Overloaded Assignment Operator)
  // Preconditions: Copies an Lqueue into an existing Lqueue
  //                Requires a Lqueue
  // Postconditions: Copy of existing Lqueue
  // Required
  Lqueue<T>& operator= (Lqueue& obj)
  {
  	this->Clear();
  	
  	Node<T> *temp = obj.m_head;
  	Node <T> *temp2 = new Node<T>(temp->GetData());
  	this->m_size = obj.m_size;
  	m_head = temp2;
	for(int i =0; i< obj.m_size-1; i++)
	{
		temp2->SetNext(new Node<T>(temp->GetNext()->GetData()));
		temp = temp->GetNext();
		temp2 = temp2->GetNext();
	}
  	m_tail = temp2;
  }
  // Name: Push
  // Preconditions: Takes in data. Creates new node.
  //                Requires a Lqueue
  // Postconditions: Adds a new node to the end of the lqueue.
  // Required
  void Push(const T&data)
  {
  	if(m_size == 0)
  	{
  		m_head = new Node<T>(data);
  		m_tail = m_head;
  		m_size++;
	}
	else
	{
		m_tail->SetNext(new Node<T>(data));
		m_tail= m_tail->GetNext();
		m_size ++;
	}
	//cout << "Inserted " << *data << " \nSize: " << m_size << endl;
  }
 // Name: Pop
  // Preconditions: Lqueue with at least one node.
  // Postconditions: Removes first node in the lqueue, returns data from first node.
  // Required
  T Pop()
  {
  	T temp = m_head->GetData();
  	Node<T> *t = m_head;
  	m_head = m_head->GetNext();
  	delete t;
  	m_size--;
  	if(m_size == 0)
  	{
  		m_head = 0;
  		m_tail = 0;
	}
	return temp;
  }
  // Name: Display
  // Preconditions: Outputs the lqueue.
  // Postconditions: Displays the data in each node of lqueue
  // Required (used only for testing)
  void Display()
  {
  	Node <T> *temp = m_head;
  	for(int i = 0; i<m_size; i++)
  	{
  		cout << temp->GetData() << " ";
  		temp = temp->GetNext();
	}
	cout << endl;
  }
  // Name: Front
  // Preconditions: Requires a populated lqueue
  // Postconditions: Returns whatever data is in front
  // Required
  T Front()
  {
  	return m_head->GetData();
  }
  // Name: IsEmpty
  // Preconditions: Requires a lqueue
  // Postconditions: Returns if the lqueue is empty.
  // Required
  bool IsEmpty()
  {
  	return m_size == 0;
  }
// Name: GetSize
  // Preconditions: Requires a lqueue
  // Postconditions: Returns m_size
  // Required
  int GetSize()
  {
  	return m_size;
  }
  // Name: Find()
  // Preconditions: Requires a lqueue
  // Postconditions: Iterates and if it finds the thing, returns index, else -1
  // Required
  int Find(T& str)
  {
  	Node <T> *temp = m_head;
  	for(int i =0; i<m_size; i++)
  	{
  		if(temp->GetData() == str)
  		{
  			return i;
		  }
		  temp = temp->GetNext();
	  }
	  return -1;
  }
  // Name: Swap(int)
  // Preconditions: Requires a lqueue
  // Postconditions: Swaps the nodes at the index with the node prior to it.
  // Required
  void Swap(int)
  {
  	if(m_size<2)
  	return;
  	Node<T> *temp = m_head;
  	for(int i  =0; i< m_size-2;i++)
  	{
  		temp = temp->GetNext();
	}
	Node<T> *link = temp->GetNext()->GetNext()->GetNext();
	Node<T> *second = temp->GetNext()->GetNext();
	second->SetNext(temp->GetNext());
	temp->GetNext()->SetNext(link);
	temp->SetNext(second);
  }
  // Name: Clear
  // Preconditions: Requires a lqueue
  // Postconditions: Removes all nodes in a lqueue
  // Required
  void Clear()
  {
  	Node <T> *temp = m_head;
  	while(m_head != m_tail)
  	{
  		Node <T>* temp2 = temp;
  		temp = temp->GetNext();
  		delete temp2;
	}
	delete temp;
	m_head = m_tail = 0;
	m_size = 0;
  }
// Name: At
  // Precondition: Existing Lqueue
  // Postcondition: Returns object from Lqueue at a specific location
  // Desc: Iterates to node x and returns data from Lqueue
  // Required
  T At (int x)
  {
  	Node<T> *temp = m_head;
  	for(int i =0; i<x; i++)
  	{
  		temp = temp->GetNext();
	  }
	  return temp->GetData();
  }
private:
  Node <T> *m_head; //Node pointer for the head
  Node <T> *m_tail; //Node pointer for the tail
  int m_size; //Number of nodes in queue
};

//**********Implement Lqueue Class Here***********
//**********All Functions Are Required Even If Not Used for Trivia**************

#endif


