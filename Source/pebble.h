//=============================================================================
//
// 小石処理 [pebble.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _PEBBLE_H_
#define _PEBBLE_H_

#include "main.h"
#include "sceneX.h"

//========================================
// クラスの定義
//========================================
//=====================
// ブロッククラス
//=====================
class CPebble : public CSceneX
{
public:
	CPebble();								// コンストラクタ
	~CPebble();								// デストラクタ

	HRESULT Init(void);						// プレイヤー初期化処理
	void Uninit(void);						// プレイヤー終了処理
	void Update(void);						// プレイヤー更新処理
	void Draw(void);						// プレイヤー描画処理

	static HRESULT LoadModel(void);				// テクスチャ読み込み
	static void UnloadModel(void);				// テクスチャ解放

	static HRESULT LoadMat(void);				// マテリアル読み込み
	static void UnloadMat(void);				// マテリアル解放

	static CPebble *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);	// オブジェクトの生成

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

	D3DXMATRIX				m_mtxWorld;		// ワールドマトリックス
};

#endif