#ifndef _RECTANGLE_HPP_
#define _RECTANGLE_HPP_

#include <stdint.h>

namespace Xna {

	struct Point;

	struct Rectangle {

		int32_t X{ 0 };
		int32_t Y{ 0 };
		int32_t Width{ 0 };
		int32_t Height{ 0 };
		
		static const Rectangle Empty;

		Rectangle();
		Rectangle(int32_t x, int32_t y, int32_t width, int32_t height);
		Rectangle(Point location, Point size);

		friend bool operator==(Rectangle const& a, Rectangle const& b);
		friend bool operator!=(Rectangle const& a, Rectangle const& b);

		static Rectangle Intersect(Rectangle a, Rectangle b);
		static Rectangle Union(Rectangle a, Rectangle b);

		int32_t Left() const;
		int32_t Right() const;
		int32_t Top() const;
		int32_t Bottom() const;
		bool IsEmpty() const;
		Point Location() const;
		void Location(Point const& point);
		Point Size() const;
		void Size(Point const& point);
		Point Center() const;
		bool Contains(int32_t x, int32_t y) const;
		bool Contains(float x, float y) const;
		bool Contains(Point const& point) const;
		bool Contains(Rectangle const& rectangle) const;
		void Inflate(int32_t horizontalAmount, int32_t verticalAmount);
		void Inflate(float horizontalAmount, float verticalAmount);
		bool Intersects(Rectangle const& other) const;
		void Offset(int32_t x, int32_t y);
		void Offset(float x, float y);
		void Offset(Point const& amount);
		// TODO: criar método bool Contains(Vector2 const& vector2) const;
		bool Equals(Rectangle const& other) const;
		void Deconstruct(int32_t& x, int32_t& y, int32_t& width, int32_t& height) const;
	};
}

#endif