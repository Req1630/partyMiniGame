#ifndef D3DX_H
#define D3DX_H

#include "..\..\Global.h"

class CD3DX
{
private: //----- �萔 ------.
	const float CLEAR_BACK_COLOR[4] = { 0.1f, 0.1f, 0.1f, 1.0f };	// �o�b�N�J���[.

public: //----- �֐� ------.
	CD3DX();
	~CD3DX();

	// �쐬�֐�.
	HRESULT Init( HWND hWnd );
	// ����֐�.
	HRESULT Destroy();

	// �N���A�o�b�N�o�b�t�@.
	void ClearBackBuffer();
	// �X���b�v�`�F�[���v���[���g.
	void SwapChainPresent();

	// �f�o�C�X11�̎擾�֐�.
	static ID3D11Device*		GetDevice11() { return m_pDevice11; }
	// �R���e�L�X�g11�̎擾�֐�.
	static ID3D11DeviceContext*	GetContext11() { return m_pContext11; }
	// �f�o�C�X9�̎擾�֐�.
	static LPDIRECT3DDEVICE9	GetDevice9() { return m_pDevice9; }

private: //----- �֐� ------.
	// �f�o�C�X9�̍쐬.
	HRESULT InitDevice9();
	// �f�o�C�X11�̍쐬.
	HRESULT InitDevice11();
	// �����_�[�^�[�Q�b�g�r���[�̍쐬.
	HRESULT InitTexRTV();
	// �X�e���V���r���[�̍쐬.
	HRESULT InitDSTex();
	// �r���[�|�[�g�̍쐬.
	HRESULT InitViewports();
	// ���X�^���C�U�̍쐬.
	HRESULT InitRasterizer();

private: //----- �ϐ� ------.
	HWND	m_hWnd;	// �E�B���h�E�n���h��.

	static ID3D11Device*		m_pDevice11;	// �f�o�C�X11.
	static ID3D11DeviceContext*	m_pContext11;	// �R���e�L�X�g11.
	static LPDIRECT3DDEVICE9	m_pDevice9;		// �f�o�C�X9.

	IDXGISwapChain*			m_pSwapChain;			// �X���b�v�`�F�[��.

	ID3D11RenderTargetView*	m_pBackBuffer_TexRTV;	// �����_�[�^�[�Q�b�g�r���[.
	ID3D11Texture2D*		m_pBackBuffer_DSTex;	// �e�N�X�`���[2D.
	ID3D11DepthStencilView*	m_pBackBuffer_DSTexDSV;	// �X�e���V���r���[.
	
};

#endif	// #ifndef D3DX_H.