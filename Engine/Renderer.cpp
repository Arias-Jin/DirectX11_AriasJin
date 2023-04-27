#include "Renderer.h"

#include "ResourceManager.h"
#include "Material.h"
#include "PaintShader.h"
#include "ParticleShader.h"

#include "SceneManager.h"

namespace arias::renderer
{
	Vertex vertexes[4] = {};
	ConstantBuffer* constantBuffers[(UINT)eCBType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerStates[(UINT)eSamplerType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[(UINT)eRSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthstencilStates[(UINT)eDSType::End] = {};
	Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[(UINT)eBSType::End] = {};

	Camera* mainCamera = nullptr;
	std::vector<Camera*> cameras[(UINT)eSceneType::End];
	std::vector<DebugMesh> debugMeshes;
	std::vector<LightAttribute> lights;
	StructedBuffer* lightBuffer = nullptr;

	void LoadMesh()
	{
		// Point Mesh
		Vertex v = {};
		std::shared_ptr<Mesh> pointMesh = std::make_shared<Mesh>();
		ResourceManager::Insert<Mesh>(L"PointMesh", pointMesh);
		UINT pointIndex = 0;
		pointMesh->CreateIndexBuffer(&pointIndex, 1);

		// Rect
		vertexes[0].pos = Vector4(-0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[0].color = Vector4(0.f, 1.f, 0.f, 1.f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, 0.0f, 1.0f);
		vertexes[1].color = Vector4(1.f, 1.f, 1.f, 1.f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[2].color = Vector4(1.f, 0.f, 0.f, 1.f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, 0.0f, 1.0f);
		vertexes[3].color = Vector4(0.f, 0.f, 1.f, 1.f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		// Create RectMesh
		std::shared_ptr<Mesh> rectMesh = std::make_shared<Mesh>();
		ResourceManager::Insert<Mesh>(L"RectMesh", rectMesh);
		rectMesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes;

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);

		rectMesh->CreateIndexBuffer(indexes.data(), (UINT)indexes.size());

		// DebugRect
		vertexes[0].pos = Vector4(-0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[0].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector4(0.5f, 0.5f, -0.00001f, 1.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(0.0f, 0.0f);

		vertexes[2].pos = Vector4(0.5f, -0.5f, -0.00001f, 1.0f);
		vertexes[2].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[2].uv = Vector2(0.0f, 0.0f);

		vertexes[3].pos = Vector4(-0.5f, -0.5f, -0.00001f, 1.0f);
		vertexes[3].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 0.0f);

		// Create DebugRectMesh
		std::shared_ptr<Mesh> debugMesh = std::make_shared<Mesh>();
		ResourceManager::Insert<Mesh>(L"DebugRectMesh", debugMesh);
		debugMesh->CreateVertexBuffer(vertexes, 4);
		debugMesh->CreateIndexBuffer(indexes.data(), (UINT)indexes.size());

		// Circle
		std::vector<Vertex> circleVtxes;
		Vertex center = {};
		center.pos = Vector4(0.0f, 0.0f, -0.00001f, 1.0f);
		center.color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		center.uv = Vector2::Zero;

		circleVtxes.push_back(center);

		size_t iSlice = 80;
		float fRadius = 0.5f;
		float fTheta = XM_2PI / (float)iSlice;

		for (size_t i = 0; i < iSlice; ++i)
		{
			Vertex vtx = {};

			vtx.pos = Vector4(
				fRadius * cosf(fTheta * (float)i),
				fRadius * sinf(fTheta * (float)i),
				-0.00001f,
				1.0f
			);
			vtx.color = center.color;

			circleVtxes.push_back(vtx);
		}

		// Create CircleMesh
		std::shared_ptr<Mesh> circleMesh = std::make_shared<Mesh>();
		ResourceManager::Insert<Mesh>(L"CircleMesh", circleMesh);
		circleMesh->CreateVertexBuffer(circleVtxes.data(), (UINT)circleVtxes.size());

		indexes.clear();

		for (UINT i = 0; i < iSlice; ++i)
		{
			indexes.push_back(i + 1);
		}

		indexes.push_back(1);

		circleMesh->CreateIndexBuffer(indexes.data(), (UINT)indexes.size());
	}

	void SetUpState()
	{
#pragma region Input Layout
		D3D11_INPUT_ELEMENT_DESC arrLayoutDesc[3] = {};

		arrLayoutDesc[0].AlignedByteOffset = 0;
		arrLayoutDesc[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[0].InputSlot = 0;
		arrLayoutDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[0].SemanticName = "POSITION";
		arrLayoutDesc[0].SemanticIndex = 0;

		arrLayoutDesc[1].AlignedByteOffset = 16;
		arrLayoutDesc[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayoutDesc[1].InputSlot = 0;
		arrLayoutDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[1].SemanticName = "COLOR";
		arrLayoutDesc[1].SemanticIndex = 0;

		arrLayoutDesc[2].AlignedByteOffset = 32;
		arrLayoutDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayoutDesc[2].InputSlot = 0;
		arrLayoutDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayoutDesc[2].SemanticName = "TEXCOORD";
		arrLayoutDesc[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = ResourceManager::Find<Shader>(L"RectShader");
		GetDevice()->CreateInputLayout(
			arrLayoutDesc,
			3,
			shader->GetVSBlobBufferPointer(),
			shader->GetVSBlobBufferSize(),
			shader->GetInputLayoutAddressOf()
		);

		std::shared_ptr<Shader> spriteShader = ResourceManager::Find<Shader>(L"SpriteShader");
		GetDevice()->CreateInputLayout(
			arrLayoutDesc,
			3,
			spriteShader->GetVSBlobBufferPointer(),
			spriteShader->GetVSBlobBufferSize(),
			spriteShader->GetInputLayoutAddressOf()
		);

		std::shared_ptr<Shader> uiShader = ResourceManager::Find<Shader>(L"UIShader");
		GetDevice()->CreateInputLayout(
			arrLayoutDesc,
			3,
			uiShader->GetVSBlobBufferPointer(),
			uiShader->GetVSBlobBufferSize(),
			uiShader->GetInputLayoutAddressOf()
		);

		std::shared_ptr<Shader> gridShader = ResourceManager::Find<Shader>(L"GridShader");
		GetDevice()->CreateInputLayout(
			arrLayoutDesc,
			3,
			gridShader->GetVSBlobBufferPointer(),
			gridShader->GetVSBlobBufferSize(),
			gridShader->GetInputLayoutAddressOf()
		);

		std::shared_ptr<Shader> debugShader = ResourceManager::Find<Shader>(L"DebugShader");
		GetDevice()->CreateInputLayout(
			arrLayoutDesc,
			3,
			debugShader->GetVSBlobBufferPointer(),
			debugShader->GetVSBlobBufferSize(),
			debugShader->GetInputLayoutAddressOf()
		);

		std::shared_ptr<Shader> particleShader = ResourceManager::Find<Shader>(L"ParticleShader");
		GetDevice()->CreateInputLayout(
			arrLayoutDesc,
			3,
			particleShader->GetVSBlobBufferPointer(),
			particleShader->GetVSBlobBufferSize(),
			particleShader->GetInputLayoutAddressOf()
		);

		std::shared_ptr<Shader> fadeShader = ResourceManager::Find<Shader>(L"FadeShader");
		GetDevice()->CreateInputLayout(
			arrLayoutDesc,
			3,
			fadeShader->GetVSBlobBufferPointer(),
			fadeShader->GetVSBlobBufferSize(),
			fadeShader->GetInputLayoutAddressOf()
		);
#pragma endregion
#pragma region Sampler State
		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

		// D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR = 0x5,
		// D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT = 0x10,

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_LINEAR_MAG_MIP_POINT;
		GetDevice()->CreateSamplerState(
			&samplerDesc,
			samplerStates[(UINT)eSamplerType::Point].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_MIN_POINT_MAG_MIP_LINEAR;
		GetDevice()->CreateSamplerState(
			&samplerDesc,
			samplerStates[(UINT)eSamplerType::Linear].GetAddressOf()
		);

		samplerDesc.Filter = D3D11_FILTER::D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSamplerState(
			&samplerDesc,
			samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf()
		);

		GetDevice()->BindsSamplers((UINT)eSamplerType::Point, 1, samplerStates[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindsSamplers((UINT)eSamplerType::Linear, 1, samplerStates[(UINT)eSamplerType::Linear].GetAddressOf());
		GetDevice()->BindsSamplers((UINT)eSamplerType::Anisotropic, 1, samplerStates[(UINT)eSamplerType::Anisotropic].GetAddressOf());
#pragma endregion
#pragma region Rasterizer State
		D3D11_RASTERIZER_DESC rsDesc = {};

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
		GetDevice()->CreateRasterizerState(&rsDesc, rasterizerStates[(UINT)eRSType::SolidBack].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
		GetDevice()->CreateRasterizerState(&rsDesc, rasterizerStates[(UINT)eRSType::SolidFront].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizerState(&rsDesc, rasterizerStates[(UINT)eRSType::SolidNone].GetAddressOf());

		rsDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
		rsDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
		GetDevice()->CreateRasterizerState(&rsDesc, rasterizerStates[(UINT)eRSType::WireframeNone].GetAddressOf());
#pragma endregion
#pragma region Depth Stencil State
		D3D11_DEPTH_STENCIL_DESC dsDesc = {};
		
		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsDesc, depthstencilStates[(UINT)eDSType::Less].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsDesc, depthstencilStates[(UINT)eDSType::Greater].GetAddressOf());

		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsDesc, depthstencilStates[(UINT)eDSType::NoWrite].GetAddressOf());

		dsDesc.DepthEnable = false;
		dsDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK::D3D11_DEPTH_WRITE_MASK_ZERO;
		dsDesc.StencilEnable = false;
		GetDevice()->CreateDepthStencilState(&dsDesc, depthstencilStates[(UINT)eDSType::None].GetAddressOf());
#pragma endregion
#pragma region Blend State
		blendStates[(UINT)eBSType::Default] = nullptr;
		D3D11_BLEND_DESC bsDesc = {};

		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		bsDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::AlphaBlend].GetAddressOf());

		bsDesc.AlphaToCoverageEnable = false;
		bsDesc.IndependentBlendEnable = false;
		bsDesc.RenderTarget[0].BlendEnable = true;
		bsDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP::D3D11_BLEND_OP_ADD;
		bsDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		bsDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		GetDevice()->CreateBlendState(&bsDesc, blendStates[(UINT)eBSType::OneOne].GetAddressOf());
#pragma endregion
	}

	void LoadBuffer()
	{
		// Constant Buffer
		constantBuffers[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffers[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));

		constantBuffers[(UINT)eCBType::Material] = new ConstantBuffer(eCBType::Material);
		constantBuffers[(UINT)eCBType::Material]->Create(sizeof(MaterialCB));

		constantBuffers[(UINT)eCBType::Grid] = new ConstantBuffer(eCBType::Grid);
		constantBuffers[(UINT)eCBType::Grid]->Create(sizeof(GridCB));

		constantBuffers[(UINT)eCBType::Animation] = new ConstantBuffer(eCBType::Animation);
		constantBuffers[(UINT)eCBType::Animation]->Create(sizeof(AnimationCB));

		constantBuffers[(UINT)eCBType::Light] = new ConstantBuffer(eCBType::Light);
		constantBuffers[(UINT)eCBType::Light]->Create(sizeof(LightCB));

		constantBuffers[(UINT)eCBType::ParticleSystem] = new ConstantBuffer(eCBType::ParticleSystem);
		constantBuffers[(UINT)eCBType::ParticleSystem]->Create(sizeof(ParticleSystemCB));

		constantBuffers[(UINT)eCBType::Noise] = new ConstantBuffer(eCBType::Noise);
		constantBuffers[(UINT)eCBType::Noise]->Create(sizeof(NoiseCB));

		constantBuffers[(UINT)eCBType::Fade] = new ConstantBuffer(eCBType::Fade);
		constantBuffers[(UINT)eCBType::Fade]->Create(sizeof(FadeCB));

		// Structed Buffer
		lightBuffer = new StructedBuffer();
		lightBuffer->Create(sizeof(LightAttribute), 128, eSRVType::SRV, nullptr, true);
	}

	void LoadShader()
	{
		// Default
		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		ResourceManager::Insert<Shader>(L"RectShader", shader);

		// Sprite
		std::shared_ptr<Shader> spriteShader = std::make_shared<Shader>();
		spriteShader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteShader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		spriteShader->SetRSState(eRSType::SolidNone);
		ResourceManager::Insert<Shader>(L"SpriteShader", spriteShader);

		// UI
		std::shared_ptr<Shader> uiShader = std::make_shared<Shader>();
		uiShader->Create(eShaderStage::VS, L"UserInterfaceVS.hlsl", "main");
		uiShader->Create(eShaderStage::PS, L"UserInterfacePS.hlsl", "main");
		ResourceManager::Insert<Shader>(L"UIShader", uiShader);

		// Grid Shader
		std::shared_ptr<Shader> gridShader = std::make_shared<Shader>();
		gridShader->Create(eShaderStage::VS, L"GridVS.hlsl", "main");
		gridShader->Create(eShaderStage::PS, L"GridPS.hlsl", "main");
		gridShader->SetRSState(eRSType::SolidNone);
		gridShader->SetDSState(eDSType::NoWrite);
		gridShader->SetBSState(eBSType::AlphaBlend);
		ResourceManager::Insert<Shader>(L"GridShader", gridShader);

		// Debug Shader
		std::shared_ptr<Shader> debugShader = std::make_shared<Shader>();
		debugShader->Create(eShaderStage::VS, L"DebugVS.hlsl", "main");
		debugShader->Create(eShaderStage::PS, L"DebugPS.hlsl", "main");
		debugShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);
		ResourceManager::Insert<Shader>(L"DebugShader", debugShader);

		// Paint Shader
		std::shared_ptr<PaintShader> paintShader = std::make_shared<PaintShader>();
		paintShader->Create(L"PaintCS.hlsl", "main");
		ResourceManager::Insert<PaintShader>(L"PaintShader", paintShader);

		// Particle Shader
		std::shared_ptr<Shader> particleShader = std::make_shared<Shader>();
		particleShader->Create(eShaderStage::VS, L"ParticleVS.hlsl", "main");
		particleShader->Create(eShaderStage::GS, L"ParticleGS.hlsl", "main");
		particleShader->Create(eShaderStage::PS, L"ParticlePS.hlsl", "main");
		particleShader->SetRSState(eRSType::SolidNone);
		particleShader->SetDSState(eDSType::NoWrite);
		particleShader->SetBSState(eBSType::AlphaBlend);
		particleShader->SetTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		ResourceManager::Insert<Shader>(L"ParticleShader", particleShader);

		std::shared_ptr<ParticleShader> particleCS = std::make_shared<ParticleShader>();
		ResourceManager::Insert<ParticleShader>(L"ParticleCS", particleCS);
		particleCS->Create(L"ParticleCS.hlsl", "main");

		// Fade Shader
		std::shared_ptr<Shader> fadeShader = std::make_shared<Shader>();
		fadeShader->Create(eShaderStage::VS, L"FadeVS.hlsl", "main");
		fadeShader->Create(eShaderStage::PS, L"FadePS.hlsl", "main");
		ResourceManager::Insert<Shader>(L"FadeShader", fadeShader);
	}

	void LoadTexture()
	{
#pragma region Public
		ResourceManager::Load<Texture>(L"CrosshairTexture", L"Public\\Crosshair.png");
#pragma endregion

#pragma region Title Scene
		ResourceManager::Load<Texture>(L"BackgroundTexture", L"Title\\Background.jpg");
		ResourceManager::Load<Texture>(L"PlayButtonTexture", L"Title\\Play_Button.png");
		ResourceManager::Load<Texture>(L"OptionButtonTexture", L"Title\\Option_Button.png");
		ResourceManager::Load<Texture>(L"ExitButtonTexture", L"Title\\Exit_Button.png");
#pragma endregion

#pragma region Play Scene
		ResourceManager::Load<Texture>(L"PlayerTexture", L"Play\\Player_Atlas.png");
#pragma endregion

#pragma region Public
		ResourceManager::Load<Texture>(L"SmileTexture", L"Smile.png");
		ResourceManager::Load<Texture>(L"DefaultSprite", L"Light.png");
		ResourceManager::Load<Texture>(L"HPBarTexture", L"HPBar.png");
		ResourceManager::Load<Texture>(L"CartoonSmoke", L"particle\\CartoonSmoke.png");
#pragma endregion

#pragma region Test
		std::shared_ptr<Texture> uavTexture = std::make_shared<Texture>();
		uavTexture->Create(1024, 1024, DXGI_FORMAT_R8G8B8A8_UNORM, D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS);
		ResourceManager::Insert<Texture>(L"PaintTexture", uavTexture);

		ResourceManager::Load<Texture>(L"noise_01", L"noise\\noise_01.png");
		ResourceManager::Load<Texture>(L"noise_02", L"noise\\noise_02.png");
#pragma endregion
	}

	void LoadMaterial()
	{
#pragma region Public
		// Debug
		std::shared_ptr<Shader> debugShader = ResourceManager::Find<Shader>(L"DebugShader");
		std::shared_ptr<Material> debugMaterial = std::make_shared<Material>();
		debugMaterial->SetRenderingMode(eRenderingMode::Transparent);
		debugMaterial->SetShader(debugShader);
		ResourceManager::Insert<Material>(L"DebugMaterial", debugMaterial);

		// Grid
		std::shared_ptr<Shader> gridShader = ResourceManager::Find<Shader>(L"GridShader");
		std::shared_ptr<Material> gridMaterial = std::make_shared<Material>();
		gridMaterial->SetRenderingMode(eRenderingMode::Transparent);
		gridMaterial->SetShader(gridShader);
		ResourceManager::Insert<Material>(L"GridMaterial", gridMaterial);

		// Crosshair
		std::shared_ptr<Texture> crosshairTexture = ResourceManager::Find<Texture>(L"CrosshairTexture");
		std::shared_ptr<Shader> crosshairShader = ResourceManager::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> crosshairMaterial = std::make_shared<Material>();
		crosshairMaterial->SetRenderingMode(eRenderingMode::Transparent);
		crosshairMaterial->SetShader(crosshairShader);
		crosshairMaterial->SetTexture(eTextureSlot::T0, crosshairTexture);
		ResourceManager::Insert<Material>(L"CrosshairMaterial", crosshairMaterial);
#pragma endregion

#pragma region Title Scene
		// Title Background
		std::shared_ptr<Texture> backgroundTexture = ResourceManager::Find<Texture>(L"BackgroundTexture");
		std::shared_ptr<Shader> backgroundShader = ResourceManager::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> backgroundMaterial = std::make_shared<Material>();
		backgroundMaterial->SetShader(backgroundShader);
		backgroundMaterial->SetTexture(eTextureSlot::T0, backgroundTexture);
		ResourceManager::Insert<Material>(L"BackgroundMaterial", backgroundMaterial);

		// Title Play Button
		std::shared_ptr<Texture> playButtonTexture = ResourceManager::Find<Texture>(L"PlayButtonTexture");
		std::shared_ptr<Shader> playButtonShader = ResourceManager::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> playButtonMaterial = std::make_shared<Material>();
		playButtonMaterial->SetShader(playButtonShader);
		playButtonMaterial->SetTexture(eTextureSlot::T0, playButtonTexture);
		ResourceManager::Insert<Material>(L"PlayButtonMaterial", playButtonMaterial);

		// Title Option Button
		std::shared_ptr<Texture> optionButtonTexture = ResourceManager::Find<Texture>(L"OptionButtonTexture");
		std::shared_ptr<Shader> optionButtonShader = ResourceManager::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> optionButtonMaterial = std::make_shared<Material>();
		optionButtonMaterial->SetShader(optionButtonShader);
		optionButtonMaterial->SetTexture(eTextureSlot::T0, optionButtonTexture);
		ResourceManager::Insert<Material>(L"OptionButtonMaterial", optionButtonMaterial);

		// Title Exit Button
		std::shared_ptr<Texture> exitButtonTexture = ResourceManager::Find<Texture>(L"ExitButtonTexture");
		std::shared_ptr<Shader> exitButtonShader = ResourceManager::Find<Shader>(L"UIShader");
		std::shared_ptr<Material> exitButtonMaterial = std::make_shared<Material>();
		exitButtonMaterial->SetShader(exitButtonShader);
		exitButtonMaterial->SetTexture(eTextureSlot::T0, exitButtonTexture);
		ResourceManager::Insert<Material>(L"ExitButtonMaterial", exitButtonMaterial);
#pragma endregion

#pragma region Play Scene
		// Player
		std::shared_ptr<Texture> playerTexture = ResourceManager::Find<Texture>(L"PlayerTexture");
		std::shared_ptr<Shader> playerShader = ResourceManager::Find<Shader>(L"SpriteShader");
		std::shared_ptr<Material> playerMaterial = std::make_shared<Material>();
		playerMaterial->SetRenderingMode(eRenderingMode::Transparent);
		playerMaterial->SetShader(playerShader);
		playerMaterial->SetTexture(eTextureSlot::T0, playerTexture);
		ResourceManager::Insert<Material>(L"PlayerMaterial", playerMaterial);
#pragma endregion

#pragma region Test
		// Default
		std::shared_ptr <Texture> texture = ResourceManager::Find<Texture>(L"PaintTexture");
		std::shared_ptr<Shader> shader = ResourceManager::Find<Shader>(L"RectShader");
		std::shared_ptr<Material> material = std::make_shared<Material>();
		material->SetShader(shader);
		material->SetTexture(eTextureSlot::T0, texture);
		ResourceManager::Insert<Material>(L"RectMaterial", material);

		// Particle
		std::shared_ptr<Shader> particleShader = ResourceManager::Find<Shader>(L"ParticleShader");
		std::shared_ptr<Material> particleMaterial = std::make_shared<Material>();
		particleMaterial->SetRenderingMode(eRenderingMode::Transparent);
		particleMaterial->SetShader(particleShader);
		ResourceManager::Insert<Material>(L"ParticleMaterial", particleMaterial);

		// // UI
		// std::shared_ptr<Texture> uiTexture = ResourceManager::Find<Texture>(L"HPBarTexture");
		// std::shared_ptr<Shader> uiShader = ResourceManager::Find<Shader>(L"UIShader");
		// std::shared_ptr<Material> uiMaterial = std::make_shared<Material>();
		// uiMaterial->SetRenderingMode(eRenderingMode::Transparent);
		// uiMaterial->SetShader(uiShader);
		// uiMaterial->SetTexture(uiTexture);
		// ResourceManager::Insert<Material>(L"UIMaterial", uiMaterial);
		// 
		// // Fade
		// std::shared_ptr<Texture> fadeTexture = ResourceManager::Find<Texture>(L"SmileTexture");
		// std::shared_ptr<Shader> fadeShader = ResourceManager::Find<Shader>(L"FadeShader");
		// std::shared_ptr<Material> fadeMaterial = std::make_shared<Material>();
		// fadeMaterial->SetRenderingMode(eRenderingMode::Transparent);
		// fadeMaterial->SetShader(fadeShader);
		// fadeMaterial->SetTexture(fadeTexture);
		// ResourceManager::Insert<Material>(L"FadeMaterial", fadeMaterial);
#pragma endregion
	}

	void Initialize()
	{
		LoadMesh();
		LoadShader();
		SetUpState();
		LoadBuffer();
		LoadTexture();
		LoadMaterial();
	}

	void Render()
	{
		BindNoiseTexture();
		BindLights();

		eSceneType type = SceneManager::GetActiveScene()->GetSceneType();

		for (Camera* cam : cameras[(UINT)type])
		{
			if (cam == nullptr)
			{
				continue;
			}

			cam->Render();
		}

		cameras[(UINT)type].clear();
		renderer::lights.clear();
	}

	void Release()
	{
		for (size_t i = 0; i < (UINT)eCBType::End; ++i)
		{
			delete constantBuffers[i];
			constantBuffers[i] = nullptr;
		}

		delete lightBuffer;
		lightBuffer = nullptr;
	}
	
	void PushLightAttribute(LightAttribute lightAttribute)
	{
		lights.push_back(lightAttribute);
	}

	void BindLights()
	{
		lightBuffer->SetData(lights.data(), (UINT)lights.size());
		lightBuffer->BindSRV(eShaderStage::VS, 13);
		lightBuffer->BindSRV(eShaderStage::PS, 13);

		renderer::LightCB trCb = {};
		trCb.numberOfLight = (UINT)lights.size();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Light];
		cb->SetData(&trCb);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}

	void BindNoiseTexture()
	{
		std::shared_ptr<Texture> noise = ResourceManager::Find<Texture>(L"noise_01");
		noise->BindShaderResource(eShaderStage::VS, 16);
		noise->BindShaderResource(eShaderStage::HS, 16);
		noise->BindShaderResource(eShaderStage::DS, 16);
		noise->BindShaderResource(eShaderStage::GS, 16);
		noise->BindShaderResource(eShaderStage::PS, 16);
		noise->BindShaderResource(eShaderStage::CS, 16);

		NoiseCB info = {};
		info.noiseSize.x = (float)noise->GetWidth();
		info.noiseSize.y = (float)noise->GetHeight();

		ConstantBuffer* cb = renderer::constantBuffers[(UINT)eCBType::Noise];
		cb->SetData(&info);
		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::HS);
		cb->Bind(eShaderStage::DS);
		cb->Bind(eShaderStage::GS);
		cb->Bind(eShaderStage::PS);
		cb->Bind(eShaderStage::CS);
	}
}