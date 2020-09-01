// Plane Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief The Plane Geaometrical Primitive class
 */
class CPrimPlane : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param origin Point on the plane
	 * @param normal Normal to the plane
	 * @param color Color of the primitive
	 */
	CPrimPlane(Vec3f color, Vec3f origin, Vec3f normal)
		: CPrim(color)
		, m_normal(normal)
		, m_origin(origin)
	{
		normalize(m_normal);
	}
	virtual ~CPrimPlane(void) = default;

	virtual bool Intersect(Ray& ray) override
	{
		float x;
		//check if ray is parallel to plane
		if(m_normal.dot(ray.dir) == 0)
			return false;
		else //assign the value before checking the size conditions
			x = (m_origin.dot(m_normal)-ray.org.dot(m_normal))/ray.dir.dot(m_normal);
		
		// check if x satisfies the conditions
		if(x<Epsilon || x>ray.t)
		 	return false;
		
		ray.t = x;
		return true;
	}
	
	
private:
	Vec3f m_normal;	///< Normal on the plane
	Vec3f m_origin;	///< Point to the plane
};
