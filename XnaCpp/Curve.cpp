#include <cmath>
#include "Curve.hpp"
#include "MathHelper.hpp"

namespace Xna {
	Curve::Curve() {}
}

namespace Xna {
	bool Curve::IsConstant() const {
		return _keys.Count() <= 1;
	}

	CurveLoopType Curve::PreLoop() const {
		return _preLoop;
	}

	void Curve::PreLoop(CurveLoopType const& value) {
		_preLoop = value;
	}

	CurveLoopType Curve::PostLoop() const {
		return _postLoop;
	}

	void Curve::PostLoop(CurveLoopType const& value) {
		_postLoop = value;
	}

	CurveKeyCollection Curve::Keys() const {
		return _keys;
	}

	Curve Curve::Clone() {
		Curve curve;
		curve._keys = _keys.Clone();
		curve._preLoop = _preLoop;
		curve._postLoop = _postLoop;

		return curve;
	}

	float Curve::Evaluate(float position) {
        if (_keys.Count() == 0) {
            return 0.f;
        }

        if (_keys.Count() == 1) {
            return _keys.This(0).Value();
        }

        CurveKey first = _keys.This(0);
        CurveKey last = _keys.This(_keys.Count() - 1);
        int32_t cycle;
        float virtualPos;

        if (position < first.Position()) {
            switch (PreLoop())
            {
            case CurveLoopType::Constant:                
                return first.Value();

            case CurveLoopType::Linear:
                return first.Value() - first.TangentIn() * (first.Position() - position);

            case CurveLoopType::Cycle:
                cycle = GetNumberOfCycle(position);
                virtualPos = position - (cycle * (last.Position() - first.Position()));
                return GetCurvePosition(virtualPos);

            case CurveLoopType::CycleOffset:
                cycle = GetNumberOfCycle(position);
                virtualPos = position - (cycle * (last.Position() - first.Position()));
                return (GetCurvePosition(virtualPos) + cycle * (last.Value() - first.Value()));

            case CurveLoopType::Oscillate:
                cycle = GetNumberOfCycle(position);
                if (0 == fmod(cycle, 2.f))
                    virtualPos = position - (cycle * (last.Position() - first.Position()));
                else
                    virtualPos = last.Position() - position + first.Position() + (cycle * (last.Position() - first.Position()));
                return GetCurvePosition(virtualPos);
            }
        }
        else if (position > last.Position()) {
            int32_t cycle;
            switch (PostLoop())
            {
            case CurveLoopType::Constant:
                return last.Value();

            case CurveLoopType::Linear:
                return last.Value() + first.TangentOut() * (position - last.Position());

            case CurveLoopType::Cycle:
                cycle = GetNumberOfCycle(position);
                virtualPos = position - (cycle * (last.Position() - first.Position()));
                return GetCurvePosition(virtualPos);

            case CurveLoopType::CycleOffset:
                cycle = GetNumberOfCycle(position);
                virtualPos = position - (cycle * (last.Position() - first.Position()));
                return (GetCurvePosition(virtualPos) + cycle * (last.Value() - first.Value()));

            case CurveLoopType::Oscillate:
                cycle = GetNumberOfCycle(position);
                virtualPos = position - (cycle * (last.Position() - first.Position()));
                if (0 == fmod(cycle, 2.f))
                    virtualPos = position - (cycle * (last.Position() - first.Position()));
                else
                    virtualPos = last.Position() - position + first.Position() + (cycle * (last.Position() - first.Position()));
                return GetCurvePosition(virtualPos);
            }
        }

        return GetCurvePosition(position);
	}

    void Curve::ComputeTangents(CurveTangent const& tangentType) {
        ComputeTangents(tangentType, tangentType);
    }

    void Curve::ComputeTangents(CurveTangent const& tangentInType, CurveTangent const& tangentOutType) {
        for (size_t i = 0; i < _keys.Count(); ++i)
        {
            ComputeTangent(i, tangentInType, tangentOutType);
        }
    }

    void Curve::ComputeTangent(size_t keyIndex, CurveTangent const& tangentType) {
        ComputeTangent(keyIndex, tangentType, tangentType);
    }

    void Curve::ComputeTangent(size_t keyIndex, CurveTangent const& tangentInType, CurveTangent const& tangentOutType) {
        auto key = _keys.This(keyIndex);

        float p0, p, p1;
        p0 = p = p1 = key.Position();

        float v0, v, v1;
        v0 = v = v1 = key.Value();

        if (keyIndex > 0) {
            p0 = _keys.This(keyIndex - 1).Position();
            v0 = _keys.This(keyIndex - 1).Value();
        }

        if (keyIndex < _keys.Count() - 1) {
            p1 = _keys.This(keyIndex + 1).Position();
            v1 = _keys.This(keyIndex + 1).Value();
        }

        switch (tangentInType)
        {
        case CurveTangent::Flat:
            key.TangentIn(0);
            break;
        case CurveTangent::Linear:
            key.TangentIn(v - v0);
            break;
        case CurveTangent::Smooth:
            auto pn = p1 - p0;
            if (abs(pn) < MathHelper::Epsilon)
                key.TangentIn(0);
            else
                key.TangentIn((v1 - v0) * ((p - p0) / pn));
            break;
        }

        switch (tangentOutType)
        {
        case CurveTangent::Flat:
            key.TangentOut(0);
            break;
        case CurveTangent::Linear:
            key.TangentOut(v1 - v);
            break;
        case CurveTangent::Smooth:
            auto pn = p1 - p0;
            if (abs(pn) < MathHelper::Epsilon)
                key.TangentOut(0);
            else
                key.TangentOut((v1 - v0) * ((p1 - p) / pn));
            break;
        }
    }

    int32_t Curve::GetNumberOfCycle(float position) {
        auto cycle = (position - _keys.This(0).Position()) / (_keys.This(_keys.Count() - 1).Position() - _keys.This(0).Position());
        
        if (cycle < 0.f)
            cycle--;

        return static_cast<int32_t>(cycle);
    }

    float Curve::GetCurvePosition(float position) {
        CurveKey prev = _keys.This(0);
        CurveKey next;

        for (size_t i = 1; i < _keys.Count(); ++i)
        {
            next = _keys.This(i);

            if (next.Position() >= position) {
                if (prev.Continuity() == CurveContinuity::Step) {
                    if (position >= 1.f) {
                        return next.Value();
                    }
                    return prev.Value();
                }

                auto t = (position - prev.Position()) / (next.Position() - prev.Position());
                auto ts = t * t;
                auto tss = ts * t;
                
                return (2.F * tss - 3 * ts + 1.f) * prev.Value()
                    + (tss - 2 * ts + t) * prev.TangentOut()
                    + (3 * ts - 2 * tss) * next.Value()
                    + (tss - ts) * next.TangentIn();
            }
        
            prev = next;
        }

        return 0.f;
    }
}