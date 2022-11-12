#include "CurveKeyCollection.hpp"
#include <algorithm>

using std::vector;
using std::find;

namespace Xna {
	CurveKeyCollection::CurveKeyCollection() {}
}

namespace Xna {
	CurveKey CurveKeyCollection::This(size_t index) const {
		return _keys[index];
	}

	void CurveKeyCollection::This(size_t index, CurveKey const& value) {
		//TODO: verificar exceções
		if (_keys[index].Position() == value.Position())
			_keys[index] = value;
		else
		{			
			_keys.erase(_keys.begin() + index);
			_keys.push_back(value);
		}
	}

	int32_t CurveKeyCollection::Count() const {
		return _keys.size();
	}

	bool CurveKeyCollection::IsReadOnly() const {
		return false;
	}

	void CurveKeyCollection::Add(CurveKey const& item) {
		//TODO: verificar exceções

		if (_keys.size() == 0)
		{
			_keys.push_back(item);
			return;
		}

		for (size_t i = 0; i < _keys.size(); i++)
		{
			if (item.Position() < _keys[i].Position()) {				
				_keys.insert(_keys.begin() + i, item);
				return;
			}
		}

		_keys.push_back(item);
	}

	void CurveKeyCollection::Clear() {
		_keys.clear();
	}

	CurveKeyCollection CurveKeyCollection::Clone() const {
		CurveKeyCollection curveKeyCollection;
		curveKeyCollection._keys = _keys;
		
		return curveKeyCollection;
	}

	bool CurveKeyCollection::Contains(CurveKey const& item) const {
		return find(_keys.begin(), _keys.end(), item) != _keys.end();
	}

	void CurveKeyCollection::CopyTo(std::vector<CurveKey>& array, size_t arrayIndex) const {		
		array = vector<CurveKey>(_keys.begin() + arrayIndex, _keys.end());
	}

	int32_t CurveKeyCollection::IndexOf(CurveKey const& item) const {
		auto it = find(_keys.begin(), _keys.end(), item);
		size_t index = -1;

		if (it != _keys.end())
			index = it - _keys.begin();

		return index;
	}

	void CurveKeyCollection::RemoveAt(size_t index) {
		_keys.erase(_keys.begin() + index);
	}

	bool CurveKeyCollection::Remove(CurveKey const& item) {
		auto index = IndexOf(item);

		if (index != -1)
			_keys.erase(_keys.begin() + index);
	}
}