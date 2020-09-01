#pragma once

#include "ILight.h"

/**
 * @brief Point light source class
 */
class CLightPoint : public ILight
{
public:
	/**
	 * @brief Constructor
	 * @param position The position (origin) of the light source
	 * @param intensity The emission color and strength of the light source
	 */
	CLightPoint(Vec3f intensity, Vec3f position)
		: m_intensity(intensity)
		, m_position(position)
	{} 
	virtual ~CLightPoint(void) = default;

	virtual std::optional<Vec3f> Illuminate(Ray& ray) override
	{
		// Get new direction
		ray.t = (m_position-ray.org).dot(m_position-ray.org);
		ray.dir = normalize(m_position-ray.org);
		// Calculate and return normalized intensity
		return normalize(m_intensity/(4*Pif));
	}


private:
	Vec3f m_intensity; ///< emission (red, green, blue)
	Vec3f m_position;  ///< The light source origin
};
