#include "Collision.h"
#include <math.h>

void ConvertToNomalizeVector(Vec2& out, Vec2 in)//単位ベクトル化
{
	float distance = sqrtf((in.X * in.X) + (in.Y * in.Y));
	if (distance > 0.0f)
	{
		out.X = in.X / distance;
		out.Y = in.Y / distance;
	}
	else
	{
		out = Vec2(0.0f, 0.0f);
	}
}

float CalculationVectorLength(const Vec2& vec01)//ベクトルの長さを測る
{
	return sqrtf((vec01.X * vec01.X) + (vec01.Y * vec01.Y));

}

bool LineAndCircleCollision(Line line, Circle circle)
{
	//①.必要なベクトルを用意する
	Vec2 startToCenter = Vec2(circle.posX - line.StartX, circle.posY - line.StartY);
	Vec2 endToCenter = Vec2(circle.posX - line.EndX, circle.posY - line.EndY);
	Vec2 startToEnd = Vec2(line.EndX - line.StartX, line.EndY - line.StartY);
	Vec2 normalStartToEnd;

	//②.線分と円の中心の最短の長さを求める
	ConvertToNomalizeVector(normalStartToEnd, startToEnd);// 単位ベクトル化

	float distance_projection = startToCenter.X * normalStartToEnd.Y - normalStartToEnd.X * startToCenter.Y;

	//③.②の長さと円の長さの比較をする
	// 線分と円の最短の長さが半径よりも小さい
	if (fabs(distance_projection) < circle.radius)
	{
		// 当たってる可能性あり
		//④線分内に円があるかを調べる
		// 始点 => 終点と始点 => 円の中心の内積を計算する
		float dot01 = startToCenter.X * startToEnd.X + startToCenter.Y * startToEnd.Y;
		// 始点 => 終点と終点 => 円の中心の内積を計算する
		float dot02 = endToCenter.X * startToEnd.X + endToCenter.Y * startToEnd.Y;
		// 二つの内積の掛け算結果が0以下なら当たり
		if (dot01 * dot02 <= 0.0f)
		{
			//return true;
			return 1;
		}
		//⑤.線分の末端が円の範囲内かを調べる
		else if (CalculationVectorLength(startToCenter) < circle.radius ||
			CalculationVectorLength(endToCenter) < circle.radius)
		{
			return true;
		}
	}
	else
	{
		// 当たってる可能性なし
		return 0;
	}
}


bool PointAndCircleCollision(Point point, Circle circle)
{
	float a = point.posX - circle.posX;
	float b = point.posY - circle.posY;
	float c = sqrt(a * a + b * b);

	if (c <= circle.radius)
	{
		return 1;//当たった
	}
	return 0;//当たっていない
}