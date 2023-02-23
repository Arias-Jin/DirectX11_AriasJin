#pragma once
#include "GameObject.h"

#include "Transform.h"

#include "SceneManager.h"

namespace arias::object
{
	template <typename T>
	static T* Instantiate(enums::eLayerType type)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);

		layer.AddGameObject(gameObj);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Transform* parent)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		Transform* trans = gameObj->GameObject::GetComponent<Transform>();
		
		layer.AddGameObject(gameObj);
		trans->SetParent(parent);

		return gameObj;
	}

	template <typename T>
	static T* Instantiate(enums::eLayerType type, Vector3 position, Vector3 rotation, Vector3 scale)
	{
		T* gameObj = new T();
		Scene* scene = SceneManager::GetActiveScene();
		Layer& layer = scene->GetLayer(type);
		Transform* trans = gameObj->GameObject::GetComponent<Transform>();

		layer.AddGameObject(gameObj);
		trans->SetPosition(position);
		trans->SetRotation(rotation);
		trans->SetScale(scale);

		return gameObj;
	}

	void Destroy(GameObject* gameObject)
	{
		gameObject->Death();
	}
}