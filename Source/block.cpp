//=============================================================================
//
// ブロック処理 [block.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "block.h"
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
#define COUNT_FALL	(20)						// 20フレームを超すまで落ちる
#define SPEED_FALL	(50.0f)						// 落ちるスピード
#define UNINIT_TIME0	(100)					// 消えるスピード
#define UNINIT_TIME1	(90)					// 消えるサイン
#define NUM_PARTICLE_X	(100)					// 破壊パーティクルの数
#define LIFE_PARTICLE_X	(20)					// 破壊パーティクルの出現時間
#define NUM_PARTICLE_3D	(50)					// 消滅サインパーティクルの数
#define LIFE_PARTICLE_3D	(20)				// 消滅サインパーティクルの出現時間
#define SIZE_PARTICLE_3D	(5.0f)				// 消滅サインパーティクルのサイズ

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPD3DXMESH CBlock::m_pMesh = NULL;		// メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER CBlock::m_pBuffMat = NULL;	// マテリアル情報へのポインタ
DWORD CBlock::m_nNumMat = 0;			// マテリアル情報の数
LPDIRECT3DTEXTURE9 *CBlock::m_pTexture = 0;			// テクスチャ情報

//=============================================================================
// ブロッククラスのコンストラクタ
//=============================================================================
CBlock::CBlock()
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
	m_State = STATE_NORMAL;
	m_nCntTime = 0;
}

//=============================================================================
// デストラクタ
//=============================================================================
CBlock::~CBlock()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CBlock *CBlock::Create(D3DXVECTOR3 pos, STATE state)
{
	CBlock *pBlock = NULL;

	if (pBlock == NULL)
	{
		// オブジェクトクラスの生成
		pBlock = new CBlock;

		if (pBlock != NULL)
		{
			pBlock->SetPosition(pos);
			pBlock->BindModel(m_pBuffMat, m_nNumMat, m_pMesh);
			pBlock->BindMat(m_pTexture);
			pBlock->Init();
			pBlock->m_State = state;
		}
	}

	return pBlock;
}

//=============================================================================
// ブロック初期化処理
//=============================================================================
HRESULT CBlock::Init(void)
{
	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_BLOCK);

	// 初期化処理
	CSceneX::Init();

	m_bFall = true;

	m_nCntFall = 0;

	m_State = STATE_NORMAL;
	m_nCntTime = 0;

	return S_OK;
}

//=============================================================================
// ブロック終了処理
//=============================================================================
void CBlock::Uninit(void)
{
	CSceneX::Uninit();
}

//=============================================================================
// ブロック更新処理
//=============================================================================
void CBlock::Update(void)
{
	// ゲームのモードを取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	// 位置を取得
	m_pos = CSceneX::GetPosition();

	if (m_State == STATE_NORMAL)
	{
		StateNormal();
	}
	else if (m_State == STATE_PLAYER)
	{
		StatePlayer();
	}

	SetPosition(m_pos);
}

//=============================================================================
// ブロック描画処理
//=============================================================================
void CBlock::Draw(void)
{
	D3DMATERIAL9 matDef;						// 現在のマテリアル保存用
	D3DXMATERIAL *pMat;					// マテリアルデータへのポインタ

	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	CManager::MODE mode;
	mode = CManager::GetMode();

	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// 頂点法線の自動正規化	開始
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);

	if (m_State == STATE_PLAYER)
	{
		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			// マテリアルの設定
			pMat[nCntMat].MatD3D.Diffuse.a = 0.5f;
		}

		CSceneX::Draw();
	}
	else if(m_State == STATE_NORMAL)
	{
		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)m_pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_nNumMat; nCntMat++)
		{
			// マテリアルの設定
			pMat[nCntMat].MatD3D.Diffuse.a = 1.0f;
		}

		CSceneX::Draw();
	}

	// 頂点法線の自動正規化	終了
	pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, FALSE);
}

