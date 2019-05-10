//=============================================================================
//
// ブロック処理 [block.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "blockPos.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"
#include "particle3D.h"
#include "particleX.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BLOCK_NAME	"data\\MODEL\\woodBox.x"	// ブロックのモデル名
#define BLOCK_ALPHA		(0.7f)				// 透明度
#define BLOCK_ALPHASPEED		(0.01f)				// 透明度

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXMESH CBlockPos::m_pMesh = NULL;		// メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER CBlockPos::m_pBuffMat = NULL;	// マテリアル情報へのポインタ
DWORD CBlockPos::m_nNumMat = 0;			// マテリアル情報の数
LPDIRECT3DTEXTURE9 *CBlockPos::m_pTexture = 0;			// テクスチャ情報

//=============================================================================
// ブロッククラスのコンストラクタ
//=============================================================================
CBlockPos::CBlockPos() : CSceneX(5)
{
	// 値をクリア
	m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	D3DXMatrixIdentity(&m_mtxWorld);		// ワールドマトリックス
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_VtxMin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_VtxMax = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_bFall = true;
	m_nCntFall = 0;
	m_nCntTime = 0;
	m_fAlpha = 0.0f;
	m_fAlphaSpeed = 0.0f;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBlockPos::~CBlockPos()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CBlockPos *CBlockPos::Create(D3DXVECTOR3 pos)
{
	CBlockPos *pBlock = NULL;

	if (pBlock == NULL)
	{
		// オブジェクトクラスの生成
		pBlock = new CBlockPos;

		if (pBlock != NULL)
		{
			pBlock->SetPosition(pos);
			pBlock->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pBlock->BindMat(m_pTexture);
			pBlock->Init();
		}
	}

	return pBlock;
}

//=============================================================================
// ブロック初期化処理
//=============================================================================
HRESULT CBlockPos::Init(void)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_BLOCK);

	// 初期化処理
	CSceneX::Init();

	m_bFall = true;

	m_nCntFall = 0;
	m_nCntTime = 0;
	m_fAlpha = BLOCK_ALPHA;
	m_fAlphaSpeed = BLOCK_ALPHASPEED;

	return S_OK;
}

//=============================================================================
// ブロック終了処理
//=============================================================================
void CBlockPos::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// ブロック更新処理
//=============================================================================
void CBlockPos::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ゲームのモードを取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	// 位置を取得
	m_pos = CSceneX::GetPosition();

	CScene *pScene = NULL;

	// 先頭のオブジェクトを取得(モデルの優先順位が1だから、1にあるオブジェクトをすべて見る)
	pScene = CScene::GetTop(PLAYER_PRIORITY);

	while (pScene != NULL)
	{// 優先順位が3のオブジェクトを1つ1つ確かめる
	 // 処理の最中に消える可能性があるから先に記録しておく
		CScene *pSceneNext = pScene->GetNext();

		if (pScene->GetDeath() == false)
		{// 死亡フラグが立っていないもの
			if (pScene->GetObjType() == CScene::OBJTYPE_PLAYER)
			{// オブジェクトの種類を確かめる
				m_pos = ((CPlayer*)pScene)->GetBlockPos();
			}
		}
		// 次のシーンに進める
		pScene = pSceneNext;
	}

	SetPosition(m_pos);

	m_fAlpha -= m_fAlphaSpeed;

	if (m_fAlpha <= 0.2f)
	{
		m_fAlphaSpeed *= -1.0f;
	}
	if (m_fAlpha > BLOCK_ALPHA)
	{
		m_fAlphaSpeed *= -1.0f;
	}
}

//=============================================================================
// ブロック描画処理
//=============================================================================
void CBlockPos::Draw(void)
{
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;					// マテリアルデータへのポインタ

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

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
	{
		// マテリアルの設定
		pMat[nCntMat].MatD3D.Diffuse.a = m_fAlpha;
	}

	CSceneX::Draw();

	// 頂点法線の自動正規化	終了
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//=============================================================================
// ブロックのモデル読み込み処理
//=============================================================================
HRESULT CBlockPos::LoadModel(void)
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
	D3DXLoadMeshFromX(BLOCK_NAME,
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
void CBlockPos::UnloadModel(void)
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
HRESULT CBlockPos::LoadMat(void)
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
void CBlockPos::UnloadMat(void)
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
D3DXVECTOR3 CBlockPos::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CBlockPos::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}