// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h" #include <math.h>
// Helpful cotang function
double cotan(double i) { return(1 / tan(i)); }

/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{
public:
	/**
	 * @brief Constructor
	 * @param pos Camera origin (center of projection)
	 * @param dir Camera viewing direction
	 * @param up Up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
	 * @param resolution The image resolution
	 */
	CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)
		: ICamera(resolution)
		, m_pos(pos)
		, m_up(up)
	{	
		// Make sure direction is normalized
		m_dir = normalize(dir);	

		//we first calculate the aspect and then focus using trigonometry
		m_aspect =  (1.0) * resolution.width / resolution.height;
		m_focus = cotan(angle * M_PI / 360);

		/*
		  Initialize the x and y axis that we used in the first theoritical assignment
		  As we saw in the slides, yAxis was the opposite vector of up, so we only need to
		  negate up to get it. To get xAxis we only need to take the cross product of the 
		  camera direction, which is perpendicular to the screen, with the yAxis that we 
		  first found.
		*/
		m_yAxis = (-1) * m_up;
		m_xAxis = m_dir.cross(m_up);				
	}
	virtual ~CCameraPerspective(void) = default;

	virtual bool InitRay(float x, float y, Ray& ray) override
	{
		/*
		 We first normalize x and y 
		*/
		float ndcx = (x + 0.5) / getResolution().width;  
		float ndcy = (y + 0.5) / getResolution().height;
		
		/*
     * We go from normal to screen coordinates
     * We multiply by aspect to take care of the case 
     * in which the screen is not a square
		*/
		float sscx = (2 * ndcx - 1) * m_aspect;  
		float sscy = (2 * ndcy - 1);

    /*
     * Calculate ray direction
		*/
		Vec3f f = m_dir * m_focus;
		ray.org = m_pos;
		ray.dir =  f + sscx * m_xAxis + sscy * m_yAxis;
		
		/*
     * Initialize t to a relatiely large value
		*/
		ray.t   = 340282e+38;

		return true;
	}


private:
	// input values
	Vec3f m_pos;
	Vec3f m_dir;
	Vec3f m_up;

	// preprocessed values
	float m_focus;
	Vec3f m_xAxis;
	Vec3f m_yAxis;
	Vec3f m_zAxis;
	float m_aspect;
};
