#pragma once
/*****************************************************************//**
 * @file   KT_InsertionSort.h
 * @brief  This file contains the InsertionSort
 *
 * @author Kroktur
 * @date   February 2025
 *********************************************************************/
#include "KT_Algorithm.h"
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
		 * @brief InsertionSort
		 * @tparam container
		 */
		template<typename container>
		struct InsertionSort
		{
			void operator()(container& data)
			{
				for (auto it = data.begin() + 1; it != data.end(); ++it)
				{
					auto curent = *it;
					auto it2 = it;
					while (*(it2 - 1) > curent && it2 != data.begin())
					{
						*it2 = *(it2 - 1);
						--it2;
					}
					*it2 = curent;
				}
			}
		};
	}
	
}
