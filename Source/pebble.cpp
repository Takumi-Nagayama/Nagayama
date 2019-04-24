//=============================================================================
//
// ブロック処理 [block.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "pebble.h"
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
#define PEBBLE_NAME	"data\\MODEL\\OBJECT\\pebble.x"	// ブロックのモデル名

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXMESH CPebble::m_pMesh = NULL;		// メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER CPebble::m_pBuffMat = NULL;	// マテリアル情報へのポインタ
DWORD CPebble::m_nNumMat = 0;			// マテリアル情報の数
LPDIRECT3DTEXTURE9 *CPebble::m_pTexture = 0;			// テクスチャ情報

//=============================================================================
// プレイヤークラスのコンストラクタ
//=============================================================================
CPebble::CPebble()
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
CPebble::~CPebble()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CPebble *CPebble::Create(D3DXVECTOR3 pos,D3DXVECTOR3 rot)
{
	CPebble *pPebble = NULL;

	if (pPebble == NULL)
	{
		// オブジェクトクラスの生成
		pPebble = new CPebble;

		if (pPebble != NULL)
		{
			pPebble->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pPebble->BindMat(m_pTexture);
			pPebble->Init();
			pPebble->SetPosition(pos);
			pPebble->SetRot(rot);
		}
	}

	return pPebble;
}

//=============================================================================
// ブロック初期化処理
//=============================================================================
HRESULT CPebble::Init(void)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_PEBBLE);

	// 初期化処理
	CSceneX::Init();

	return S_OK;
}

//=============================================================================
// ブロック終了処理
//=============================================================================
void CPebble::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// ブロック更新処理
//=============================================================================
void CPebble::Update(void)
{
}

//=============================================================================
// ブロック描画処理
//=============================================================================
void CPebble::Draw(void)
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
// ブロックのモデル読み込み処理
//=============================================================================
HRESULT CPebble::LoadModel(void)
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
	D3DXLoadMeshFromX(PEBBLE_NAME,
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
// ブロックのモデル解放処理
//=============================================================================
void CPebble::UnloadModel(void)
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
// ブロックのモデル読み込み処理
//=============================================================================
HRESULT CPebble::LoadMat(void)
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
// ブロックのモデル解放処理
//=============================================================================
void CPebble::UnloadMat(void)
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