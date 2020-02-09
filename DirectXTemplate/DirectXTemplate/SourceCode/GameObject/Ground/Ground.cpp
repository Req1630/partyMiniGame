#include "Ground.h"
#include "..\..\Common\Mesh\Dx9StaticMesh\Dx9StaticMesh.h"
#include "..\..\Resource\MeshResource\MeshResource.h"

CGround::CGround()
	: m_StaticMesh	( nullptr )
{
	m_ModelScale = MODEL_SCALE;		// ���f���̃T�C�Y��ݒ�.
	m_vPosition.y = INIT_POSITION_Y;// �������W�̐ݒ�.
}

CGround::~CGround()
{
}

//-----------------------.
// �X�V�֐�.
//-----------------------.
void CGround::Update()
{
	if( m_StaticMesh == nullptr ){
		m_StaticMesh = CMeshResorce::GetStatic( MODEL_NAME );
	}
	if( m_StaticMesh == nullptr ) return;
}

//-----------------------.
// �����蔻��֐�.
//-----------------------.
void CGround::Collision( pCollisionManager )
{
}

//-----------------------.
// �`��֐�.
//-----------------------.
void CGround::Render( SCENE_INFO& info )
{
	if( m_StaticMesh == nullptr ) return;

	m_StaticMesh->SetPosition( m_vPosition );
	m_StaticMesh->SetRotation( m_vRotation );
	m_StaticMesh->SetScale( m_ModelScale );
	m_StaticMesh->Render( info.pCamera, *info.pLight );
}