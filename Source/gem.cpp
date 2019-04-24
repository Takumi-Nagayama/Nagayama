//=============================================================================
//
// 宝石処理 [gem.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "gem.h"
#include "input.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "camera.h"
#include "scene3D.h"
#include "meshField.h"
#include "player.h"
#include "game.h"
#include "coin.h"
#include "particle3D.h"
#include "sound.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define GEM_NAME			"data\\MODEL\\gem.x"	// 宝石のモデル名
#define GEM_ROTATION		(0.05f)					// 宝石の回転スピード
#define GEM_PARTICLE_MAX	(3)						// パーティクルの出る量
#define GEM_PARTICLE_COLOR	(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f))	// パーティクルの色
#define GEM_PARTICLE_SIZE	(10.0f)					// パーティクルのサイズ
#define GEM_PARTICLE_LIFE	(20)					// パーティクルの出現時間

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXMESH CGem::m_pMesh = NULL;		// メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER CGem::m_pBuffMat = NULL;	// マテリアル情報へのポインタ
DWORD CGem::m_nNumMat = 0;			// マテリアル情報の数
bool CGem::m_bGet = false;			// 獲得できるかどうか

//=============================================================================
// 宝石クラスのコンストラクタ
//=============================================================================
CGem::CGem() : CSceneX(GEM_PRIORITY)
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
CGem::~CGem()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CGem *CGem::Create(D3DXVECTOR3 pos)
{
	CGem *pGem = NULL;

	if (pGem == NULL)
	{
		// オブジェクトクラスの生成
		pGem = new CGem;

		if (pGem != NULL)
		{
			pGem->SetPosition(pos);
			pGem->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pGem->Init();
		}
	}

	return pGem;
}

//=============================================================================
// 宝石初期化処理
//=============================================================================
HRESULT CGem::Init(void)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_GEM);

	// 初期化処理
	CSceneX::Init();

	m_bGet = false;			// 獲得できるかどうか
	m_bSound = true;

	return S_OK;
}

//=============================================================================
// 宝石終了処理
//=============================================================================
void CGem::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// 宝石更新処理
//=============================================================================
void CGem::Update(void)
{
	// 入力情報を取得
	CInputKeyboard *pInputKeyboard;
	pInputKeyboard = CManager::GetInputKeyboard();

	// ゲームのモードを取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	// 音楽情報を取得
	CSound *pSound;
	pSound = CManager::GetSound();

	if (CCoin::GetNumCoin() <= 0)
	{// 獲得できる状態にする
		if (m_bSound == true)
		{
			pSound->PlaySound(CSound::SOUND_LABEL_SE_TIMEGEM);
			m_bSound = false;
		}
		m_bGet = true;
	}

	// 回転
	m_rot.y += GEM_ROTATION;

	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2.0f;
	}
	if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2.0f;
	}

	if (CCamera::GetGem() == true)
	{
		for (int nCntParticle = 0; nCntParticle < GEM_PARTICLE_MAX; nCntParticle++)
		{
			CParticle3D::Create(D3DXVECTOR3(CSceneX::GetPosition().x, CSceneX::GetPosition().y - 10.0f, CSceneX::GetPosition().z),
				D3DXVECTOR3(sinf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1))),
				GEM_PARTICLE_COLOR,
				GEM_PARTICLE_SIZE,
				GEM_PARTICLE_SIZE,
				GEM_PARTICLE_LIFE,
				CParticle3D::TYPE_UP,
				CParticle3D::TYPE_EFFECT);
		}
	}

	SetRot(m_rot);
}

//=============================================================================
// 宝石描画処理
//=============================================================================
void CGem::Draw(void)
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


	if (m_bGet == false)
	{
		CSceneX::Draw();

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			// マテリアルの設定
			pMat[nCntMat].MatD3D.Diffuse.a = 0.4f;
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			// モデル(パーツ)の描画
			m_pMesh->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
	else
	{
		CSceneX::Draw();

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			// マテリアルの設定
			pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
			pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

			//テクスチャの設定
			pDevice->SetTexture(0, NULL);

			// モデル(パーツ)の描画
			m_pMesh->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}

	// 頂点法線の自動正規化	終了
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//=============================================================================
// 宝石との当たり判定処理
//=============================================================================
bool CGem::Collision(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;	// 当たっていない状態

	if (m_bGet == true)
	{
		// 中心と中心の差を求める
		D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - CSceneX::GetPosition().x, pos->y - CSceneX::GetPosition().y - 20.0f, pos->z - CSceneX::GetPosition().z);

		// 中心から中心のベクトルの長さを算出
		float fLength = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

		if (fLength < fRadius + m_VtxMax.x && fLength < fRadius + m_VtxMax.y && fLength < fRadius + m_VtxMax.z)
		{// 長さが半径の和より小さければ当たっている
			bHit = true;
		}
	}

	return bHit;	// 宝石に当たっているかどうかを返す
}

//=============================================================================
// 宝石のモデル読み込み処理
//=============================================================================
HRESULT CGem::LoadModel(void)
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
	D3DXLoadMeshFromX(GEM_NAME,
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
// 宝石のモデル解放処理
//=============================================================================
void CGem::UnloadModel(void)
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
// 位置の取得
//=============================================================================
D3DXVECTOR3 CGem::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CGem::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 獲得できるかどうかの取得
//=============================================================================
bool CGem::GetGem(void)
{
	return m_bGet;
}