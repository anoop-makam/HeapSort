//********************************************************************************
// Assignment: ASU CSE310 HW#3
// Name: Anoop Makam
// ASU ID: 1215235593
// ASU Email Address: amakam@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//             	//---- is where you should add your own code
//********************************************************************************

#include <iostream>
#include <string>

//include the header file here
#include "Heap.h"

using namespace std;

void printMenu();


int main()
{
	char input1 = 'Z';
	string foodName;
	int key, newKey;
	int capacity, index = -1;   //1D array capacity and index
	double price;
	bool success = false;

    Food oneFood;

	//a variable used to represent a Heap object
	Heap* heap1 = nullptr;
	heap1 = new Heap(5);
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n');	//flush the buffer

		// matches one of the cases
		switch (input1)
		{
			case 'C':	//create empty Heap with the relevant capacity
				cout << "\nPlease enter the heap capacity: ";
				cin>>capacity;
				heap1 = new Heap(capacity);
				cin.ignore(20, '\n');	//flush the buffer
				break;

			//delete the heap, call the destructor explicitly. Re-initialize heap1
			//with capacity 5
			case 'D':
				cout << "\nDelete the heap" << endl;
				//Explicitly calling the destructor
				heap1 ->~Heap();
				capacity = 5;
				heap1 = new Heap(capacity);
				break;

			case 'E':	//Extract the maximum node
				
				
				if(heap1 -> getSize() <= 0)
				{
					cout <<" \nEmpty heap, can NOT extract max"<<endl;
				}
				else
				{
					cout<<"\nBefore extract heap max operation:\n";
					heap1->printHeap();
					cout<<"\nAfter extract heap max operation:\n";
					heap1->extractHeapMax();
					heap1->printHeap();
				}
				
                break;

			case 'F':	//Find a food
				cout << "\nEnter the food key you want to search: \n";
				cin >> key;
				cin.ignore(20, '\n');	//flush the buffer

				
				if(heap1 -> isFound(key) >= 0)
				cout<<"Food with key: "<<key <<" is found\n";
				else 
				cout<<"Food with key: "<< key<<" is NOT found\n";
				break;

			case 'I':	//Insert a Food
				cout << "\nEnter the food name: ";
				getline(cin, foodName);
				cout << "\nEnter food key: ";
				cin >> key;
				cout << "\nEnter the food price: ";
				cin >> price;
				cin.ignore(20, '\n');	//flush the buffer
				//To confirm the insertion of Food object into the heap.
				success = heap1 -> insert(key, foodName, price );
				if (success == true)
				{
                	cout << "\nThe food \"" << foodName << "\" is added\n";
				}	
                else
				{
                	cout << "\nThe food \"" << foodName << "\" is NOT added\n";
				}	
				break;

			case 'K':	//increase the key
				cout << "\nEnter the old food key you want to increase: ";
				cin >> key;
				cout << "\nEnter the new key value: ";
				cin >> newKey;
				cin.ignore(20, '\n');	//flush the buffer
				//Cases to check if the old key replaces the new key 
				if(newKey < key)
				{
					cout<<"\nIncrease key error: new key is smaller than current key"<<endl;
				}
				else if(heap1->isFound(key) < 0)
				{
					cout<<"\nThe old key you try to increase does not exist"<<endl;
				}
				else if(heap1 -> isFound(newKey) >= 0)
				{
					cout<<"\nThe new key you entered already exist, increase key operation failed"<<endl;
				}
				else
				{
					cout<<"\nBefore increase key operation:\n";
					heap1 -> printHeap();

					cout<<"\nFood with old key: "<<key<<" is increased to new key: "<<newKey<<endl;
					
					cout<<"\nAfter increase key operation:\n";
					Food* temp = heap1->getFoodArr();
					oneFood = temp[heap1->isFound(key)];
					oneFood.key = newKey;
                    heap1->increaseKey(heap1->isFound(key),oneFood);
					heap1 -> printHeap();

				}
				break;

			case 'M':	//get the maximum node
				if(heap1 -> getSize() <= 0)
				{
					cout<<"\nEmpty heap, cannot get max node\n"<<endl;
				}
				else 
				{
					cout<<"\nThe maximum heap node is:"<<endl;
					cout << setw(5) << heap1->getHeapMax().key
					<< setw(8) << heap1->getHeapMax().foodName
					<< setw(8) << fixed << setprecision(2) << heap1->getHeapMax().price << endl;
				}
				break;

			case 'P':	//Print heap contents
			    heap1 -> printHeap();
				break;

			case 'Q':	//Quit
				delete heap1;
				break;

			case '?':	//Display Menu
				printMenu();
				break;

			default:
				cout << "Unknown action\n";
				break;
		}
	} while (input1 != 'Q');
	return 0;
}

/**The function displays the menu to a user**/
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a food by key\n";
	cout << "I\t\tInsert a food\n";
	cout << "K\t\tIncrease the key\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}
