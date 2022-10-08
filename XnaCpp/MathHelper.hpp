#ifndef _MATHHELPER_HPP_
#define _MATHHELPER_HPP_

#include <cstdint>

namespace Xna {
	class MathHelper {
	public:
		static constexpr float E = 2.7182818284590451F;
		static constexpr float PI = 3.1415926535897931F;
		static constexpr float LOG10E = 0.4342945F;
		static constexpr float LOG2E = 1.442695F;
		static constexpr float PIOVER2 = PI / 2.0F;
		static constexpr float PiOVER4 = PI / 4.0F;
		static constexpr float TWOPI = PI * 2.0F;
		static constexpr float TAU = TWOPI;

		static float Barycentric(float value1, float value2, float value3, float amount1, float amount2);
		static float CatmullRom(float value1, float value2, float value3, float value4, float amount);
		static float Clamp(float value, float min, float max);

		static int Clamp(int32_t value, int32_t min, int32_t max);
		static float Distance(float value1, float value2);
		static float Hermite(float value1, float tangent1, float value2, float tangent2, float amount);
		static float Lerp(float value1, float value2, float amount);		
		static float LerpPrecise(float value1, float value2, float amount);
		static float Max(float value1, float value2);
		static int32_t Max(int32_t value1, int32_t value2);
		static float Min(float value1, float value2);
		static int32_t Min(int32_t value1, int32_t value2);
		static float SmoothStep(float value1, float value2, float amount);
		static float ToDegrees(float radians);
		static float ToRadians(float degrees);
		static float WrapAngle(float angle);
		static bool IsPowerOfTwo(int32_t value);
	};
}

#endif