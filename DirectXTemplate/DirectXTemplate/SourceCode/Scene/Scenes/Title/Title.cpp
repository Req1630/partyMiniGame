#include "..\SceneList.h"
#include "..\..\..\Resource\MeshResource\MeshResource.h"
#include "..\..\..\Common\Mesh\Dx9StaticMesh\Dx9StaticMesh.h"

namespace scene
{
	CTitle::CTitle( SCENE_INIT_INFO sceneInitInfo )
		: CSceneBase	( sceneInitInfo )

		, m_pStaticMesh	( nullptr )
	{}

	CTitle::~CTitle()
	{
	}

	//============================.
	//	�Ǎ��֐�.
	//============================.
	void CTitle::Load()
	{
		if( m_pStaticMesh == nullptr ){
			m_pStaticMesh = CMeshResorce::GetStatic("GhostA");
		}
	}

	//============================.
	//	�X�V�֐�.
	//============================.
	void CTitle::Update()
	{
		if( GetAsyncKeyState(VK_RETURN) & 0x0001 ){
			m_Info.Change( std::make_shared<CGame>( m_Info ) );
		}
	}

	//============================.
	//	�`��֐�.
	//============================.
	void CTitle::Render()
	{
		if( m_pStaticMesh == nullptr ) return;
		m_pStaticMesh->SetPosition( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) );
		m_pStaticMesh->SetRotation( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) );
		m_pStaticMesh->SetScale( 0.04f );
		m_pStaticMesh->Render( m_Info.pCamera, *m_Info.pLight );
	}

};