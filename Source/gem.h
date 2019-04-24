//=============================================================================
//
// 宝石処理 [gem.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _GEM_H_
#define _GEM_H_

#include "main.h"
#include "sceneX.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GEM_PRIORITY	(6)

//========================================
// クラスの定義
//========================================
//=====================
// ブロッククラス
//=====================
class CGem : public CSceneX
{
public:
	CGem();								// コンストラクタ
	~CGem();								// デストラクタ

	HRESULT Init(void);						// コイン初期化処理
	void Uninit(void);						// コイン終了処理
	void Update(void);						// コイン更新処理
	void Draw(void);						// コイン描画処理

	static HRESULT LoadModel(void);				// モデル読み込み
	static void UnloadModel(void);				// モデル解放

	static CGem *Create(D3DXVECTOR3 pos);	// オブジェクトの生成

	D3DXVECTOR3 GetPos(void);						// 位置の取得
	void SetPos(D3DXVECTOR3 pos);					// 位置の設定

	static bool GetGem(void);						// 獲得できるかどうかの取得

	bool CGem::Collision(D3DXVECTOR3 *pos, float fRadius);

private:
	static LPD3DXMESH		m_pMesh;			// メッシュ情報（頂点情報）へのポインタ
	static LPD3DXBUFFER		m_pBuffMat;			// マテリアル情報へのポインタ
	static DWORD			m_nNumMat;			// マテリアル情報の数
	static bool				m_bGet;				// 獲得できるかどうか
	bool					m_bSound;			// 音が鳴る状態かどうか
	D3DXVECTOR3				m_pos;				// 位置
	D3DXVECTOR3				m_move;				// 移動量
	D3DXVECTOR3				m_rot;				// 向き
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// ブロックの最小値、最大値
	D3DXVECTOR3				m_scale;			// 拡大率

	D3DXMATRIX				m_mtxWorld;		// ワールドマトリックス
};

#endif