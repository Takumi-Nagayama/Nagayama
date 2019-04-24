//=============================================================================
//
// 3Dモデル処理 [object.cpp]
// Author : 長山拓実
//
//=============================================================================
#include "object.h"
#include "input.h"
#include "block.h"
#include "renderer.h"
#include "manager.h"
#include "debugProc.h"
#include "game.h"
#include "camera.h"
#include "text.h"

//=============================================================================
// 静的メンバ変数宣言
//=============================================================================
LPDIRECT3DTEXTURE9 CObject::m_apTexture[SETOBJTYPE_MAX] = {};	// マテリアル情報へのポインタ
LPD3DXMESH CObject::m_apMesh[SETOBJTYPE_MAX] = {};		// メッシュ情報（頂点情報）へのポインタ
LPD3DXBUFFER CObject::m_apBuffMat[SETOBJTYPE_MAX] = {};	// マテリアル情報へのポインタ
DWORD CObject::m_anNumMat[SETOBJTYPE_MAX] = {};			// マテリアル情報の数
CObject::SETOBJTYPE CObject::m_SetObjType = CObject::SETOBJTYPE_BLOCK;
int CObject::m_nModel = 0;
char CObject::m_aFilenameModel[SETOBJTYPE_MAX][256] = {};

//=============================================================================
// 3Dモデルクラスのコンストラクタ
//=============================================================================
CObject::CObject():CSceneObject(OBJ_PRIORITY)
{
	// 値をクリア
	m_pVtxBuff = NULL;						// 頂点バッファへのポインタ
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 向き
	m_bCollision = false;
}

