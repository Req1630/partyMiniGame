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

	// �Ǎ��֐�.
	void CEditor::Load()
	{
	}

	// �X�V�֐�.
	void CEditor::Update()
	{
		m_pStage->Update();
		m_pGround->Update();

		// �V�[�������o��.
		ScenePop();
	}

	// �`��֐�.
	void CEditor::Render()
	{
		// ImGui�̃t���[��������.
		CImGuiManager::SetingNewFrame();

		m_pStage->Render( m_Info );
		m_pGround->Render( m_Info );

		// �R���g���[���[�G�f�B�b�g�̕`��.
		m_pControllerEdit->Render();
		// �L�����N�^�[�G�f�B�b�g�̕`��.
		m_pCharacterEdit->Render( m_Info );

		// ImGui�ŏI�`��.
		CImGuiManager::Render();
	}

	// ���݂̃V�[�������o��.
	void CEditor::ScenePop()
	{
		if(!( GetAsyncKeyState('T') & 0x8000 )) return;
		if(!( GetAsyncKeyState('O') & 0x8000 )) return;
		if(!( GetAsyncKeyState(VK_TAB) & 0x0001 )) return;
		m_Info.Pop();
	}

};	// namespace scene.