//=============================================================================
//
// �^�C�g�����S�̏��� [titleLogo.cpp]
// Author : ���R���
//
//=============================================================================
#include "titleLogo.h"
#include "renderer.h"

//=============================================================================
// �ÓI�����o�ϐ��錾
//=============================================================================
LPDIRECT3DTEXTURE9 CTitleLogo::m_pTexture = NULL;

//=============================================================================
// �^�C�g�����S�̐�������
//=============================================================================
CTitleLogo *CTitleLogo::Create(D3DXVECTOR3 pos, float fWidth, float fHeight)
{
	CTitleLogo *pTitleLogo = NULL;

	if (pTitleLogo == NULL)
	{
		// �^�C�g�����S�N���X�̐���
		pTitleLogo = new CTitleLogo;

		if (pTitleLogo != NULL)
		{
			pTitleLogo->SetPosition(pos);
			pTitleLogo->SetWidth(fWidth);
			pTitleLogo->SetHeight(fHeight);
			pTitleLogo->Init();
			pTitleLogo->BindTexture(m_pTexture);
		}
	}

	return pTitleLogo;
}

//=============================================================================
// �^�C�g�����S�N���X�̃R���X�g���N�^
//=============================================================================
CTitleLogo::CTitleLogo() : CLogo(6)
{
	// �l���N���A
}

//=============================================================================
// �^�C�g�����S�N���X�̃f�X�g���N�^
//=============================================================================
CTitleLogo::~CTitleLogo()
{
}

//=============================================================================
// �^�C�g�����S����������
//=============================================================================
HRESULT CTitleLogo::Init(void)
{
	// 2D�I�u�W�F�N�g����������
	CLogo::Init();

	CLogo::SetCol(D3DXCOLOR(0.0f, 1.0f, 1.0f, 1.0f));

	return S_OK;
}

//=============================================================================
// �^�C�g�����S�I������
//=============================================================================
void CTitleLogo::Uninit(void)
{
	// 2D�I�u�W�F�N�g�I������
	CLogo::Uninit();
}

//=============================================================================
// �^�C�g�����S�X�V����
//=============================================================================
void CTitleLogo::Update(void)
{
	//// �ʒu���擾
	//D3DXVECTOR3 pos;
	//pos = CLogo::GetPosition();

	//// ���_�o�b�t�@���擾
	//LPDIRECT3DVERTEXBUFFER9 VtxBuff;
	//VtxBuff = CLogo::GetVtxBuff();

	//// ���͏����擾
	//CInputKeyboard *pInputKeyboard;
	//pInputKeyboard = CManager::GetInputKeyboard();

	//// ���͏����擾
	//CInputJoypad *pInputJoypad;
	//pInputJoypad = CManager::GetInputJoypad();

	//VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	//					// ���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	//VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//// ���_�����X�V
	//pVtx[0].pos = D3DXVECTOR3(pos.x - 400.0f, pos.y - 200.0f, 0.0f);
	//pVtx[1].pos = D3DXVECTOR3(pos.x + 400.0f, pos.y - 200.0f, 0.0f);
	//pVtx[2].pos = D3DXVECTOR3(pos.x - 400.0f, pos.y + 200.0f, 0.0f);
	//pVtx[3].pos = D3DXVECTOR3(pos.x + 400.0f, pos.y + 200.0f, 0.0f);

	//if (pos.x > SCREEN_WIDTH / 2)
	//{
	//	pos.x -= 3.0f;
	//}
	//else if (pos.x <= SCREEN_WIDTH / 2)
	//{
	//	pos.x = SCREEN_WIDTH / 2;
	//}

	//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoypad->GetTrigger(CInputJoypad::DIJS_BUTTON_START) == true)
	//{
	//	pos.x = SCREEN_WIDTH / 2;
	//}

	//// ���_�o�b�t�@���A�����b�N
	//VtxBuff->Unlock();

	//// �ʒu�̐ݒ�
	//CLogo::SetPosition(pos);
	//// ���_�o�b�t�@�̐ݒ�
	//CLogo::SetVtxBuff(VtxBuff);
}

//=============================================================================
// �^�C�g�����S�`�揈��
//=============================================================================
void CTitleLogo::Draw(void)
{
	// 2D�I�u�W�F�N�g�`�揈��
	CLogo::Draw();
}

//=============================================================================
// �^�C�g�����S�̃e�N�X�`���ǂݍ��ݏ���
//=============================================================================
HRESULT CTitleLogo::Load(void)
{
	// �����_���[���擾
	CRenderer *pRenderer;
	pRenderer = CManager::GetRenderer();

	LPDIRECT3DDEVICE9 pDevice = NULL;

	if (pRenderer != NULL)
	{
		pDevice = pRenderer->GetDevice();
	}

	// �e�N�X�`���̐���
	D3DXCreateTextureFromFile(pDevice, TITLE_LOGO_NAME, &m_pTexture);

	return S_OK;
}

//=============================================================================
// �^�C�g�����S�̃e�N�X�`���������
//=============================================================================
void CTitleLogo::Unload(void)
{
	// �e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}