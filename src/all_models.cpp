#include "all_models.h"

#pragma region Init
AllModels* AllModels::_this = nullptr;

AllModels* AllModels::Init()
{
	if (_this == nullptr)
	{
		_this = new AllModels();
	}

	return _this;
}

AllModels::AllModels()
{
}
#pragma endregion


Model* AllModels::Load(const char* pathToModel)
{
    _this->_models.push_back(LoadModel(pathToModel));
    return &_this->_models[_this->_models.size() - 1];
}

Model* AllModels::Load(Mesh mesh)
{
    _model = LoadModelFromMesh(mesh);
    Texture2D mainTex = {};
    if (mainTexPath != "") {
        mainTex = LoadTexture(mainTexPath);
        _model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = mainTex;
    }
}