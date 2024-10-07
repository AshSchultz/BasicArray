/* 
* fsarray.hpp
*
* Author: Ashley Moore-Schultz
*
* Date: 9-18-2023
* Revised 10/7/2024
*
* Class FSArray
* 
* Description:
* Template class for a basic array like the vector class in stdlib.
* It implements an array with some basic features, including a way to copy the array,
* move ownership of the array, handles size of the array at initialization 
* and easy access to the beginning and end of the array with begin() and end(). 
* The array also has an exception safe design
* with asserts protecting the access of elements, 
* proper memory management with the destructor, and a noexcept move constructor. 
*/

#pragma once

#include <cstddef>
#include <cassert>
#include <type_traits>
#include <algorithm>

template <typename T>
class FSArray  
{
public:
    using value_type = T;
    using size_type = std::size_t;

private:
    value_type* _data;
    size_type _size;

public:
     FSArray()
	 	: _data(new T[8]), _size(8)
     {}
     FSArray(size_type size)
	 	: _data(new T[size]), _size(size)
     {}

     FSArray(size_type size, T values)
	 	: _data(new T[size]), _size(size)
     {
		for (int i = 0; i < size; i++)
		{
		_data[i] = values;
		}
     }

     FSArray(const FSArray<value_type> & other)
	 	: _data(other._size ? new T[other._size] : nullptr), _size(other._size)
     {
         if (_data) 
         {
             std::copy(other._data, other._data + _size, _data);
         }
     }

     FSArray(FSArray<value_type>&& other) noexcept
          : _data(other._data), _size(other._size)
     {
          other._data = nullptr;
          other._size = 0;
     }

     FSArray& operator=(const FSArray<value_type>& other)
     {
         delete[] _data;
         
         _size = other._size;
         _data = _size ? new T[_size] : nullptr;

          if (_data) 
          {
               std::copy(other._data, other._data + _size, _data);
          }
          
          return *this;
     }

     ~FSArray()
     {
         delete[] _data;
     }

	 size_type size() const
	 {
		return _size;
	 }

	 value_type * end()
	 {
        return &_data[_size];
	 }

	 const value_type * end() const
	 {
        return &_data[_size];
	 }
     
	 value_type * begin()
     {
        return &_data[0];
     }
     
	 const value_type * begin() const
     {
        return &_data[0];
     }

    value_type& operator[](size_type subscript)
     {
        assert(subscript < _size);
        return _data[subscript];
     }
    const value_type& operator[](size_type subscript) const 
     {
        assert(subscript < _size);
        return _data[subscript];
     }
	 bool operator==(const FSArray<value_type> & other) const
	 {
		return size() == other.size() && std::equal(begin(), end(), other.begin());
	 }

	 bool operator!=(const FSArray<value_type> & other) const
	 {
		return !(*this == other);
	 }

      bool operator<(const FSArray<value_type> & other) const
      {
          for (size_type i = 0; i < size() && i < other.size(); i++)
          {
               if (_data[i] < other._data[i])
               {
                    return true;
               }
               else if (other._data[i] < _data[i])
               {
                    return false;
               }
          }

          return size() < other.size();

      }
      bool operator>(const FSArray<value_type> & other) const
      {
          return other < *this;
      }

      bool operator<=(const FSArray<value_type> & other) const
      {
          return !(*this > other); 
      }

      // Greater than or equal to operator
      bool operator>=(const FSArray<value_type> & other) const
      {
          return !(*this < other); 
      }

};