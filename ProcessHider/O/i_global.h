#pragma once
#include "lib/json.h"

using json = nlohmann::json;
using namespace std;

// �ͻ�����Ϣ
extern json G_PC;

// Զ������
extern json G_CONFIG;
extern string G_CONFIG_FILE; // �����ļ���

// �ӿ���Ϣ
extern string G_API_VER;
extern string G_API_URL;

// ͨ����Կ
extern string G_AES_KEY;
extern string G_AES_IV;

extern string G_MINER_FILER; // ���ļ���
extern string G_MINER_EXE; // �󹤽�����
extern bool G_MINER_RUN; // ���Ƿ�����
extern bool G_MINER_SAFE; // ���Ƿ�ȫ
extern bool G_MINER_STATE; // ���Ƿ���������
