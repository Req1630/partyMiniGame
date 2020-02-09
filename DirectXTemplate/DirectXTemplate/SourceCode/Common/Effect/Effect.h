#ifndef EFFECT_H
#define EFFECT_H

// �x���ɂ��ẴR�[�h���͂𖳌��ɂ���. 4005: �Ē�`.
#pragma warning(disable:4005)

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")



// XAudio2�֌W�̃R�[�h��L���ɂ���.
#if 0
#define ENABLE_XAUDIO2
#endif // #if 0.

#ifdef ENABLE_XAUDIO2
#include <XAudio2.h>
#endif	// #ifdef ENABLE_XAUDIO2

//-------------------------------------------------
//	��������Effekseer�֌W �w�b�_�A���C�u�����ǂݍ���.
//-------------------------------------------------
#include <Effekseer.h>
#include <EffekseerRendererDX11.h>

#ifdef ENABLE_XAUDIO2
#include <EffekseerSoundXAudio2.h>
#endif	// #ifdef ENABLE_XAUDIO2

#if _DEBUG
#pragma comment(lib,"_Debug\\Effekseer.lib")
#pragma comment(lib,"_Debug\\EffekseerRendererDX11.lib")
#ifdef ENABLE_XAUDIO2
#pragma comment(lib,"_Debug\\EffekseerSoundXAudio2.lib")
#endif	// #ifdef ENABLE_XAUDIO2

#else	// #if _DEBUG
#pragma comment(lib,"_Release\\Effekseer.lib")
#pragma comment(lib,"_Release\\EffekseerRendererDX11.lib")
#ifdef ENABLE_XAUDIO2
#pragma comment(lib,"_Release\\EffekseerSoundXAudio2.lib")
#endif	//#ifdef ENABLE_XAUDIO2

#endif	// #if _DEBUG


#include <D3DX10.h>	// ����:Effekseer�֌W����œǂݍ��ނ���.
#pragma comment(lib, "d3dx10.lib")

/************************************************************
*	Effeksser�̃f�[�^���g���ׂ̃N���X.
**/
class CEffect
{
public:
	typedef int Handle;
public:
	CEffect();	// �R���X�g���N�^..
	CEffect( 
		ID3D11Device* pDevice11, 
		ID3D11DeviceContext* pContext11, 
		const std::string& fileName );
	~CEffect();	// �f�X�g���N�^.

	// ������.
	HRESULT Init( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11, const std::string& fileName );

	// �\�z.
	HRESULT Create( ID3D11Device* pDevice11, ID3D11DeviceContext* pContext11 );
	// �j��.
	void Destroy();
	// �f�[�^�ǂݍ���.
	HRESULT LoadData( const std::string& fileName );
	// �f�[�^���.
	void ReleaseData();
	// �`��֐�.
	void Render( 
		D3DXMATRIX& mView, 
		D3DXMATRIX& mProj, 
		const Effekseer::Handle& eHandle );

	// �Đ��֐�.
	Effekseer::Handle Play( const D3DXVECTOR3& vPos ) const
	{
		return m_pManager->Play( m_pEffect, vPos.x, vPos.y, vPos.z );
	}
	// ��~�֐�.
	void Stop( const Effekseer::Handle& handle )
	{
		if( handle == -1 ) return; 
		m_pManager->StopEffect( handle );
	} 
	// �S�Ē�~�֐�.
	void StopAll()
	{
		m_pManager->StopAllEffects();
	}
	// �ꎞ��~.
	void Pause( const Effekseer::Handle& handle, bool bFlag )
	{
		if( handle == -1 ) return;
		m_pManager->SetPaused( handle, bFlag );
	}

	// �ʒu���w�肷��.
	void SetLocation( const Effekseer::Handle& handle, const D3DXVECTOR3& vPos )
	{
		if( handle == -1 ) return;
		m_pManager->SetLocation( handle, ConvertToVec3Efk(vPos) );
	}
	void SetLocation( const Effekseer::Handle& handle, const float& x, const float& y, const float& z )
	{
		if( handle == -1 ) return;
		m_pManager->SetLocation( handle, x, y, z );
	}
	// �T�C�Y���w�肷��.
	void SetScale( const Effekseer::Handle& handle, const D3DXVECTOR3& vScale )
	{
		if( handle == -1 ) return;
		m_pManager->SetScale( handle, vScale.x, vScale.y, vScale.z );
	}
	// ��]���w�肷��.
	void SetRotation( const Effekseer::Handle& handle, const D3DXVECTOR3& vRot )
	{
		if( handle == -1 ) return;
		m_pManager->SetRotation( handle, vRot.x, vRot.y, vRot.z );
	}
	// ��]���w�肷��(���ƃ��W�A��).
	void SetRotation( const Effekseer::Handle& handle, const D3DXVECTOR3& vAxis, float fRadian )
	{
		if( handle == -1 ) return;
		m_pManager->SetRotation( handle, ConvertToVec3Efk(vAxis), fRadian );
	}
	// �Đ����x��ݒ肷��.
	void SetSpeed( const Effekseer::Handle& handle, float fSpeed )
	{
		if( handle == -1 ) return;
		m_pManager->SetSpeed( handle, fSpeed );
	}

private:
	//--------------------------------------
	//	DirectX <--> Effekseer �ϊ��֐�.
	//--------------------------------------
	// vector�ϊ�.
	Effekseer::Vector3D	ConvertToVec3Efk( const D3DXVECTOR3& SrcVec3Dx ) const;
	D3DXVECTOR3 ConvertToVec3Dx( const Effekseer::Vector3D& SrcVec3Efk ) const;
	// matrix�ϊ�.
	Effekseer::Matrix44 ConvertToMatEfk( const D3DXMATRIX& SrcMatDx ) const;
	D3DXMATRIX ConvertToMatDx( const Effekseer::Matrix44& SrcMatEfk ) const;

	// �ޭ��s���ݒ�.
	void SetViewMatrix(D3DXMATRIX& mView);
	// ��ۼު���ݍs���ݒ�.
	void SetProjectionMatrix(D3DXMATRIX& mProj);

	// �̪�Ă𓮍삳���邽�߂ɕK�v.
	Effekseer::Manager*				m_pManager;
	EffekseerRenderer::Renderer*	m_pRenderer;
	Effekseer::Effect*				m_pEffect;

#ifdef ENABLE_XAUDIO2
	//�̪���ް��Ɋ܂܂�鉹�̍Đ��ɕK�v.
	::EffekseerSound::Sound*		m_pSound;
	IXAudio2*						m_pXA2;
	IXAudio2MasteringVoice*			m_pXA2Master;
#endif//#ifdef ENABLE_XAUDIO2
};

#endif	// #ifndef EFFECT_H.