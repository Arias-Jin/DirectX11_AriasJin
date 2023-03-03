#pragma once
#include "..\EDITOR_SOURCE\DebugObject.h"
#include "..\EDITOR_SOURCE\EditorObject.h"
#include "..\EDITOR_SOURCE\Widget.h"

namespace arias
{
	class Editor
	{
	private:
		std::vector<Widget> mWidgets;
		std::vector<EditorObject> mEditorObjects;
		std::vector<DebugObject> mDebugObjects;

	public:
		void Initialize();
		void Run();
		void Update();
		void FixedUpdate();
		void Render();
		void Release();
		void DebugRender();
	};
}