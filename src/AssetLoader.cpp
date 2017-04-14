#include "AssetLoader.h"
#include <iostream>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

bgfx::VertexDecl VertexStructure::decl;

struct vec3 {
	float x, y, z;

	vec3(float x=0, float y=0, float z=0): x(x), y(y), z(z) {}

	vec3 operator- ( vec3 v ) {
		return vec3(x-v.x, y-v.y, z-v.z);
	}

	vec3 operator* ( float a ) {
		return vec3( x*a, y*a, z*a );
	}
};

void AssetLoader::LoadAsset( const std::string &filename ) {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;

	bool ret = tinyobj::LoadObj( &attrib, &shapes, &materials, &err, filename.c_str() );

	if ( !err.empty() ) {
		std::cerr << err << std::endl;
	}

	assert( ret );

	// Process the data
	for ( auto shape : shapes ) {
		size_t index_offset = 0;

		AssetVertexData.reserve( shape.mesh.num_face_vertices.size() );
		for ( size_t f = 0; f < shape.mesh.num_face_vertices.size(); f++ ) {

			int fv = shape.mesh.num_face_vertices[f];
			// Loop over vertices in the face.
			for ( size_t v = 0; v < fv; v++ ) {
				// access to vertex
				tinyobj::index_t idx = shape.mesh.indices[index_offset + v];
				Indices.push_back( (f*3)+v);

				float vx{ 0 }, vy{ 0 }, vz{ 0 };
				float nx{ 0 }, ny{ 0 }, nz{ 0 };
				float tx{ 0 }, ty{ 0 };

				vx = attrib.vertices[3 * idx.vertex_index + 0];
				vy = attrib.vertices[3 * idx.vertex_index + 1];
				vz = attrib.vertices[3 * idx.vertex_index + 2];

				if ( attrib.normals.size() > 0 ) {
					nx = attrib.normals[3 * idx.normal_index + 0];
					ny = attrib.normals[3 * idx.normal_index + 1];
					nz = attrib.normals[3 * idx.normal_index + 2];
				}

				if ( attrib.texcoords.size() > 0 ) {
					tx = attrib.texcoords[2 * idx.texcoord_index + 0];
					ty = attrib.texcoords[2 * idx.texcoord_index + 1];
				}

				AssetVertexData.push_back(VertexStructure{ vx, vy, vz, nx, ny, nz, 0.0, 0.0, 0.0, 0.0,0.0,0.0, tx, ty });
			}
			index_offset += fv;
		}

		// Generate Tangents and bitangents
		for ( size_t i = 0; i < Indices.size() / 3; i += 3 ) {
			// Get face vertices
			vec3 v0( AssetVertexData[Indices[i*3 + 0]].x, AssetVertexData[Indices[i*3 + 0]].y, AssetVertexData[Indices[i*3 + 0]].z );
			vec3 v1( AssetVertexData[Indices[i*3 + 1]].x, AssetVertexData[Indices[i*3 + 1]].y, AssetVertexData[Indices[i*3 + 1]].z );
			vec3 v2( AssetVertexData[Indices[i*3 + 2]].x, AssetVertexData[Indices[i*3 + 2]].y, AssetVertexData[Indices[i*3 + 2]].z );

			// Get face normals
			vec3 n0( AssetVertexData[Indices[i*3 + 0]].nx, AssetVertexData[Indices[i*3 + 0]].ny, AssetVertexData[Indices[i*3 + 0]].nz );
			vec3 n1( AssetVertexData[Indices[i*3 + 1]].nx, AssetVertexData[Indices[i*3 + 1]].ny, AssetVertexData[Indices[i*3 + 1]].nz );
			vec3 n2( AssetVertexData[Indices[i*3 + 2]].nx, AssetVertexData[Indices[i*3 + 2]].ny, AssetVertexData[Indices[i*3 + 2]].nz );

			// Get face uvs
			vec3 uv0( AssetVertexData[Indices[i*3 + 0]].u, AssetVertexData[Indices[i*3 + 0]].v, 0 );
			vec3 uv1( AssetVertexData[Indices[i*3 + 1]].u, AssetVertexData[Indices[i*3 + 1]].v, 0 );
			vec3 uv2( AssetVertexData[Indices[i*3 + 2]].u, AssetVertexData[Indices[i*3 + 2]].v, 0 );

			vec3 dpos1 = v1 - v0;
			vec3 dpos2 = v2 - v0;

			vec3 duv1 = uv1 - uv0;
			vec3 duv2 = uv2 - uv0;

			float r = 1.0f / (duv1.x * duv2.y - duv1.y*duv2.x);
			vec3 tangent = (dpos1 * duv2.y - dpos2*duv1.y)*r;
			vec3 bitangent = (dpos2 * duv1.x - dpos1 * duv2.x)*r;

			AssetVertexData[Indices[i*3 + 0]].tx = tangent.x;
			AssetVertexData[Indices[i*3 + 1]].tx = tangent.x;
			AssetVertexData[Indices[i*3 + 2]].tx = tangent.x;

			AssetVertexData[Indices[i*3 + 0]].bx = bitangent.x;
			AssetVertexData[Indices[i*3 + 1]].bx = bitangent.x;
			AssetVertexData[Indices[i*3 + 2]].bx = bitangent.x;

			AssetVertexData[Indices[i*3 + 0]].ty = tangent.y;
			AssetVertexData[Indices[i*3 + 1]].ty = tangent.y;
			AssetVertexData[Indices[i*3 + 2]].ty = tangent.y;

			AssetVertexData[Indices[i*3 + 0]].by = bitangent.y;
			AssetVertexData[Indices[i*3 + 1]].by = bitangent.y;
			AssetVertexData[Indices[i*3 + 2]].by = bitangent.y;
			
			AssetVertexData[Indices[i*3 + 0]].tz = tangent.z;
			AssetVertexData[Indices[i*3 + 1]].tz = tangent.z;
			AssetVertexData[Indices[i*3 + 2]].tz = tangent.z;

			AssetVertexData[Indices[i*3 + 0]].bz = bitangent.z;
			AssetVertexData[Indices[i*3 + 1]].bz = bitangent.z;
			AssetVertexData[Indices[i*3 + 2]].bz = bitangent.z;
		}
	}

}