//=============================================================================
// ブロックとの当たり判定処理
//=============================================================================
bool CBlock::CollisionBreak(D3DXVECTOR3 *pos, float fRadius)
{
	bool bHit = false;	// 当たっていない状態

	// 中心と中心の差を求める
	D3DXVECTOR3 DiffLength = D3DXVECTOR3(pos->x - m_pos.x, pos->y - m_pos.y - 20.0f, pos->z - m_pos.z);

	// 中心から中心のベクトルの長さを算出
	float fLength = sqrtf((DiffLength.x * DiffLength.x) + (DiffLength.y * DiffLength.y) + (DiffLength.z * DiffLength.z));

	if (fLength < fRadius + m_VtxMax.x && fLength < fRadius + m_VtxMax.y && fLength < fRadius + m_VtxMax.z)
	{// 長さが半径の和より小さければ当たっている
		if (m_State == STATE_NORMAL)
		{
			bHit = true;
		}
	}

	return bHit;	// ブロックに当たっているかどうかを返す
}

//=============================================================================
// ブロックのモデル読み込み処理
//=============================================================================
HRESULT CBlock::LoadModel(void)
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
void CBlock::UnloadModel(void)
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
HRESULT CBlock::LoadMat(void)
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
void CBlock::UnloadMat(void)
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
// 通常
//=============================================================================
void CBlock::StateNormal(void)
{
	// ゲームのモードを取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	if (mode == CManager::MODE_TITLE || mode == CManager::MODE_RANKING)
	{
		if (m_bFall == true)
		{
			m_nCntFall++;
			m_pos.y -= SPEED_FALL;

			if (m_nCntFall > COUNT_FALL)
			{
				m_bFall = false;
				m_nCntFall = 0;
			}
		}
	}
	if (mode == CManager::MODE_GAME || mode == CManager::MODE_TUTORIAL)
	{
		m_nCntTime++;

		if (m_nCntTime / 60 > UNINIT_TIME0)
		{
			for (int nCntParticle = 0; nCntParticle < NUM_PARTICLE_X; nCntParticle++)
			{
				CParticleX::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z),
					D3DXVECTOR3(sinf(D3DX_PI * PARTICLE_ROT), cosf(D3DX_PI * PARTICLE_ROT), cosf(D3DX_PI * PARTICLE_ROT)),
					D3DXVECTOR3(sinf(PARTICLE_ROT) * ((rand() % 7 + 1)), cosf(PARTICLE_ROT) * ((rand() % 7 + 1)), cosf(PARTICLE_ROT) * ((rand() % 7 + 1))),
					LIFE_PARTICLE_X,
					CParticleX::TYPE_DOWN);
			}

			Uninit();

			m_nCntTime = 0;
		}

		if (m_nCntTime / 60 > UNINIT_TIME1)
		{
			if ((m_nCntTime % 60) == 0)
			{
				for (int nCntParticle = 0; nCntParticle < NUM_PARTICLE_3D; nCntParticle++)
				{
					CParticle3D::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 30.0f, m_pos.z),
						D3DXVECTOR3(sinf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1)), cosf(PARTICLE_ROT) * ((rand() % 5 + 1))),
						D3DXCOLOR(1.0f, 0.5f, 0.5f, 0.7f),
						SIZE_PARTICLE_3D,
						SIZE_PARTICLE_3D,
						LIFE_PARTICLE_3D,
						CParticle3D::TYPE_NORMAL,
						CParticle3D::TYPE_EFFECT);
				}
			}
		}
	}
}

//=============================================================================
// プレイヤー
//=============================================================================
void CBlock::StatePlayer(void)
{
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
}

//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CBlock::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CBlock::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 落ちているかどうかの取得
//=============================================================================
bool CBlock::GetFall(void)
{
	return m_bFall;
}

//=============================================================================
// 落ちているかどうかの設定
//=============================================================================
void CBlock::SetFall(bool bFall)
{
	m_bFall = bFall;
}

//=============================================================================
// 状態の取得
//=============================================================================
CBlock::STATE CBlock::GetState(void)
{
	return m_State;
}