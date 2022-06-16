#pragma once
#include "Structure.h"
#include "Vector2.h"

void ConvertToNomalizeVector(Vec2& out, Vec2 in);
bool LineAndCircleCollision(Line line, Circle circle);
bool PointAndCircleCollision(Point point, Circle circle);
