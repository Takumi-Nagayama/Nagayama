//=============================================================================
//
// 障害物の処理 [obstacle.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "main.h"
#include "sceneX.h"

//========================================
// クラスの定義
//========================================
//=====================
// ブロッククラス
//=====================
class CObstacle : public CSceneX
{
public:
	CObstacle();								// コンストラクタ
	~CObstacle();								// デストラクタ

	HRESULT Init(void);						// プレイヤー初期化処理
	void Uninit(void);						// プレイヤー終了処理
	void Update(void);						// プレイヤー更新処理
	void Draw(void);						// プレイヤー描画処理

	static HRESULT LoadObstacle(void);				// テクスチャ読み込み
	static void UnloadObstacle(void);				// テクスチャ解放

	static CObstacle *Create(D3DXVECTOR3 pos);	// オブジェクトの生成

private:
	static LPD3DXMESH		m_pMesh;			// メッシュ情報（頂点情報）へのポインタ
	static LPD3DXBUFFER		m_pBuffMat;			// マテリアル情報へのポインタ
	static DWORD			m_nNumMat;			// マテリアル情報の数
	D3DXVECTOR3				m_rot;				// 向き
	LPDIRECT3DTEXTURE9		m_pTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;			// 頂点バッファへのポインタ
	D3DXVECTOR3				m_VtxMin, m_VtxMax;	// ブロックの最小値、最大値
	bool					m_bLand;			// ブロックに乗っているかどうか

	D3DXMATRIX				m_mtxWorld;		// ワールドマトリックス
};

#endif