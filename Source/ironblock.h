//=============================================================================
//
// 鉄ブロック処理 [ironblock.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _IRONBLOCK_H_
#define _IRONBLOCK_H_

#include "main.h"
#include "sceneX.h"

//========================================
// クラスの定義
//========================================
//=====================
// ブロッククラス
//=====================
class CIronBlock : public CSceneX
{
public:
	CIronBlock();								// コンストラクタ
	~CIronBlock();								// デストラクタ

	HRESULT Init(void);						// 鉄ブロック初期化処理
	void Uninit(void);						// 鉄ブロック終了処理
	void Update(void);						// 鉄ブロック更新処理
	void Draw(void);						// 鉄ブロック描画処理

	static HRESULT LoadModel(void);				// テクスチャ読み込み
	static void UnloadModel(void);				// テクスチャ解放

	static HRESULT LoadMat(void);				// マテリアル読み込み
	static void UnloadMat(void);				// マテリアル解放

	static CIronBlock *Create(D3DXVECTOR3 pos);	// オブジェクトの生成

	D3DXVECTOR3 GetPos(void);						// 位置の取得
	void SetPos(D3DXVECTOR3 pos);					// 位置の設定

	bool CollisionBreak(D3DXVECTOR3 *pos, float fRadius);	// 当たり判定

private:
	static LPD3DXMESH		m_pMesh;			// メッシュ情報（頂点情報）へのポインタ
	static LPD3DXBUFFER		m_pBuffMat;			// マテリアル情報へのポインタ
	static DWORD			m_nNumMat;			// マテリアル情報の数
	static LPDIRECT3DTEXTURE9		*m_pTexture;			// テクスチャへのポインタ
	D3DXVECTOR3				m_pos;				// 位置
	D3DXVECTOR3				m_move;				// 移動量
	D3DXVECTOR3				m_rot;				// 向き
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// ブロックの最小値、最大値
	bool					m_bLand;			// ブロックに乗っているかどうか

	D3DXMATRIX				m_mtxWorld;		// ワールドマトリックス
};

#endif