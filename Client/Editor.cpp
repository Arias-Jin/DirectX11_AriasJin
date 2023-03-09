#include "Editor.h"

#include "../Engine/Camera.h"
#include "../Engine/MeshRenderer.h"
#include "../Engine/GridScript.h"
#include "../Engine/Transform.h"

#include "../Engine/Object.h"

#include "../Engine/ResourceManager.h"
#include "../Engine/Material.h"
#include "../Engine/Mesh.h"

namespace arias
{
	void Editor::Initialize()
	{
		// 충돌체의 종류 갯수 만큼만 있으면 된다.
		mDebugObjects.resize((UINT)eColliderType::End);

#pragma region Debug Rect
		mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<Transform>();
		MeshRenderer* rectRenderer = mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<MeshRenderer>();

		std::shared_ptr<Mesh> rectMesh = ResourceManager::Find<Mesh>(L"DebugRectMesh");
		std::shared_ptr<Material> rectMaterial = ResourceManager::Find<Material>(L"DebugMaterial");

		rectRenderer->SetMaterial(rectMaterial);
		rectRenderer->SetMesh(rectMesh);
#pragma endregion

#pragma region Debug Circle
		mDebugObjects[(UINT)eColliderType::Circle] = new DebugObject();
		mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<Transform>();
		MeshRenderer* circleRenderer = mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<MeshRenderer>();

		std::shared_ptr<Mesh> circleMesh = ResourceManager::Find<Mesh>(L"CircleMesh");
		std::shared_ptr<Material> circleMaterial = ResourceManager::Find<Material>(L"DebugMaterial");

		circleRenderer->SetMaterial(circleMaterial);
		circleRenderer->SetMesh(circleMesh);
#pragma endregion

#pragma region Grid Object
		// EditorObject* gridObject = new EditorObject();
		// MeshRenderer* gridRenderer = gridObject->AddComponent<MeshRenderer>();
		// GridScript* gridScript = gridObject->AddComponent<GridScript>();
		// Transform* gridTransform = gridObject->AddComponent<Transform>();
		// 
		// gridRenderer->SetMesh(ResourceManager::Find<Mesh>(L"RectMesh"));
		// gridRenderer->SetMaterial(ResourceManager::Find<Material>(L"GridMaterial"));
		// 
		// mEditorObjects.push_back(gridObject);
#pragma endregion
	}

	void Editor::Run()
	{
		Update();
		FixedUpdate();
		Render();
	}

	void Editor::Update()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Update();
		}
	}

	void Editor::FixedUpdate()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->FixedUpdate();
		}
	}

	void Editor::Render()
	{
		for (EditorObject* obj : mEditorObjects)
		{
			obj->Render();
		}

		for (DebugMesh& mesh : renderer::debugMeshes)
		{
			DebugRender(mesh);
		}

		renderer::debugMeshes.clear();
	}

	void Editor::Release()
	{
		for (auto obj : mWidgets)
		{
			delete obj;
			obj = nullptr;
		}

		for (auto obj : mEditorObjects)
		{
			delete obj;
			obj = nullptr;
		}

		delete mDebugObjects[(UINT)eColliderType::Rect];
		delete mDebugObjects[(UINT)eColliderType::Circle];
	}

	void Editor::DebugRender(graphics::DebugMesh& mesh)
	{
		DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];
		Transform* trans = debugObj->GetComponent<Transform>();

		trans->SetPosition(mesh.position);
		trans->SetRotation(mesh.rotation);

		if (mesh.type == eColliderType::Rect)
		{
			trans->SetScale(mesh.scale);
		}
		else
		{
			trans->SetScale(Vector3(mesh.radius));
		}

		BaseRenderer* renderer = debugObj->GetComponent<BaseRenderer>();
		Camera* camera = renderer::mainCamera;

		trans->FixedUpdate();

		Camera::SetGpuViewMatrix(renderer::mainCamera->GetViewMatrix());
		Camera::SetGpuProjectionMatrix(renderer::mainCamera->GetProjectionMatrix());

		debugObj->Render();
	}
}