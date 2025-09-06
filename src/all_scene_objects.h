#pragma once
#include <raylib.h>
#include <vector>
#include <queue>
#include <stdexcept>

#include "handle.h"
#include "scene_object.h"

class AllSceneObjects 
{
	std::vector<SceneObject> _SOs;
	std::queue<int> _freeSlots;

public:

	static AllSceneObjects* Init();
	static Handle Load(const char* path);
	static Handle Load(Mesh mesh);
	static SceneObject* Get(Handle handle);
	static void Free(Handle handle);
	static void CleanUp();

	static void Draw();

private:
	static AllSceneObjects* _this;

	AllSceneObjects();                               // Hidden constructor.
	AllSceneObjects(AllSceneObjects& other) = delete;// Singletons should not be cloneable.
	void operator=(const AllSceneObjects&) = delete; // Singletons should not be assignable.

	int NewSceneObject();
};