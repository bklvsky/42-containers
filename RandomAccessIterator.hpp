/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomAccessIterator.hpp                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 20:26:23 by dselmy            #+#    #+#             */
/*   Updated: 2022/07/05 20:06:46 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RANDOMACCESSITERATOR_HPP
# define FT_RANDOMACCESSITERATOR_HPP

# include "iterator.hpp"
# include <iterator>

namespace ft
{
	template<typename T>
	class RandomAccessIterator: public iterator<std::random_access_iterator_tag, T>
	{
		public:
		
			// typedef iterator<std::random_access_iterator_tag, T> iterator;
			typedef typename iterator<std::random_access_iterator_tag, T>::iterator_category iterator_category;
			typedef typename iterator<std::random_access_iterator_tag, T>::value_type value_type;
			typedef typename iterator<std::random_access_iterator_tag, T>::difference_type difference_type;
			typedef value_type* iterator_type;
			typedef value_type* pointer;
			typedef value_type& reference;
			

			RandomAccessIterator(): _ptr(NULL) {}
		
			RandomAccessIterator(const pointer elem): _ptr(elem)
			{
			}
		
			RandomAccessIterator<T>(const RandomAccessIterator& copy): _ptr(copy._ptr)
			{
			}
		
			virtual ~RandomAccessIterator() {};
			
			RandomAccessIterator& operator=(const RandomAccessIterator & other)
			{
				this->_ptr = other._ptr;
				return (*this);
			}

			operator RandomAccessIterator<const T> () const
			{
				return RandomAccessIterator<const T> (this->_ptr);
			}

		private:
			pointer _ptr;
		
		public:
		
			/*****    Dereferencing operators    *****/
		
			reference operator* ()
			{
				return *(this->_ptr);
			}

			pointer operator-> ()
			{
				return (this->_ptr);
			}

			reference operator[](difference_type n)
			{
				return (*(this->_ptr + n));
			}

			/*****    Difference operator    *****/
			
			difference_type operator-(RandomAccessIterator rhs)
			{
				return (this->_ptr - rhs._ptr);
			}
			
			/*****    Decrement and increment operators    *****/

			RandomAccessIterator<T> & operator++()
			{
				return *this += 1;
			}

			RandomAccessIterator<T> operator++(int)
			{
				RandomAccessIterator<T> ret = *this;
				*this += 1;
				return ret;
			}

			RandomAccessIterator<T> & operator--()
			{
				return *this -= 1;
			}

			RandomAccessIterator<T> operator--(int)
			{
				RandomAccessIterator<T> ret = *this;
				*this -= 1;
				return ret;
			}

			RandomAccessIterator<T> & operator+=(difference_type n)
			{
				this->_ptr += n;
				return *this;
			}

			RandomAccessIterator<T> & operator-=(difference_type n)
			{
				this->_ptr -= n;
				return *this;
			}

			RandomAccessIterator<T> operator+(difference_type n)
			{
				RandomAccessIterator<T> ret = *this;
				return ret += n;
			}

			RandomAccessIterator<T> operator-(difference_type n)
			{
				RandomAccessIterator<T> ret = *this;
				return ret -= n;
			}

			/*****    Relational operator templates    *****/

			template <typename A, typename B>
			inline friend bool operator==(const RandomAccessIterator<A> & lhs, \
											const RandomAccessIterator<B> & rhs);
			template <typename A, typename B>
			inline friend bool operator!=(const RandomAccessIterator<A> & lhs, \
											const RandomAccessIterator<B> & rhs);
			template <typename A, typename B>
			inline friend bool operator<(const RandomAccessIterator<A> & lhs, \
											const RandomAccessIterator<B> & rhs);

			template <typename A, typename B>
			inline friend bool operator<=(const RandomAccessIterator<A> & lhs, \
											const RandomAccessIterator<B> & rhs);
			template <typename A, typename B>
			inline friend bool operator>(const RandomAccessIterator<A> & lhs, \
											const RandomAccessIterator<B> & rhs);

			template <typename A, typename B>
			inline friend bool operator>=(const RandomAccessIterator<A> & lhs, \
											const RandomAccessIterator<B> & rhs);
			
			template <typename A, typename B>
			inline friend typename RandomAccessIterator<A>::difference_type
			operator-(const RandomAccessIterator<A> & lhs, \
											const RandomAccessIterator<B> & rhs);
	};

	template <typename A, typename B>
	inline bool operator==(const RandomAccessIterator<A> & lhs, \
												const RandomAccessIterator<B> & rhs)
	{
		return (lhs._ptr == rhs._ptr);
	}

	template <typename A, typename B>
	inline bool operator!=(const RandomAccessIterator<A> & lhs, \
												const RandomAccessIterator<B> & rhs)
	{
		return (lhs._ptr != rhs._ptr);
	}

	template <typename A, typename B>
	inline bool operator<(const RandomAccessIterator<A> & lhs, \
												const RandomAccessIterator<B> & rhs)
	{
		return (lhs._ptr < rhs._ptr);
	}

	template <typename A, typename B>
	inline bool operator<=(const RandomAccessIterator<A> & lhs, \
												const RandomAccessIterator<B> & rhs)
	{
		return (!(rhs._ptr < lhs._ptr));
	}

	template <typename A, typename B>
	inline bool operator>(const RandomAccessIterator<A> & lhs, \
												const RandomAccessIterator<B> & rhs)
	{
		return (rhs._ptr < lhs._ptr);
	}

	template <typename A, typename B>
	inline bool operator>=(const RandomAccessIterator<A> & lhs, \
												const RandomAccessIterator<B> & rhs)
	{
		return (!(lhs._ptr < rhs._ptr));
	}

	template <typename A, typename B>
	inline typename RandomAccessIterator<A>::difference_type
	operator-(const RandomAccessIterator<A> & lhs, \
												const RandomAccessIterator<B> & rhs)
	{
		return (lhs._ptr - rhs._ptr);
	}

	template <typename T>
	inline RandomAccessIterator<T> operator+ 
	(typename RandomAccessIterator<T>::difference_type lhs, const RandomAccessIterator<T> & rhs)
	{
		return (rhs + lhs);
	}
}

#endif
