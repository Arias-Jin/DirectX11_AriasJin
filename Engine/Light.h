#pragma once
#include "Component.h"

#include "Graphics.h"

namespace arias
{
	class Light : public Component
	{
	public:
		Light();
		~Light();

	private:
		graphics::LightAttribute mAttribute;

	public:
		virtual void Initialize() override;
		virtual void Update() override;
		virtual void FixedUpdate() override;
		virtual void Render() override;

	public:
		graphics::LightAttribute GetLightAttribute() const { return mAttribute; }

		void SetDiffuse(Vector4 diffuse) { mAttribute.diffuse = diffuse; }
		Vector4 GetDiffuse() const { return mAttribute.diffuse; }

		void SetAmbient(Vector4 ambient) { mAttribute.ambient = ambient; }

		void SetType(eLightType type) { mAttribute.type = type; }
		eLightType GetType() const { return (eLightType)mAttribute.type; }

		void SetRadius(float radius) { mAttribute.radius = radius; }
		float GetRadius() { return mAttribute.radius; }

		void SetAngle(float angle) { mAttribute.angle = angle; }
		float GetAngle() { return mAttribute.angle; }
	};
}