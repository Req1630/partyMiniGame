#include "Player.h"
#include "PlayerManager.h"
#include "..\..\..\Common\Mesh\Dx9StaticMesh\Dx9StaticMesh.h"
#include "..\..\..\Resource\MeshResource\MeshResource.h"
#include "..\..\..\Collider\CollsionManager\CollsionManager.h"
#include "..\..\..\Utility\MyVector\MyVector.h"
#include "..\..\..\Utility\XInput\XInput.h"
#include "..\..\..\Common\DebugText\DebugText.h"

CPlayer::CPlayer()
	: m_pStaticMesh			( nullptr )
	, m_MoveVector			{ 0.0f, 0.0f } 
	, m_MovePower			{ 0.0f, 0.0f } 
	, m_PlayerNumber		( 0 )
{
	// �R���C�_�[�N���X�̍쐬.
	m_pCollider = std::make_shared<CCollsionManager>();
	m_vRotation.y = CVector::ToRadian( 180.0f );
}

CPlayer::~CPlayer()
{
}

//-------------------------------------------.
// �X�V�֐�.
//-------------------------------------------.
void CPlayer::Update()
{
	if( m_pStaticMesh == nullptr ){
		m_pStaticMesh = CMeshResorce::GetStatic( m_ModelName );
		if( m_pStaticMesh != nullptr ){
			// �����蔻��̏�����.
			m_pCollider->SetSphereAdjRadius( m_SphereRadius );
			m_pCollider->SetSphereAdjPosition( m_SphereAdjPosition );
			m_pCollider->Init( m_pStaticMesh->GetMesh(),
				&m_vPosition,
				&m_vRotation,
				&m_ModelScale );
		}
	}
	if( m_pStaticMesh == nullptr ) return;
	Move();
}

//-------------------------------------------.
// �����蔻��֐�.
//-------------------------------------------.
void CPlayer::Collision( pGameObject gameObj )
{
}

//-------------------------------------------.
// �`��֐�.
//-------------------------------------------.
void CPlayer::Render( SCENE_INFO& info )
{
	m_pStaticMesh->SetPosition( m_vPosition );
	m_pStaticMesh->SetRotation( m_vRotation );
	m_pStaticMesh->SetScale( m_ModelScale );
	m_pStaticMesh->Render( info.pCamera, *info.pLight );

	m_pCollider->DebugRender( info.pCamera );
}

//-------------------------------------------.
// ����֐�.
//-------------------------------------------.
void CPlayer::Control()
{
	m_MovePower = m_MoveVector = { 0.0f, 0.0f };	// �ړ��x�N�g���̏�����.
	// �R���g���[���̃X�e�B�b�N�̌X�����擾.
	m_MoveVector.x = static_cast<float>(CXInput::LThumbX_Axis( m_PlayerNumber ));
	m_MoveVector.y = static_cast<float>(CXInput::LThumbY_Axis( m_PlayerNumber ));
}

//-------------------------------------------.
// �v���C���[���m�̓����蔻��.
//-------------------------------------------.
void CPlayer::PlayerToCollision( pGameObject gameObj )
{
	if( m_pCollider->IsShereToShere( gameObj->GetCollider()->GetSphere() ) ){
		m_vPosition.x += sinf( m_vRotation.y ) * m_MovePower.x;
		m_vPosition.z += cosf( m_vRotation.y ) * m_MovePower.y;
	}
}

//-------------------------------------------.
// �ړ��֐�.
//-------------------------------------------.
void CPlayer::Move()
{
	// �e�l���L���͈͊O�Ȃ�I��.
	if( m_MoveVector.x < IDLE_THUMB_MAX && IDLE_THUMB_MIN < m_MoveVector.x &&
		m_MoveVector.y < IDLE_THUMB_MAX && IDLE_THUMB_MIN < m_MoveVector.y ) return;

	// �X�e�B�b�N�̌X���������Ɍ���.
	m_vRotation.y = atan2f( m_MoveVector.x, m_MoveVector.y );

	// �ړ��ʂ��v�Z����.
	m_MovePower.x = fabsf( m_MoveVector.x ) / MOVE_DIVISION;	// x����.
	m_MovePower.y = fabsf( m_MoveVector.y ) / MOVE_DIVISION;	// z����.

	// ��]���ňړ�.
	m_vPosition.x -= sinf( m_vRotation.y ) * m_MovePower.x;
	m_vPosition.z -= cosf( m_vRotation.y ) * m_MovePower.y;

	// �X�e�[�W�O�ɍs���Ȃ��悤�ɂ���.
	OutsideMove();
}

//-------------------------------------------.
// �X�e�[�W�O�ɍs���Ȃ��悤�ɂ���.
//-------------------------------------------.
void CPlayer::OutsideMove()
{
	if( m_vPosition.x <= -OUTSIDE_STAGE_VALUE || OUTSIDE_STAGE_VALUE <= m_vPosition.x ){
		m_vPosition.x += sinf( m_vRotation.y ) * m_MovePower.x;
	}
	if( m_vPosition.z <= -OUTSIDE_STAGE_VALUE || OUTSIDE_STAGE_VALUE <= m_vPosition.z ){
		m_vPosition.z += cosf( m_vRotation.y ) * m_MovePower.y;
	}
}

//-------------------------------------------.
// �v���C���[�l���̐ݒ�.
//-------------------------------------------.
void CPlayer::SetPlayerNumber( const int& playerNumber )
{ 
	m_PlayerNumber = playerNumber; 
}