#ifndef CHARACTER_H
#define CHARACTER_H

#include "..\GameObject.h"

class CCharacter : public CGameObject
{
public:
	CCharacter();
	virtual ~CCharacter();

protected:
	// ˆÚ“®ŠÖ”.
	virtual void Move() = 0;
};

#endif	// #ifndef CHARACTER_H.