#pragma once
/*****************************************************************//**
 * @file   KT_Algorithm.h
 * @brief  This file contains the sort and transform
 *
 * @author Kroktur
 * @date   February 2025
 *********************************************************************/
#include "KT_FusionSort.h"
#include "KT_BubbleSort.h"
#include "KT_InsertionSort.h"
 /**
  * @brief Namespace of my library
  */
namespace KT
{
	/**
	 * @brief Namespace of my Algorithm
	 */
	namespace Algorithm
	{
		/**
		 * @brief This function sorts all KT::Container and stl container by KT::Instrusivlist
		 * @tparam container 
		 * @tparam sort method KT::Algorithm or any method with the () operator
		 * @param container
		 */
		template<typename container, template<typename>class SortMethode>
		void Sort(container& data)
		{
			SortMethode<container>()(data);
		}
		/**
		 * @brief This function allows you to make transformations Enregistrer la traduction
		 * @tparam Iterator input
		 * @tparam Iterator output
		 * @tparam Founction
		 * 
		 * @param begin
		 * @param end
		 * @param dest
		 * @param fn_
		 */
		template<typename input, typename output, typename fn>
		void transform(input* begin, input* end, output* dest, fn fn_)
		{
			for (auto it = begin; it != end; ++it, ++dest)
			{
				*dest = fn_(*it);
			}
		}
	}
}
