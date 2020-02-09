#include "ImGuiManager.h"

CImGuiManager::CImGuiManager()
{
}

CImGuiManager::~CImGuiManager()
{
}

//----------------------.
// �������֐�.
//----------------------.
HRESULT CImGuiManager::Init( 
	HWND hWnd, 
	ID3D11Device* pDevice11,
	ID3D11DeviceContext* pContext11 )
{
	IMGUI_CHECKVERSION();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImFont* font = io.Fonts->AddFontFromFileTTF(
		FONT_FILE_PATH, FONT_SIZE,
		nullptr, 
		io.Fonts->GetGlyphRangesJapanese());

	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes( FONT_SIZE*0.06f ); // UI�̑傫�����ꊇ�ŕύX�ł��܂��B
	io.FontGlobalScale = FONT_SIZE*0.06f; // �t�H���g�̑傫�����ꊇ�ŕύX�ł��܂��B
	if( ImGui_ImplWin32_Init( hWnd ) == false ) return E_FAIL;
	if( ImGui_ImplDX11_Init( pDevice11, pContext11 ) == false ) return E_FAIL;

	ImGui::StyleColorsDark();

	return S_OK;
}

//----------------------.
// ����֐�.
//----------------------.
HRESULT CImGuiManager::Release()
{
	// ImGui�̉��.
	ImGui_ImplWin32_Shutdown();
	ImGui_ImplDX11_Shutdown();
	ImGui::DestroyContext();

	return S_OK;
}

//----------------------.
// �t���[���̐ݒ�.
//----------------------.
void CImGuiManager::SetingNewFrame()
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

//----------------------.
// �`��.
//----------------------.
void CImGuiManager::Render()
{
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData( ImGui::GetDrawData() );
}