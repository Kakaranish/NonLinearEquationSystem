#pragma once
#include "Libs.h"
#include <type_traits>
#include <ostream>

template <typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
class Vec2 {
public:
	T x, y;
	inline Vec2() { this->x = this->y = 0;}
	inline Vec2(T x, T y) : x(std::move(x)), y(std::move(y)) {}
	
	//Overloadings 
	inline Vec2<T>& operator=(const Vec2<T>& vec) {
		if (this != &vec) {
			this->x = vec.x;
			this->y = vec.y;
		}
		return *this;
	}
	bool operator!=(const Vec2<T>& q) const{
		if(this->x != q.x || this->y != q.y)
			return true;
		return false;
	}

	inline Vec2<T> operator+(const Vec2<T>& q) {
		return std::move(Vec2<T>(this->x + q.x, this->y + q.y));
	}
	inline Vec2<T> operator-(const Vec2<T>& q) {
		return std::move(Vec2<T>(this->x + q.x, this->y + q.y));
	}
	inline friend std::ostream& operator<<(std::ostream& output, const Vec2<T>& vec) {
		return output << vec.x << ", " << vec.y;
	}
	inline Vec2<T>& operator+=(const Vec2<T>& vec) {
		this->x += vec.x;
		this->y += vec.y;
		return *this;
	}
	inline Vec2<T>& operator-=(const Vec2<T>& vec) {
		this->x -= vec.x;
		this->y -= vec.y;
		return *this;
	}
};