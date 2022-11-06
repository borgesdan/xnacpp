#include "Point.hpp"
#include "Vector2.hpp"

namespace Xna {
	const Point Zero = Point();

	Point::Point() {}
	Point::Point(int32_t x, int32_t y) :
		X(x), Y(y) {}
	Point::Point(Vector2 vector2) :
		X(static_cast<int32_t>(vector2.X)),
		Y(static_cast<int32_t>(vector2.Y)){}	

	Point Point::operator-() const {
		return Point::Negate(*this);
	}

	Point operator+ (Point const& value1, Point const& value2) {
		return Point::Add(value1, value2);
	}

	Point operator- (Point const& value1, Point const& value2) {
		return Point::Subtract(value1, value2);
	}

	Point operator* (Point const& value1, Point const& value2) {
		return Point::Multiply(value1, value2);
	}

	Point operator/ (Point const& value1, Point const& divisor) {
		return Point::Divide(value1, divisor);
	}
	
	bool operator== (Point const& a, Point const& b) {
		return a.Equals(b);
	}

	bool operator!= (Point const& a, Point const& b) {
		return !a.Equals(b);
	}

	Point Point::Add(Point const& value1, Point const& value2) {
		return Point(
			value1.X + value2.X,
			value1.Y + value2.Y);
	}

	Point Point::Subtract(Point const& value1, Point const& value2) {
		return Point(
			value1.X - value2.X,
			value1.Y - value2.Y);
	}

	Point Point::Multiply(Point const& value1, Point const& value2) {
		return Point(
			value1.X * value2.X,
			value1.Y * value2.Y);
	}

	Point Point::Divide(Point const& value1, Point const& divisor) {
		return Point(
			value1.X * divisor.X,
			value1.Y * divisor.Y);
	}

	Point Point::Negate(Point const& value) {
		return Point(-value.X, -value.Y);
	}

	bool Point::Equals(Point const& other) const {
		return X == other.X && Y == other.Y;
	}

	void Point::Deconstruct(int32_t& x, int32_t& y) {
		x = X;
		y = Y;
	}
}