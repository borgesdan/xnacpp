#ifndef _CURVEKEYCOLLECTION_HPP_
#define _CURVEKEYCOLLECTION_HPP_

#include <vector>
#include "CurveKey.hpp"

namespace Xna {
	class CurveKeyCollection {
		std::vector<CurveKey> _keys;

	public:

		CurveKeyCollection();

		CurveKey This(size_t index) const;
		void This(size_t index, CurveKey const& value);
		int32_t Count() const;
		bool IsReadOnly() const;
		void Add(CurveKey const& item);
		void Clear();
		CurveKeyCollection Clone() const;
		bool Contains(CurveKey const& item) const;		
		void CopyTo(std::vector<CurveKey>& array, size_t arrayIndex) const;
		int32_t IndexOf(CurveKey const& item) const;
		void RemoveAt(size_t index);
		bool Remove(CurveKey const& item);
	};
}

#endif