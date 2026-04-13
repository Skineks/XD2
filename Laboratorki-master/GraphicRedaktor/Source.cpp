#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// ВАЖНО: Проверь, что в MyForm.h написано "namespace GraphicRedaktor"
	// Если пространство имен другое, замени GraphicRedaktor ниже на свое
	GraphicRedaktor::MyForm form;

	Application::Run(% form);
	return 0;
}