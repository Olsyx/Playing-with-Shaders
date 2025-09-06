#include "all_scene_objects.h"

#pragma region Init
AllSceneObjects* AllSceneObjects::_this = nullptr;

AllSceneObjects* AllSceneObjects::Init()
{
	if (_this == nullptr)
	{
		_this = new AllSceneObjects();
	}

	return _this;
}

AllSceneObjects::AllSceneObjects()
{
}
#pragma endregion


Handle AllSceneObjects::Load(const char* pathToModel)
{
	int index = _this->NewSceneObject();
	SceneObject* so = &_this->_SOs[index];
	so->Load(pathToModel);
	
    return Handle{ index, so->GetGen() };
}

Handle AllSceneObjects::Load(Mesh mesh)
{
	int index = _this->NewSceneObject();
	SceneObject* so = &_this->_SOs[index];
	so->Load(mesh);

	return Handle{ index, so->GetGen() };
}

int AllSceneObjects::NewSceneObject() 
{
	if (_freeSlots.empty()) 
	{
		_this->_SOs.emplace_back();
		return _this->_SOs.size() - 1;
	}

	int index = _freeSlots.front();
	_freeSlots.pop();
	return index;
}

SceneObject* AllSceneObjects::Get(Handle handle)
{
	if (handle.index < 0 || handle.index >= _this->_SOs.size())
	{
		throw std::runtime_error("Trying to access forbidden memory space: " + handle.index);
	}

	if (handle.gen < 0)
	{
		throw std::runtime_error("Trying to access invalid generation SceneObject");
	}

	SceneObject* so = &_this->_SOs[handle.index];
	if (handle.gen != so->GetGen())
	{
		throw std::runtime_error("Trying to access outdated SceneObject");
	}

	return so;
}

void AllSceneObjects::Free(Handle handle) 
{
	if (handle.index < 0 || handle.index >= _this->_SOs.size())
	{
		throw std::runtime_error("Trying to free forbidden memory space: " + handle.index);
	}

	if (handle.gen < 0)
	{
		throw std::runtime_error("Trying to free invalid generation SceneObject");
	}

	SceneObject* so = &_this->_SOs[handle.index];
	if (handle.gen != so->GetGen())
	{
		throw std::runtime_error("Trying to free outdated SceneObject");
	}

	so->CleanUp();
	_this->_freeSlots.push(handle.index);
}

void AllSceneObjects::CleanUp()
{
	for (SceneObject& so : _this->_SOs) {
		so.CleanUp();
	}
}

void AllSceneObjects::Draw()
{
	for (SceneObject& so : _this->_SOs) {
		so.Draw();	// Is this efficient or should I bring the draw function completely here?
	}
}