//=============================================================================
// デストラクタ
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// オブジェクトの生成処理
//=============================================================================
CObject *CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SETOBJTYPE SetObjType)
{
	CObject *pObject = NULL;

	if (pObject == NULL)
	{
		// オブジェクトクラスの生成
		pObject = new CObject;

		if (pObject != NULL)
		{
			pObject->m_pos = pos;
			pObject->m_rot = rot;
			pObject->BindModel(m_apBuffMat[SetObjType], m_anNumMat[SetObjType], m_apMesh[SetObjType]);
			pObject->Init();
		}
	}

	return pObject;
}

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT CObject::Init(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// オブジェクトの種類の設定
	SetObjType(CScene::OBJTYPE_SETOBJECT);

	m_bCollision = false;

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void CObject::Uninit(void)
{
	CSceneObject::Uninit();
}

//=============================================================================
// 更新処理
//=============================================================================
void CObject::Update(void)
{
	
}

//=============================================================================
// 描画処理
//=============================================================================
void CObject::Draw(void)
{
	CSceneObject::Draw();
}

//=============================================================================
// 位置の取得
//=============================================================================
D3DXVECTOR3 CObject::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// 位置の設定
//=============================================================================
void CObject::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// 向きの取得
//=============================================================================
D3DXVECTOR3 CObject::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// 向きの設定
//=============================================================================
void CObject::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// モデルのロード
//=============================================================================
void CObject::LoadFile(int nMode)
{
	LoadModel();

	FILE *pFile = NULL;

	CManager::MODE mode;
	mode = CManager::GetMode();

	CText *pText;
	pText = CManager::GetText();

	if (nMode == 0)
	{
		pFile = fopen(OBJECT_FILE_GAME, "r");
	}
	else if (nMode == 1)
	{
		pFile = fopen(OBJECT_FILE_TUTORIAL, "r");
	}
	// モデルのタイプを一回保存
	int nSaveType = m_SetObjType;

	if (pFile != NULL)
	{
		char *pStrCur;		// 文字列の先頭へのポインタ
		char aLine[256];	// 文字列読み込み用（1行分）
		char aStr[256];		// 文字列抜き出し用

		pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
		pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
		strcpy(&aStr[0], pStrCur);

		if (memcmp(&aStr[0], "SCRIPT", strlen("SCRIPT")) == 0)
		{
			while (1)
			{
				pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
				pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
				strcpy(&aStr[0], pStrCur);

				if (memcmp(&aStr[0], "NUM_MODEL =", strlen("NUM_MODEL =")) == 0)
				{
					pStrCur += strlen("NUM_MODEL =");	// 頭出し

					m_nModel = atoi(pStrCur);	// 文字列を値に変換
				}

				if (memcmp(&aStr[0], "MODEL INFO", strlen("MODEL INFO")) == 0)
				{
					for (int nCntModel = 0; nCntModel < m_nModel; nCntModel++)
					{
						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
						pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
						strcpy(&aStr[0], pStrCur);

						int nCntTimer = 0;

						if (memcmp(&aStr[0], "ModelType", strlen("ModelType")) == 0)
						{
							pStrCur += strlen("ModelType");	// 頭出し

							int nType = atoi(pStrCur);	// 文字列を値に変換

							m_SetObjType = (SETOBJTYPE)nType;

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
							pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
							strcpy(&aStr[0], pStrCur);

							D3DXVECTOR3 pos;
							D3DXVECTOR3 rot;

							if (memcmp(&aStr[0], "POS =", strlen("POS =")) == 0)
							{// 位置
								pStrCur += strlen("POS =");	// 頭出し
								int nWord;

								// floatに変換して代入
								pos.x = (float)atof(pStrCur);

								// aStr[0]に何文字入っているかを確かめる
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// 次まで進める
								pStrCur += nWord;

								// floatに変換して代入
								pos.y = (float)atof(pStrCur);

								// aStr[0]に何文字入っているかを確かめる
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// 次まで進める
								pStrCur += nWord;

								// floatに変換して代入
								pos.z = (float)atof(pStrCur);
							}

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
							pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
							strcpy(&aStr[0], pStrCur);

							if (memcmp(&aStr[0], "ROT =", strlen("ROT =")) == 0)
							{// 位置
								pStrCur += strlen("ROT =");	// 頭出し

								int nWord;

								// floatに変換して代入
								rot.x = (float)atof(pStrCur);

								// aStr[0]に何文字入っているかを確かめる
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// 次まで進める
								pStrCur += nWord;

								// floatに変換して代入
								rot.y = (float)atof(pStrCur);

								// aStr[0]に何文字入っているかを確かめる
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// 次まで進める
								pStrCur += nWord;

								// floatに変換して代入
								rot.z = (float)atof(pStrCur);
							}
							CSceneObject::Create(pos, rot, m_apBuffMat[m_SetObjType], m_anNumMat[m_SetObjType], m_apMesh[m_SetObjType]);
						}
					}
				}

				if (memcmp(&aStr[0], "ENDSCRIPT", strlen("ENDSCRIPT")) == 0)
				{
					break;
				}
			}
		}
		fclose(pFile);
	}

	// モデルのタイプを元に戻す
	m_SetObjType = (SETOBJTYPE)nSaveType;
}

//=============================================================================
// ブロックのモデル読み込み処理
//=============================================================================
HRESULT CObject::LoadModel(void)
{
	// レンダラーを取得
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	CText *pText;
	pText = CManager::GetText();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	FILE *pFile;

	pFile = fopen(OBJECTNAME_FILE, "r");

	D3DXMATERIAL *pMat;					// マテリアルデータへのポインタ

	// モデルのタイプを一回保存
	int nSaveType = m_SetObjType;

	if (pFile != NULL)
	{
		char *pStrCur;		// 文字列の先頭へのポインタ
		char aLine[256];	// 文字列読み込み用（1行分）
		char aStr[256];		// 文字列抜き出し用

		pStrCur = pText->ReadLine(pFile, &aLine[0]);	// 無効な行を無視する処理
		pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
		strcpy(&aStr[0], pStrCur);
		if (memcmp(&aStr[0], "SCRIPT", strlen("SCRIPT")) == 0)
		{
			for (int nCntModel = 0; nCntModel < SETOBJTYPE_MAX; nCntModel++)
			{// モデルの読み込み
				pStrCur = pText->ReadLine(pFile, &aLine[0]);
				pStrCur = pText->GetLineTop(&aLine[0]);		// 文字列の先頭を設定
				strcpy(&aStr[0], pStrCur);

				if (memcmp(&aStr[0], MODEL_FILENAME, strlen(MODEL_FILENAME)) == 0)
				{
					pStrCur += strlen(MODEL_FILENAME);

					strcpy(&aStr[0], pStrCur);

					// コメントを消す
					int nNullNum = pText->PopString(pStrCur, &aStr[0]);
					strcpy(&aStr[0], pStrCur);
					aStr[nNullNum - 1] = '\0';

					strcpy(&m_aFilenameModel[nCntModel][0], aStr);	//

					D3DXLoadMeshFromX(&m_aFilenameModel[nCntModel][0],
						D3DXMESH_SYSTEMMEM,
						pDevice,
						NULL,
						&m_apBuffMat[nCntModel],
						NULL,
						&m_anNumMat[nCntModel],
						&m_apMesh[nCntModel]);

					// マテリアルデータへのポインタを取得
					pMat = (D3DXMATERIAL*)m_apBuffMat[nCntModel]->GetBufferPointer();

					for (int nCntMat = 0; nCntMat < (int)m_anNumMat[nCntModel]; nCntMat++)
					{
						// 入れる前に空にする
						m_apTexture[nCntMat] = NULL;

						if (pMat[nCntMat].pTextureFilename != NULL)
						{
							// テクスチャの生成
							D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &m_apTexture[nCntMat]);
						}
					}
				}
			}
		}
		fclose(pFile);
	}

	return S_OK;
}

