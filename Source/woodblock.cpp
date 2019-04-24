//=============================================================================
//
// 木ブロック処理 [woodblock.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "woodblock.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define WOODBLOCK_NAME	"data\\MODEL\\woodBox001.x"	// 木ブロックのモデル名
#define BLOCKSIZE	(15.0f)					// 木ブロックのサイズ

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXMESH CWoodBlock::m_pMesh = NULL;		// メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER CWoodBlock::m_pBuffMat = NULL;	// マテリアル情報へのポインタ
DWORD CWoodBlock::m_nNumMat = 0;			// マテリアル情報の数
LPDIRECT3DTEXTURE9 *CWoodBlock::m_pTexture = NULL;			// テクスチャ情報

//=============================================================================
// 木ブロッククラスのコンストラクタ
//=============================================================================
CWoodBlock::CWoodBlock()
{
	// 値をクリア
	m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	D3DXMatrixIdentity(&m_mtxWorld);		// ワールドマトリックス
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}

//=============================================================================
// デストラクタ
//=============================================================================
CWoodBlock::~CWoodBlock()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CWoodBlock *CWoodBlock::Create(D3DXVECTOR3 pos)
{
	CWoodBlock *pBlock = NULL;

	if (pBlock == NULL)
	{
		// オブジェクトクラスの生成
		pBlock = new CWoodBlock;

		if (pBlock != NULL)
		{
			pBlock->SetPosition(pos);
			pBlock->m_pos = pos;
			pBlock->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pBlock->BindMat(m_pTexture);
			pBlock->Init();
		}
	}

	return pBlock;
}

//=============================================================================
// 木ブロック初期化処理
//=============================================================================
HRESULT CWoodBlock::Init(void)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_WOODBLOCK);

	// 初期化処理
	CSceneX::Init();

	return S_OK;
}

//=============================================================================
// 木ブロック終了処理
//=============================================================================
void CWoodBlock::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// 木ブロック更新処理
//=============================================================================
void CWoodBlock::Update(void)
{
}

//=============================================================================
// 木ブロック描画処理
//=============================================================================
void CWoodBlock::Draw(void)
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

	// 頂点法線の自動正規化	開始
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	CSceneX::Draw();

	// 頂点法線の自動正規化	終了
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//=============================================================================
// 木ブロックとの当たり判定処理
//=============================================================================
bool CWoodBlock::CollisionBreak(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;	// 当たっていない状態

	// 中心と中心の差を求める
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - m_pos.x, pos->y - m_pos.y - 50.0f, pos->z - m_pos.z);

	// 中心から中心のベクトルの長さを算出
	float fLength = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (fLength < fRadius + m_VtxMax.x && fLength < fRadius + m_VtxMax.y && fLength < fRadius + m_VtxMax.z)
	{// 長さが半径の和より小さければ当たっている
		bHit = true;
	}

	return bHit;	// 木ブロックに当たっているかどうかを返す
}

//=============================================================================
// 木ブロックのモデル読み込み処理
//=============================================================================
HRESULT CWoodBlock::LoadModel(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// Xファイルの読み込み
	D3DXLoadMeshFromX(WOODBLOCK_NAME,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_nNumMat,
		&m_pMesh);

	return S_OK;
}

//=============================================================================
// 木ブロックのモデル解放処理
//=============================================================================
void CWoodBlock::UnloadModel(void)
{
	// メッシュの開放
	if (m_pMesh != NULL)
	{
		m_pMesh->Release();
		m_pMesh = NULL;
	}

	// マテリアルの開放
	if (m_pBuffMat != NULL)
	{
		m_pBuffMat->Release();
		m_pBuffMat = NULL;
	}
}

//=============================================================================
// 木ブロックのモデル読み込み処理
//=============================================================================
HRESULT CWoodBlock::LoadMat(void)
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


	D3DXMATERIAL *pMat;					// マテリアルデータへのポインタ

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

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

	return S_OK;
}

//=============================================================================
// 木ブロックのモデル解放処理
//=============================================================================
void CWoodBlock::UnloadMat(void)
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
}

//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CWoodBlock::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CWoodBlock::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}