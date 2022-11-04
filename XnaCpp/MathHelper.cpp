#include "MathHelper.hpp"
#include <cmath>
#include <limits>

using std::numeric_limits;

namespace Xna {

	float MathHelper::Barycentric(float value1, float value2, float value3, float amount1, float amount2) {
		return value1 + (value2 - value1) * amount1 + (value3 - value1) * amount2;
	}

	float MathHelper::CatmullRom(float value1, float value2, float value3, float value4, float amount) {
		float amountSquared = amount * amount;
		float amountCubed = amountSquared * amount;
		return (0.5F * (2.0F * value2 +
			(value3 - value1) * amount +
			(2.0F * value1 - 5.0F * value2 + 4.0F * value3 - value4) * amountSquared +
			(3.0F * value2 - value1 - 3.0F * value3 + value4) * amountCubed));
	}

	float MathHelper::Clamp(float value, float min, float max) {
		value = (value > max) ? max : value;
		value = (value < min) ? min : value;
		return value;
	}

	int32_t MathHelper::Clamp(int32_t value, int32_t min, int32_t max) {
		value = (value > max) ? max : value;
		value = (value < min) ? min : value;
		return value;
	}

	float MathHelper::Distance(float value1, float value2) {
		return abs(value1 - value2);
	}

	float MathHelper::Hermite(float value1, float tangent1, float value2, float tangent2, float amount) {
		float v1 = value1, v2 = value2, t1 = tangent1, t2 = tangent2, s = amount, result;
		float sCubed = s * s * s;
		float sSquared = s * s;

		if (amount == 0.0)
			result = value1;
		else if (amount == 1.0)
			result = value2;
		else
			result = (2 * v1 - 2 * v2 + t2 + t1) * sCubed +
			(3 * v2 - 3 * v1 - 2 * t1 - t2) * sSquared +
			t1 * s +
			v1;
		return result;
	}

	float MathHelper::Lerp(float value1, float value2, float amount) {
		return value1 + (value2 - value1) * amount;
	}

	float MathHelper::LerpPrecise(float value1, float value2, float amount) {
		return ((1.0F - amount) * value1) + (value2 * amount);
	}

	float MathHelper::Max(float value1, float value2) {
		return value1 > value2 ? value1 : value2;
	}

	int32_t MathHelper::Max(int32_t value1, int32_t value2) {
		return value1 > value2 ? value1 : value2;
	}
	
	float MathHelper::Min(float value1, float value2) {
		return value1 < value2 ? value1 : value2;
	}

	int32_t MathHelper::Min(int32_t value1, int32_t value2) {
		return value1 < value2 ? value1 : value2;
	}

	float MathHelper::SmoothStep(float value1, float value2, float amount) {
		float result = Clamp(amount, 0.0, 1.0);
		result = Hermite(value1, 0.0, value2, 0.0, result);

		return result;
	}

	float MathHelper::ToDegrees(float radians) {
		return radians * static_cast<float>(57.295779513082320876798154814105);
	}

	float MathHelper::ToRadians(float degrees) {
		return degrees * static_cast<float>(0.017453292519943295769236907684886);
	}

	float MathHelper::WrapAngle(float angle) {
		if ((angle > -PI) && (angle <= PI))
			return angle;

		angle = fmod(angle, TWOPI);
		
		if (angle <= -PI)
			return angle + TWOPI;
		
		if (angle > PI)
			return angle - TWOPI;
		
		return angle;
	}

	bool MathHelper::IsPowerOfTwo(int32_t value) {
		return (value > 0) && ((value & (value - 1)) == 0);
	}

	float MathHelper::IsPositiveInfinity(float value) {
		return value == numeric_limits<float>::infinity();
	}
}