//=============================================================================
//
// 3Dモデル処理 [sceneObject.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "sceneObject.h"
#include "input.h"
#include "object.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"

//=============================================================================
// マクロ定義
//=============================================================================
#define MAX_Y	(200.0f)	//見えない壁の高さ

//=============================================================================
// 3Dモデルクラスのコンストラクタ
//=============================================================================
CSceneObject::CSceneObject(int nPriority, OBJTYPE objType) : CScene(nPriority, objType)
{
	// 値をクリア
	m_pTexture = NULL;						// テクスチャへのポインタ
	m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	m_pMesh = NULL;							// メッシュ情報（頂点情報）へのポインタ
	m_pBuffMat = NULL;						// マテリアル情報へのポインタ
	m_nNumMat = 0;							// マテリアル情報の数
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_nType = 0;
	m_bCollision = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CSceneObject::~CSceneObject()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CSceneObject *CSceneObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh)
{
	CSceneObject *pSceneObject = NULL;

	if (pSceneObject == NULL)
	{
		// オブジェクトクラスの生成
		pSceneObject = new CSceneObject;

		if (pSceneObject != NULL)
		{
			pSceneObject->m_pos = pos;
			pSceneObject->m_rot = rot;
			pSceneObject->BindModel(pBuffMat, nNumMat, pMesh);
			pSceneObject->Init();
		}
	}

	return pSceneObject;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CSceneObject::Init(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// 頂点座標の設定
	SetVtx();

	// 設置されているオブジェクトのタイプを取得
	m_nType = CObject::GetObjType();

	// 当たっていない判定にする
	m_bCollision = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CSceneObject::Uninit(void)
{
	if (m_pTexture != NULL)
	{// テクスチャのポインタのNULLチェック(家)
		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			if (m_pTexture[nCntMat] != NULL)
			{// ポインタの中のNULLチェック(家具)
				m_pTexture[nCntMat]->Release();
				m_pTexture[nCntMat] = NULL;
			}
		}

		// メモリの開放(解体)
		delete[] m_pTexture;
		// NULLにする(更地)
		m_pTexture = NULL;
	}

	// オブジェクトの解放
	Release();
}

//=============================================================================
// 更新処理
//=============================================================================
void CSceneObject::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void CSceneObject::Draw(void)
{
	D3DXMATRIX mtxRot, mtxTrans;				// 計算用マトリックス
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;							// マテリアルデータへのポインタ

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		if (pMat[nCntMat].pTextureFilename != NULL)
		{// マテリアルにテクスチャがあった場合
		 // テクスチャの設定
			pDevice->SetTexture(0, m_pTexture[nCntMat]);
		}
		else
		{// マテリアルにテクスチャが無かった場合
			pDevice->SetTexture(0, NULL);
		}

		// モデル(パーツ)の描画
		m_pMesh->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CSceneObject::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CSceneObject::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// タイプの取得
//=============================================================================
int CSceneObject::GetType(void)
{
	return m_nType;
}

//=============================================================================
// タイプの取得
//=============================================================================
void CSceneObject::SetType(int nType)
{
	m_nType = nType;
}

//=============================================================================
// 向きの取得
//=============================================================================
D3DXVECTOR3 CSceneObject::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// 向きの設定
//=============================================================================
void CSceneObject::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// モデルを割り当てる
//=============================================================================
void CSceneObject::BindModel(LPD3DXBUFFER pBuffMat, DWORD nNumMat, LPD3DXMESH pMesh)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	m_pBuffMat = pBuffMat;
	m_nNumMat = nNumMat;
	m_pMesh = pMesh;

	D3DXMATERIAL *pMat;					// マテリアルデータへのポインタ

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	if (m_pTexture != NULL)
	{// テクスチャの情報が入っていたら空にする
		delete[] m_pTexture;
		m_pTexture = NULL;
	}
	// マテリアルの数分テクスチャを入れるものを動的に確保
	m_pTexture = new LPDIRECT3DTEXTURE9[m_nNumMat];

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// 入れる前に空にする
		m_pTexture[nCntMat] = NULL;

		if (pMat[nCntMat].pTextureFilename != NULL)
		{
			// テクスチャの生成
			D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_pTexture[nCntMat]);
		}
	}
}

