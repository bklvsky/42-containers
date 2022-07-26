/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 12:46:26 by dselmy            #+#    #+#             */
/*   Updated: 2022/06/25 16:19:31 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REVERSEITERATOR_HPP
# define FT_REVERSEITERATOR_HPP

# include "iterator.hpp"

namespace ft
{
	template<class Iter>
	class reverse_iterator
	{
		public:
			typedef Iter iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer pointer;
			typedef typename ft::iterator_traits<Iter>::reference reference;
			
		protected:
			iterator_type current;
		
		public:
			reverse_iterator(): current() {}
			explicit reverse_iterator( iterator_type x): current(x) {}
			reverse_iterator(const reverse_iterator & copy): current(copy.current) {}
			virtual ~reverse_iterator() {}
			
			template<class U>
			reverse_iterator(const reverse_iterator<U> & other): current(other.base()) {}
			
			template<class U>
			reverse_iterator& operator=(const reverse_iterator<U>& other)
			{
				this->current = other.base();
				return *this;
			}

			iterator_type base() const
			{
				return (this->current);
			}

			reference operator*() const
			{
				iterator_type tmp = this->current;
				return *(tmp - 1);
			}

			pointer operator->() const
			{
				return &(*(this->current - 1));
			}

			reference operator[](difference_type n) const
			{
				return (this->current[-n - 1]);
			}

				/*****    Decrement and increment operators    *****/

			reverse_iterator& operator++()
			{
				this->current -= 1;
				return *(this);
			}

			reverse_iterator& operator--()
			{
				this->current += 1;
				return *(this);
			}

			reverse_iterator operator++( int)
			{
				reverse_iterator<Iter> ret = *this;
				this->current -= 1;
				return (ret);
			}
			
			reverse_iterator operator--( int)
			{
				reverse_iterator<Iter> ret = *this;
				this->current += 1;
				return (ret);
			}
			
			reverse_iterator& operator+=( difference_type n)
			{
				this->current -= n;
				return (*this);
			}
			reverse_iterator& operator-=( difference_type n)
			{
				this->current += n;
				return (*this);
			}
			
			reverse_iterator operator+(difference_type n) const
			{
				reverse_iterator<Iter> ret = *this;
				return (ret += n);				
			}

			reverse_iterator operator-(difference_type n) const
			{
				reverse_iterator<Iter> ret = *this;
				return (ret -= n);
			}
			
			/*****    Relational operator templates    *****/
			
	};

	template< class Iterator1, class Iterator2 >
	bool operator==(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=(const ft::reverse_iterator<Iterator1>& lhs,\
		const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() != rhs.base());
	}
	
	template< class Iterator1, class Iterator2 >
	bool operator>(const ft::reverse_iterator<Iterator1>& lhs,
					const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=(const ft::reverse_iterator<Iterator1>& lhs,\
		const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() >= rhs.base());
	}
	
	template< class Iterator1, class Iterator2 >
	bool operator<(const ft::reverse_iterator<Iterator1>& lhs,\
					const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=(const ft::reverse_iterator<Iterator1>& lhs,\
		const ft::reverse_iterator<Iterator2>& rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template< class Iter >
	reverse_iterator<Iter>
	operator+(typename reverse_iterator<Iter>::difference_type n,\
				const reverse_iterator<Iter>& it)
	{
		return (it + n);
	}

	template<class Iterator>
	typename reverse_iterator<Iterator>::difference_type
	operator-(const reverse_iterator<Iterator>& lhs,\
				const reverse_iterator<Iterator>& rhs)
	{
		return (rhs.base() - lhs.base());
	}
}

#endif

