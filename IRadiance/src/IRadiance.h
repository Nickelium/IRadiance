#pragma once

// Intended for client application usage
// Include once

#include "IRadiance/Framework/Base.h"
#include "IRadiance/Framework/Core/Logger.h"
#include "IRadiance/Framework/Core/Time.h"

#include "IRadiance/Framework/Core/Application.h"

#include "IRadiance/Framework/Core/Layer.h"
#include "IRadiance/Framework/ImGui/ImGuiLayer.h"

#include "IRadiance/Framework/Core/Input.h"
#include "IRadiance/Framework/Core/KeyCodes.h"
#include "IRadiance/Framework/Core/MouseButtonCodes.h"

#include "IRadiance/Framework/Renderer/API/Shader.h"
#include "IRadiance/Framework/Renderer/API/Buffer.h"
#include "IRadiance/Framework/Renderer/API/VertexArray.h"
#include "IRadiance/Framework/Renderer/API/Buffer.h"
#include "IRadiance/Framework/Renderer/API/Texture2D.h"

#include "IRadiance/Framework/Renderer/Render.h"
#include "IRadiance/Framework/Renderer/MeshRender.h"
#include "IRadiance/Framework/Renderer/Camera/Orthographic.h"
#include "IRadiance/Framework/Renderer/Camera/Perspective.h"
#include "IRadiance/Framework/Renderer/Camera/FreeCamera.h"

#include "IRadiance/Framework/Components/Actor.h"
#include "IRadiance/Framework/Components/Component.h"
#include "IRadiance/Framework/Components/TransformComponent.h"
#include "IRadiance/Framework/Components/MeshComponent.h"

#include "IRadiance/Framework/Prefab/Prefab.h"

#include "IRadiance/Framework/Utility/Utility.h"

#include "IRadiance/Framework/Core/BaseLayer.h"
#include "IRadiance/Framework/Renderer/ImageBuffer.h"

// Vendor
#include <glm/glm.hpp>
#include <imgui.h>

// EntryPoint
#include "EntryPoint.h"

/////////////////////////////
///////RAYTRACER/////////////
/////////////////////////////
#include "IRadiance/Raytracer/Renderer.h"
