#pragma once
#include "vector2.h"
#include "Boid.h"
#include "Point.h"

namespace pruebas
{
	bool checkVectorInit()
	{
		vector2 vecPrueba(0, 0);
		vector2 vec;
		if (vecPrueba == vec)
			return true;
		else
			return false;
	}
	bool checkModulo()
	{
		vector2 vecPrueba(-5, -1);
		float result = (vecPrueba.x*vecPrueba.x + vecPrueba.y * vecPrueba.y);
		result = std::sqrt(result);
		if (result >= 0)
			return true;
		else
			return false;
	}
	bool checkVectorSum()
	{
		vector2 vecPrueba(1, 1);
		vector2 vec(1, 1);
		vec.x = vec.x + vecPrueba.x;
		vec.y = vec.y + vecPrueba.y;
		if (vec == vector2(2, 2))
			return true;
		else
			return false;
	}
	bool checkVectorDot()
	{
		vector2 vecPrueba(2, 2);
		vector2 vec(1, 2);
		float result;
		result = vec.x * vecPrueba.x;
		result += vec.y * vecPrueba.y;
		if (result = 6)
			return true;
		else
			return false;
	}
	bool checkVectorCroos()
	{
		vector2 vecPrueba(2, 2);
		vector2 vec(2, 3);
		vec=vec.cross(vecPrueba);
		if (vec == vector2(6,-4))
			return true;
		else
			return false;
	}
	bool checkVectorNormalize()
	{
		vector2 vecPrueba(2, 2);
		vecPrueba=vecPrueba.normalize();
		float result= vecPrueba.magnitud();
		if (result = 1)
			return true;
		else
			return false;
	}
	bool ChecKBoidsFunctionSeek()
	{
		vector2 vecPrueba(10, 0);
		vector2 vec(1, 0);
		vector2 result = Boid::seek(vec, vecPrueba, 10);
		if (result == vector2(90, 0))
			return true;
		else
			return false;
	}
	bool ChecKBoidsFunctionFlee()
	{
		vector2 vecPrueba(1, 0);
		vector2 vec(0, 0);

		vector2 result = Boid::flee(vec, vecPrueba, 10, 10);
		if (result == vector2(10, 0))
			return true;
		else
			return false;
	}
};
