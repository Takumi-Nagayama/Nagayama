//=============================================================================
//
// 3D���f������ [object.cpp]
// Author : ���R���
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
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CObject::m_apTexture[SETOBJTYPE_MAX] = {};	// �}�e���A�����ւ̃|�C���^
LPD3DXMESH CObject::m_apMesh[SETOBJTYPE_MAX] = {};		// ���b�V�����i���_���j�ւ̃|�C���^
LPD3DXBUFFER CObject::m_apBuffMat[SETOBJTYPE_MAX] = {};	// �}�e���A�����ւ̃|�C���^
DWORD CObject::m_anNumMat[SETOBJTYPE_MAX] = {};			// �}�e���A�����̐�
CObject::SETOBJTYPE CObject::m_SetObjType = CObject::SETOBJTYPE_BLOCK;
int CObject::m_nModel = 0;
char CObject::m_aFilenameModel[SETOBJTYPE_MAX][256] = {};

//=============================================================================
// 3D���f���N���X�̃R���X�g���N�^
//=============================================================================
CObject::CObject():CSceneObject(OBJ_PRIORITY)
{
	// �l���N���A
	m_pVtxBuff = NULL;						// ���_�o�b�t�@�ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ����
	m_bCollision = false;
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CObject::~CObject()
{
}

//=============================================================================
// �I�u�W�F�N�g�̐�������
//=============================================================================
CObject *CObject::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SETOBJTYPE SetObjType)
{
	CObject *pObject = NULL;

	if (pObject == NULL)
	{
		// �I�u�W�F�N�g�N���X�̐���
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
// ����������
//=============================================================================
HRESULT CObject::Init(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �I�u�W�F�N�g�̎�ނ̐ݒ�
	SetObjType(CScene::OBJTYPE_SETOBJECT);

	m_bCollision = false;

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void CObject::Uninit(void)
{
	CSceneObject::Uninit();
}

//=============================================================================
// �X�V����
//=============================================================================
void CObject::Update(void)
{
	
}

//=============================================================================
// �`�揈��
//=============================================================================
void CObject::Draw(void)
{
	CSceneObject::Draw();
}

//=============================================================================
// �ʒu�̎擾
//=============================================================================
D3DXVECTOR3 CObject::GetPos(void)
{
	return m_pos;
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void CObject::SetPos(D3DXVECTOR3 pos)
{
	m_pos = pos;
}

//=============================================================================
// �����̎擾
//=============================================================================
D3DXVECTOR3 CObject::GetRot(void)
{
	return m_rot;
}

//=============================================================================
// �����̐ݒ�
//=============================================================================
void CObject::SetRot(D3DXVECTOR3 rot)
{
	m_rot = rot;
}

//=============================================================================
// ���f���̃��[�h
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
	// ���f���̃^�C�v�����ۑ�
	int nSaveType = m_SetObjType;

	if (pFile != NULL)
	{
		char *pStrCur;		// ������̐擪�ւ̃|�C���^
		char aLine[256];	// ������ǂݍ��ݗp�i1�s���j
		char aStr[256];		// �����񔲂��o���p

		pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
		pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
		strcpy(&aStr[0], pStrCur);

		if (memcmp(&aStr[0], "SCRIPT", strlen("SCRIPT")) == 0)
		{
			while (1)
			{
				pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
				pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
				strcpy(&aStr[0], pStrCur);

				if (memcmp(&aStr[0], "NUM_MODEL =", strlen("NUM_MODEL =")) == 0)
				{
					pStrCur += strlen("NUM_MODEL =");	// ���o��

					m_nModel = atoi(pStrCur);	// �������l�ɕϊ�
				}

				if (memcmp(&aStr[0], "MODEL INFO", strlen("MODEL INFO")) == 0)
				{
					for (int nCntModel = 0; nCntModel < m_nModel; nCntModel++)
					{
						pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
						pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
						strcpy(&aStr[0], pStrCur);

						int nCntTimer = 0;

						if (memcmp(&aStr[0], "ModelType", strlen("ModelType")) == 0)
						{
							pStrCur += strlen("ModelType");	// ���o��

							int nType = atoi(pStrCur);	// �������l�ɕϊ�

							m_SetObjType = (SETOBJTYPE)nType;

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
							pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
							strcpy(&aStr[0], pStrCur);

							D3DXVECTOR3 pos;
							D3DXVECTOR3 rot;

							if (memcmp(&aStr[0], "POS =", strlen("POS =")) == 0)
							{// �ʒu
								pStrCur += strlen("POS =");	// ���o��
								int nWord;

								// float�ɕϊ����đ��
								pos.x = (float)atof(pStrCur);

								// aStr[0]�ɉ����������Ă��邩���m���߂�
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// ���܂Ői�߂�
								pStrCur += nWord;

								// float�ɕϊ����đ��
								pos.y = (float)atof(pStrCur);

								// aStr[0]�ɉ����������Ă��邩���m���߂�
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// ���܂Ői�߂�
								pStrCur += nWord;

								// float�ɕϊ����đ��
								pos.z = (float)atof(pStrCur);
							}

							pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
							pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
							strcpy(&aStr[0], pStrCur);

							if (memcmp(&aStr[0], "ROT =", strlen("ROT =")) == 0)
							{// �ʒu
								pStrCur += strlen("ROT =");	// ���o��

								int nWord;

								// float�ɕϊ����đ��
								rot.x = (float)atof(pStrCur);

								// aStr[0]�ɉ����������Ă��邩���m���߂�
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// ���܂Ői�߂�
								pStrCur += nWord;

								// float�ɕϊ����đ��
								rot.y = (float)atof(pStrCur);

								// aStr[0]�ɉ����������Ă��邩���m���߂�
								nWord = pText->PopString(pStrCur, &aStr[0]);

								// ���܂Ői�߂�
								pStrCur += nWord;

								// float�ɕϊ����đ��
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

	// ���f���̃^�C�v�����ɖ߂�
	m_SetObjType = (SETOBJTYPE)nSaveType;
}

//=============================================================================
// �u���b�N�̃��f���ǂݍ��ݏ���
//=============================================================================
HRESULT CObject::LoadModel(void)
{
	// �����_���[���擾
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

	D3DXMATERIAL *pMat;					// �}�e���A���f�[�^�ւ̃|�C���^

	// ���f���̃^�C�v�����ۑ�
	int nSaveType = m_SetObjType;

	if (pFile != NULL)
	{
		char *pStrCur;		// ������̐擪�ւ̃|�C���^
		char aLine[256];	// ������ǂݍ��ݗp�i1�s���j
		char aStr[256];		// �����񔲂��o���p

		pStrCur = pText->ReadLine(pFile, &aLine[0]);	// �����ȍs�𖳎����鏈��
		pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
		strcpy(&aStr[0], pStrCur);
		if (memcmp(&aStr[0], "SCRIPT", strlen("SCRIPT")) == 0)
		{
			for (int nCntModel = 0; nCntModel < SETOBJTYPE_MAX; nCntModel++)
			{// ���f���̓ǂݍ���
				pStrCur = pText->ReadLine(pFile, &aLine[0]);
				pStrCur = pText->GetLineTop(&aLine[0]);		// ������̐擪��ݒ�
				strcpy(&aStr[0], pStrCur);

				if (memcmp(&aStr[0], MODEL_FILENAME, strlen(MODEL_FILENAME)) == 0)
				{
					pStrCur += strlen(MODEL_FILENAME);

					strcpy(&aStr[0], pStrCur);

					// �R�����g������
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

					// �}�e���A���f�[�^�ւ̃|�C���^���擾
					pMat = (D3DXMATERIAL*)m_apBuffMat[nCntModel]->GetBufferPointer();

					for (int nCntMat = 0; nCntMat < (int)m_anNumMat[nCntModel]; nCntMat++)
					{
						// �����O�ɋ�ɂ���
						m_apTexture[nCntMat] = NULL;

						if (pMat[nCntMat].pTextureFilename != NULL)
						{
							// �e�N�X�`���̐���
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
// �u���b�N�̃��f���������
//=============================================================================
void CObject::UnloadModel(void)
{
	for (int nCntMesh = 0; nCntMesh < SETOBJTYPE_MAX; nCntMesh++)
	{
		// ���b�V���̊J��
		if (m_apMesh[nCntMesh] != NULL)
		{
			m_apMesh[nCntMesh]->Release();
			m_apMesh[nCntMesh] = NULL;
		}
	}

	for (int nCntBuffMat = 0; nCntBuffMat < SETOBJTYPE_MAX; nCntBuffMat++)
	{
		// �}�e���A���̊J��
		if (m_apBuffMat[nCntBuffMat] != NULL)
		{
			m_apBuffMat[nCntBuffMat]->Release();
			m_apBuffMat[nCntBuffMat] = NULL;
		}
	}

	for (int nCntTex = 0; nCntTex < SETOBJTYPE_MAX; nCntTex++)
	{
		// �}�e���A���̊J��
		if (m_apTexture[nCntTex] != NULL)
		{
			m_apTexture[nCntTex]->Release();
			m_apTexture[nCntTex] = NULL;
		}
	}
}

//=============================================================================
// �I�u�W�F�N�g�̃^�C�v�̎擾
//=============================================================================
CObject::SETOBJTYPE CObject::GetObjType(void)
{
	return m_SetObjType;
}

//=============================================================================
// ���b�V�����i���_���j�̎擾
//=============================================================================
LPD3DXMESH CObject::GetMesh(SETOBJTYPE SetObjType)
{
	return m_apMesh[SetObjType];
}

//=============================================================================
// �}�e���A�����̎擾
//=============================================================================
LPD3DXBUFFER CObject::GetBuffMat(SETOBJTYPE SetObjType)
{
	return m_apBuffMat[SetObjType];
}

//=============================================================================
// �}�e���A�����̎擾
//=============================================================================
DWORD CObject::GetNumMat(SETOBJTYPE SetObjType)
{
	return m_anNumMat[SetObjType];
}

//=============================================================================
// �e�N�X�`�����̎擾
//=============================================================================
LPDIRECT3DTEXTURE9 CObject::GetTexture(SETOBJTYPE SetObjType)
{
	return m_apTexture[SetObjType];
}