/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 13:12:48 by dselmy            #+#    #+#             */
/*   Updated: 2022/07/05 21:48:56 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VECTOR_HPP
# define FT_VECTOR_HPP

# include <memory>
# include <iterator> // later ft::
# include "RandomAccessIterator.hpp"
# include "iterator.hpp"
# include "reverse_iterator.hpp"
# include <stdexcept>
# include <cstddef>
# include <algorithm> // for lexicographical compare and equal, later ft::

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
			typedef T value_type;
			typedef Alloc allocator_type;
			typedef size_t size_type;
			typedef std::ptrdiff_t difference_type;
			typedef value_type& reference;
			typedef const value_type& const_reference;
			typedef typename Alloc::pointer pointer;
			typedef typename Alloc::const_pointer const_pointer;
			typedef ft::RandomAccessIterator<T> iterator;
			typedef ft::RandomAccessIterator<const T> const_iterator;
			typedef ft::reverse_iterator<iterator> reverse_iterator;
			typedef ft::reverse_iterator<const iterator> const_reverse_iterator;
		private:
			pointer _arr;
			size_type _size;
			size_type _cap;
			allocator_type _alloc;
		public:

			/*****    Constructors    *****/

			explicit vector (const allocator_type& alloc = allocator_type()): \
							_arr(NULL), _size(0), _cap(0), _alloc(alloc) {}

			explicit vector (size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()): \
				_size(n), _cap(n), _alloc(alloc)
			{
				if (n < 0)
					throw std::out_of_range("std::out_of_range");
				this->_arr = this->_alloc.allocate(n);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_arr + i, val);
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last, \
				const allocator_type& alloc = allocator_type(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type* = 0)
			{
				if (first > last)
					throw std::length_error("std::length_error");
				this->_size = last - first;
				this->_cap = _size;
				this->_alloc = alloc;
				this->_arr = _alloc.allocate(_cap);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(this->_arr + i, *first);
					++first;
				}
			}

			vector(const vector& x): _size(x._size), _cap(x._cap), _alloc(x._alloc)
			{
				this->_arr = this->_alloc.allocate(this->_cap);
				for (size_type i = 0; i < x._size; i++)
					this->_alloc.construct(this->_arr + i, x._arr[i]);
			}

			/*****    Destructors    *****/

			~vector()
			{
				for (size_t i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_arr + i);
				this->_alloc.deallocate(this->_arr, this->_cap);
			}

			vector& operator= (const vector& x)
			{
				this->~vector();
				
				this->_alloc = x._alloc;
				this->_size = x._size;
				this->_cap = x._cap;
				
				this->_arr = this->_alloc.allocate(this->_cap);
				for (size_type i = 0; i < this->_size; i++)
					this->_alloc.construct(this->_arr + i, x[i]);
				return *this;
			}

			allocator_type get_allocator() const
			{
				return (this->_alloc);
			}

			/*****    Iterators    *****/

			iterator begin()
			{
				return (iterator(this->_arr));
			}

			const_iterator begin() const
			{
				return (const_iterator(this->_arr));
			}

			iterator end()
			{
				return (iterator(this->_arr + this->_size));
			}
			const_iterator end() const
			{
				return (const_iterator(this->_arr + this->_size));
			}

			reverse_iterator rbegin()
			{
				return (reverse_iterator(this->end()));
			}

			const_reverse_iterator rbegin() const
			{
				return (const_reverse_iterator(this->end()));
			}

			reverse_iterator rend()
			{
				return (reverse_iterator(this->_arr));
			}

			const_reverse_iterator rend() const
			{
				return (const_reverse_iterator(this->_arr));
			}

			/*****    Capacity    *****/

			size_type size() const
			{
				return (this->_size);
			}

			size_type max_size() const
			{
				return (this->_alloc.max_size());
			}

			void resize (size_type n, value_type val = value_type())
			{
				if (n < this->_size)
				{
					while (n < this->_size)
						this->pop_back();
				}
				else if (n > this->_size)
				{
					if (n > this->_cap)
						this->reserve(n);
					for (size_t i = this->_size; i < n; i++)
					{
						this->_alloc.construct(this->_arr + i, val);
						this->_size += 1;
					}
				}
			}

			size_type capacity() const
			{
				return (this->_cap);
			}

			bool empty() const
			{
				return (this->_size == 0);
			}

			void reserve(size_type new_cap)
			{
				if (new_cap > this->max_size())
					throw std::length_error("vector");
				if (new_cap <= this->_cap)
					return;
				pointer new_arr = this->_alloc.allocate(new_cap);
				size_t i = 0;
				try
				{
					for (; i < this->_size; i++)
					{
						this->_alloc.construct(new_arr + i, this->_arr[i]);
					}
				}
				catch(std::exception & e)
				{
					for (size_t j = 0; j <= i; j++)
						this->_alloc.destroy(new_arr + j);
					this->_alloc.deallocate(new_arr, new_cap);
					throw;
				}
				for (size_t j = 0; j < this->_size; j++)
					this->_alloc.destroy(this->_arr + j);
				this->_alloc.deallocate(this->_arr, this->_cap);
				this->_arr = new_arr;
				this->_cap = new_cap;
			}

			/*****    Element Access    *****/

			reference operator[](size_type n)
			{
				return (this->_arr[n]);
			}

			const_reference operator[](size_type n) const
			{
				return (this->_arr[n]);
			}

			reference at(size_type n)
			{
				if (n >= this->_size)
					throw std::out_of_range("vector");
				return (this->_arr[n]);
			}

			const_reference at (size_type n) const
			{
				if (n >= this->_size)
					throw std::out_of_range("vector");
				return (this->_arr[n]);
			}

			reference front()
			{
				return (this->_arr[0]);
			}

			const_reference front() const
			{
				return (this->_arr[0]);
			}

			reference back()
			{
				return (this->_arr[this->_size - 1]);
			}

			const_reference back() const
			{
				return (this->_arr[this->_size - 1]);
			}

			/*****    Modifiers    *****/

			void assign (size_type n, const value_type& val)
			{
				this->clear();
				if (n > this->_cap)
					this->reserve(n);
				for (size_t i = 0; i < n; i++)
					this->_alloc.construct(this->_arr + i, val);
				this->_size = n;
			}

			template <class InputIterator>
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
			assign (InputIterator first, InputIterator last)
			{
				difference_type toAssign = last - first;
				this->clear();
				if (toAssign > this->_cap)
					this->reserve(toAssign);
				iterator it = this->begin();
				for (; first != last; first++)
				{
					this->_alloc.construct(&(*it), *first);
					it += 1;
					this->_size += 1;
				}
			}

			void push_back (const value_type& val)
			{
				if (this->_size + 1 > this->_cap)
					this->reserve(this->_cap == 0 ? 1 : this->_cap * 2);
				this->_alloc.construct(this->_arr + this->_size, val);
				this->_size += 1;
			}

			void pop_back()
			{
				this->_alloc.destroy(this->_arr + this->_size);
				this->_size -= 1;
			}

			iterator insert (iterator position, const value_type& val)
			{
				difference_type offset = position - this->begin();
				insert(position, 1, val);
				return (iterator(this->_arr + offset));
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				if (n == 0)
					return;
				difference_type offset = position - this->begin();
				if (this->_size + n >= this->_cap)
				{
					this->reserve(this->_cap * 2 > this->_size + n ? this->_cap * 2 : this->_size + n);
					position = this->begin() + offset;
				}
				for (difference_type i = this->_size; i > offset; i--)
				{
					this->_alloc.construct(this->_arr + i + n - 1, this->_arr[i - 1]);
					this->_alloc.destroy(this->_arr + i - 1);
				}
				for (size_type i = 0; i < n; i++)
				{
					this->_alloc.construct(this->_arr + offset + i, val);
				}
				this->_size += n;
			}

			template <class InputIterator>
			typename ft::enable_if<!ft::is_integral<InputIterator>::value, void>::type
			insert(iterator position, InputIterator first, InputIterator last)
			{
				vector<T> tmp(position, this->end());
				difference_type toAdd = last - first;
				difference_type pos = position - this->begin();
				if (this->_size + toAdd >= this->_cap)
					this->reserve(this->_cap * 2 > this->_size + toAdd ? this->_cap * 2 : this->_size + toAdd);
				while (first != last)
				{
					this->_alloc.construct(this->_arr + pos, *first);
					pos += 1;
					++first;
				}	
				for (iterator it = tmp.begin(); it != tmp.end(); it++)
				{
					this->_alloc.construct(this->_arr + pos, *it);
					pos += 1;
				}
				this->_size = this->_size + toAdd;
			}

			iterator erase (iterator position)
			{
				difference_type offset = position - this->begin();
				for (size_type i = offset; i < this->_size - 1; i++)
				{
					this->_arr[i] = this->_arr[i + 1];
				}
				_alloc.destroy(this->_arr + offset);
				this->_size -= 1;
				return (iterator(this->_arr + offset));
			}

			iterator erase (iterator first, iterator last)
			{
				difference_type toErase = last - first;
				difference_type startErasing = first - this->begin();
				for (size_type i = startErasing; i + toErase != this->_size; i++)
				{
					this->_arr[i] = this->_arr[i + toErase];
				}
				for (size_type i = this->_size - toErase; i != this->_size; i++)
				{
					_alloc.destroy(this->_arr + i);
				}
				this->_size -= toErase;
				return (iterator(this->_arr + startErasing));
			}

			template <typename U>
			void swap(U & a, U & b)
			{
				U tmp = a;
				a = b;
				b = tmp;
			}

			void swap(vector& x)
			{
				swap(this->_arr, x._arr);
				swap(this->_size, x._size);
				swap(this->_cap, x._cap);
				swap(this->_alloc, x._alloc);
			}

			void clear()
			{
				for (size_t i = 0; i < this->_size; i++)
					this->_alloc.destroy(this->_arr + i);
				this->_size = 0;
			}
	};

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

			/*****    Relational operators    *****/

	template <class T, class Alloc>
	bool operator==(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator<(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs <= rhs));
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs < rhs));
	}
}

#endif
