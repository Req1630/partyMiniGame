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
		m_pStaticMesh = CMeshResorce::GetStatic( m_ModelName );
	}

	if( m_isAssailable == false ) return;
	m_AttackCount++;
	Move();

	if( GetAsyncKeyState(VK_UP) & 0x8000 )		m_vPosition.z -= 0.01f;
	if( GetAsyncKeyState(VK_DOWN) & 0x8000 )	m_vPosition.z += 0.01f;
	if( GetAsyncKeyState(VK_RIGHT) & 0x8000 )	m_vPosition.x -= 0.01f;
	if( GetAsyncKeyState(VK_LEFT) & 0x8000 )	m_vPosition.x += 0.01f;
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
	if( m_AttackCount <= 3*65 ){
		m_vPosition.x -= sinf( m_vRotation.y ) * 0.04f;
		m_vPosition.z -= cosf( m_vRotation.y ) * 0.04f;
	} else {

	}
}