#ifndef _CURVEKEY_HPP_
#define _CURVEKEY_HPP_

#include "CurveContinuity.hpp"

namespace Xna {
	class CurveKey {
		CurveContinuity _continuity{ CurveContinuity::Smooth };
		float _position{ 0 };
		float _tangentIn{ 0 };
		float _tangentOut{ 0 };
		float _value{ 0 };

	public:

		CurveKey();
		CurveKey(float position, float value);
		CurveKey(float position, float value, float tangentIn, float tangentOut);
		CurveKey(float position, float value, float tangentIn, float tangentOut, CurveContinuity const& continuity);

		friend bool operator ==(CurveKey const& value1, CurveKey const& value2);
		friend bool operator !=(CurveKey const& value1, CurveKey const& value2);

		CurveContinuity Continuity() const;
		void Continuity(CurveContinuity const& value);
		float Position() const;
		float TangentIn() const;
		void TangentIn(float value);
		float TangentOut() const;
		void TangentOut(float value);
		float Value() const;
		void Value(float value);
		CurveKey Clone() const;
		bool Equals(CurveKey const& other) const;
	};
}

#endif