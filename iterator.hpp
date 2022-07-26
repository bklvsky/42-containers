/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dselmy <dselmy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 01:35:01 by dselmy            #+#    #+#             */
/*   Updated: 2022/07/05 20:23:03 by dselmy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

# include <cstddef>
namespace ft
{
	template <class Category, class T, class Distance = std::ptrdiff_t,
			class Pointer = T*, class Reference = T&>
	class iterator
	{
		public:
			iterator() {} ;
			virtual ~iterator() {};
			typedef Category iterator_category;
			typedef T value_type;
			typedef Distance difference_type;
			typedef Pointer pointer;
			typedef Reference reference;
	};

	struct bidirectional_iterator_tag {};

	struct random_access_iterator_tag: public bidirectional_iterator_tag {};

	template< class Iter >
	struct iterator_traits
	{
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template <bool Cond, class T = void>
	struct enable_if;

	template <class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <class T, bool v>
	struct integral_constant
	{
		static const bool value = v;
		typedef T value_type;
		typedef integral_constant type;
		operator value_type () const
		{
			return value;
		}
	};

	typedef ft::integral_constant<bool, true> true_type;
	typedef ft::integral_constant<bool, false> false_type;

	template <class T>
	struct is_integral: public ft::false_type {};

	template <>
	struct is_integral<bool>: ft::true_type {};

	template <>
	struct is_integral<char>: ft::true_type {};

	template <>
	struct is_integral<signed char>: ft::true_type {};

	template <>
	struct is_integral<unsigned char>: ft::true_type {};

	template <>
	struct is_integral<wchar_t>: ft::true_type {};

	template <>
	struct is_integral<char16_t>: ft::true_type {};

	template <>
	struct is_integral<short>: ft::true_type {};

	template <>
	struct is_integral<unsigned short>: ft::true_type {};

	template <>
	struct is_integral<int>: ft::true_type {};

	template <>
	struct is_integral<unsigned int>: ft::true_type {};

	template <>
	struct is_integral<long>: ft::true_type {};

	template <>
	struct is_integral<unsigned long>: ft::true_type {};

	template <>
	struct is_integral<long long>: ft::true_type {};

	template <>
	struct is_integral<unsigned long long>: ft::true_type {};

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1 != last1) 
		{
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1) 
		{
			if (!pred(*first1, *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (*first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
                                InputIterator2 first2, InputIterator2 last2,
                                Compare comp)
	{
		while (first1 != last1 && first2 != last2)
		{
			if (comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
			++first1;
			++first2;
		}
		return (first1 == last1) && (first2 != last2);
	}
}

#endif
