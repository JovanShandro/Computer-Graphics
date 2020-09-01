#pragma once

#include "ShaderFlat.h"

class CScene;

class CShaderPhong : public CShaderFlat
{
public:
	/**
	 * @brief Constructor
	 * @param scene Reference to the scene
	 * @param color The color of the object
	 * @param ka The ambient coefficient
	 * @param kd The diffuse reflection coefficients
	 * @param ks The specular refelection coefficients
	 * @param ke The shininess exponent
	 */
	CShaderPhong(CScene& scene, Vec3f color, float ka, float kd, float ks, float ke)
		: CShaderFlat(color)
		, m_scene(scene)
		, m_ka(ka)
		, m_kd(kd)
		, m_ks(ks)
		, m_ke(ke)
	{}
	virtual ~CShaderPhong(void) = default;

	virtual Vec3f Shade(const Ray& ray) const override
	{
		std::optional<Vec3f> Li;
		// Calculate terms of last sum
		Vec3f a = m_ka * m_color * 1.0, b = 0, c = 0;
		// Initialize light ray
		Ray lr; lr.org = ray.org + ray.t*ray.dir;
		// Calculate second term
		Vec3f I, N, R;
		N = ray.hit->GetNormal(ray);
		for(auto& light_source : m_scene.m_vpLights)
		{
			Li = light_source->Illuminate(lr);
			// When not using area light remove this loop
			for(int i = 0; i<1000; i++)
			{
				if(!m_scene.Occluded(lr)) // Take care of shadows
				{
					I = lr.dir;
					R = 2*(I.dot(N)) * N - I;
					b += (*Li) * ((I.dot(N)) ? (I.dot(N)) : (0.0));
				}			
			}
		}
		//Calculate term3
		for(auto& light_source : m_scene.m_vpLights)
		{
			Li = light_source->Illuminate(lr);
			// When not using area light remove this loop
			for(int i = 0; i<1000; i++)
			{
				if(!m_scene.Occluded(lr)) // Take care of shadows
				{
					I = lr.dir;
					R = 2*(I.dot(N)) * N - I;
					float tmp = ((R.dot(-ray.dir)) ? (R.dot(-ray.dir)) : (0.0));
					c += (*Li) * pow(tmp, m_ke);
				}
			}
		}
		/* Using mul function for element-wise multiplication.
		   When not using area lights delete the 1000s */
		b = m_kd * m_color.mul(b/1000);
		c = m_ks * RGB(1, 1, 1).mul(c/1000);
		// Finally return sum as Lr 
		return a+b+c;
	}

	
private:
	CScene& m_scene;
	float 	m_ka;    ///< ambient coefficient
	float 	m_kd;    ///< diffuse reflection coefficients
	float 	m_ks;    ///< specular refelection coefficients
	float 	m_ke;    ///< shininess exponent
};
