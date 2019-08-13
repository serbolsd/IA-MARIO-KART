#include "stdafx.h"
#include "CppUnitTest.h"

#include <vector2.h>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(vectorTest)
	{
	public:
		
		TEST_METHOD(checkVectorInit)
		{
			vector2* vecPrueba=new vector2(0,0);
			vector2* vec=new vector2();
			Assert::AreEqual(vecPrueba->x, vec->x);
			Assert::AreEqual(vecPrueba->y, vec->y);
		}
		TEST_METHOD(checkModulo)
		{
			vector2* vecPrueba = new vector2(-5,-1);
			float result=(vecPrueba->x*vecPrueba->x + vecPrueba->y * vecPrueba->y);
			result = std::sqrt(result);
			Assert::IsTrue(result>=0);
		}
		TEST_METHOD(checkVectorSum)
		{
			vector2* vecPrueba = new vector2(1, 1);
			vector2* vec = new vector2(1,1);
			vec->x = vec->x + vecPrueba->x;
			vec->y = vec->y + vecPrueba->y;
			Assert::AreEqual(vec->x, 2.0f);
			Assert::AreEqual(vec->y, 2.0f);
		}
		TEST_METHOD(checkVectorDot)
		{
			vector2* vecPrueba = new vector2(2, 2);
			vector2* vec = new vector2(1, 2);
			float result;
			result = vec->x * vecPrueba->x;
			result += vec->y * vecPrueba->y;
			Assert::AreEqual(result, 6.0f);
		}
	};
	TEST_CLASS(boidsTest)
	{
	public:
		TEST_METHOD(checkVectorInit)
		{
			//Point* pointPrueba = new Point;
			//pointPrueba->init(vector2(0,0));
			//vector2* vec = new vector2(1, 2);
			//vector2* result=new vector2(Boid::seek(*vecPrueba, *vec,10));
		}
	};
}