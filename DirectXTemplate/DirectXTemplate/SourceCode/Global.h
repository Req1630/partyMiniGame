#pragma once

//警告についてのｺｰﾄﾞ分析を無効にする.4005:再定義.
#pragma warning(disable:4005)
#include <Windows.h>
#include <crtdbg.h>
#include <memory>

#include <D3DX11.h>
#include <D3D11.h>
#include <D3DX10.h>	//「D3DX～」の定義使用時に必要.
#include <D3D10.h>
#include <d3dx9.h>

//ﾗｲﾌﾞﾗﾘ読み込み.
#pragma comment( lib, "winmm.lib" )
#pragma comment( lib, "d3dx11.lib" )
#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "d3dx10.lib" )	//「D3DX～」の定義使用時に必要.
#pragma comment( lib, "d3d9.lib" )
#pragma comment( lib, "d3dx9.lib" )

//=================================================
//	定数.
//=================================================
const int WND_W = 1280;	//ｳｨﾝﾄﾞｳの幅.
const int WND_H = 720;	//ｳｨﾝﾄﾞｳの高さ.

class CCamera;
class CDX9SkinMesh;
class CDX9StaticMesh;

//ﾗｲﾄ情報.
struct LIGHT
{
	D3DXVECTOR3	vPos;		//位置.
	D3DXVECTOR3	vDir;		//方向.
	D3DXMATRIX	mRot;		//回転行列.
	float		fIntensity;	//強度(明るさ).
};

//===========================================================
//	ﾏｸﾛ.
//===========================================================
//解放.
#define SAFE_RELEASE(p)			if(p!=nullptr){(p)->Release();(p)=nullptr;}
//破棄.
#define SAFE_DELETE(p)			if(p!=nullptr){delete (p);(p)=nullptr;}
#define SAFE_DELETE_ARRAY(p)	if(p!=nullptr){delete[] (p);(p) = nullptr;}
//_declspec()	:DLLから(関数,ｸﾗｽ,ｸﾗｽのﾒﾝﾊﾞ関数を)ｴｸｽﾎﾟｰﾄする.
//align()		:(強制的に)16byte で使用する.
#define ALIGN16	_declspec(align(16))

template<class T = const char*>
void ERROR_MESSAGE ( const T& error )
{
	size_t charSize = strlen(error)+1;
	if( charSize >= 128 ) _ASSERT_EXPR( false, L"エラー文が長いです" );

	wchar_t wError[128];
	size_t ret;
	mbstowcs_s( &ret, wError, charSize, error, _TRUNCATE );
	_ASSERT_EXPR( false, wError );
	MessageBox( nullptr, error, "警告", MB_OK );
}