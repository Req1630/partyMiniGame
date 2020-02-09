#include "RotLookAtCenter.h"
#include "..\..\Utility\MyVector\MyVector.h"

CRotLookAtCenter::CRotLookAtCenter()
	: m_vDegree			{ 0.0f, 0.0f }
	, m_Length			( DEFAULT_LENGTH )
	, m_HorizontalMax	( DEFAULT_HORIZONTAL_MAX )
	, m_HorizontalMin	( DEFAULT_HORIZONTAL_MIN )
	, m_VerticalMax		( DEFAULT_VERTICAL_MAX )
	, m_VerticalMin		( DEFAULT_VERTICAL_MIN )
{
}

CRotLookAtCenter::~CRotLookAtCenter()
{
}

//-------------------------------.
// �I�u�W�F�N�g���𒍎��ɉ�].
//-------------------------------.
void CRotLookAtCenter::RotationLookAtObject( const D3DXVECTOR3& vLookPos )
{
	// �����ʒu���擾.
	m_vLookPosition = vLookPos;

	// �J�����ʒu���Z�o.
	m_vPosition.x = m_vLookPosition.x + ( sinf(m_vDegree.x) * m_Length );
	m_vPosition.y = m_vLookPosition.y + ( sinf(m_vDegree.y) * m_Length );
	m_vPosition.z = m_vLookPosition.z + ( cosf(m_vDegree.x) * m_Length );
}

//-------------------------------.
// �������̉�].
//-------------------------------.
void CRotLookAtCenter::DegreeHorizontalMove( const float& movePower )
{
	// �������ɑ������킹��.
	m_vDegree.x += movePower;

	// �I�[�o�[�t���[�΍�.
	CVector::OverflowDegree( m_vDegree.y, 
		 m_HorizontalMax, m_HorizontalMin, 
		-m_HorizontalMax, m_HorizontalMin );
}

//-------------------------------.
// �c�����̉�].
//-------------------------------.
void CRotLookAtCenter::DegreeVerticalMove( const float& movePower )
{
	// �c�����ɑ������킹��.
	m_vDegree.y += movePower;

	// �I�[�o�[�t���[�΍�.
	CVector::OverflowDegree( m_vDegree.y, 
		m_VerticalMax, m_VerticalMax, 
		m_VerticalMin, m_VerticalMin );
}

//-------------------------------.
// �J�����ƒ����_�̒����ݒ�.
//-------------------------------.
void CRotLookAtCenter::SetLength( const float& length )
{
	m_Length = length;
}

//-------------------------------.
// �������̍ő�A�ŏ��̐ݒ�.
//-------------------------------.
void CRotLookAtCenter::SetHorizontalDegree( const float& max, const float& min )
{
	m_HorizontalMax	= max;
	m_HorizontalMin	= min;
}

//-------------------------------.
// �c�����̍ő�A�ŏ��̐ݒ�.
//-------------------------------.
void CRotLookAtCenter::SetVerticalDegree( const float& max, const float& min )
{	
	m_VerticalMax = max;
	m_VerticalMin = min;
}