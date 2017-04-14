#pragma once

#include <bgfx\bgfx.h>
#include <vector>

struct VertexStructure {
	float x, y, z;
	float nx, ny, nz;
	float tx, ty, tz;
	float bx, by, bz;
	float u, v;

	static void init() {
		decl.begin()
			.add( bgfx::Attrib::Position, 3, bgfx::AttribType::Float )
			.add( bgfx::Attrib::Normal, 3, bgfx::AttribType::Float )
			.add( bgfx::Attrib::Tangent, 3, bgfx::AttribType::Float )
			.add( bgfx::Attrib::Bitangent, 3, bgfx::AttribType::Float )
			.add( bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float )
			.end();
	};

	static bgfx::VertexDecl decl;
};

class AssetLoader {
public:
	AssetLoader() {};

	void LoadAsset( const std::string &filename );

	std::vector<VertexStructure> AssetVertexData;
	std::vector<uint32_t> Indices;
};