#include "GameObject.h"

CGameObject::CGameObject()
	: m_vPosition	{ 0.0f, 0.0f, 0.0f }
	, m_vRotation	{ 0.0f, 0.0f, 0.0f }
	, m_pCollider	( nullptr )
	, m_ModelScale	( 1.0f )
{}

CGameObject::~CGameObject()
{}