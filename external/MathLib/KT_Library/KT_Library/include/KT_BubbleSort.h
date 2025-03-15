#pragma once
/*****************************************************************//**
 * @file   KT_BubbleSort.h
 * @brief  This file contains the BubbleSort
 *
 * @author Kroktur
 * @date   February 2025
 *********************************************************************/
#include "KT_Algorithm.h"
#include "KT_Math.h"
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
		 * @brief BubbleSort
		 * @tparam container 
		 */
		template<typename container>
		struct BubbleSort
		{
			void operator()(container& data)
			{
				for (auto it = data.begin(); it != data.end(); ++it)
				{
					for (auto it2 = data.begin(); it2 != data.end() - 1; ++it2)
					{
						if (*it2 > *(it2 + 1))
						{
							KT::Math::Swap(*it2, *(it2 + 1));
						}
					}
				}
			}

		};
	}
}
