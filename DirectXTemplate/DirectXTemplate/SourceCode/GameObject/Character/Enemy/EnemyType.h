#ifndef ENEMY_TYPE_H
#define ENEMY_TYPE_H

// 敵の種類.
enum class enENEMY_TYPE
{
	None,		// 何もなし.
	
	RUN = None,	// 走る.
	SHOOT,		// 撃つ.

	Max,		// 最大.
};

// 敵がどの方向に移動するか.
enum class enENEMY_DIRECTION
{
	None,		// 何もなし.

	UP = None,	// 上方向.
	DOWN,		// 下方向.
	RIGHT,		// 右方向.
	LEFT,		// 左方向.

	Max,		// 最大.
};

#endif	// #ifndef ENEMY_TYPE_H.