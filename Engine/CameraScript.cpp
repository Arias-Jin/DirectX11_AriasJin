#include "CameraScript.h"

#include "Camera.h"
#include "Transform.h"

#include "GameObject.h"
#include "Player.h"

#include "Input.h"

#include "SceneManager.h"

#include "Time.h"

namespace arias
{
	CameraScript::CameraScript() :
		Script()
	{
	}

	CameraScript::~CameraScript()
	{
	}

	void CameraScript::Initialize()
	{
	}
	
	void CameraScript::Update()
	{
		std::vector<GameObject*> objects = SceneManager::GetActiveScene()->GetGameObjects(eLayerType::Player);

		bool isPlayerExist = false;

		for (auto iter : objects)
		{
			if (dynamic_cast<Player*>(iter))
			{
				isPlayerExist = true;
				GetOwner()->SetPositionXY(iter->GetPositionXY());
			}
		}

		if (!isPlayerExist)
		{
			GetOwner()->SetPositionXY(Vector2(0.f, 0.f));
		}
	}
	
	void CameraScript::Render()
	{
	}
}