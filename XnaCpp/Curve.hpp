#ifndef _CURVE_HPP_
#define _CURVE_HPP_

#include <cstdint>
#include "CurveLoopType.hpp"
#include "CurveKeyCollection.hpp"
#include "CurveTangent.hpp"

namespace Xna {
	class Curve {
		CurveLoopType _preLoop;
		CurveLoopType _postLoop;
		CurveKeyCollection _keys;

	public:
		Curve();

		bool IsConstant() const;
		CurveLoopType PreLoop() const;
		void PreLoop(CurveLoopType const& value);
		CurveLoopType PostLoop() const;
		void PostLoop(CurveLoopType const& value);
		CurveKeyCollection Keys() const;
		Curve Clone();
		float Evaluate(float position);
		void ComputeTangents(CurveTangent const& tangentType);
		void ComputeTangents(CurveTangent const& tangentInType, CurveTangent const& tangentOutType);
		void ComputeTangent(size_t keyIndex, CurveTangent const& tangentInType, CurveTangent const& tangentOutType);
		void ComputeTangent(size_t keyIndex, CurveTangent const& tangentType);
		int32_t GetNumberOfCycle(float position);
		float GetCurvePosition(float position);
	};
}

#endif