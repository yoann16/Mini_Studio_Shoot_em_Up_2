#pragma once

/*****************************************************************//**
 * @file   KT_Math.h
 * @brief  This file contains all the function stl like
 *
 * @author Kroktur
 * @date   February 2025
 *********************************************************************/
 /**
  * @brief Namespace of my library
  */
namespace KT
{
	/**
	* @brief Namespace of my Math function
	*/
	namespace Math
	{
		/**
		 * @brief Fill a container with value
		 * @tparam Iterator begin 
		 * @tparam Iterator End 
		 * @tparam value_type
		 * @param Iterator 
		 * @param Iterator 
		 * @param value_type 
		 */
		template<typename input, typename outpout, typename value>
		void Fill(input begin, outpout end, const value& val)
		{
			if (begin == end)
				return;
			for (auto it = begin; it != end; ++it)
			{
				*it = val;
			}
		}

		/**
		 * @brief Copy a range of data in a dest
		 * @tparam Iterator begin 
		 * @tparam Iterator End 
		 * @tparam Iterator Destination 
		 * @param Iterator 
		 * @param Iterator 
		 * @param Iterator 
		 */
		template<typename input, typename output, typename dest>
		void Copy(input begin, output end, dest val)
		{
			if (begin == end)
				return;
			auto myval = val;
			size_t i = 0;
			for (auto it = begin; it != end; ++it)
			{
				*myval = *it;
				++myval;
				++i;
			}
		}

		/**
		 * @brief swap element
		 * @tparam value_type 
		 * @param value_type lhs
		 * @param value_type rhs
		 */
		template<typename type>
		void Swap(type& lhs, type& rhs)
		{
			auto type = lhs;
			lhs = rhs;
			rhs = lhs;
		}

		/**
		 * @brief find an iterator by value
		 * @tparam Iteator 
		 * @tparam Value_type 
		 * @param begin 
		 * @param end 
		 * @param val 
		 * @return Iterator
		 */
		template<typename Iteator, typename Value_type>
		Iteator Find(Iteator begin , Iteator end , const Value_type& val)
		{
			for (auto it = begin ; it != end ; ++it)
			{
				if (*it == val)
					return it;
			}
			return end;
		}
	}
	
}