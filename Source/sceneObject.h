//=============================================================================
//
// 3Dモデル処理 [sceneObject.h]
// Author : 長山拓実
//
//=============================================================================
#ifndef _SCENEOBJECT_H_
#define _SCENEOBJECT_H_

#include "main.h"
#include "scene.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************

//========================================
// クラスの定義
//========================================
//=====================
// オブジェクトクラス
//=====================
class CSceneObject : public CScene
{
public:
	CSceneObject(int nPriority = SCENEOBJ_PRIORITY, OBJTYPE objType = OBJTYPE_OBJECT);		// コンストラクタ
	~CSceneObject();														// デストラクタ

	HRESULT Init(void);														// 3Dオブジェクト初期化処理
	void Uninit(void);														// 3Dオブジェクト終了処理
	void Update(void);														// 3Dオブジェクト更新処理
	void Draw(void);														// 3Dオブジェクト描画処理
	
	static CSceneObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh);			// オブジェクトの生成

	bool Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius);					// 当たり判定
	void SetVtx(void);														// 頂点座標の設定

	D3DXVECTOR3 GetPos(void);												// 位置の取得
	void SetPos(D3DXVECTOR3 pos);											// 位置の設定

	D3DXVECTOR3 GetRot(void);												// 向きの取得
	void SetRot(D3DXVECTOR3 rot);											// 向きの設定

	int GetType(void);														// タイプの取得
	void SetType(int nType);

	void BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh);	// モデルを割り当てる
private:
	LPDIRECT3DTEXTURE9		*m_pTexture;									// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;										// 頂点バッファへのポインタ
	LPD3DXMESH				m_pMesh;										// メッシュ情報（頂点情報）へのポインタ
	LPD3DXBUFFER			m_pBuffMat;										// マテリアル情報へのポインタ
	D3DXMATRIX				m_mtxWorld;										// ワールドマトリックス
	DWORD					m_nNumMat;										// マテリアル情報の数
	bool					m_bCollision;									// 当たっているかどうか
	int						m_nType;
	D3DXVECTOR3				m_VtxMin, m_VtxMax;								// モデルの最小値、最大値

	D3DXVECTOR3				m_pos;											// ポリゴンの位置
	D3DXVECTOR3				m_rot;											// 上方向ベクトル
};

#endif