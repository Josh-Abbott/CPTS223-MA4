//***************************************************************************//
//**
//**  Simple Heap implementation
//**
//***************************************************************************//

#ifndef __HEAP_H
#define __HEAP_H
#include <iostream>
#include <vector>
#include <stdexcept>      // std::out_of_range
#include <math.h>         // pow()
#include <string>
#include <limits>

/**
 *  Declaring Heap class
 */
template<typename T>
class Heap
{

private:
	std::vector<T> _items;    // Main vector of elements for heap storage. The first item in the array is a placeholder.

/*********************************************************************/
/********************* Start Microassignment zone ********************/

	/**
	 *  Percolates the item specified at by index down 
     *   into its proper location within a heap.
	 *  Used for dequeue operations and array to heap conversions
	 *  MA TODO: Implement percolateDown
	 */
	void percolateDown(unsigned int hole) // Modified code taken from https://wsu.instructure.com/courses/1566350/files/98248856?module_item_id=16941541
	{
        int tmp = _items[hole];
        int child;

        for ( ; hole * 2 <= _items.capacity();)
        {
            child = hole * 2;
            if (child != _items.capacity() && _items[child + 1] < _items[child])
            {
                child++;
            }
            if (_items[child] < tmp)
            {
                _items[hole] = _items[child];
            }
            else
            {
                break;
            }
        }
        _items[hole] = tmp;
	}

	/**
	 *  Add a new item to the end of the heap and percolate up this item to fix heap property
	 *  Used in inserting new nodes into the heap
	 *  MA TODO: Implement percolateUp
	 */
	void percolateUp(T item) // Modified code taken from https://wsu.instructure.com/courses/1566350/files/98248856?module_item_id=16941541
	{
        int currentSize = _items.capacity();
        int sizeTest;

        for(int i = 0; i < _items.size(); i++)
        {
            if (_items[i])
            {
                sizeTest++;
            }
        }

    	if (currentSize == size())
        {
            _items.resize(_items.size() * 2);
        }

        int hole = ++currentSize;
        for ( ; hole > 1 && item < _items[hole / 2]; hole /= 2)
        {
            _items[hole] = _items[hole / 2];
        }
        _items[hole] = item;
        std::cout << "CAPACITY AND ITEM: " << _items.capacity() << " " << item << std::endl;
        _items.resize(_items.size()+1);
	}

/********************** End Microassigment zone *********************/

public:
	/**
	 *  Default empty constructor
	 */
	Heap() {
        _items.push_back(std::numeric_limits<T>::min()); // Push a placeholder for the first item in the array
	}


	/**
	 *  Adds a new item to the heap
	 */
	void push(T item)
	{
		percolateUp(item);
	}

	/**
	 *  Removes minimum value from heap 
	 */
	T pop()
	{
		long unsigned int last_index = _items.size() - 1;	// Calc last item index
		int root_index = 1;                      // Root index (for readability)

		if( size() == 0 ) {
			throw std::out_of_range("pop() - No elements in heap");
		}

		T minItem = _items[root_index];

		_items[root_index] = _items[last_index]; // Move last item to root
		_items.pop_back();          // Erase last element entry

		if( size() > 0 ) {			// Only runs if the heap isn't empty now
			percolateDown(1);       // Fix heap property
		}
        return minItem;
	}


	/**
	 *  Returns true if heap is empty, else false
	 *  Consider the first placeholder in the array
	 */
	bool empty() const
	{
		if( _items.size() == 1 ) {
			return true;
		} else {
			return false;
		}
	}


	/**
	 *  Returns current quantity of elements in heap (N)
	 *  Consider the first placeholder in the array
	 */
	long unsigned int size() const
	{
		return _items.size() - 1;
	}


	/**
	 *  Return heap data in order from the _items vector
	 */
	std::string to_string() const
	{
		std::string ret = "";
		for(unsigned int i = 1; i < _items.size(); i++)
     	{
			ret += std::to_string(_items[i]) + " ";
		}
		return ret;
	}
};

#endif