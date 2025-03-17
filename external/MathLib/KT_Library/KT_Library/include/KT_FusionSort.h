#pragma once
/*****************************************************************//**
 * @file   KT_FusionSort.h
 * @brief  This file contains the FusionSort
 *
 * @author Kroktur
 * @date   February 2025
 *********************************************************************/
#include "KT_Vector.h"
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
		 * @brief FusionSort
		 * @tparam container
		 */
		template<typename container>
		struct FusionSort
		{
			using Iterator = typename container::iterator;
			void operator()(container& data)
			{
				auto it = data.end();
				internalfusion(data, data.begin(), --it);
			}

		private:
			void merge_fusion(container& val, Iterator startidx, Iterator middleidx, Iterator endrightidx)
			{
				auto leftstartidx = startidx;
				auto leftendidx = middleidx;
				auto rightstartidx = middleidx + 1;
				auto rightendidx = endrightidx;

				auto curentleftidx = leftstartidx;
				auto curentrightidx = rightstartidx;
				KT::Vector<typename container::value_type> tmptab;
				tmptab.reserve(endrightidx - startidx);

				while (curentleftidx < leftendidx + 1 && curentrightidx < rightendidx + 1)
				{
					if (*curentleftidx <= *curentrightidx)
					{
						tmptab.pushBack(*curentleftidx);
						++curentleftidx;
					}
					else
					{
						tmptab.pushBack(*curentrightidx);
						++curentrightidx;
					}
				}
				while (curentleftidx < leftendidx + 1)
				{
					tmptab.pushBack(*curentleftidx);
					++curentleftidx;
				}

				while (curentrightidx < rightendidx + 1)
				{
					tmptab.pushBack(*curentrightidx);
					++curentrightidx;
				}
				auto tmpit = tmptab.begin();
				for (auto it = startidx; it != endrightidx + 1; ++it)
				{
					*it = *tmpit;
					++tmpit;
				}
			}

			void internalfusion(container& val, Iterator startidx, Iterator endidx)
			{
				if (startidx == endidx)
					return;

				auto it = startidx;
				size_t size = 0;
				while (it != endidx)
				{
					++it;
					++size;
				}
				auto middleidx = startidx + (size / 2);

				internalfusion(val, startidx, middleidx);
				internalfusion(val, middleidx + 1, endidx);

				merge_fusion(val, startidx, middleidx, endidx);
			}
		};
	}
}
