#include "Collision.h"
#include <math.h>

void ConvertToNomalizeVector(Vec2& out, Vec2 in)//�P�ʃx�N�g����
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

float CalculationVectorLength(const Vec2& vec01)//�x�N�g���̒����𑪂�
{
	return sqrtf((vec01.X * vec01.X) + (vec01.Y * vec01.Y));

}

bool LineAndCircleCollision(Line line, Circle circle)
{
	//�@.�K�v�ȃx�N�g����p�ӂ���
	Vec2 startToCenter = Vec2(circle.posX - line.StartX, circle.posY - line.StartY);
	Vec2 endToCenter = Vec2(circle.posX - line.EndX, circle.posY - line.EndY);
	Vec2 startToEnd = Vec2(line.EndX - line.StartX, line.EndY - line.StartY);
	Vec2 normalStartToEnd;

	//�A.�����Ɖ~�̒��S�̍ŒZ�̒��������߂�
	ConvertToNomalizeVector(normalStartToEnd, startToEnd);// �P�ʃx�N�g����

	float distance_projection = startToCenter.X * normalStartToEnd.Y - normalStartToEnd.X * startToCenter.Y;

	//�B.�A�̒����Ɖ~�̒����̔�r������
	// �����Ɖ~�̍ŒZ�̒��������a����������
	if (fabs(distance_projection) < circle.radius)
	{
		// �������Ă�\������
		//�C�������ɉ~�����邩�𒲂ׂ�
		// �n�_ => �I�_�Ǝn�_ => �~�̒��S�̓��ς��v�Z����
		float dot01 = startToCenter.X * startToEnd.X + startToCenter.Y * startToEnd.Y;
		// �n�_ => �I�_�ƏI�_ => �~�̒��S�̓��ς��v�Z����
		float dot02 = endToCenter.X * startToEnd.X + endToCenter.Y * startToEnd.Y;
		// ��̓��ς̊|���Z���ʂ�0�ȉ��Ȃ瓖����
		if (dot01 * dot02 <= 0.0f)
		{
			//return true;
			return 1;
		}
		//�D.�����̖��[���~�͈͓̔����𒲂ׂ�
		else if (CalculationVectorLength(startToCenter) < circle.radius ||
			CalculationVectorLength(endToCenter) < circle.radius)
		{
			return true;
		}
	}
	else
	{
		// �������Ă�\���Ȃ�
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
		return 1;//��������
	}
	return 0;//�������Ă��Ȃ�
}