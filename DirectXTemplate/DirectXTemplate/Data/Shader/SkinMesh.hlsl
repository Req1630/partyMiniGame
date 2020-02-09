/***************************************************************************************************
*	SkinMeshCode Version 2.00
*	LastUpdate	: 2019/10/09
*	Auther		: an.
**/
//��`.
#define MAX_BONE_MATRICES (255)

//�O���[�o��.
Texture2D		g_Texture	: register( t0 );	//�e�N�X�`���[�� ���W�X�^�[t(n).
SamplerState	g_Sampler	: register( s0 );	//�T���v���[�̓��W�X�^�[s(n).


//�R���X�^���g�o�b�t�@(���b�V������).
cbuffer per_mesh		: register( b0 )
{
	matrix g_mW;		//���[���h�s��.
	matrix g_mWVP;		//���[���h����ˉe�܂ł̕ϊ��s��.
};
//�R���X�^���g�o�b�t�@(�}�e���A������).
cbuffer per_material	: register( b1 )
{
	float4 g_Ambient	= float4( 0, 0, 0, 0 );	//�A���r�G���g��.
	float4 g_Diffuse	= float4( 1, 0, 0, 0 );	//�g�U����(�F�j
	float4 g_Specular	= float4( 1, 1, 1, 1 );	//���ʔ���.
};
//�R���X�^���g�o�b�t�@(�t���[������).
cbuffer per_frame		: register( b2 )
{
	float4 g_vLight;//���C�g�̕����x�N�g��.
	float4 g_vEye;	//�J�����ʒu.
};
//�{�[���̃|�[�Y�s�񂪓���.
cbuffer per_bones		: register( b3 )
{
	matrix g_mConstBoneWorld[MAX_BONE_MATRICES];
};

//�X�L�j���O��̒��_�E�@��������.
struct Skin
{
	float4 Pos;
	float3 Norm;
};
//�o�[�e�b�N�X�o�b�t�@�[�̓���.
struct VSSkinIn
{
	float3 Pos		: POSITION;		//�ʒu.  
	float3 Norm		: NORMAL;		//���_�@��.
	float2 Tex		: TEXCOORD;		//�e�N�X�`���[���W.
	uint4  Bones	: BONE_INDEX;	//�{�[���̃C���f�b�N�X.
	float4 Weights	: BONE_WEIGHT;	//�{�[���̏d��.
};

//�s�N�Z���V�F�[�_�[�̓��́i�o�[�e�b�N�X�o�b�t�@�[�̏o�́j�@
struct PSSkinIn
{
	float4 Pos	: SV_Position;	//�ʒu.
	float3 Norm : NORMAL;		//���_�@��.
	float2 Tex	: TEXCOORD;		//�e�N�X�`���[���W.
	float4 Color: COLOR0;		//�ŏI�J���[�i���_�V�F�[�_�[�ɂ����Ắj.
};


//�w�肵���ԍ��̃{�[���̃|�[�Y�s���Ԃ�.
//�T�u�֐��i�o�[�e�b�N�X�V�F�[�_�[�Ŏg�p�j.
matrix FetchBoneMatrix( uint iBone )
{
	return g_mConstBoneWorld[iBone];
}


//���_���X�L�j���O�i�{�[���ɂ��ړ��j����.
//�T�u�֐��i�o�[�e�b�N�X�V�F�[�_�[�Ŏg�p�j.
Skin SkinVert( VSSkinIn Input )
{
	Skin Output = (Skin)0;

	float4 Pos = float4(Input.Pos,1);
	float3 Norm = Input.Norm;
	//�{�[��0.
	uint iBone	=Input.Bones.x;
	float fWeight= Input.Weights.x;
	matrix m	=  FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );
	//�{�[��1.
	iBone	= Input.Bones.y;
	fWeight	= Input.Weights.y;
	m		= FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );
	//�{�[��2.
	iBone	= Input.Bones.z;
	fWeight	= Input.Weights.z;
	m		= FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );
	//�{�[��3.
	iBone	= Input.Bones.w;
	fWeight	= Input.Weights.w;
	m		= FetchBoneMatrix( iBone );
	Output.Pos	+= fWeight * mul( Pos, m );
	Output.Norm	+= fWeight * mul( Norm, (float3x3)m );

	return Output;
}

// �o�[�e�b�N�X�V�F�[�_.
PSSkinIn VS_Main( VSSkinIn input )
{
	PSSkinIn output;
	Skin vSkinned = SkinVert( input);

	output.Pos	= mul( vSkinned.Pos, g_mWVP );
	output.Norm	= normalize( mul( vSkinned.Norm, (float3x3)g_mW ) );
	output.Tex	= input.Tex;
	float3 LightDir	= normalize( g_vLight );
	float3 PosWorld	= mul( vSkinned.Pos, g_mW );
	float3 ViewDir	= normalize( g_vEye - PosWorld );
	float3 Normal	= normalize( output.Norm );
	float4 NL		= saturate( dot( Normal, LightDir ) );

	float3 Reflect	= normalize( 2 * NL * Normal - LightDir );
	float4 specular = pow( saturate( dot( Reflect, ViewDir ) ), 4.0f ); 

	output.Color	= g_Diffuse * NL + specular * g_Specular;

	return output;
}


// �s�N�Z���V�F�[�_.
float4 PS_Main( PSSkinIn input ) : SV_Target
{
	// �e�N�X�`������s�N�Z���F�����o��.
	float4 TexDiffuse = g_Texture.Sample( g_Sampler, input.Tex );
	// �o�͗p���쐬.
	float4 RetColor = input.Color/2.0f + TexDiffuse/2.0f;

	// �e�N�X�`���̃��l�����̂܂܎g�p�B
	RetColor.a = TexDiffuse.a;

	return RetColor;
}