//=============================================================================
// ブロックのモデル解放処理
//=============================================================================
void CObject::UnloadModel(void)
{
	for (int nCntMesh = 0; nCntMesh < SETOBJTYPE_MAX; nCntMesh++)
	{
		// メッシュの開放
		if (m_apMesh[nCntMesh] != NULL)
		{
			m_apMesh[nCntMesh]->Release();
			m_apMesh[nCntMesh] = NULL;
		}
	}

	for (int nCntBuffMat = 0; nCntBuffMat < SETOBJTYPE_MAX; nCntBuffMat++)
	{
		// マテリアルの開放
		if (m_apBuffMat[nCntBuffMat] != NULL)
		{
			m_apBuffMat[nCntBuffMat]->Release();
			m_apBuffMat[nCntBuffMat] = NULL;
		}
	}

	for (int nCntTex = 0; nCntTex < SETOBJTYPE_MAX; nCntTex++)
	{
		// マテリアルの開放
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//=============================================================================
// オブジェクトのタイプの取得
//=============================================================================
CObject::SETOBJTYPE CObject::GetObjType(void)
{
	return m_SetObjType;
}

//=============================================================================
// メッシュ情報（頂点情報）の取得
//=============================================================================
LPD3DXMESH CObject::GetMesh(SETOBJTYPE SetObjType)
{
	return m_apMesh[SetObjType];
}

//=============================================================================
// マテリアル情報の取得
//=============================================================================
LPD3DXBUFFER CObject::GetBuffMat(SETOBJTYPE SetObjType)
{
	return m_apBuffMat[SetObjType];
}

//=============================================================================
// マテリアル情報の取得
//=============================================================================
DWORD CObject::GetNumMat(SETOBJTYPE SetObjType)
{
	return m_anNumMat[SetObjType];
}

//=============================================================================
// テクスチャ情報の取得
//=============================================================================
LPDIRECT3DTEXTURE9 CObject::GetTexture(SETOBJTYPE SetObjType)
{
	return m_apTexture[SetObjType];
}