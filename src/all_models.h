#pragma once
#include <raylib.h>
#include <vector>

class AllModels {

	std::vector<Model> _models;

public:
	static AllModels* Init();
	static Model* Load(const char* path);
	static Model* Load(Mesh mesh);

	static void Draw();

private:
	static AllModels* _this;

	AllModels();                               // Hidden constructor.
	AllModels(AllModels& other) = delete;     // Singletons should not be cloneable.
	void operator=(const AllModels&) = delete; // Singletons should not be assignable.

};