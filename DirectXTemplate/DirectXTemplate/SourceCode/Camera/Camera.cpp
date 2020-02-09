#include "Camera.h"

CCamera::CCamera()
	: m_ViewMatrix			()
	, m_ProjMatrix			()
	, m_vPosition			()
	, m_vLookPosition		()
	, m_ViewingAngle		( INITIAL_VIEWING_ANGLE )
	, m_MaxClippingDistance	( INITIAL_MAX_CLIPPING_DISTANCE )
	, m_MinClippingDistance	( INITIAL_MIN_CLIPPING_DISTANCE )
{
}

CCamera::~CCamera()
{
}

//--------------------------------------------.
// �J�����̍X�V����.
//--------------------------------------------.
void CCamera::Update()
{
	if( GetAsyncKeyState('C') & 0x8000 ){
		if( GetAsyncKeyState(VK_UP) & 0x8000 ) m_vPosition.x += 0.1f;
		if( GetAsyncKeyState(VK_DOWN) & 0x8000 ) m_vPosition.x -= 0.1f;
		if( GetAsyncKeyState(VK_RIGHT) & 0x8000 ) m_vPosition.z += 0.1f;
		if( GetAsyncKeyState(VK_LEFT) & 0x8000 ) m_vPosition.z -= 0.1f;
	}
}

//--------------------------------------------.
// �r���[�s��A�v���W�F�N�V�����s��̏�����.
//--------------------------------------------.
void CCamera::InitViewProj()
{
	// �r���[(�J����)�ϊ�.
	D3DXMatrixLookAtLH( 
		&m_ViewMatrix,		// (out)viewMarix.
		&m_vPosition,		// �J�������W.
		&m_vLookPosition,	// �J�����������W.
		&VIEW_UP_VECTOR );	// �J�����x�N�g��.

	// �v���W�F�N�V����(�ˉe)�ϊ�.
	D3DXMatrixPerspectiveFovLH(
		&m_ProjMatrix,				// (out)ProjMatrix.
		m_ViewingAngle,				// ����p.
		SCREEN_ASPECT_RATIO,		// ��ʃA�X�y�N�g��.
		m_MinClippingDistance,		// �ŏ��`�拗��.
		m_MaxClippingDistance );	// �ő�`�拗��.
}

//--------------------------------------------.
// �p����̃J�������̐ݒ�֐�.
//--------------------------------------------.
void CCamera::SetCamera( std::shared_ptr<CCamera> camera )
{
	this->m_vPosition		= camera->GetPosition();
	this->m_vLookPosition	= camera->GetLookPosition();
}