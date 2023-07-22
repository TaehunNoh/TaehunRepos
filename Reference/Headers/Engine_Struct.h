#pragma once

namespace Engine
{
	typedef struct tagGraphicDesc
	{
		enum WINMODE { MODE_FULL, MODE_WIN, MODE_END };

		HWND hWnd;
		WINMODE eWinMode;
		unsigned int iWinSizeX;
		unsigned int iWinSizeY;
	}GRAPHICDESC;

	typedef struct tagLightDesc
	{
		enum TYPE { TYPE_DIRECTION, TYPE_POINT, TYPE_END };

		TYPE			eType;
		XMFLOAT4		vLightDir;
		XMFLOAT4		vLightDiffuse;
		XMFLOAT4		vLightAmbient;
		XMFLOAT4		vLightSpecular;

	}LIGHTDESC;

	typedef struct tagMeshMaterial
	{
		class CTexture* pTexture[AI_TEXTURE_TYPE_MAX];
	}MESHMATERIALS;

	typedef struct tagKeyFrame
	{
		double		dTime;
		XMFLOAT3	vScale;
		XMFLOAT4	vRotation;
		XMFLOAT3	vPosition;
	}KEYFRAME;

#pragma region Buffer

	typedef struct tagVertex_Position
	{
		XMFLOAT3 vPosition;
	}VTXPOS;

	typedef struct ENGINE_DLL tagVertex_Position_Declaration
	{
		const static unsigned int iNumElements = { 1 };
		static D3D11_INPUT_ELEMENT_DESC Elements[1];
	}VTXPOS_DECL;

	typedef struct tagVertex_Position_UV
	{
		XMFLOAT3 vPosition;
		XMFLOAT2 vUV;
	}VTXTEX;

	typedef struct ENGINE_DLL tagVertex_Position_UV_Declaration
	{
		const static unsigned int iNumElements = { 2 };
		static D3D11_INPUT_ELEMENT_DESC Elements[2];
	}VTXTEX_DECL;

	typedef struct tagVertex_Position_Normal_UV
	{
		XMFLOAT3 vPosition;
		XMFLOAT3 vNormal;
		XMFLOAT2 vUV;
	}VTXNORTEX;

	typedef struct ENGINE_DLL tagVertex_Position_Normal_UV_Declaration
	{
		const static unsigned int iNumElements = { 3 };
		static D3D11_INPUT_ELEMENT_DESC Elements[3];
	}VTXNORTEX_DECL;

	typedef struct tagVertex_Position_Cube_UV
	{
		XMFLOAT3		vPosition;
		XMFLOAT3		vUV;
	}VTXCUBETEX;

	typedef struct ENGINE_DLL tagVertex_Position_Cube_UV_Declaration
	{
		const static unsigned int			iNumElements = { 2 };
		static D3D11_INPUT_ELEMENT_DESC		Elements[2];
	}VTXCUBETEX_DECL;

	typedef struct tagVertex_Model
	{
		XMFLOAT3 vPosition;
		XMFLOAT3 vNormal;
		XMFLOAT2 vUV;
		XMFLOAT3 vTangent;
	}VTXMODEL;

	typedef struct ENGINE_DLL tagVertex_Model_Declaration
	{
		const static unsigned int iNumElements = { 4 };
		static D3D11_INPUT_ELEMENT_DESC Elements[4];
	}VTXMODEL_DECL;

	typedef struct tagVertex_Animation_Model
	{
		XMFLOAT3	vPosition;
		XMFLOAT3	vNormal;
		XMFLOAT2	vUV;
		XMFLOAT3	vTangent;
		XMUINT4		vBlendIndices;
		XMFLOAT4	vBlendWeights;
	}VTXANIMMODEL;

	typedef struct ENGINE_DLL tagVertex_Animation_Model_Declaration
	{
		const static unsigned int iNumElements = { 6 };
		static D3D11_INPUT_ELEMENT_DESC Elements[6];
	}VTXANIMMODEL_DECL;

	typedef struct tagVertex_Instance
	{
		XMFLOAT4		vRight;
		XMFLOAT4		vUp;
		XMFLOAT4		vLook;
		XMFLOAT4		vTranslation;
		XMFLOAT4		vColor;
		XMFLOAT2		vPSize;
		float			fAngle;
	}VTXINSTANCE;

	typedef struct ENGINE_DLL tagVertex_Rect_Instance_Declaration
	{
		static const unsigned int			iNumElements = { 9 };
		static D3D11_INPUT_ELEMENT_DESC		Elements[9];
	}VTXRECTINSTANCE_DECL;

	typedef struct ENGINE_DLL tagVertex_Point_Instance_Declaration
	{
		const static unsigned int			iNumElements = { 8 };
		static D3D11_INPUT_ELEMENT_DESC		Elements[8];
	}VTXPOINTINSTANCE_DECL;

#pragma endregion
}

