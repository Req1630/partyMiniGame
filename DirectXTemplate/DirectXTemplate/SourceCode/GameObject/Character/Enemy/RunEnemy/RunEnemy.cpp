#include "RunEnemy.h"
#include "..\..\..\..\Resource\MeshResource\MeshResource.h"
#include "..\..\..\..\Common\Mesh\Dx9StaticMesh\Dx9StaticMesh.h"
#include "..\..\..\..\Scene\SceneBase\SceneBase.h"

#include "..\..\..\..\Common\DebugText\DebugText.h"

CRunEnemy::CRunEnemy()
	: m_pStaticMesh	( nullptr )
{
}

CRunEnemy::~CRunEnemy()
{
}

// çXêVä÷êî.
void CRunEnemy::Update()
{
	if( m_pStaticMesh == nullptr ){
		m_pStaticMesh = CMeshResorce::GetStatic( MODEL_NAME );
	}

	if( m_isAssailable == false ) return;

	Move();
}

// ìñÇΩÇËîªíËä÷êî.
void CRunEnemy::Collision( pGameObject )
{
}

// ï`âÊä÷êî.
void CRunEnemy::Render( SCENE_INFO& info )
{
	if( m_pStaticMesh == nullptr ) return;
	
	m_pStaticMesh->SetPosition( m_vPosition );
	m_pStaticMesh->SetRotation( m_vRotation );
	m_pStaticMesh->SetScale( m_ModelScale );
	m_pStaticMesh->Render( info.pCamera, *info.pLight );

	CDebugText::SetPosition( { 0.0f, 50.0f, 0.0f } );
	CDebugText::Render( "pos_x : ", m_vPosition.x );
	CDebugText::SetPosition( { 0.0f, 70.0f, 0.0f } );
	CDebugText::Render( "pos_z : ", m_vPosition.z );
}

// à⁄ìÆä÷êî.
void CRunEnemy::Move()
{
	m_vPosition.x -= sinf( m_vRotation.y ) * 0.02f;
	m_vPosition.z -= cosf( m_vRotation.y ) * 0.02f;
	//if( m_vPosition.x <= 5.0f ){
	//	m_vPosition.x += sinf( m_vRotation.y ) * 0.02f;
	//}
}