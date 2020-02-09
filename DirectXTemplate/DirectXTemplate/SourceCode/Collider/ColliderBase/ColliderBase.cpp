#include "ColliderBase.h"

CColliderBase::CColliderBase()
	: m_pvPosition		( nullptr )
	, m_vAdjPosition	{ 0.0f, 0.0f, 0.0f }
	, m_pvRotation		( nullptr )
	, m_pScale			( nullptr )
{
}

CColliderBase::~CColliderBase()
{
}