//=============================================================================
//
// ブロックの出現位置表示処理 [blockPos.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "blockPos.h"
#include "manager.h"
#include "renderer.h"
#include "scene2D.h"
#include "player.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURENAME000			"data\\TEXTURE\\woodBox.jpg"	//テクスチャのファイル名

//--------------------------------------------
//静的メンバ変数宣言
//--------------------------------------------
LPDIRECT3DTEXTURE9	CBlockPos::m_pTexture = NULL;

//--------------------------------------------
// ブロックの出現位置表示コンストラクタ
//--------------------------------------------
CBlockPos::CBlockPos()
{
	m_pos = D3DXVECTOR3(0, 0, 0);			//位置
	m_rot = D3DXVECTOR3(0, 0, 0);		//向き
	D3DXMatrixIdentity(&m_mtxWorld);	//ワールドマトリックス
}

//--------------------------------------------
// ブロックの出現位置表示デストラクタ
//--------------------------------------------
CBlockPos::~CBlockPos()
{
}

//=============================================================================
// 生成処理
//=============================================================================
CBlockPos * CBlockPos::Create(D3DXVECTOR3 pos, float fDepth, float fWifth, float fTextureU, float fTextureV, D3DXCOLOR col)
{
	CBlockPos *pBlockPos = NULL;

	if (pBlockPos == NULL)
	{
		// 地面クラスの生成
		pBlockPos = new CBlockPos;

		if (pBlockPos != NULL)
		{
			pBlockPos->SetDepth(fDepth);
			pBlockPos->SetWidth(fWifth);
			pBlockPos->SetTextureU(fTextureU);
			pBlockPos->SetTextureV(fTextureV);
			pBlockPos->SetPos(pos);
			pBlockPos->Init();								// 初期化処理
			pBlockPos->SetCol(col);				// 種類の設定
			pBlockPos->BindTexture(m_pTexture);				// 種類の設定
		}
	}
	return pBlockPos;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CBlockPos::Init(void)
{
	// 2Dオブジェクト初期化処理
	CPolygon::Init();

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_BLOCKPOS);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CBlockPos::Uninit(void)
{
	// 2Dオブジェクト終了処理
	CPolygon::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CBlockPos::Update(void)
{
	// ゲームのモードを取得
	CManager::MODE mode;
	mode = CManager::GetMode();

	// 位置を取得
	m_pos = CPolygon::GetPos();

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


	SetPos(D3DXVECTOR3(m_pos.x, m_pos.y + 1.0f, m_pos.z));
}

//=============================================================================
// 描画処理
//=============================================================================
void CBlockPos::Draw(void)
{
	// 2Dオブジェクト描画処理
	CPolygon::Draw();
}

//=============================================================================
// 位置設定処理
//=============================================================================
void CBlockPos::Setpos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// テクスチャロード処理
//=============================================================================
HRESULT CBlockPos::Load(void)
{
	//デバイスを取得
	CRenderer *pRenderer = CManager::GetRenderer();
	LPDIRECT3DDEVICE9 pDevice = pRenderer->GetDevice();

	//テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice, TEXTURENAME000, &m_pTexture);

	return S_OK;
}
//=============================================================================
// テクスチャ破棄処理
//=============================================================================
void CBlockPos::UnLoad(void)
{
	// テクスチャの破棄
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}
