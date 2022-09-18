#include <algorithm>
#include "Rectangle.hpp"
#include "Point.hpp"

using std::min;
using std::max;

namespace Xna {
	const Rectangle Rectangle::Empty = Rectangle();

	//----- Constructors -----
	Rectangle::Rectangle() {}
	
	Rectangle::Rectangle(int32_t x, int32_t y, int32_t width, int32_t height) :
		X(x), Y(y), Width(width), Height(height) {}
	
	Rectangle::Rectangle(Point location, Point size) :
		X(location.X), Y(location.Y), Width(size.X), Height(size.Y) {}

	//----- Operators -----

	bool operator==(Rectangle const& a, Rectangle const& b) {
		return a.Equals(b);
	}

	bool operator!=(Rectangle const& a, Rectangle const& b) {
		return !a.Equals(b);
	}

	//----- Static Functions -----

	Rectangle Rectangle::Intersect(Rectangle a, Rectangle b) {
		
		if (a.Intersects(b)) {
			int32_t right_side = min(a.X + a.Width, b.X + b.Width);
			int32_t left_side = max(a.X, b.X);
			int32_t top_side = max(a.Y, b.Y);
			int32_t bottom_side = min(a.Y + a.Height, b.Y + b.Height);
			
			return Rectangle(
				left_side, 
				top_side,
				right_side - left_side,
				bottom_side - top_side
			);
		}
		
		return Rectangle::Empty;
	}

	Rectangle Rectangle::Union(Rectangle a, Rectangle b) {
		int32_t x = min(a.X, b.X);
		int32_t y = min(a.Y, b.Y);
		return Rectangle(
			x, y,
			max(a.Right(), b.Right()) - x,
			max(a.Bottom(), b.Bottom()) - y);
	}

	//----- Functions -----

	int32_t Rectangle::Left() const {
		return X;
	}

	int32_t Rectangle::Right() const {
		return X + Width;
	}

	int32_t Rectangle::Top() const {
		return Y;
	}

	int32_t Rectangle::Bottom() const {
		return Y + Height;
	}

	bool Rectangle::IsEmpty() const {
		return Width == 0 
			&& Height == 0
			&& X == 0
			&& Y == 0;
	}

	Point Rectangle::Location() const {
		return Point(X, Y);
	}

	void Rectangle::Location(Point const& point) {
		X = point.X;
		Y = point.Y;
	}

	Point Rectangle::Size() const {
		return Point(Width, Height);
	}

	void Rectangle::Size(Point const& point) {
		Width = point.X;
		Height = point.Y;
	}

	Point Rectangle::Center() const {
		return Point(
			X + (Width / 2),
			Y + (Height / 2)
		);
	}
	
	bool Rectangle::Contains(int32_t x, int32_t y) const {
		return X <= x 
			&& x < (X + Width)
			&& Y <= y
			&& y < (Y + Height);
	}

	bool Rectangle::Contains(float x, float y) const {
		return Contains(static_cast<int32_t>(x), static_cast<int32_t>(y));
	}

	bool Rectangle::Contains(Point const& point) const {
		return Contains(point.X, point.Y);
	}

	bool Rectangle::Contains(Rectangle const& rectangle) const {
		return X <= rectangle.X 
			&& rectangle.X + rectangle.Width <= X +  Width
			&& Y <= rectangle.Y
			&& rectangle.Y + rectangle.Height <= Y +  Height;
	}

	bool Rectangle::Equals(Rectangle const& other) const {
		return X == other.X
			&& Y == other.Y
			&& Width == other.Width
			&& Height == other.Height;
	}

	void Rectangle::Inflate(int32_t horizontalAmount, int32_t verticalAmount) {
		X -= horizontalAmount;
		Y -= verticalAmount;
		Width += horizontalAmount * 2;
		Height += verticalAmount * 2;
	}

	void Rectangle::Inflate(float horizontalAmount, float verticalAmount) {
		Inflate(static_cast<int32_t>(horizontalAmount), static_cast<int32_t>(verticalAmount));
	}

	void Rectangle::Offset(int32_t x, int32_t y) {
		X += x;
		Y += y;
	}

	void Rectangle::Offset(float x, float y) {
		Offset(static_cast<int32_t>(x), static_cast<int32_t>(y));
	}

	void Rectangle::Offset(Point const& amount) {
		Offset(amount.X, amount.Y);
	}

	bool Rectangle::Intersects(Rectangle const& other) const {
		return other.Left() < Right()
			&& Left() < other.Right()
			&& other.Top() < Bottom()
			&& Top() < other.Bottom();
	}

	void Rectangle::Deconstruct(int32_t& x, int32_t& y, int32_t& width, int32_t& height) const {
		x = X;
		y = Y;
		width = Width;
		height = Height;
	}
}