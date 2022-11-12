#include "CurveKey.hpp"

namespace Xna {
	CurveKey::CurveKey(){}

	CurveKey::CurveKey(float position, float value) :
		_position(position), _value(value) {}
	
	CurveKey::CurveKey(float position, float value, float tangentIn, float tangentOut) :
		_position(position), _value(value), _tangentIn(tangentIn), _tangentOut(tangentOut) {}

	CurveKey::CurveKey(float position, float value, float tangentIn, float tangentOut, CurveContinuity const& continuity) :
		_position(position), _value(value), _tangentIn(tangentIn), _tangentOut(tangentOut), _continuity(continuity) {}
}

namespace Xna {
	bool operator ==(CurveKey const& value1, CurveKey const& value2) {
		return value1.Equals(value2);
	}

	bool operator !=(CurveKey const& value1, CurveKey const& value2) {
		return !value1.Equals(value2);
	}
}

namespace Xna {
	CurveContinuity CurveKey::Continuity() const {
		return _continuity;
	}

	void CurveKey::Continuity(CurveContinuity const& value) {
		_continuity = value;
	}

	float CurveKey::Position() const {
		return _position;
	}

	float CurveKey::TangentIn() const {
		return _tangentIn;
	}

	void CurveKey::TangentIn(float value) {
		_tangentIn = value;
	}

	float CurveKey::TangentOut() const {
		return _tangentOut;
	}

	void CurveKey::TangentOut(float value) {
		_tangentOut = value;
	}

	float CurveKey::Value() const {
		return _value;
	}

	void CurveKey::Value(float value) {
		_value = value;
	}

	CurveKey CurveKey::Clone() const {
		return CurveKey(_position, _value, _tangentIn, _tangentOut, _continuity);
	}

	bool CurveKey::Equals(CurveKey const& other) const {
		return (_position == other._position)
			&& (_value == other._value)
			&& (_tangentIn == other._tangentIn)
			&& (_tangentOut == other._tangentOut)
			&& (_continuity == other._continuity);
	}
}