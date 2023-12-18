#include "Modules/SceneModule.h"

#include "ModuleManager.h"

SceneModule::SceneModule(): Module()
{
	Scene* main_scene = new Scene("MainScene");
	scenes.push_back(main_scene);
	mainScene = main_scene;
}

void SceneModule::Start()
{
	Module::Start();

	timeModule = moduleManager->GetModule<TimeModule>();
	windowModule = moduleManager->GetModule<WindowModule>();
}

void SceneModule::Render()
{
	Module::Render();

	for (const Scene* scene : scenes)
	{
		scene->Render(windowModule->GetWindow());
	}
}

void SceneModule::Update()
{
	Module::Update();

	for (const Scene* scene : scenes)
	{
		scene->Update(timeModule->GetDeltaTime());
	}
}

Scene* SceneModule::GetScene(const std::string& _scene_name) const
{
	for (Scene* scene : scenes)
	{
		if (scene->GetName() == _scene_name)
		{
			return scene;
		}
	}
	return nullptr;
}

bool SceneModule::SetMainScene(const std::string& _scene_name) {
	Scene* new_main_scene = GetScene(_scene_name);
	if (new_main_scene != nullptr) {
		mainScene = new_main_scene;
		return true;
	}
	return false;
}

bool SceneModule::RemoveScene(const std::string& _scene_name)
{
	for (auto it = scenes.begin(); it != scenes.end(); ++it)
	{
		if ((*it)->GetName() == _scene_name)
		{
			scenes.erase(it);
			//delete* it;
			return true;
		}
	}
	return false;
}
