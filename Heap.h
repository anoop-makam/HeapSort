//********************************************************
// Assignment: ASU CSE310 HW#3
// Your Name: Anoop Makam
// ASU ID: 1215235593
// ASU Email address: amakam@asu.edu
// Description: Implementing various heap operations 
//********************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Food represents a food. Each food with a unique key
struct Food
{
	int key;
	string foodName;
	double price;
};

//class Heap represents a Max heap that contains Food objects. Underline data structure is
//a one dimensional array of Food objects.
class Heap
{
    private:
	struct Food* foodArr;	//an array of Food
	int capacity, size;

    public:
	Heap(int capacity);
	~Heap();
	Food* getFoodArr();
	int getSize();
	int getCapacity();
	int isFound(int foodKey);
	bool increaseKey(int index, Food oneFoodwithNewKey);
	bool insert(int key, string foodName, double foodPrice);
	void heapify(int index);
	Food getHeapMax();
	void extractHeapMax();
	int leftChild(int parentIndex);
	int rightChild(int parentIndex);
	int parent(int childIndex);
	void printHeap();
	
};




//Constructor to dynamically allocate memory for a heap with the specified capacity
Heap::Heap(int capacity)
{
	//initializing the capacity 
	this->capacity = capacity;
	//Initializing the size of the heap to be zero.
	size = 0;
	//Dynamically allocating memory to heap with a specified capacity.
	foodArr = new Food[capacity];
	
	
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
Heap::~Heap()
{
	//Food counter 
	int foodCount = 0;

	// Deleting memory 
	for(int i = 0; i <= getSize() - 1; i++)
	{
		//Counter to calculate the size of the Food array.
		foodCount++;
	}
	//Deallocating memory 
	delete[] foodArr;
	
	cout << "\nThe number of deleted food items is: " << foodCount << endl;
	
}


//Function getFoodArr() used to return the first elements address.
Food* Heap:: getFoodArr()
{
	return foodArr;
}
//Function getSize() used to return the size of the Heap.
int Heap::getSize()
{
	return size;
}
//Function getCapacity() used to return the capacity of the Heap.
int Heap::getCapacity()
{
	return capacity;
}
//Function isFound() is used to return the index of the key passed in the method argument.
int Heap::isFound( int foodKey)
{
	for( int i = 0; i <= getSize() - 1; i++)
	{
		//Checking if the key passed in matches the key we are looking for.
		if( foodKey == foodArr[i].key )
		{
			//Returning the index at which the index is located.
			return i;
		}
	}
	//Returning -1 if key is not found.
	return -1;

}
//Function increaseKey() is used to increase the key at a particular index.
bool Heap::increaseKey(int index, Food foodwithNewKey)
{
	//Obtaining the parent index of the child index using the parent() function.
	int parentInd = parent(index);
	//Checking if the objects key is less than the Food array key 
	if (foodwithNewKey.key < foodArr[index].key)
	{
		cout<<"\n new key is smaller than current key"<<endl;
		return false;
	}

	else

	{
		
		foodArr[index] = foodwithNewKey;
		//Sawpping Child node and Parent node in heap in order for it to satisfy Max-Heap properties.
		while ( index >= 0 && foodArr[parentInd].key < foodArr[index].key)
		{
			//Using the swap method to swap the two objects
			swap(foodArr[index], foodArr[parentInd]);
			//New index is now parent index.
			index = parentInd;
			parentInd = parent(index);
		}
		return true;

	}
	return false;
}
//Function insert() is used to insert an object into the Food Array.
bool Heap::insert(int key, string foodName, double foodPrice)
{	
	//Condition to check if the Size of heap is less than the Capacity of the heap.
	if(getSize() < getCapacity())
	{
		//New food object.
		Food objInsert;
		//Condition to check if duplicate food item exists.
		for(int i = 0; i <= getSize() - 1; i++)
		{
			if(key == foodArr[i].key)
			{
				cout<<"\nDuplicated food item. Not added\n"<<endl;
				return false;
			}
		}
	
		//Inserting data into the object 
		objInsert.key = key;
		objInsert.foodName = foodName;
		objInsert.price = foodPrice;
		//Incrementing size 
		size = size + 1;
		//Inserting dummy key 
		foodArr[size - 1].key = -255;
		
		//Used to float the new key up to satisfy max heap properties.
		increaseKey(size - 1  , objInsert);
		return true;
	}
	
	else 

	{
		struct Food *objInsert;
		Food objInsert1;
		//Condition to check if duplicate food item exists.
		for(int i = 0; i <= getSize() - 1; i++)
		{
			if(key == foodArr[i].key)
			{
				cout<<"\nDuplicated food item. Not added\n"<<endl;
				return false;
			}
		}
		//Doubling the capacity of the array.
		capacity  = 2*capacity;
		//New Food object created of size Capacity(double the size)
		objInsert = new Food[capacity];
		//Transferring the old elements in the array to the new array
		for(int i = 0; i < getCapacity()/2; i++)
		{
			objInsert[i] = foodArr[i];
		}
		//Deallocating memory 
		delete[] foodArr;
		//Old array is now new food array.
		foodArr = objInsert;
		//Dealloctaing memory 
		delete[] objInsert;
		//Inserting data into the object to be inserted 
		objInsert1.key = key;
		objInsert1.foodName = foodName;
		objInsert1.price = foodPrice;
		//Inserting object at last node.
		size = size + 1;
		foodArr[size - 1].key = -255;
		
		
		//Used to float the new key up to satisfy max heap properties.
		increaseKey(size - 1  , objInsert1);

		cout<<"\nReach the capacity limit. Double the capacity\n";
		cout<<"The new capacity now is "<<capacity<<endl;
		
		return true;
		
	}
	
	return false;
	
}
//Function heapify used to Max-Heapify from the index passed.
void Heap::heapify(int index )
{
	
	int l, r, largest;
	largest = 0;
	//accessing the left child and right child index respectively.
	l = leftChild(index);
	r = rightChild(index);
	if( l <= getSize() - 1  && foodArr[l].key > foodArr[index].key )
	{
		largest = l;
	}

	else 

	{
		largest = index;
	}
	
	if( r <= getSize() - 1 && foodArr[r].key > foodArr[largest].key )
	{
		largest = r;
	}
	if( largest != index )
	{
		//Sawpping the current index with the largest index.
		swap(foodArr[index], foodArr[largest]);
		heapify(largest);
	}
	
}

//Returning the first node of the Max-Heap , i.e., the max value 
Food Heap::getHeapMax()
{
	return foodArr[0];
}

//Function extractmax() extracts the root node of the function.
void Heap::extractHeapMax()
{
	foodArr[0] = foodArr[getSize() - 1];
	size = size - 1;
	heapify(0);
}

//Returning the left Child of the parent.
int Heap::leftChild(int parentIndex)
{
	return ((2*parentIndex) + 1);
}

//Returning the right Child of the parent.
int Heap::rightChild(int parentIndex)
{
	return ((2*parentIndex) + 2);
}

//Returning the child's parent node
int Heap::parent(int childIndex)
{
	return ((childIndex - 1)/2);
}

//Prints all the elements in the heap with correct format.
void Heap::printHeap()
{
	//Condition to check if Heap size is less than 0.
	if(getSize() <= 0)
	{
		cout<<"Empty heap, no elements\n"<<endl;
	}

	else

	{
		cout<<"\nHeap capacity = "<<getCapacity()<<endl;
		cout<<"\nHeap size = "<<getSize()<<endl;
		cout<<"\n";

		for(int i = 0; i<= getSize() - 1 ; i++)
		{
			cout << left;
			cout << setw(5) << foodArr[i].key;
    		cout << setw(8) << foodArr[i].foodName;
			cout << setw(8) << fixed << setprecision(2) << foodArr[i].price<<endl;
		}

	}
	
}
//End of program.
