#include "Mesh.h"

#include <fstream>
#include <sstream>
#include <filesystem>

#include "Math/int3.h"
#include "HitData.h"

///////////static functions for loading obj files
static int3 loadVertex(std::string &index)
{
	std::istringstream stream;
	stream.str(index);
	

	int3 indexes(0, 0, 0);
	
	
	stream>>indexes.a;

	if(stream.peek() != '/')//no more indexes to read
		return indexes;
	else
		stream.get();//remove one character ('/')
	
	if(stream.peek() != '/')//if there is uv data
	{
		stream>>indexes.b;
		if(stream.peek() != '/')//no normal index
			return indexes;
	}
	
	stream.get();//remove '/'
	stream>>indexes.c;
	return indexes;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

static std::vector<int3> loadFace(std::string &face)
{
	std::istringstream stream;
	stream.str(face);

	std::vector<int3> indexes;
	unsigned int vertexCount = 1;
	
	while(!stream.eof())
	{
		std::string vertex;
		stream>>vertex;
		
		int3 index = loadVertex(vertex);
	
		if(vertexCount > 3)//triangulate if necessary
		{
			indexes.push_back(indexes[0]);
			indexes.push_back(indexes[vertexCount-2]);
		}

		indexes.push_back(index);
		vertexCount++;
	}

	return indexes;
}

////////////////////////////////////////////////////////////////////////////////////////////////////

void Mesh::loadObjFile(std::string filename, float4x4 &transform)
{
	std::ifstream file;
	file.open(filename);
	if (!file)
		return;
//temporary vectors
	std::vector<float3> vertexPosition;
	std::vector<float3> uvPosition;// where float2?
	std::vector<float3> normals;
	
	std::vector<int3> face;//face format: x=pos, y=uv, z=normal
	std::vector<Material*> faceMaterials;
	
	std::string filePath = std::filesystem::path(filename).parent_path().string();
	std::string mtlFilename("");
	Material *currentMaterial {nullptr};
	
	std::istringstream lineStream;
	std::string str;
	
	while(!file.eof())
	{
		std::getline(file, str);
		lineStream.clear();
		lineStream.str(str);
		lineStream.seekg(0);
		
		str = "";
		lineStream>>str;
		
		if(str[0] == '#')//comment
			continue;
		else if(str == "mtllib")
		{
			lineStream>>mtlFilename;
			materials[""] = new Material(filePath + "/" + mtlFilename);
			this->mat = materials[""];
		}
		else if(str == "usemtl" and mtlFilename != "")
		{
			std::string mtlName;
			lineStream>>mtlName;
			
			auto it = materials.find(mtlName);
			if(it == materials.end())
			{
				materials[mtlName] = new Material(filePath + "/" + mtlFilename, mtlName);
				currentMaterial = materials[mtlName];
			}
			else
			{
				currentMaterial = materials[mtlName];
			}
		}
		else if(str == "v")//vertex position
		{
			float3 pos;
			lineStream>>pos.x>>pos.y>>pos.z;
			vertexPosition.push_back(pos);
		}
		else if(str == "vt")
		{
			float3 uv;
			lineStream>>uv.x>>uv.y;
			uvPosition.push_back(uv);
		}
		else if(str == "vn")
		{
			float3 normal;
			lineStream>>normal.x>>normal.y>>normal.z;
			normals.push_back(normal.Normalize());
		}
		else if(str == "f")//TODO: expect negative values
		{
			std::string line;
			std::getline(lineStream, line);
			std::vector<int3> indexes = loadFace(line);
			for(auto x: indexes)
				face.push_back(x);
			faceMaterials.push_back(currentMaterial);
		}
	}
	file.close();
	
	triangles.reserve(face.size() / 3);
	for(unsigned int i = 0; i < face.size(); i += 3)
	{
		float4 v1 = float4(vertexPosition[face[i].a-1], 1.);
		float4 v2 = float4(vertexPosition[face[i+1].a-1], 1.);
		float4 v3 = float4(vertexPosition[face[i+2].a-1], 1.);
		v1 = transform * v1;
		v2 = transform * v2;
		v3 = transform * v3;
		
		float3 tv1 = float3(v1.x, v1.y, v1.z);
		float3 tv2 = float3(v2.x, v2.y, v2.z);
		float3 tv3 = float3(v3.x, v3.y, v3.z);
		
		Triangle triangle(tv1, tv2, tv3,
						  uvPosition[face[i].b-1],
						  uvPosition[face[i+1].b-1],
						  uvPosition[face[i+2].b-1]);
		triangles.push_back(triangle);
		triangles.back().setMaterial(faceMaterials[i/3]);
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////


Mesh::Mesh(std::string filename, float4x4 const &transform)
{
	float4x4 localTransform = transform;
	loadObjFile(filename, localTransform);
	if(triangles.size() > 24)
		calculateBoundingBox();
}
////////////////////////////////////////////////////////////////////////////////////////////////////

Mesh::~Mesh()
{
	for(auto element: materials)
	{
		delete element.second;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////

HitData Mesh::intersects(Ray& ray, float maxT, float minT)
{
	HitData closestHit{HitData::Miss};
	HitData currentHit;
	
	if(boundingBox.size() > 0)
	{
		bool inBox {false};
		for(auto &x: boundingBox)
		{
			currentHit = x.intersects(ray, maxT, minT);
			if(currentHit.result != HitData::Miss)
			{
				inBox = true;
				break;
			}
		}
		if(!inBox)
			return closestHit;
	}
	
	for(auto &x: triangles)
	{
		currentHit = x.intersects(ray, maxT, minT);
		if(currentHit.result != HitData::Miss)
		{
			closestHit = currentHit;
			maxT = currentHit.distance;
		}
	}
	
	return closestHit;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void Mesh::setMaterial(Material *_mat)
{
	for(auto &x: triangles)
		reinterpret_cast<Primitive*>(&x)->setMaterial(_mat);
}
////////////////////////////////////////////////////////////////////////////////////////////////////

void Mesh::calculateBoundingBox()
{
	float minX {999}, minY {999}, minZ {999};
	float maxX {-999}, maxY {-999}, maxZ {-999};
	
	for(auto &t: triangles)
	{
		for(int i = 0; i < 3; i++)
		{
			float3 point = t.getPoint(i);
			if(point.x < minX) minX = point.x;
			if(point.x > maxX) maxX = point.x;
			if(point.y < minY) minY = point.y;
			if(point.y > maxY) maxY = point.y;
			if(point.z < minZ) minZ = point.z;
			if(point.z > maxZ) maxZ = point.z;
		}
	}
	
	float3 v1(minX, maxY, maxZ);
	float3 v2(maxX, maxY, maxZ);
	float3 v3(minX, minY, maxZ);
	float3 v4(maxX, minY, maxZ);
	float3 v5(minX, maxY, minZ);
	float3 v6(maxX, maxY, minZ);
	float3 v7(minX, minY, minZ);
	float3 v8(maxX, minY, minZ);
	
	boundingBox.emplace_back(v1, v2, v4);//front
	boundingBox.emplace_back(v1, v4, v3);
	boundingBox.emplace_back(v2, v6, v8);//right
	boundingBox.emplace_back(v2, v8, v4);
	boundingBox.emplace_back(v5, v6, v2);//top
	boundingBox.emplace_back(v5, v2, v1);
	boundingBox.emplace_back(v5, v1, v3);//left
	boundingBox.emplace_back(v5, v3, v7);
	boundingBox.emplace_back(v6, v5, v7);//back
	boundingBox.emplace_back(v6, v7, v8);
	boundingBox.emplace_back(v3, v4, v8);//bottom
	boundingBox.emplace_back(v3, v8, v7);
}
