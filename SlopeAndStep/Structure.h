#pragma once
// 線の構造体
struct Line
{
	float StartX;
	float StartY;
	float EndX;
	float EndY;
};

//点の構造体
struct Point
{
	float posX;
	float posY;
};
// 円の構造体
struct Circle
{
	float posX;
	float posY;
	float radius;
	int flag1;
	int flag2;
	int flag3;
};