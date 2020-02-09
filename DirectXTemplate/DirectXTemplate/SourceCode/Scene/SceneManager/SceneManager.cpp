#include "SceneManager.h"
#include "..\Scenes\Editor\Editor.h"

namespace scene
{
	CSceneManager::CSceneManager()
	{
	}
	CSceneManager::~CSceneManager()
	{
	}

	//=================================.
	//	�Ǎ��֐�.
	//=================================.
	void CSceneManager::Load()
	{
		m_pStackScene.top()->Load();
	}
	//=================================.
	//	�X�V�֐�.
	//=================================.
	void CSceneManager::Update()
	{
		m_pStackScene.top()->Update();
	}
	//=================================.
	//	�`��֐�.
	//=================================.
	void CSceneManager::Render()
	{
		m_pStackScene.top()->Render();
		ScenePushEditor();
	}


	//-----------------------------------------------.
	// �V�[����ǉ�����.
	//-----------------------------------------------.
	void CSceneManager::Push( std::shared_ptr<CSceneBase> pScenebase )
	{
		if( pScenebase == nullptr ) return;
		m_pStackScene.push( pScenebase );
	}
	//-----------------------------------------------.
	// �V�[�������o��.
	//-----------------------------------------------.
	void CSceneManager::Pop()
	{
		m_pStackScene.pop();
	}
	//-----------------------------------------------.
	// �V�[�������o��.
	//-----------------------------------------------.
	void CSceneManager::TwoPop()
	{
		m_pStackScene.pop();
		m_pStackScene.pop();
	}
	//-----------------------------------------------.
	// �V�[����؂�ւ���.
	//-----------------------------------------------.
	void CSceneManager::Change( std::shared_ptr<CSceneBase> pScenebase )
	{
		m_pStackScene.pop();
		m_pStackScene.push( pScenebase );
	}
	//-----------------------------------------------.
	// ���݃X�^�b�N���Ă���V�[�������ׂĎ��o��.
	//-----------------------------------------------.
	void CSceneManager::StackRelease()
	{
		const size_t stackSceneSize = m_pStackScene.size();
		for( size_t i = 0; i < stackSceneSize; i++ ){
			m_pStackScene.pop();
		}
	}

	//-----------------------------------------------.
	// �G�f�B�b�g�V�[���ɕύX.
	//-----------------------------------------------.
	void CSceneManager::ScenePushEditor()
	{
		if(!( GetAsyncKeyState('T') & 0x8000 )) return;
		if(!( GetAsyncKeyState('O') & 0x8000 )) return;
		if(!( GetAsyncKeyState(VK_TAB) & 0x0001 )) return;
		Push( std::make_shared<scene::CEditor>(m_pStackScene.top()->GetInfo()) );
	}
}

//=================================.
//	SCENE_INIT_INFO �֐�.
//=================================.
namespace scene
{
	//------------------------.
	// �V�[���̒ǉ�.
	//------------------------.
	void CSceneBase::SCENE_INIT_INFO::Push( std::shared_ptr<CSceneBase> pScenebase )
	{
		this->pSceneManager->Push( pScenebase );
	} 
	//------------------------.
	// �V�[���̎��o��.
	//------------------------.
	void CSceneBase::SCENE_INIT_INFO::Pop()
	{
		this->pSceneManager->Pop();
	}
	//------------------------.
	// �V�[����2���o��.
	//------------------------.
	void CSceneBase::SCENE_INIT_INFO::TwoPop()
	{
		this->pSceneManager->TwoPop();
	}
	//------------------------.
	// �V�[����؂�Ԃ�.
	//------------------------.
	void CSceneBase::SCENE_INIT_INFO::Change( std::shared_ptr<CSceneBase> pScenebase )
	{
		this->pSceneManager->Change( pScenebase );
	}
};	// namespace scene.