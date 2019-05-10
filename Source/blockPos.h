//=============================================================================
//
// ブロック処理 [block.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _BLOCKPOS_H_
#define _BLOCKPOS_H_

#include "main.h"
#include "sceneX.h"

//========================================
// クラスの定義
//========================================
//=====================
// ブロッククラス
//=====================
class CBlockPos : public CSceneX
{
public:
	CBlockPos();								// コンストラクタ
	~CBlockPos();								// デストラクタ

	HRESULT Init(void);						// プレイヤー初期化処理
	void Uninit(void);						// プレイヤー終了処理
	void Update(void);						// プレイヤー更新処理
	void Draw(void);						// プレイヤー描画処理

	static HRESULT LoadModel(void);				// テクスチャ読み込み
	static void UnloadModel(void);				// テクスチャ解放

	static HRESULT LoadMat(void);				// マテリアル読み込み
	static void UnloadMat(void);				// マテリアル解放

	static CBlockPos *Create(D3DXVECTOR3 pos);	// オブジェクトの生成

	D3DXVECTOR3 GetPos(void);						// 位置の取得
	void SetPos(D3DXVECTOR3 pos);					// 位置の設定

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
	bool					m_bFall;			// 落ちているかどうか
	int						m_nCntFall;			// 落ちている時間をカウント
	int						m_nCntTime;			// 消えるカウント
	float						m_fAlpha;			// 透明度
	float						m_fAlphaSpeed;		// 透明度

	D3DXMATRIX				m_mtxWorld;		// ワールドマトリックス
};

#endif