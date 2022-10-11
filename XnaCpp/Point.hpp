#ifndef _POINT_HPP_
#define _POINT_HPP_

#include <stdint.h>

namespace Xna {
	struct Point {
		int32_t X{ 0 };
		int32_t Y{ 0 };

		static const Point Zero;

		Point();
		Point(int32_t x, int32_t y);

		Point operator-() const;
		friend Point operator+ (Point const& value1, Point const& value2);
		friend Point operator- (Point const& value1, Point const& value2);
		friend Point operator* (Point const& value1, Point const& value2);
		friend Point operator/ (Point const& value1, Point const& divisor);
		friend bool operator== (Point const& a, Point const& b);
		friend bool operator!= (Point const& a, Point const& b);

		static Point Add(Point const& value1, Point const& value2);
		static Point Subtract(Point const& value1, Point const& value2);
		static Point Multiply(Point const& value1, Point const& value2);
		static Point Divide(Point const& value1, Point const& divisor);

		bool Equals(Point const& other) const;
		void Deconstruct(int32_t& x, int32_t& y);
	};
}

#endif