#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>

#include "Scene.h"
#include "ShaderEyelight.h"
#include "ShaderPhong.h"
#include "PrimTriangle.h"

void CScene::ParseOBJ(const std::string& fileName)
{
	std::cout << "Parsing OBJFile : " << fileName << std::endl;

	std::shared_ptr<IShader> pShader = std::make_shared<CShaderEyelight>(RGB(1, 1, 1));
	// Vector and counter to keep track of vertices
	std::vector<Vec3f> vertices;
	vertices.push_back(0); // to make sure we start from index 1
	Vec3f tmpv;
	Vec3d tmpf;
	//Open the file
	std::ifstream file(fileName);
	if(!file.is_open())
	{
		std::cerr << "Error, file could not be opened!!\n";
		exit(EXIT_FAILURE);
	}
	std::string line; // will be used to read each line
	// Reading the OBJ file
	while(std::getline(file, line))
	{
		switch (line[0])
		{
			case 'v':
			{
				std::istringstream a(line.substr(2));
				// read the three values
				a >> tmpv[0] >> tmpv[1] >> tmpv[2];
				vertices.push_back(tmpv*100);
				break;
			}
			case 'f':
			{
				std::istringstream a(line.substr(2));
				// read the three values
				a >> tmpf[0] >> tmpf[1] >> tmpf[2];
				this->Add(std::make_shared<CPrimTriangle>(vertices[tmpf[0]], vertices[tmpf[1]], vertices[tmpf[2]], pShader));
				break;
			}
			default:
				// just skip line
				break;
		}
	}
	file.close();
	std::cout << "Finished Parsing" << std::endl;
}

