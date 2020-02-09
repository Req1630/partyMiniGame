#include "Editor.h"
#include "..\..\..\Editor\ControllerEdit\ControllerEdit.h"
#include "..\..\..\Editor\CharacterEdit\CharacterEdit.h"

#include "..\..\..\GameObject\Stage\Stage.h"
#include "..\..\..\GameObject\Ground\Ground.h"

namespace scene
{
	CEditor::CEditor( SCENE_INIT_INFO sceneInitInfo )
		: CSceneBase		( sceneInitInfo )

		, m_pStage			( std::make_shared<CStage>() )
		, m_pGround			( std::make_shared<CGround>() )
		, m_pControllerEdit	( std::make_unique<CControllerEdit>() )
		, m_pCharacterEdit	( std::make_unique<CCharacterEdit>() )
	{
	}

	CEditor::~CEditor()
	{
	}

	// 読込関数.
	void CEditor::Load()
	{
	}

	// 更新関数.
	void CEditor::Update()
	{
		m_pStage->Update();
		m_pGround->Update();

		// シーンを取り出す.
		ScenePop();
	}

	// 描画関数.
	void CEditor::Render()
	{
		// ImGuiのフレーム初期化.
		CImGuiManager::SetingNewFrame();

		m_pStage->Render( m_Info );
		m_pGround->Render( m_Info );

		// コントローラーエディットの描画.
		m_pControllerEdit->Render();
		// キャラクターエディットの描画.
		m_pCharacterEdit->Render( m_Info );

		// ImGui最終描画.
		CImGuiManager::Render();
	}

	// 現在のシーンを取り出す.
	void CEditor::ScenePop()
	{
		if(!( GetAsyncKeyState('T') & 0x8000 )) return;
		if(!( GetAsyncKeyState('O') & 0x8000 )) return;
		if(!( GetAsyncKeyState(VK_TAB) & 0x0001 )) return;
		m_Info.Pop();
	}

};	// namespace scene.