#include "..\SceneList.h"
#include "..\..\..\GameObject\Stage\Stage.h"
#include "..\..\..\GameObject\Ground\Ground.h"
#include "..\..\..\GameObject\Character\Player\PlayerManager.h"

namespace scene
{
	CGame::CGame( SCENE_INIT_INFO sceneInitInfo )
		: CSceneBase			( sceneInitInfo )

		, m_pStage				( std::make_shared<CStage>() )
		, m_pGround				( std::make_shared<CGround>() )
		, m_pPlayerManager		( std::make_shared<CPlayerManager>() )
	{}

	CGame::~CGame()
	{
	}

	//============================.
	//	“ÇžŠÖ”.
	//============================.
	void CGame::Load()
	{
		
	}

	//============================.
	//	XVŠÖ”.
	//============================.
	void CGame::Update()
	{
		m_pStage->Update();
		m_pGround->Update();

		m_pPlayerManager->Update();
		m_pPlayerManager->Collision( m_pGround->GetCollider() );
	}

	//============================.
	//	•`‰æŠÖ”.
	//============================.
	void CGame::Render()
	{
		m_pStage->Render( m_Info );
		m_pGround->Render( m_Info );

		m_pPlayerManager->Render( m_Info );
	}

};