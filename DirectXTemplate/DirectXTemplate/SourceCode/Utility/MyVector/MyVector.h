#ifndef MY_VECTOR_H
#define MY_VECTOR_H

class CVector
{
public:
	inline static const double PI = 3.14159265358979323846;

public:
	CVector(){};
	~CVector(){};

	// ラジアンに変換.
	template<class T>
	static T ToRadian( const T& t )
	{ return t * (static_cast<T>(PI/180.0)); }

	// ディグリーに変換.
	template<class T>
	static T ToDegree( const T& t )
	{ return t * (static_cast<T>(180.0/PI)); }

	// ディグリーでのオーバーフロー対策.
	template<class T, class VOver1, class V1, class VOver2, class V2>
	static void OverflowDegree( T& t, 
		const VOver1& vOver1, const V1& vAdj1,
		const VOver2& vOver2, const V2& vAdj2 )
	{
		if( t > CVector::ToRadian(vOver1) )
			t = CVector::ToRadian(vAdj1);
		if( t < CVector::ToRadian(vOver2) )
			t = CVector::ToRadian(vAdj2);
	}
};

#endif	// #ifndef MY_VECTOR_H.