#include "MainForm.h"
#include <Windows.h>

#include "FileCtrlStore.h"

TFileCtrlStore * pFileCtrlStore = nullptr;// Определение переменной
std::vector<std::string> vectRestoredFiles;

using namespace LabWork01CLR;

[STAThread]
int WINAPI WinMain (HINSTANCE, HINSTANCE, LPSTR, int) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew MainForm);
	return 0;
}

