// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

/*
	Reference:
	https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
*/

#include "Prim.h"

/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param center Position of the center of the sphere
	 * @param radius Radius of the sphere
	 * @param color Color of the primitive
	 */
	CPrimSphere(Vec3f color, Vec3f center, float radius)
		: CPrim(color)
		, m_center(center)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		float t0, t1; // quadratic roots

		Vec3f diff = ray.org - m_center;
		float A = ray.dir.dot(ray.dir);
		float B = 2 * ray.dir.dot(diff);
		float C = diff.dot(diff) - m_radius*m_radius;

		float dis = B*B - 4*A*C;
		if(dis < 0)
			return false; // No intersection
		else if(dis == 0)
		{
			t0 = (-0.5) * B / A;
			t1 = (-0.5) * B / A;
		}else {	
			 t0 = (-0.5) * (B - sqrt(dis)) / A;
			 t1 = (-0.5) * (B + sqrt(dis)) / A;
		}
		// Make sure t0 is always the right value of t
		if(t0 > t1)
			std::swap(t0, t1);
		// Check the boundaries
		if( t0 < Epsilon || t0 > ray.t)
		{
			t0 = t1;
			if(t0 < Epsilon || t0 > ray.t) return false;
		}
		ray.t = t0;
		return true;
		
	}
		
private:
	Vec3f m_center;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};

