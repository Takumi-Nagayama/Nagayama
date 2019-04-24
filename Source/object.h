//=============================================================================
//
// 3D���f������ [object.h]
// Author : ���R���
//
//=============================================================================
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "main.h"
#include "sceneObject.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define MAX_SETOBJECT	(200)	// �u���郂�f���̍ő吔
#define OBJECT_FILE_GAME	"data\\TEXT\\modelGame.txt"	// �ݒu�������f���������o���e�L�X�g
#define OBJECT_FILE_TUTORIAL	"data\\TEXT\\modelTutorial.txt"	// �ݒu�������f���������o���e�L�X�g
#define OBJECT_FILE_TITLE	"data\\TEXT\\modelTitle.txt"	// �ݒu�������f���������o���e�L�X�g
#define OBJECT_FILE_GAMECLEAR	"data\\TEXT\\modelGameClear.txt"	// �ݒu�������f���������o���e�L�X�g
#define OBJECT_FILE_GAMEOVER	"data\\TEXT\\modelGameOver.txt"	// �ݒu�������f���������o���e�L�X�g
#define OBJECTNAME_FILE	"data\\TEXT\\modelName.txt"	// �ݒu���������f���̖��O������
#define MODEL_FILENAME	"MODEL_FILENAME = "	// �ݒu���������f���̖��O������

//========================================
// �N���X�̒�`
//========================================
//=====================
// �I�u�W�F�N�g�N���X
//=====================
class CObject : public CSceneObject
{
public:
	typedef enum
	{// �I�u�W�F�N�g�̎��
		SETOBJTYPE_BLOCK = 0,
		SETOBJTYPE_OBSTACLE,								// ��Q��
		SETOBJTYPE_TREE,									// ��
		SETOBJTYPE_PLAMTREE,									// ��
		SETOBJTYPE_ROCK,									// ��
		SETOBJTYPE_ROCK1,									// ��
		SETOBJTYPE_ROCK2,									// ��
		SETOBJTYPE_ROCK3,									// ��
		SETOBJTYPE_ROCK4,									// ��
		SETOBJTYPE_ROCK5,									// ��
		SETOBJTYPE_ROCK6,									// ��
		SETOBJTYPE_WOODBOX,									// �ؔ�
		SETOBJTYPE_LONGSTONE001,									// �ؔ�
		SETOBJTYPE_LONGSTONE002,									// �ؔ�
		SETOBJTYPE_DELETE,									// �����S��
		SETOBJTYPE_MAX										// ����
	} SETOBJTYPE;

	CObject();												// �R���X�g���N�^
	~CObject();												// �f�X�g���N�^

	HRESULT Init(void);										// 3D�I�u�W�F�N�g����������
	void Uninit(void);										// 3D�I�u�W�F�N�g�I������
	void Update(void);										// 3D�I�u�W�F�N�g�X�V����
	void Draw(void);										// 3D�I�u�W�F�N�g�`�揈��

	static CObject *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, SETOBJTYPE SetObjType);				// �I�u�W�F�N�g�̐���

	D3DXVECTOR3 GetPos(void);								// �ʒu�̎擾
	void SetPos(D3DXVECTOR3 pos);							// �ʒu�̐ݒ�

	D3DXVECTOR3 GetRot(void);								// �����̎擾
	void SetRot(D3DXVECTOR3 rot);							// �����̐ݒ�

	void LoadFile(int nMode);

	static SETOBJTYPE GetObjType(void);

	HRESULT LoadModel(void);							// �e�N�X�`���ǂݍ���
	static void UnloadModel(void);							// �e�N�X�`�����

	static LPD3DXMESH GetMesh(SETOBJTYPE SetObjType);
	static LPD3DXBUFFER GetBuffMat(SETOBJTYPE SetObjType);
	static DWORD GetNumMat(SETOBJTYPE SetObjType);
	static LPDIRECT3DTEXTURE9 GetTexture(SETOBJTYPE SetObjType);

private:
	static LPDIRECT3DTEXTURE9	m_apTexture[SETOBJTYPE_MAX];	// �e�N�X�`���ւ̃|�C���^
	static LPD3DXMESH			m_apMesh[SETOBJTYPE_MAX];	// ���b�V�����i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER			m_apBuffMat[SETOBJTYPE_MAX];	// �}�e���A�����ւ̃|�C���^
	static DWORD				m_anNumMat[SETOBJTYPE_MAX];	// �}�e���A�����̐�
	static SETOBJTYPE			m_SetObjType;
	static int					m_nModel;
	LPDIRECT3DVERTEXBUFFER9		m_pVtxBuff;					// ���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX					m_mtxWorld;					// ���[���h�}�g���b�N�X

	bool						m_bCollision;				// �ݒu�����I�u�W�F�N�g�Ɠ������Ă��邩�ǂ����Ɏg��

	D3DXVECTOR3					m_pos;						// �|���S���̈ʒu
	D3DXVECTOR3					m_rot;						// ������x�N�g��
	static char m_aFilenameModel[SETOBJTYPE_MAX][256];
};

#endif