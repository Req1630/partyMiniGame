#ifndef DX9_STATIC_MESH_H
#define DX9_STATIC_MESH_H

#include "..\..\Common.h"

//ү���ް���̧�ق�����o���ׂ�����DirectX9���g�p����.
//�������ݸ�(�`��)�́ADirectX11�ōs��.
class CDX9StaticMesh : public CCommon
{
public:
	CDX9StaticMesh( 
		HWND hWnd, 
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11, 
		LPDIRECT3DDEVICE9 pDevice9,
		const char* fileName )
		: CDX9StaticMesh()
	{
		Init( hWnd, pDevice11, pContext11, pDevice9, fileName );
	}

	CDX9StaticMesh();	//�ݽ�׸�.
	~CDX9StaticMesh();	//�޽�׸�.

	HRESULT Init(
		HWND hWnd, 
		ID3D11Device* pDevice11,
		ID3D11DeviceContext* pContext11, 
		LPDIRECT3DDEVICE9 pDevice9,
		const char* fileName );

	//ү���ǂݍ���.
	HRESULT LoadXMesh(const char* fileName);
	//����֐�.
	void Release();

	//����ލ쐬.
	HRESULT InitShader();

	//�����ݸޗp.
	void Render( std::shared_ptr<CCamera> pCamera, LIGHT& Light );

	//ү�����擾.
	LPD3DXMESH GetMesh() const { return m_pMeshForRay; }
	
private:
	//======================================
	//	�\����.
	//======================================
	//�ݽ����ޯ̧�̱��ؑ��̒�`.
	//������ޓ��̺ݽ����ޯ̧�ƈ�v���Ă���K�v����.
	//ү���P�ʂœn�����.
	struct CBUFFER_PER_MESH
	{
		D3DXMATRIX	mW;			//ܰ��ލs��.
		D3DXMATRIX	mWVP;		//ܰ���,�ޭ�,��ۼު���݂̍����ϊ��s��.	
	};
	//��رْP�ʂœn�����.
	struct CBUFFER_PER_MATERIAL
	{
		D3DXVECTOR4 vAmbient;	//���޴�ĐF(���F).
		D3DXVECTOR4	vDiffuse;	//�ި̭��ސF(�g�U���ːF).
		D3DXVECTOR4	vSpecular;	//��߷�אF(���ʔ��ːF).
	};
	//�ڰђP�ʂœn�����.ײ�,̫�ޏ��͂����ɓ����.
	struct CBUFFER_PER_FRAME
	{
		D3DXVECTOR4	vCamPos;		//��׈ʒu(���_�ʒu).
		D3DXVECTOR4	vLightDir;		//ײĕ���.
		ALIGN16 float fIntensity;	//ײċ��x(���邳).
	};

	//���_�̍\����.
	struct VERTEX
	{
		D3DXVECTOR3 Pos;	//���_���W.
		D3DXVECTOR3	Normal;	//�@��(�A�e�v�Z�ɕK�{).
		D3DXVECTOR2	Tex;	//ø������W.
	};
	//��رٍ\����.
	struct MY_MATERIAL
	{
		D3DXVECTOR4	Ambient;	//���޴��.
		D3DXVECTOR4	Diffuse;	//�ި̭���.
		D3DXVECTOR4	Specular;	//��߷��.
		char szTextureName[64];	//ø���̧�ٖ�.
		ID3D11ShaderResourceView* pTexture;//ø���.
		DWORD dwNumFace;		//������رق���غ�ݐ�.
		//�ݽ�׸�.
		MY_MATERIAL()
			: Ambient(),Diffuse(),Specular(),szTextureName()
			, pTexture(nullptr),dwNumFace(0)
		{
		}
		//�޽�׸�.
		~MY_MATERIAL() 
		{
//			SAFE_RELEASE(pTexture);
		}
	};
	
	HWND				m_hWnd;		//����޳�����.

	//Dx9.
	LPDIRECT3DDEVICE9	m_pDevice9;	//Dx9���޲���޼ު��.

	ID3D11VertexShader*		m_pVertexShader;	//���_�����.
	ID3D11InputLayout*		m_pVertexLayout;	//���_ڲ���.
	ID3D11PixelShader*		m_pPixelShader;		//�߸�ټ����.
	ID3D11Buffer*			m_pCBufferPerMesh;		//�ݽ����ޯ̧(ү����).
	ID3D11Buffer*			m_pCBufferPerMaterial;	//�ݽ����ޯ̧(��رٖ�).
	ID3D11Buffer*			m_pCBufferPerFrame;		//�ݽ����ޯ̧(�ڰі�).

	ID3D11Buffer*				m_pVertexBuffer;	//���_�ޯ̧.
	ID3D11Buffer**				m_ppIndexBuffer;	//���ޯ���ޯ̧.
	ID3D11SamplerState*			m_pSampleLinear;	//�����:ø����Ɋe��̨����������.

	LPD3DXMESH			m_pMesh;		//ү����޼ު��.
	LPD3DXMESH			m_pMeshForRay;	//ڲ��ү���p.
	DWORD				m_NumMaterials;	//��رِ�.

	MY_MATERIAL*	m_pMaterials;	//��رٍ\����.
	DWORD			m_NumAttr;		//������.
	DWORD			m_AttrID[300];	//����ID ��300�����܂�.

	bool			m_EnableTexture;//ø�������.

	//�����ݸފ֐�(�׽���ł̂ݎg�p����).
	void RenderMesh(
		D3DXMATRIX& mWorld, 
		const D3DXMATRIX& mView, 
		const D3DXMATRIX& mProj);
 };

#endif	// #ifndef DX9_STATIC_MESH_H.