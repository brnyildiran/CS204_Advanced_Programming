#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <cctype>

using namespace std;

struct node 
{	
	int month, year;
	vector<string> cards; 
	node *next; 

	//default constructor
	node::node():next(NULL)
	{};

}; 

bool searchMyLinkedList(node *head, int searchMonth, int searchYear)
	// checks if the entered expiration month and year existed in the previous nodes.
{

	bool statue = false;
	node *current = head;
	while (current != NULL)
	{
		if(current->month == searchMonth && current->year == searchYear) 
		{
			return true;
		}
		else
		{
			current = current->next;
		}
	}
	return false;
}



node * GetNthNode(node *head, int searchMonth, int searchYear)
	//Find and return the node with same expiration month and year
{
	node *ptr = head;

	while (ptr != NULL )
	{
		if(ptr->month == searchMonth && ptr->year == searchYear)
		{
			return ptr;
		}
		ptr = ptr->next;
	}
	return NULL;
}

void swap(node *a, node *b) 
{ 
	int temp = a->year; 
	a->year = b->year; 
	b->year = temp; 

	temp = a->month;
	a->month = b->month;
	b->month = temp;

	vector<string> vectemp = a->cards;
	a->cards = b->cards;
	b->cards = vectemp;
} 

/* Bubble sort the given linked list */
void bubbleSort(node *start) 
{ 
	int swapped; 
	struct node *pointer1; 
	struct node *pointer2 = NULL; 

	/* Checking for empty list */
	if (start == NULL) 
		return; 

	do
	{ 
		swapped = 0; 
		pointer1 = start; 

		while (pointer1->next != pointer2) 
		{ 
			if (pointer1->year > pointer1->next->year)
			{
				swap(pointer1, pointer1->next); 
				swapped = 1; 
			}
			else if(pointer1->year == pointer1->next->year)
			{
				if(pointer1->month > pointer2->month)
				{
					swap(pointer1, pointer1->next); 
					swapped = 2;
				}
			}
			pointer1 = pointer1->next; 
		} 
		pointer2 = pointer1; 
	} 
	while (swapped); 
} 

void printList(node *start) 
{ 
	node *temp = start; 
	cout << endl << endl;
	while (temp!=NULL) 
	{ 
		cout << "Expiration Date: " << temp->month << " " << temp->year << endl;
		for(unsigned int i=1 ; i<= temp->cards.size(); i++)
		{
			cout << i << ") " << temp->cards.at(i-1) << endl;
		}
		cout << "-------------------" << endl << endl;

		temp = temp->next; 
	} 
} 

bool isCCardValid(string CreditCard)
{
	bool statue = true;
	if(CreditCard.length() != 16)
	{
		statue = false;
	}
	else if(CreditCard.length() == 16)
	{
		for(unsigned int i = 0; i < CreditCard.length(); i++)
		{
			if(CreditCard[i] != '0' && CreditCard[i] != '1' && CreditCard[i] != '2' && CreditCard[i] != '3' 
				&& CreditCard[i] != '4' && CreditCard[i] != '5' && CreditCard[i] != '6' && CreditCard[i] != '7'
				&& CreditCard[i] != '8' && CreditCard[i] != '9') 
			{
				statue = false;
			}
		}
	}
	return statue;
}

node *nodeOfTheCCards(node *head, string creditcardentery)
{
	node *pointer = head;
	while(pointer != NULL)
	{
		for(unsigned int i = 0; i < pointer->cards.size() ; i++)
		{
			if (pointer->cards[i] == creditcardentery)
				return pointer;
		}
		pointer = pointer->next;
	}
	return NULL;
}



void deleteNode(node *head, node *n)  
{  
    // When node to be deleted is head node  
    if(head == n)  
    {  
        if(head->next == NULL)  
        {  
            cout << "There is only one node." << 
                    " The list can't be made empty ";  
            return;  
        }  
  
        /* Copy the data of next node to head */
		head->next = head->next->next;  
  
        // store address of next node  
        n = head->next;  
  
        // Remove the link of next node  
        head->next = head->next->next;  
  
        // free memory  
        free(n);  
  
        return;  
    }  
	    // When not first node, follow  
    // the normal deletion process  
  
    // find the previous node  
    node *prev = head;  
    while(prev->next != NULL && prev->next != n)  
        prev = prev->next;  
  
    // Check if node really exists in Linked List  
    if(prev->next == NULL)  
    {  
        cout << "\nGiven node is not present in Linked List";  
        return;  
    }  
  
    // Remove node from Linked List  
    prev->next = prev->next->next;  
  
    // Free memory  
    free(n);  
  
    return;  
} 


