#pragma once

//�x���ɂ��Ă̺��ޕ��͂𖳌��ɂ���.4005:�Ē�`.
#pragma warning(disable:4005)
#include <Windows.h>
#include <crtdbg.h>
#include <memory>

#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>	//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#include <D3D10.h>
#include <d3dx9.h>

//ײ���ؓǂݍ���.
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx10.lib" )	//�uD3DX�`�v�̒�`�g�p���ɕK�v.
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

//=================================================
//	�萔.
//=================================================
const int WND_W = 1280;	//����޳�̕�.
const int WND_H = 720;	//����޳�̍���.

class CCamera;
class CDX9SkinMesh;
class CDX9StaticMesh;

//ײď��.
struct LIGHT
{
	D3DXVECTOR3	vPos;		//�ʒu.
	D3DXVECTOR3	vDir;		//����.
	D3DXMATRIX	mRot;		//��]�s��.
	float		fIntensity;	//���x(���邳).
};

//===========================================================
//	ϸ�.
//===========================================================
//���.
#define SAFE_RELEASE(p)			if(p!=nullptr){(p)->Release();(p)=nullptr;}
//�j��.
#define SAFE_DELETE(p)			if(p!=nullptr){delete (p);(p)=nullptr;}
#define SAFE_DELETE_ARRAY(p)	if(p!=nullptr){delete[] (p);(p) = nullptr;}
//_declspec()	:DLL����(�֐�,�׽,�׽�����ފ֐���)����߰Ă���.
//align()		:(�����I��)16byte �Ŏg�p����.
#define ALIGN16	_declspec(align(16))

template<class T = const char*>
void ERROR_MESSAGE ( const T& error )
{
	size_t charSize = strlen(error)+1;
	if( charSize >= 128 ) _ASSERT_EXPR( false, L"�G���[���������ł�" );

	wchar_t wError[128];
	size_t ret;
	mbstowcs_s( &ret, wError, charSize, error, _TRUNCATE );
	_ASSERT_EXPR( false, wError );
	MessageBox( nullptr, error, "�x��", MB_OK );
}