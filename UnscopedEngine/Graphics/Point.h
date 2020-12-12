#pragma once

namespace ue
{
	template<typename T>
	class Point2D
	{
	public:
		Point2D() :_x(0), _y(0) {}
		Point2D(T x, T y) :_x(x), _y(y) {}
		Point2D(const Point2D& other) :_x(other._x), _y(other._y) {}

		inline T GetX()const { return _x; }
		inline void SetX(T x) { _x = x; }
		inline T GetY()const { return _y; }
		inline void SetY(T y) { _y = y; }
	private:
		T _x;
		T _y;
	};

}