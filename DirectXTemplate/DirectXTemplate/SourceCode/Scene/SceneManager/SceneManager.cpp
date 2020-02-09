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
	//	読込関数.
	//=================================.
	void CSceneManager::Load()
	{
		m_pStackScene.top()->Load();
	}
	//=================================.
	//	更新関数.
	//=================================.
	void CSceneManager::Update()
	{
		m_pStackScene.top()->Update();
	}
	//=================================.
	//	描画関数.
	//=================================.
	void CSceneManager::Render()
	{
		m_pStackScene.top()->Render();
		ScenePushEditor();
	}


	//-----------------------------------------------.
	// シーンを追加する.
	//-----------------------------------------------.
	void CSceneManager::Push( std::shared_ptr<CSceneBase> pScenebase )
	{
		if( pScenebase == nullptr ) return;
		m_pStackScene.push( pScenebase );
	}
	//-----------------------------------------------.
	// シーンを取り出す.
	//-----------------------------------------------.
	void CSceneManager::Pop()
	{
		m_pStackScene.pop();
	}
	//-----------------------------------------------.
	// シーンを二つ取り出す.
	//-----------------------------------------------.
	void CSceneManager::TwoPop()
	{
		m_pStackScene.pop();
		m_pStackScene.pop();
	}
	//-----------------------------------------------.
	// シーンを切り替える.
	//-----------------------------------------------.
	void CSceneManager::Change( std::shared_ptr<CSceneBase> pScenebase )
	{
		m_pStackScene.pop();
		m_pStackScene.push( pScenebase );
	}
	//-----------------------------------------------.
	// 現在スタックしているシーンをすべて取り出す.
	//-----------------------------------------------.
	void CSceneManager::StackRelease()
	{
		const size_t stackSceneSize = m_pStackScene.size();
		for( size_t i = 0; i < stackSceneSize; i++ ){
			m_pStackScene.pop();
		}
	}

	//-----------------------------------------------.
	// エディットシーンに変更.
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
//	SCENE_INIT_INFO 関数.
//=================================.
namespace scene
{
	//------------------------.
	// シーンの追加.
	//------------------------.
	void CSceneBase::SCENE_INIT_INFO::Push( std::shared_ptr<CSceneBase> pScenebase )
	{
		this->pSceneManager->Push( pScenebase );
	} 
	//------------------------.
	// シーンの取り出す.
	//------------------------.
	void CSceneBase::SCENE_INIT_INFO::Pop()
	{
		this->pSceneManager->Pop();
	}
	//------------------------.
	// シーンを2つ取り出す.
	//------------------------.
	void CSceneBase::SCENE_INIT_INFO::TwoPop()
	{
		this->pSceneManager->TwoPop();
	}
	//------------------------.
	// シーンを切り返る.
	//------------------------.
	void CSceneBase::SCENE_INIT_INFO::Change( std::shared_ptr<CSceneBase> pScenebase )
	{
		this->pSceneManager->Change( pScenebase );
	}
};	// namespace scene.