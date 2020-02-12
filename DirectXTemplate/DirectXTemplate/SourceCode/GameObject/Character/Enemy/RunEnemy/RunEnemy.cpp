#include "RunEnemy.h"
#include "..\..\..\..\Resource\MeshResource\MeshResource.h"
#include "..\..\..\..\Common\Mesh\Dx9StaticMesh\Dx9StaticMesh.h"
#include "..\..\..\..\Scene\SceneBase\SceneBase.h"

CRunEnemy::CRunEnemy()
	: m_pStaticMesh	( nullptr )
{
}

CRunEnemy::~CRunEnemy()
{
}

// XVŠÖ”.
void CRunEnemy::Update()
{
	if( m_pStaticMesh == nullptr ){
		m_pStaticMesh = CMeshResorce::GetStatic( MODEL_NAME );
	}
}

// “–‚½‚è”»’èŠÖ”.
void CRunEnemy::Collision( pGameObject )
{
}

// •`‰æŠÖ”.
void CRunEnemy::Render( SCENE_INFO& info )
{
	if( m_pStaticMesh == nullptr ) return;
	
	m_pStaticMesh->SetPosition( m_vPosition );
	m_pStaticMesh->SetRotation( m_vRotation );
	m_pStaticMesh->SetScale( m_ModelScale );
	m_pStaticMesh->Render( info.pCamera, *info.pLight );
}

// ˆÚ“®ŠÖ”.
void CRunEnemy::Move()
{
}