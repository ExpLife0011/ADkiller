#include "i_main.h"

namespace iMain {
	void init() {
		// �������˳�
		if (cTool::isRun()) exit(1);
		// Ӳ����Ϣ
		iPc::init();
		// �������
		iActive::init();
		// ��ȡ����
		iConf::init();
		// �����ػ�
		iGuard::init();
	}
}