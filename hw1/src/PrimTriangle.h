// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition

#pragma once

#include "Prim.h"

/**
 * @brief Triangle Geaometrical Primitive class
 */
class CPrimTriangle : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 * @param color Color of the primitive
	 */
	CPrimTriangle(Vec3f color, Vec3f a, Vec3f b, Vec3f c)
		: CPrim(color)
		, m_a(a)
		, m_b(b)
		, m_c(c)
  	{}
	virtual ~CPrimTriangle(void) = default;
	
	virtual bool Intersect(Ray& ray) override
	{
		// Calculate normal of the triangle plane
		Vec3f normal = (m_b-m_a).cross(m_c-m_a);
		// Check if the ray is parallel to the plane
		if(normal.dot(ray.dir) == 0)
			return false;
		/*
		 Calculating the areas of OAB, OBC and OCA
		 as in the slides
		*/
		Vec3f nab = (m_b-ray.org).cross(m_a-ray.org);
		Vec3f nbc = (m_c-ray.org).cross(m_b-ray.org);
		Vec3f nca = (m_a-ray.org).cross(m_c-ray.org);

		// Calculating lambda stars
		float lambda_star1  = nab.dot(ray.dir);
		float lambda_star2  = nbc.dot(ray.dir);
		float lambda_star3  = nca.dot(ray.dir);
		float lambda_star_sum = (nca + nab + nbc).dot(ray.dir);
		// Calculating Lambdas
		float lambda1  = nab.dot(ray.dir) /lambda_star_sum;
		float lambda2  = nbc.dot(ray.dir) /lambda_star_sum;
		float lambda3  = nca.dot(ray.dir) /lambda_star_sum;
		// Check if Lambdas are positive
		if(lambda1 < 0)
			return false;
		if(lambda2 < 0)
			return false;
		if(lambda3 < 0)
			return false;

		// Calc new value of t as see if there is an intersection
		float new_t = ((-1) * normal.dot(ray.org - m_a)) / normal.dot(ray.dir);
		if(new_t < Epsilon || new_t > ray.t)
			return false;

		ray.t = new_t;
		return true;
	}

	
private:
	Vec3f m_a;	///< Position of the first vertex
	Vec3f m_b;	///< Position of the second vertex
	Vec3f m_c;	///< Position of the third vertex
};
