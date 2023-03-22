#include "Light.h"

#include "Transform.h"

#include "GameObject.h"

#include "Renderer.h"

namespace arias
{
	Light::Light() :
		Component(eComponentType::Light)
	{
	}
	
	Light::~Light()
	{
	}
	
	void Light::Initialize()
	{
	}
	
	void Light::Update()
	{
	}
	
	void Light::FixedUpdate()
	{
		Transform* trans = GetOwner()->GetComponent<Transform>();
		Vector3 position = trans->GetPosition();

		mAttribute.position = Vector4(position.x, position.y, position.z, 1.0f);
		mAttribute.direction = Vector4(trans->Right().x, trans->Right().y, trans->Right().z, 1.0f);

		renderer::PushLightAttribute(mAttribute);
	}
	
	void Light::Render()
	{
	}
}