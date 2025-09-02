#pragma once
#include <raylib.h>

enum TextureIds {
	Checkerboard = 0,


	TOTAL
};

class AllTextures {

	Texture2D _textures[TextureIds::TOTAL];

public:
	static AllTextures* Init();
	static Texture2D* Get(TextureIds id);
	static void CleanUp();

private:
	static AllTextures* _this;

	AllTextures();                               // Hidden constructor.
	AllTextures(AllTextures& other) = delete;     // Singletons should not be cloneable.
	void operator=(const AllTextures&) = delete; // Singletons should not be assignable.

	void LoadTextures();
};