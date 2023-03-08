#pragma once

#include "DebugObject.h"
#include "EditorObject.h"
#include "Widget.h"

#include "../Engine/Graphics.h"

namespace arias
{
	class Editor
	{
	private:
		std::vector<Widget*> mWidgets;
		std::vector<EditorObject*> mEditorObjects;
		std::vector<DebugObject*> mDebugObjects;

	public:
		void Initialize();
		void Run();
		void Update();
		void FixedUpdate();
		void Render();
		void Release();
		void DebugRender(graphics::DebugMesh& mesh);
	};
}