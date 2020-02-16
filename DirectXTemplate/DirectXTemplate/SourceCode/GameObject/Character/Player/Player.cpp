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
	// コライダークラスの作成.
	m_pCollider = std::make_shared<CCollsionManager>();
	m_vRotation.y = CVector::ToRadian( 180.0f );
}

CPlayer::~CPlayer()
{
}

//-------------------------------------------.
// 更新関数.
//-------------------------------------------.
void CPlayer::Update()
{
	if( m_pStaticMesh == nullptr ){
		m_pStaticMesh = CMeshResorce::GetStatic( m_ModelName );
		if( m_pStaticMesh != nullptr ){
			// 当たり判定の初期化.
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
// 当たり判定関数.
//-------------------------------------------.
void CPlayer::Collision( pGameObject gameObj )
{
}

//-------------------------------------------.
// 描画関数.
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
// 操作関数.
//-------------------------------------------.
void CPlayer::Control()
{
	m_MovePower = m_MoveVector = { 0.0f, 0.0f };	// 移動ベクトルの初期化.
	// コントローラのスティックの傾きを取得.
	m_MoveVector.x = static_cast<float>(CXInput::LThumbX_Axis( m_PlayerNumber ));
	m_MoveVector.y = static_cast<float>(CXInput::LThumbY_Axis( m_PlayerNumber ));
}

//-------------------------------------------.
// プレイヤー同士の当たり判定.
//-------------------------------------------.
void CPlayer::PlayerToCollision( pGameObject gameObj )
{
	if( m_pCollider->IsShereToShere( gameObj->GetCollider()->GetSphere() ) ){
		m_vPosition.x += sinf( m_vRotation.y ) * m_MovePower.x;
		m_vPosition.z += cosf( m_vRotation.y ) * m_MovePower.y;
	}
}

//-------------------------------------------.
// 移動関数.
//-------------------------------------------.
void CPlayer::Move()
{
	// 各値が有効範囲外なら終了.
	if( m_MoveVector.x < IDLE_THUMB_MAX && IDLE_THUMB_MIN < m_MoveVector.x &&
		m_MoveVector.y < IDLE_THUMB_MAX && IDLE_THUMB_MIN < m_MoveVector.y ) return;

	// スティックの傾いた方向に向く.
	m_vRotation.y = atan2f( m_MoveVector.x, m_MoveVector.y );

	// 移動量を計算する.
	m_MovePower.x = fabsf( m_MoveVector.x ) / MOVE_DIVISION;	// x方向.
	m_MovePower.y = fabsf( m_MoveVector.y ) / MOVE_DIVISION;	// z方向.

	// 回転軸で移動.
	m_vPosition.x -= sinf( m_vRotation.y ) * m_MovePower.x;
	m_vPosition.z -= cosf( m_vRotation.y ) * m_MovePower.y;

	// ステージ外に行かないようにする.
	OutsideMove();
}

//-------------------------------------------.
// ステージ外に行かないようにする.
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
// プレイヤー人数の設定.
//-------------------------------------------.
void CPlayer::SetPlayerNumber( const int& playerNumber )
{ 
	m_PlayerNumber = playerNumber; 
}