#include "CollisionManager.h"

#include "Scene.h"
#include "SceneManager.h"

namespace arias
{
	std::bitset<(UINT)eLayerType::End> CollisionManager::mLayerCollisionMatrix[(UINT)eLayerType::End] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap;

	CollisionManager::CollisionManager()
	{
	}
	
	CollisionManager::~CollisionManager()
	{
	}
	
	void CollisionManager::Initialize()
	{
	}
	
	void CollisionManager::Update()
	{
		Scene* scene = SceneManager::GetActiveScene();

		for (UINT row = 0; row < (UINT)eLayerType::End; ++row)
		{
			for (UINT col = 0; col < (UINT)eLayerType::End; ++col)
			{
				if (mLayerCollisionMatrix[row][col])
				{
					LayerCollision(scene, (eLayerType)row, (eLayerType)col);
				}
			}
		}
	}
	
	void CollisionManager::FixedUpdate()
	{
	}
	
	void CollisionManager::Render()
	{
	}
	
	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = 0;
		int col = 0;

		if ((UINT)left <= (UINT)right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			row = (UINT)right;
			col = (UINT)left;
		}

		mLayerCollisionMatrix[row][col] = enable;
	}
	
	void CollisionManager::LayerCollision(Scene* scene, eLayerType left, eLayerType right)
	{
		const std::vector<GameObject*>& lefts = scene->GetGameObjects(left);
		const std::vector<GameObject*>& rights = scene->GetGameObjects(right);

		for (GameObject* left : lefts)
		{
			if (left->GetState() != GameObject::Active)
			{
				continue;
			}
			if (left->GetComponent<Collider2D>() == nullptr)
			{
				continue;
			}

			for (GameObject* right : rights)
			{
				if (right->GetState() != GameObject::Active)
				{
					continue;
				}
				if (right->GetComponent<Collider2D>() == nullptr)
				{
					continue;
				}
				if (left == right)
				{
					continue;
				}

				ColliderCollision(left->GetComponent<Collider2D>(), right->GetComponent<Collider2D>());
			}
		}
	}
	
	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right)
	{
		ColliderID colliderID;
		colliderID.left = (UINT64)left;
		colliderID.right = (UINT64)right;

		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(colliderID.id);
		
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(colliderID.id, false));
			iter = mCollisionMap.find(colliderID.id);
		}

		if (Intersect(left, right))
		{
			if (iter->second == false)
			{
				if (left->IsTrigger())
				{
					left->OnTriggerEnter(right);
				}
				else
				{
					left->OnCollisionEnter(right);
				}

				if (right->IsTrigger())
				{
					right->OnTriggerEnter(left);
				}
				else
				{
					right->OnCollisionEnter(left);
				}
			}
			else
			{
				if (left->IsTrigger())
				{
					left->OnTriggerStay(right);
				}
				else
				{
					left->OnCollisionStay(right);
				}

				if (right->IsTrigger())
				{
					right->OnTriggerStay(left);
				}
				else
				{
					right->OnCollisionStay(left);
				}
			}
		}
		else
		{
			if (iter->second == true)
			{
				if (left->IsTrigger())
				{
					left->OnTriggerExit(right);
				}
				else
				{
					left->OnCollisionExit(right);
				}

				if (right->IsTrigger())
				{
					right->OnTriggerExit(left);
				}
				else
				{
					right->OnCollisionExit(left);
				}

				iter->second = false;
			}
		}
	}
	
	bool CollisionManager::Intersect(Collider2D* left, Collider2D* right)
	{
		return true;
	}
}