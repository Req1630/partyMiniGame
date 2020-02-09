#ifndef MAIN_H
#define MAIN_H

#include <memory>
#include <string>

#include "..\Global.h"

//-------------------------.
//	�O���錾.
class CD3DX;
class CFrameRate;
class CLoadManager;
namespace scene { class CSceneManager; }
//-------------------------.

/**************************************************
*	Ҳݸ׽.
**/
class CMain
{
	std::string WND_TITLE;
	std::string APP_NAME;
	const char* WINDOW_INFO_TEXT_PATH = "Data\\WindowInfo.txt";
public:
	CMain();
	~CMain();
	// �E�B���h�E�������֐�.
	HRESULT InitWindow( HINSTANCE hInstance );

	// ���b�Z�[�W���[�v.
	void Loop();

	HRESULT Init();
	void Destroy();

private:
	// �X�V����.
	void Update();
	// �`�揈��.
	void Render();

	// ���b�V���̓ǂݍ��݊֐�.
	HRESULT Load();

	// �E�B���h�E���ǂݍ���.
	void ReadWindowInfo();

private:
	HWND m_hWnd;

	std::unique_ptr<CD3DX>		m_pD3DX;		// DirectX�֌W.
	// Dx11.
	ID3D11Device*				m_pDevice11;	// �f�o�C�X "11".
	ID3D11DeviceContext*		m_pContext11;	// �R���e�L�X�g "11".
	// Dx9.
	LPDIRECT3DDEVICE9			m_pDevice9;		// �f�o�C�X "9".

	std::unique_ptr<CFrameRate>	m_pFrameRate;	// �t���[�����[�g.
	std::shared_ptr<CCamera>	m_pCamera;		// �J�����N���X.

	LIGHT m_Light;	// ���C�g���.

	std::shared_ptr<scene::CSceneManager>	m_pSceneManager;
	std::unique_ptr<CLoadManager>	m_pLoadManager;
};

#endif	// #ifndef MAIN_H.
