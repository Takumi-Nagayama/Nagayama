//=============================================================================
//
// 餌の処理 [feed.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _FEED_H_
#define _FEED_H_

#include "model3D.h"
#include "camerabace.h"
#include "shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define FEED_PRIOTITY				(3)

//*****************************************************************************
// 前方宣言
//*****************************************************************************
class CObjBillboad;

//=====================
//  CModel3Dの派生クラス
//=====================
class CFeed : public CModel3D
{
public:
	typedef enum
	{// 餌の種類
		FEEDTYPE_ATTACK = 0,	// 攻撃
		FEEDTYPE_ANNOY,			// 妨害
		FEEDTYPE_SPEED,			// 加速
		FEEDTYPE_MAX,			//最大数
	}FEEDTYPE;

	CFeed();
	~CFeed();
	static HRESULT Load(void);
	static void UnLoad(void);
	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	static CFeed *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXVECTOR3 scale, FEEDTYPE feedType);
	bool CollisionFeed(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld);
	FEEDTYPE GetFeedType(void) { return m_feedType; }

private:
	static LPD3DXMESH	m_pMeshModel[FEEDTYPE_MAX];		//メッシュ情報へのポインタ
	static LPD3DXBUFFER m_pBuffMatModel[FEEDTYPE_MAX];	//マテリアルの情報へのポインタ
	static DWORD		m_nNumMatModel[FEEDTYPE_MAX];	//マテリアルの情報数
	static LPDIRECT3DTEXTURE9 m_pMeshTextures;			//テクスチャ情報
	static D3DXVECTOR3 m_VtxMaxModel[FEEDTYPE_MAX];		//モデルの最大値
	static D3DXVECTOR3 m_VtxMinModel[FEEDTYPE_MAX];		//モデルの最小値

	FEEDTYPE			m_feedType;						// 餌の種類
	D3DXVECTOR3			m_scale;						// 大きさ
	D3DXVECTOR3			m_rot;							// 回転
	CShadow				*m_pShadow;						// 影のポインタ
	CObjBillboad *		m_pObjBill;						// オブジェクトビルボードのポインタ
};
#endif