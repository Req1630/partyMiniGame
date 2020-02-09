#include "LoadManager.h"
#include "..\EffectResource\EffectResource.h"
#include "..\MeshResource\MeshResource.h"
#include "..\SpriteResource\SpriteResource.h"

CLoadManager::CLoadManager()
	: m_isLoadEnd		( false )
	, m_isThreadJoined	( false )
{
}

CLoadManager::~CLoadManager()
{
}

//------------------------.
// �ǂݍ���.
//------------------------.
void CLoadManager::Load(  
	HWND hWnd, 
	ID3D11Device* pDevice11, 
	ID3D11DeviceContext* pContext11, 
	LPDIRECT3DDEVICE9 pDevice9 )
{
	auto load = [&]( HWND hWnd, 
		ID3D11Device* pDevice11, 
		ID3D11DeviceContext* pContext11, 
		LPDIRECT3DDEVICE9 pDevice9 )
	{
		CMeshResorce::Load( hWnd, pDevice11, pContext11, pDevice9 );
		CEffectResource::Load( pDevice11, pContext11 );
		CSpriteResource::Load( pDevice11, pContext11 );

		m_isLoadEnd = true;
	};
	m_Thread = std::thread( load, hWnd, pDevice11, pContext11, pDevice9 );
}

//------------------------.
// �X���b�h�̉��.
//------------------------.
bool CLoadManager::ThreadRelease()
{
	if( m_isThreadJoined == true ) return true;
	if( m_isLoadEnd == false ) return false;
	m_Thread.join();
	m_isThreadJoined = true;
	return true;
}