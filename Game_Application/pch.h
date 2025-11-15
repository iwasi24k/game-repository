//==============================================================================
// File        : pch.h
//------------------------------------------------------------------------------
// Author      : ix.U
// Created     : 2025-11-06
// Last Update : 2025-11-08
//------------------------------------------------------------------------------
// Overview :
// 汎用 include&マクロ定義
//==============================================================================
#ifndef PCH_H
#define PCH_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NOMINMAX
#include <Windows.h>
#include <assert.h>
#include <functional>

#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment (lib, "d3d11.lib")

#include <wrl/client.h>
using Microsoft::WRL::ComPtr;


#include <DirectXMath.h>
using namespace DirectX;

#include "DirectXTex.h"

#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>

#define SCREEN_WIDTH    (1280)
#define SCREEN_HEIGHT    (720)


#endif // PCH_H