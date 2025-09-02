#include "all_textures.h"

#pragma region Init
AllTextures* AllTextures::_this = nullptr;

AllTextures* AllTextures::Init()
{
	if (_this == nullptr)
	{
		_this = new AllTextures();
	}

	return _this;
}

AllTextures::AllTextures() 
{
	LoadTextures();
}
#pragma endregion

Texture2D* AllTextures::Get(TextureIds id)
{
	if (id < 0 || id >= TextureIds::TOTAL) {
		// TODO: log error
		return nullptr;
	}
	return &(_this->_textures[id]);
}

void AllTextures::CleanUp()
{
    for (int i = 0; i < TextureIds::TOTAL; ++i)
    {
		UnloadTexture(_this->_textures[i]);
    }
}


void AllTextures::LoadTextures()
{
	_textures[TextureIds::Checkerboard] = LoadTexture("res/textures/checkerboard.jpg");
}