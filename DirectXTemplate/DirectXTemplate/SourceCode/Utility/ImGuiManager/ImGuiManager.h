#ifndef IMGUI_MANAGER_H
#define IMGUI_MANAGER_H

#include "..\..\Global.h"

#include "..\..\..\Library\ImGui\imgui.h"
#include "..\..\..\Library\ImGui\imgui_impl_dx11.h"
#include "..\..\..\Library\ImGui\imgui_impl_win32.h"

class CImGuiManager
{
	inline static const char* FONT_FILE_PATH  = "Data\\Font\\mplus-1p-medium.ttf";
	inline static const float FONT_SIZE = 18.0f;
public:
	CImGuiManager();
	~CImGuiManager();

	// �������֐�.
	static HRESULT Init( 
		HWND hWnd, 
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11 );

	// ����֐�.
	static HRESULT Release();

	// �t���[���̐ݒ�.
	static void SetingNewFrame();

	// �`��.
	static void Render();
};

#endif	// #ifndef IMGUI_MANAGER_H.