//* Begin: code taken from CS204 Lab linkedList.cpp */
void ClearList(node *head)
{
	node *ptr;
	while(head!=NULL)
	{
		ptr=head;
		head=head->next;
		delete ptr;
	}
}
//* End: code taken from CS204 Lab linkedList.cpp */


int main()
{
	ifstream inputCCards;
	string filenameCCards;	
	string line, cardNumber, entertheCCard;
	vector<string> c;
	int expirationMonth, expirationYear, option;
	int searchedMonth, searchedYear;

	cout << "Please enter file name: ";
	cin >> filenameCCards;

	inputCCards.open(filenameCCards.c_str());

	while(inputCCards.fail())
	{
		cout << "Cannot find a file named " << filenameCCards << endl;
		cout << "Please enter file name: ";
		cin >> filenameCCards;

		inputCCards.open(filenameCCards.c_str());
	}

	node *nodeCCards = NULL; //head	
	node *temp = nodeCCards;
	node *curr = nodeCCards; //tail

	while(getline(inputCCards, line))
	{

		istringstream issCC (line);
		issCC >> cardNumber >> expirationMonth >> expirationYear;

		if(searchMyLinkedList(nodeCCards, expirationMonth, expirationYear) == false)
		{
			if (nodeCCards == NULL)
			{
				nodeCCards = curr;
				curr = new node;
				nodeCCards = curr;
			}
			else
			{
				curr->next = new node;
				curr = curr->next;
			}
			curr->month = expirationMonth;
			curr->year = expirationYear;
			curr->cards.push_back(cardNumber);

			cout << "New node is created with expiration date: " << expirationMonth << " " << expirationYear << endl;
			cout<< "Credit card " << cardNumber << " added to node " << expirationMonth << " " << expirationYear << endl;
			cout<<"***************"<<endl;

		}
		else if(searchMyLinkedList(nodeCCards, expirationMonth, expirationYear) == true)
		{
			temp = GetNthNode(nodeCCards, expirationMonth, expirationYear);
			temp->cards.push_back(cardNumber);

			cout << "Node with expiration date " << expirationMonth << " " << expirationYear << " already exists" << endl; 
			cout<< "Credit card " << cardNumber << " added to node " << expirationMonth << " " << expirationYear << endl;
			cout<<"***************"<<endl;

		}
	}

	do
	{
		cout << endl << endl;
		cout << "1)Display List" << endl;
		cout << "2)Card Search via Credit Number" << endl;
		cout << "3)Delete Card with respect to Expiration Date" << endl;
		cout << "4)Exit" << endl; 
		cout << endl << endl;
		cout << "Please choose option from the menu: ";
		cin >> option;
		cout << endl << endl;

		if(option==1)
		{
			bubbleSort(nodeCCards);
			printList(nodeCCards);
		}
		else if(option ==2)
		{
			do
			{
				cout << "Please enter the credit card number: " ;
				cin >> entertheCCard;
				if(isCCardValid(entertheCCard) == false)
				{
					cout << "Invalid format!" <<endl;
				}

			}while(isCCardValid(entertheCCard) == false);

			if(isCCardValid(entertheCCard) == true)
			{
				node *pointerOfTheCCard = nodeOfTheCCards(nodeCCards, entertheCCard);
				if(pointerOfTheCCard != NULL)
				{
					cout << "There exists a credit card given number " << entertheCCard 
						<< " with expiration date: " << pointerOfTheCCard->month << " " << pointerOfTheCCard->year <<endl;
				}
				else
				{
					cout << "There is no credit card with given credit card number: " << entertheCCard << endl;
				}
			}
		}
		else if(option == 3)
		{
			cout << "Please enter month and year: " ;
			cin >> searchedMonth >> searchedYear;
			cout << endl;

			do
			{
				
				cin.clear();
				cin.ignore(512, '\n');
				cout << "Invalid format!" << endl;
				cout << "Please enter month and year: " ;
				cin >> searchedMonth >> searchedYear;
				cout << endl;
				
			}while(cin.fail());
			if(!cin.fail()) 
			{
				for(unsigned int i = 0; i < to_string(searchedMonth).length(); i++)
				{
					if(  searchedMonth < 1 && searchedMonth > 12) 

					{
						cin.clear();
						cin.ignore(512, '\n');
						cout << "Invalid format!" << endl;
						cout << "Please enter month and year: " ;
						cin >> searchedMonth >> searchedYear;
						cout << endl;

					}
				}

			}
			
			
		}
		else if(option == 4)
		{
			ClearList(nodeCCards);
			option = 4;
		}
		else
		{
			cout << "You can only write 1, 2, 3 or 4! " << endl;
		}
	}
	while(option == 1 || option == 2 || option == 3);

	cout<<"Terminating!!!"<<endl;

	return 0;
}