#include "..\SceneList.h"
#include "..\..\..\GameObject\Stage\Stage.h"
#include "..\..\..\GameObject\Ground\Ground.h"
#include "..\..\..\GameObject\Character\Player\PlayerManager.h"
#include "..\..\..\GameObject\Character\Enemy\EnemyManager\EnemyManager.h"

namespace scene
{
	CGame::CGame( SCENE_INIT_INFO sceneInitInfo )
		: CSceneBase			( sceneInitInfo )

		, m_pStage				( std::make_shared<CStage>() )
		, m_pGround				( std::make_shared<CGround>() )
		, m_pPlayerManager		( std::make_shared<CPlayerManager>() )
		, m_pEnemyManager		( std::make_shared<CEnemyManager>() )
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
		m_pEnemyManager->Update();

		auto collision = [](
			std::shared_ptr<CGameObject> player, 
			std::shared_ptr<CGameObject> enemy )
		{
			player->Collision( enemy );
			enemy->Collision( player );
		};

		for( int i = 0; i < m_pPlayerManager->GetPlayerSize(); i++ ){
			for( int j = 0; j < m_pPlayerManager->GetPlayerSize(); j++ ){
				collision( m_pPlayerManager->GetPlayer(i), m_pPlayerManager->GetPlayer(j) );
			}
		}
	}

	//============================.
	//	•`‰æŠÖ”.
	//============================.
	void CGame::Render()
	{
		m_pStage->Render( m_Info );
		m_pGround->Render( m_Info );

		m_pPlayerManager->Render( m_Info );
		m_pEnemyManager->Render( m_Info );
	}
};