/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 16:35:26 by dselmy            #+#    #+#             */
/*   Updated: 2022/07/05 22:03:16 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_STACK_HPP
# define FT_STACK_HPP

# include "vector.hpp"

namespace ft
{
	template < class T, class Container = ft::vector<T> >
	class stack
	{
		private:
			typedef typename Container::value_type value_type;
			typedef typename Container::size_type size_type;
			typedef Container container_type;

		protected:
			Container c;

		public:
			explicit stack(const container_type& ctnr = container_type()): c(ctnr) {};

			stack( const stack& other )
			{
				*this = other;
			}
			
			stack& operator=(const stack& other)
			{
				this->c = other.c;
				return *this;
			}

			bool empty() const
			{
				return (this->c.empty());
			}

			size_type size() const
			{
				return (this->c.size());
			}

			value_type& top()
			{
				return (this->c.back());
			}

			const value_type& top() const
			{
				return (this->c.back());
			}

			void push(const value_type& val)
			{
				return (this->c.push_back(val));
			}

			void pop()
			{
				return (this->c.pop_back());
			}
		
			// template <class U, class ContU>
			// friend bool operator==(const stack<class U, class ContU>& lhs, \
			// 						const stack<class U, class ContU>& rhs);
			
			// template <class U, class ContU>
			// friend bool operator<(const stack<class U, class ContU>& lhs, \
			// 						const stack<class U, class ContU>& rhs);
			template <class U, class ContainerU>
			friend bool operator==(const ft::stack<U, ContainerU>& lhs, const ft::stack<U, ContainerU>& rhs);

			template <class U, class ContainerU>
			friend bool operator!=(const ft::stack<U, ContainerU>& lhs, const ft::stack<U, ContainerU>& rhs);
			
			template <class U, class ContainerU>
			friend bool operator<(const ft::stack<U, ContainerU>& lhs, const ft::stack<U, ContainerU>& rhs);

			template <class U, class ContainerU>
			friend bool operator<=(const ft::stack<U, ContainerU>& lhs, const ft::stack<U, ContainerU>& rhs);

			template <class U, class ContainerU>
			friend bool operator>(const ft::stack<U, ContainerU>& lhs, const ft::stack<U, ContainerU>& rhs);

			template <class U, class ContainerU>
			friend bool operator>=(const ft::stack<U, ContainerU>& lhs, const ft::stack<U, ContainerU>& rhs);
	};
	
	template <class T, class Container>
	bool operator==(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}

	template <class T, class Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c != rhs.c);
	}
			
	template <class T, class Container>
	bool operator<(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}

	template <class T, class Container>
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c > rhs.c);
	}

	template <class T, class Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c <= rhs.c);
	}

	template <class T, class Container>
	bool operator>=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c >= rhs.c);
	}
}

#endif
