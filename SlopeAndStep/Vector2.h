#pragma once
struct Vec2
{
	Vec2()
	{
		X = 0.0f;
		Y = 0.0f;
	}

	Vec2(float x, float y)
	{
		X = x;
		Y = y;
	}

	Vec2(const Vec2& size)
	{
		this->X = size.X;
		this->Y = size.Y;
	}

	float X;	//!< X’l
	float Y;	//!< Y’l
};