//=============================================================================
// 頂点座標の設定処理
//=============================================================================
void CSceneObject::SetVtx(void)
{
	DWORD sizeFvF;	//頂点フォーマットのサイズ
	D3DXVECTOR3 vtx;
	int nNumVtx;	//頂点数
	BYTE *pVtxBuff;	//頂点バッファへのポインタ

	// 頂点数を取得
	nNumVtx = m_pMesh->GetNumVertices();
	// 頂点フォーマットのサイズを取得
	sizeFvF = D3DXGetFVFVertexSize(m_pMesh->GetFVF());

	// 頂点の最小値と最大値を代入
	m_VtxMin = D3DXVECTOR3(10000, 10000, 10000);
	m_VtxMax = D3DXVECTOR3(-10000, -10000, -10000);

	//頂点バッファをロック
	m_pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

	for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
	{//頂点座標の代入
		vtx = *(D3DXVECTOR3*)pVtxBuff;

		if (m_VtxMin.x > vtx.x)
		{
			m_VtxMin.x = vtx.x;
		}
		if (m_VtxMin.y > vtx.y)
		{
			m_VtxMin.y = vtx.y;
		}
		if (m_VtxMin.z > vtx.z)
		{
			m_VtxMin.z = vtx.z;
		}

		if (m_VtxMax.x < vtx.x)
		{
			m_VtxMax.x = vtx.x;
		}
		if (m_VtxMax.y < vtx.y)
		{
			m_VtxMax.y = vtx.y;
		}
		if (m_VtxMax.z < vtx.z)
		{
			m_VtxMax.z = vtx.z;
		}

		//サイズ分ポインタを進める
		pVtxBuff += sizeFvF;
	}
	//頂点バッファをアンロック
	m_pMesh->UnlockVertexBuffer();
}

//=============================================================================
// 当たり判定
//=============================================================================
bool CSceneObject::Collision(D3DXVECTOR3 *pos, D3DXVECTOR3 *posOld, D3DXVECTOR3 *move, D3DXVECTOR3 radius)
{
	bool bCol = false;

	D3DXVECTOR3 ScaleVtxMax;
	D3DXVECTOR3 ScaleVtxMin;

	// 拡大を反映
	ScaleVtxMax.x = m_VtxMax.x * m_mtxWorld._11;
	ScaleVtxMax.y = m_VtxMax.y * m_mtxWorld._22;
	ScaleVtxMax.z = m_VtxMax.z * m_mtxWorld._33;
	ScaleVtxMin.x = m_VtxMin.x * m_mtxWorld._11;
	ScaleVtxMin.y = m_VtxMin.y * m_mtxWorld._22;
	ScaleVtxMin.z = m_VtxMin.z * m_mtxWorld._33;

	if (pos->y <= m_pos.y + ScaleVtxMax.y + MAX_Y && pos->y + radius.y >= m_pos.y + ScaleVtxMax.y + MAX_Y
		|| pos->y + radius.y >= m_pos.y + ScaleVtxMin.y && pos->y <= m_pos.y + ScaleVtxMin.y
		|| pos->y + radius.y <= m_pos.y + ScaleVtxMax.y + MAX_Y && pos->y >= m_pos.y + ScaleVtxMin.y)
	{// yの範囲の中
		if (pos->z - radius.z <= m_pos.z + ScaleVtxMax.z && pos->z + radius.z >= m_pos.z + ScaleVtxMin.z)
		{// zの範囲の中
			if (posOld->x + radius.x <= m_pos.x + ScaleVtxMin.x
				&& pos->x + radius.x > m_pos.x + ScaleVtxMin.x)
			{// X座標の中に左から入った
				pos->x = posOld->x;
				move->x = 0.0f;
			}
			else if (posOld->x - radius.x >= m_pos.x + ScaleVtxMax.x
				&& pos->x - radius.x < m_pos.x + ScaleVtxMax.x)
			{// X座標の中に右から入った
				pos->x = posOld->x;
				move->x = 0.0f;
			}
		}
		if (pos->x - radius.x <= m_pos.x + ScaleVtxMax.x && pos->x + radius.x >= m_pos.x + ScaleVtxMin.x)
		{// xの範囲の中
			if (posOld->z + radius.z <= m_pos.z + ScaleVtxMin.z
				&& pos->z + radius.z > m_pos.z + ScaleVtxMin.z)
			{// Z座標の中に手前から入った
				pos->z = posOld->z;
				move->z = 0.0f;
			}
			else if (posOld->z - radius.z >= m_pos.z + ScaleVtxMax.z
				&& pos->z - radius.z < m_pos.z + ScaleVtxMax.z)
			{// Z座標の中に後ろから入った
				pos->z = posOld->z;
				move->z = 0.0f;
			}
		}
	}

	return bCol;	// ブロックに乗っているかどうかを返す
}