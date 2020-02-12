#include "Stage.h"
#include "..\..\Common\Mesh\Dx9StaticMesh\Dx9StaticMesh.h"
#include "..\..\Resource\MeshResource\MeshResource.h"

CStage::CStage()
	: m_StaticMesh	( nullptr )
{
	m_ModelScale = MODEL_SCALE;	// モデルのサイズを設定.
}

CStage::~CStage()
{
}

//-----------------------.
// 更新関数.
//-----------------------.
void CStage::Update()
{
	if( m_StaticMesh == nullptr ){
		m_StaticMesh = CMeshResorce::GetStatic( MODEL_NAME );
	}
	if( m_StaticMesh == nullptr ) return;
}

//-----------------------.
// 当たり判定関数.
//-----------------------.
void CStage::Collision( pGameObject )
{
}

//-----------------------.
// 描画関数.
//-----------------------.
void CStage::Render( SCENE_INFO& info )
{
	if( m_StaticMesh == nullptr ) return;

	m_StaticMesh->SetPosition( m_vPosition );
	m_StaticMesh->SetRotation( m_vRotation );
	m_StaticMesh->SetScale( m_ModelScale );
	m_StaticMesh->Render( info.pCamera, *info.pLight );
}