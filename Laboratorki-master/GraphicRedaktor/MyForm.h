#pragma once

#include <stack>
#include <vector>

// Óáèğàåì êîíôëèêò ïğîñòğàíñòâ èìåí
using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;
using namespace System::Drawing::Drawing2D;

namespace GraphicRedaktor {

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			InitializeCustomComponents();

			// Ñîçäàåì íîâûé äîêóìåíò
			ñîçäàòüToolStripMenuItem_Click(nullptr, nullptr);

			// Óñòàíàâëèâàåì íà÷àëüíûå çíà÷åíèÿ
			tool = 1;
			isDrawing = false;
			isShiftPressed = false;
			zoomFactor = 1.0f;
			currentTool = "İëëèïñ";

			UpdateToolDisplay();
		}

	private:
		// Ïåğåìåííûå äëÿ ğèñîâàíèÿ
		int startX, startY;
		int prevX, prevY;
		int tool;  // 1 - ıëëèïñ, 2 - ïğÿìîóãîëüíèê, 3 - ëèíèÿ, 4 - ëàñòèê
		bool isDrawing;
		bool isShiftPressed;
		float zoomFactor;
		String^ currentTool;
		System::Drawing::Rectangle previewRect;
		System::Drawing::Point currentPoint;

		// Èñòîğèÿ äåéñòâèé - èñïîëüçóåì ïîëíîå èìÿ òèïà
		System::Collections::Generic::Stack<System::Drawing::Bitmap^>^ undoStack;
		System::Collections::Generic::Stack<System::Drawing::Bitmap^>^ redoStack;

		// Êîìïîíåíòû èíòåğôåéñà
		System::Windows::Forms::MenuStrip^ menuStrip1;
		System::Windows::Forms::ToolStripMenuItem^ ôàéëToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ ñîçäàòüToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ îòêğûòüToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ ñîõğàíèòüÊàêToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ âûõîäToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ ïğàâêàToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ îòìåíèòüToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ ïîâòîğèòüToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ èíñòğóìåíòûToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ êàğàíäàøToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ öâåòToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ òîëùèíàToolStripMenuItem;
		System::Windows::Forms::ToolStripComboBox^ thicknessCombo;
		System::Windows::Forms::ToolStripMenuItem^ êèñòüToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ öâåòToolStripMenuItem1;
		System::Windows::Forms::ToolStripMenuItem^ ôèëüòğûToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ ÷åğíîÁåëûéToolStripMenuItem;
		System::Windows::Forms::ToolStripMenuItem^ èíâåğòèğîâàòüToolStripMenuItem;

		System::Windows::Forms::Panel^ panel1;
		System::Windows::Forms::Button^ buttonLine;
		System::Windows::Forms::Button^ buttonEllipse;
		System::Windows::Forms::Button^ buttonRect;
		System::Windows::Forms::Button^ buttonEraser;
		System::Windows::Forms::Button^ btnPenColor;
		System::Windows::Forms::Button^ btnBrushColor;
		System::Windows::Forms::Button^ btnUndo;
		System::Windows::Forms::Button^ btnRedo;
		System::Windows::Forms::CheckBox^ chkFill;
		System::Windows::Forms::TrackBar^ zoomTrackBar;
		System::Windows::Forms::Label^ zoomLabel;
		System::Windows::Forms::Label^ toolLabel;
		System::Windows::Forms::PictureBox^ pictureBox1;
		System::Windows::Forms::StatusStrip^ statusStrip;
		System::Windows::Forms::ToolStripStatusLabel^ statusLabel;
		System::Windows::Forms::ToolStripStatusLabel^ positionLabel;
		System::Windows::Forms::ToolStripStatusLabel^ toolStatusLabel;

		System::Windows::Forms::OpenFileDialog^ openFileDialog1;
		System::Windows::Forms::SaveFileDialog^ saveFileDialog1;
		System::Windows::Forms::ColorDialog^ penColorDialog;
		System::Windows::Forms::ColorDialog^ brushColorDialog;
		System::Windows::Forms::ToolTip^ toolTip;

		System::ComponentModel::Container^ components;

		// Èíèöèàëèçàöèÿ äîïîëíèòåëüíûõ êîìïîíåíòîâ
		void InitializeCustomComponents()
		{
			// Èíèöèàëèçàöèÿ äèàëîãîâ
			penColorDialog = gcnew ColorDialog();
			brushColorDialog = gcnew ColorDialog();
			openFileDialog1 = gcnew OpenFileDialog();
			saveFileDialog1 = gcnew SaveFileDialog();
			toolTip = gcnew ToolTip();

			// Íàñòğîéêà äèàëîãîâ
			openFileDialog1->Filter = L"Èçîáğàæåíèÿ|*.bmp;*.jpg;*.png;*.gif|Âñå ôàéëû|*.*";
			saveFileDialog1->Filter = L"PNG Image|*.png|JPEG Image|*.jpg|BMP Image|*.bmp";
			penColorDialog->Color = Color::Black;
			brushColorDialog->Color = Color::White;

			// Èíèöèàëèçàöèÿ èñòîğèè
			undoStack = gcnew System::Collections::Generic::Stack<System::Drawing::Bitmap^>();
			redoStack = gcnew System::Collections::Generic::Stack<System::Drawing::Bitmap^>();

			// Íàñòğîéêà PictureBox
			pictureBox1->SizeMode = PictureBoxSizeMode::Zoom;
			pictureBox1->BackColor = Color::White;

			// Íàñòğîéêà òğåêáàğà çóìà
			zoomTrackBar->Minimum = 10;
			zoomTrackBar->Maximum = 200;
			zoomTrackBar->Value = 100;
			zoomTrackBar->TickFrequency = 10;

			// Íàñòğîéêà âûïàäàşùåãî ñïèñêà òîëùèíû
			thicknessCombo->ComboBox->DrawMode = DrawMode::OwnerDrawFixed;
			thicknessCombo->ComboBox->DropDownStyle = ComboBoxStyle::DropDownList;
			for (int i = 1; i <= 10; i++) thicknessCombo->Items->Add(i);
			thicknessCombo->SelectedIndex = 0;
			thicknessCombo->ComboBox->DrawItem += gcnew DrawItemEventHandler(this, &MyForm::thicknessCombo_DrawItem);

			// Íàñòğîéêà ãîğÿ÷èõ êëàâèø
			this->KeyPreview = true;
			this->KeyDown += gcnew KeyEventHandler(this, &MyForm::MyForm_KeyDown);

			// Äîáàâëåíèå ïîäñêàçîê
			toolTip->SetToolTip(buttonLine, L"Ğèñîâàíèå ëèíèè (L)");
			toolTip->SetToolTip(buttonEllipse, L"Ğèñîâàíèå ıëëèïñà (E)");
			toolTip->SetToolTip(buttonRect, L"Ğèñîâàíèå ïğÿìîóãîëüíèêà (R)");
			toolTip->SetToolTip(buttonEraser, L"Ëàñòèê (X)");
			toolTip->SetToolTip(btnPenColor, L"Âûáîğ öâåòà êîíòóğà");
			toolTip->SetToolTip(btnBrushColor, L"Âûáîğ öâåòà çàëèâêè");
			toolTip->SetToolTip(btnUndo, L"Îòìåíèòü äåéñòâèå (Ctrl+Z)");
			toolTip->SetToolTip(btnRedo, L"Ïîâòîğèòü äåéñòâèå (Ctrl+Y)");
			toolTip->SetToolTip(chkFill, L"Âêëş÷èòü/âûêëş÷èòü çàëèâêó ôèãóğ");

			// Îáíîâëåíèå îòîáğàæåíèÿ
			UpdateToolDisplay();
		}

		// Îáíîâëåíèå îòîáğàæåíèÿ òåêóùåãî èíñòğóìåíòà
		void UpdateToolDisplay()
		{
			switch (tool)
			{
			case 1: currentTool = "İëëèïñ"; break;
			case 2: currentTool = "Ïğÿìîóãîëüíèê"; break;
			case 3: currentTool = "Ëèíèÿ"; break;
			case 4: currentTool = "Ëàñòèê"; break;
			}
			toolStatusLabel->Text = String::Format(L"Èíñòğóìåíò: {0}", currentTool);
		}

		// Ñîõğàíåíèå ñîñòîÿíèÿ äëÿ îòìåíû
		void SaveState()
		{
			if (pictureBox1->Image != nullptr)
			{
				System::Drawing::Bitmap^ state = gcnew System::Drawing::Bitmap(pictureBox1->Image);
				undoStack->Push(state);
				redoStack->Clear();

				// Îãğàíè÷èâàåì èñòîğèş 30 øàãàìè
				if (undoStack->Count > 30)
				{
					delete undoStack->Pop();
				}
			}
		}

		// Îòğèñîâêà ıëåìåíòîâ â âûïàäàşùåì ñïèñêå
		void thicknessCombo_DrawItem(System::Object^ sender, DrawItemEventArgs^ e)
		{
			if (e->Index < 0) return;
			e->DrawBackground();
			int thickness = safe_cast<int>(thicknessCombo->Items[e->Index]);
			Pen^ p = gcnew Pen(Color::Black, (float)thickness);
			int y = e->Bounds.Top + e->Bounds.Height / 2;
			e->Graphics->DrawLine(p, e->Bounds.Left + 5, y, e->Bounds.Right - 5, y);
			delete p;
			e->DrawFocusRectangle();
		}

	protected:
		~MyForm()
		{
			if (components) delete components;

			// Î÷èñòêà èñòîğèè
			while (undoStack->Count > 0) delete undoStack->Pop();
			while (redoStack->Count > 0) delete redoStack->Pop();
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->ôàéëToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ñîçäàòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->îòêğûòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ñîõğàíèòüÊàêToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->âûõîäToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ïğàâêàToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->îòìåíèòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ïîâòîğèòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->èíñòğóìåíòûToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->êàğàíäàøToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->öâåòToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->òîëùèíàToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->thicknessCombo = (gcnew System::Windows::Forms::ToolStripComboBox());
			this->êèñòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->öâåòToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ôèëüòğûToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->÷åğíîÁåëûéToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->èíâåğòèğîâàòüToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->zoomLabel = (gcnew System::Windows::Forms::Label());
			this->zoomTrackBar = (gcnew System::Windows::Forms::TrackBar());
			this->toolLabel = (gcnew System::Windows::Forms::Label());
			this->btnRedo = (gcnew System::Windows::Forms::Button());
			this->btnUndo = (gcnew System::Windows::Forms::Button());
			this->buttonEraser = (gcnew System::Windows::Forms::Button());
			this->btnBrushColor = (gcnew System::Windows::Forms::Button());
			this->btnPenColor = (gcnew System::Windows::Forms::Button());
			this->buttonRect = (gcnew System::Windows::Forms::Button());
			this->buttonEllipse = (gcnew System::Windows::Forms::Button());
			this->buttonLine = (gcnew System::Windows::Forms::Button());
			this->chkFill = (gcnew System::Windows::Forms::CheckBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->statusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->positionLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->toolStatusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->menuStrip1->SuspendLayout();
			this->panel1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->zoomTrackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->statusStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->ôàéëToolStripMenuItem,
					this->ïğàâêàToolStripMenuItem,
					this->èíñòğóìåíòûToolStripMenuItem,
					this->ôèëüòğûToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1000, 28);
			this->menuStrip1->TabIndex = 2;
			// 
			// ôàéëToolStripMenuItem
			// 
			this->ôàéëToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->ñîçäàòüToolStripMenuItem,
					this->îòêğûòüToolStripMenuItem,
					this->ñîõğàíèòüÊàêToolStripMenuItem,
					this->âûõîäToolStripMenuItem
			});
			this->ôàéëToolStripMenuItem->Name = L"ôàéëToolStripMenuItem";
			this->ôàéëToolStripMenuItem->Size = System::Drawing::Size(59, 24);
			this->ôàéëToolStripMenuItem->Text = L"Ôàéë";
			// 
			// ñîçäàòüToolStripMenuItem
			// 
			this->ñîçäàòüToolStripMenuItem->Name = L"ñîçäàòüToolStripMenuItem";
			this->ñîçäàòüToolStripMenuItem->Size = System::Drawing::Size(192, 26);
			this->ñîçäàòüToolStripMenuItem->Text = L"Ñîçäàòü";
			this->ñîçäàòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ñîçäàòüToolStripMenuItem_Click);
			// 
			// îòêğûòüToolStripMenuItem
			// 
			this->îòêğûòüToolStripMenuItem->Name = L"îòêğûòüToolStripMenuItem";
			this->îòêğûòüToolStripMenuItem->Size = System::Drawing::Size(192, 26);
			this->îòêğûòüToolStripMenuItem->Text = L"Îòêğûòü";
			this->îòêğûòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::îòêğûòüToolStripMenuItem_Click);
			// 
			// ñîõğàíèòüÊàêToolStripMenuItem
			// 
			this->ñîõğàíèòüÊàêToolStripMenuItem->Name = L"ñîõğàíèòüÊàêToolStripMenuItem";
			this->ñîõğàíèòüÊàêToolStripMenuItem->Size = System::Drawing::Size(192, 26);
			this->ñîõğàíèòüÊàêToolStripMenuItem->Text = L"Ñîõğàíèòü êàê";
			this->ñîõğàíèòüÊàêToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::ñîõğàíèòüÊàêToolStripMenuItem_Click);
			// 
			// âûõîäToolStripMenuItem
			// 
			this->âûõîäToolStripMenuItem->Name = L"âûõîäToolStripMenuItem";
			this->âûõîäToolStripMenuItem->Size = System::Drawing::Size(192, 26);
			this->âûõîäToolStripMenuItem->Text = L"Âûõîä";
			this->âûõîäToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::âûõîäToolStripMenuItem_Click);
			// 
			// ïğàâêàToolStripMenuItem
			// 
			this->ïğàâêàToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->îòìåíèòüToolStripMenuItem,
					this->ïîâòîğèòüToolStripMenuItem
			});
			this->ïğàâêàToolStripMenuItem->Name = L"ïğàâêàToolStripMenuItem";
			this->ïğàâêàToolStripMenuItem->Size = System::Drawing::Size(74, 24);
			this->ïğàâêàToolStripMenuItem->Text = L"Ïğàâêà";
			// 
			// îòìåíèòüToolStripMenuItem
			// 
			this->îòìåíèòüToolStripMenuItem->Name = L"îòìåíèòüToolStripMenuItem";
			this->îòìåíèòüToolStripMenuItem->Size = System::Drawing::Size(178, 26);
			this->îòìåíèòüToolStripMenuItem->Text = L"Îòìåíèòü (Ctrl+Z)";
			this->îòìåíèòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::btnUndo_Click);
			// 
			// ïîâòîğèòüToolStripMenuItem
			// 
			this->ïîâòîğèòüToolStripMenuItem->Name = L"ïîâòîğèòüToolStripMenuItem";
			this->ïîâòîğèòüToolStripMenuItem->Size = System::Drawing::Size(178, 26);
			this->ïîâòîğèòüToolStripMenuItem->Text = L"Ïîâòîğèòü (Ctrl+Y)";
			this->ïîâòîğèòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::btnRedo_Click);
			// 
			// èíñòğóìåíòûToolStripMenuItem
			// 
			this->èíñòğóìåíòûToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->êàğàíäàøToolStripMenuItem,
					this->êèñòüToolStripMenuItem,
					this->òîëùèíàToolStripMenuItem
			});
			this->èíñòğóìåíòûToolStripMenuItem->Name = L"èíñòğóìåíòûToolStripMenuItem";
			this->èíñòğóìåíòûToolStripMenuItem->Size = System::Drawing::Size(115, 24);
			this->èíñòğóìåíòûToolStripMenuItem->Text = L"Èíñòğóìåíòû";
			// 
			// êàğàíäàøToolStripMenuItem
			// 
			this->êàğàíäàøToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {
				this->öâåòToolStripMenuItem
			});
			this->êàğàíäàøToolStripMenuItem->Name = L"êàğàíäàøToolStripMenuItem";
			this->êàğàíäàøToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->êàğàíäàøToolStripMenuItem->Text = L"Êàğàíäàø";
			// 
			// öâåòToolStripMenuItem
			// 
			this->öâåòToolStripMenuItem->Name = L"öâåòToolStripMenuItem";
			this->öâåòToolStripMenuItem->Size = System::Drawing::Size(155, 26);
			this->öâåòToolStripMenuItem->Text = L"Öâåò";
			this->öâåòToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::öâåòToolStripMenuItem_Click);
			// 
			// òîëùèíàToolStripMenuItem
			// 
			this->òîëùèíàToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {
				this->thicknessCombo
			});
			this->òîëùèíàToolStripMenuItem->Name = L"òîëùèíàToolStripMenuItem";
			this->òîëùèíàToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->òîëùèíàToolStripMenuItem->Text = L"Òîëùèíà ëèíèè";
			// 
			// thicknessCombo
			// 
			this->thicknessCombo->Name = L"thicknessCombo";
			this->thicknessCombo->Size = System::Drawing::Size(121, 28);
			// 
			// êèñòüToolStripMenuItem
			// 
			this->êèñòüToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {
				this->öâåòToolStripMenuItem1
			});
			this->êèñòüToolStripMenuItem->Name = L"êèñòüToolStripMenuItem";
			this->êèñòüToolStripMenuItem->Size = System::Drawing::Size(224, 26);
			this->êèñòüToolStripMenuItem->Text = L"Êèñòü (çàëèâêà)";
			// 
			// öâåòToolStripMenuItem1
			// 
			this->öâåòToolStripMenuItem1->Name = L"öâåòToolStripMenuItem1";
			this->öâåòToolStripMenuItem1->Size = System::Drawing::Size(155, 26);
			this->öâåòToolStripMenuItem1->Text = L"Öâåò";
			this->öâåòToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MyForm::öâåòToolStripMenuItem1_Click);
			// 
			// ôèëüòğûToolStripMenuItem
			// 
			this->ôèëüòğûToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->÷åğíîÁåëûéToolStripMenuItem,
					this->èíâåğòèğîâàòüToolStripMenuItem
			});
			this->ôèëüòğûToolStripMenuItem->Name = L"ôèëüòğûToolStripMenuItem";
			this->ôèëüòğûToolStripMenuItem->Size = System::Drawing::Size(78, 24);
			this->ôèëüòğûToolStripMenuItem->Text = L"Ôèëüòğû";
			// 
			// ÷åğíîÁåëûéToolStripMenuItem
			// 
			this->÷åğíîÁåëûéToolStripMenuItem->Name = L"÷åğíîÁåëûéToolStripMenuItem";
			this->÷åğíîÁåëûéToolStripMenuItem->Size = System::Drawing::Size(184, 26);
			this->÷åğíîÁåëûéToolStripMenuItem->Text = L"×åğíî-áåëûé";
			this->÷åğíîÁåëûéToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::÷åğíîÁåëûéToolStripMenuItem_Click);
			// 
			// èíâåğòèğîâàòüToolStripMenuItem
			// 
			this->èíâåğòèğîâàòüToolStripMenuItem->Name = L"èíâåğòèğîâàòüToolStripMenuItem";
			this->èíâåğòèğîâàòüToolStripMenuItem->Size = System::Drawing::Size(184, 26);
			this->èíâåğòèğîâàòüToolStripMenuItem->Text = L"Èíâåğòèğîâàòü öâåòà";
			this->èíâåğòèğîâàòüToolStripMenuItem->Click += gcnew System::EventHandler(this, &MyForm::èíâåğòèğîâàòüToolStripMenuItem_Click);
			// 
		// panel1
		// 
			this->panel1->Controls->Add(this->zoomLabel);
			this->panel1->Controls->Add(this->zoomTrackBar);
			this->panel1->Controls->Add(this->toolLabel);
			this->panel1->Controls->Add(this->btnRedo);
			this->panel1->Controls->Add(this->btnUndo);
			this->panel1->Controls->Add(this->buttonEraser);
			this->panel1->Controls->Add(this->btnBrushColor);
			this->panel1->Controls->Add(this->btnPenColor);
			this->panel1->Controls->Add(this->buttonRect);
			this->panel1->Controls->Add(this->buttonEllipse);
			this->panel1->Controls->Add(this->buttonLine);
			this->panel1->Controls->Add(this->chkFill);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel1->Location = System::Drawing::Point(0, 28);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1000, 100);
			this->panel1->TabIndex = 1;
			// 
			// chkFill
			// 
			this->chkFill->AutoSize = true;
			this->chkFill->Checked = true;
			this->chkFill->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chkFill->Location = System::Drawing::Point(10, 15);
			this->chkFill->Name = L"chkFill";
			this->chkFill->Size = System::Drawing::Size(90, 24);
			this->chkFill->TabIndex = 0;
			this->chkFill->Text = L"Çàëèâêà";
			this->chkFill->UseVisualStyleBackColor = true;
			// 
			// buttonLine
			// 
			this->buttonLine->Location = System::Drawing::Point(10, 50);
			this->buttonLine->Name = L"buttonLine";
			this->buttonLine->Size = System::Drawing::Size(100, 40);
			this->buttonLine->TabIndex = 2;
			this->buttonLine->Text = L"Ëèíèÿ";
			this->buttonLine->UseVisualStyleBackColor = true;
			this->buttonLine->Click += gcnew System::EventHandler(this, &MyForm::btnLine_Click);
			// 
			// buttonEllipse
			// 
			this->buttonEllipse->Location = System::Drawing::Point(120, 50);  // 10 + 100 + 10 = 120
			this->buttonEllipse->Name = L"buttonEllipse";
			this->buttonEllipse->Size = System::Drawing::Size(100, 40);
			this->buttonEllipse->TabIndex = 3;
			this->buttonEllipse->Text = L"İëëèïñ";
			this->buttonEllipse->UseVisualStyleBackColor = true;
			this->buttonEllipse->Click += gcnew System::EventHandler(this, &MyForm::btnEllipse_Click);
			// 
			// buttonRect
			// 
			this->buttonRect->Location = System::Drawing::Point(230, 50);  // 120 + 100 + 10 = 230
			this->buttonRect->Name = L"buttonRect";
			this->buttonRect->Size = System::Drawing::Size(100, 40);
			this->buttonRect->TabIndex = 4;
			this->buttonRect->Text = L"Ïğÿìîóãîëüíèê";
			this->buttonRect->UseVisualStyleBackColor = true;
			this->buttonRect->Click += gcnew System::EventHandler(this, &MyForm::btnRect_Click);
			// 
			// btnPenColor
			// 
			this->btnPenColor->BackColor = System::Drawing::Color::Black;
			this->btnPenColor->ForeColor = System::Drawing::Color::White;
			this->btnPenColor->Location = System::Drawing::Point(340, 50);  // 230 + 100 + 10 = 340
			this->btnPenColor->Name = L"btnPenColor";
			this->btnPenColor->Size = System::Drawing::Size(100, 40);
			this->btnPenColor->TabIndex = 5;
			this->btnPenColor->Text = L"Öâåò ëèíèè";
			this->btnPenColor->UseVisualStyleBackColor = false;
			this->btnPenColor->Click += gcnew System::EventHandler(this, &MyForm::öâåòToolStripMenuItem_Click);
			// 
			// btnBrushColor
			// 
			this->btnBrushColor->BackColor = System::Drawing::Color::White;
			this->btnBrushColor->Location = System::Drawing::Point(450, 50);  // 340 + 100 + 10 = 450
			this->btnBrushColor->Name = L"btnBrushColor";
			this->btnBrushColor->Size = System::Drawing::Size(100, 40);
			this->btnBrushColor->TabIndex = 6;
			this->btnBrushColor->Text = L"Öâåò çàëèâêè";
			this->btnBrushColor->UseVisualStyleBackColor = false;
			this->btnBrushColor->Click += gcnew System::EventHandler(this, &MyForm::öâåòToolStripMenuItem1_Click);
			// 
			// buttonEraser
			// 
			this->buttonEraser->Location = System::Drawing::Point(560, 50);  // 450 + 100 + 10 = 560
			this->buttonEraser->Name = L"buttonEraser";
			this->buttonEraser->Size = System::Drawing::Size(100, 40);
			this->buttonEraser->TabIndex = 7;
			this->buttonEraser->Text = L"Ëàñòèê";
			this->buttonEraser->UseVisualStyleBackColor = true;
			this->buttonEraser->Click += gcnew System::EventHandler(this, &MyForm::btnEraser_Click);
			// 
			// btnUndo
			// 
			this->btnUndo->Location = System::Drawing::Point(680, 50);  // 560 + 100 + 20 = 680
			this->btnUndo->Name = L"btnUndo";
			this->btnUndo->Size = System::Drawing::Size(80, 40);
			this->btnUndo->TabIndex = 8;
			this->btnUndo->Text = L"Îòìåíà";
			this->btnUndo->UseVisualStyleBackColor = true;
			this->btnUndo->Click += gcnew System::EventHandler(this, &MyForm::btnUndo_Click);
			// 
			// btnRedo
			// 
			this->btnRedo->Location = System::Drawing::Point(770, 50);  // 680 + 80 + 10 = 770
			this->btnRedo->Name = L"btnRedo";
			this->btnRedo->Size = System::Drawing::Size(80, 40);
			this->btnRedo->TabIndex = 9;
			this->btnRedo->Text = L"Ïîâòîğ";
			this->btnRedo->UseVisualStyleBackColor = true;
			this->btnRedo->Click += gcnew System::EventHandler(this, &MyForm::btnRedo_Click);
			// 
			// toolLabel
			// 
			this->toolLabel->AutoSize = true;
			this->toolLabel->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9, System::Drawing::FontStyle::Bold));
			this->toolLabel->Location = System::Drawing::Point(870, 20);
			this->toolLabel->Name = L"toolLabel";
			this->toolLabel->Size = System::Drawing::Size(105, 20);
			this->toolLabel->TabIndex = 10;
			this->toolLabel->Text = L"Òåêóùèé: İëëèïñ";
			// 
			// zoomTrackBar
			// 
			this->zoomTrackBar->Location = System::Drawing::Point(870, 50);
			this->zoomTrackBar->Name = L"zoomTrackBar";
			this->zoomTrackBar->Size = System::Drawing::Size(100, 56);
			this->zoomTrackBar->TabIndex = 11;
			this->zoomTrackBar->Scroll += gcnew System::EventHandler(this, &MyForm::zoomTrackBar_Scroll);
			// 
			// zoomLabel
			// 
			this->zoomLabel->AutoSize = true;
			this->zoomLabel->Location = System::Drawing::Point(920, 80);
			this->zoomLabel->Name = L"zoomLabel";
			this->zoomLabel->Size = System::Drawing::Size(47, 20);
			this->zoomLabel->TabIndex = 12;
			this->zoomLabel->Text = L"100%";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::White;
			this->pictureBox1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pictureBox1->Location = System::Drawing::Point(0, 128);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1000, 332);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pictureBox1_Paint);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::pictureBox1_MouseUp);
			// 
			// statusStrip
			// 
			this->statusStrip->ImageScalingSize = System::Drawing::Size(20, 20);
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->statusLabel,
					this->positionLabel,
					this->toolStatusLabel
			});
			this->statusStrip->Location = System::Drawing::Point(0, 460);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(1000, 26);
			this->statusStrip->TabIndex = 3;
			this->statusStrip->Text = L"statusStrip1";
			// 
			// statusLabel
			// 
			this->statusLabel->Name = L"statusLabel";
			this->statusLabel->Size = System::Drawing::Size(56, 20);
			this->statusLabel->Text = L"Ãîòîâ";
			// 
			// positionLabel
			// 
			this->positionLabel->Name = L"positionLabel";
			this->positionLabel->Size = System::Drawing::Size(81, 20);
			this->positionLabel->Text = L"Ïîçèöèÿ: 0,0";
			// 
			// toolStatusLabel
			// 
			this->toolStatusLabel->Name = L"toolStatusLabel";
			this->toolStatusLabel->Size = System::Drawing::Size(127, 20);
			this->toolStatusLabel->Text = L"Èíñòğóìåíò: İëëèïñ";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1000, 486);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->statusStrip);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->menuStrip1);
			this->DoubleBuffered = true;
			this->Name = L"MyForm";
			this->Text = L"Ãğàôè÷åñêèé ğåäàêòîğ - Ïğîôåññèîíàëüíàÿ âåğñèÿ";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->zoomTrackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion

		// Îáğàáîò÷èêè ìåíş
	private: System::Void ñîçäàòüToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		SaveState();
		if (pictureBox1->Image != nullptr) delete pictureBox1->Image;
		pictureBox1->Image = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
		Graphics^ g = Graphics::FromImage(pictureBox1->Image);
		g->Clear(Color::White);
		delete g;
		pictureBox1->Invalidate();
		statusLabel->Text = L"Ñîçäàí íîâûé äîêóìåíò";
	}

	private: System::Void îòêğûòüToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			SaveState();
			if (pictureBox1->Image != nullptr) delete pictureBox1->Image;
			pictureBox1->Image = Image::FromFile(openFileDialog1->FileName);
			pictureBox1->Invalidate();
			statusLabel->Text = L"Ôàéë îòêğûò: " + openFileDialog1->FileName;
		}
	}

	private: System::Void ñîõğàíèòüÊàêToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (pictureBox1->Image != nullptr && saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			pictureBox1->Image->Save(saveFileDialog1->FileName);
			statusLabel->Text = L"Ôàéë ñîõğàíåí: " + saveFileDialog1->FileName;
		}
	}

	private: System::Void âûõîäToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Application::Exit();
	}

		   // Îáğàáîò÷èêè èíñòğóìåíòîâ
	private: System::Void btnEllipse_Click(System::Object^ sender, System::EventArgs^ e)
	{
		tool = 1;
		UpdateToolDisplay();
		toolLabel->Text = L"Òåêóùèé: İëëèïñ";
		statusLabel->Text = L"Âûáğàí èíñòğóìåíò: İëëèïñ";
	}

	private: System::Void btnRect_Click(System::Object^ sender, System::EventArgs^ e)
	{
		tool = 2;
		UpdateToolDisplay();
		toolLabel->Text = L"Òåêóùèé: Ïğÿìîóãîëüíèê";
		statusLabel->Text = L"Âûáğàí èíñòğóìåíò: Ïğÿìîóãîëüíèê";
	}

	private: System::Void btnLine_Click(System::Object^ sender, System::EventArgs^ e)
	{
		tool = 3;
		UpdateToolDisplay();
		toolLabel->Text = L"Òåêóùèé: Ëèíèÿ";
		statusLabel->Text = L"Âûáğàí èíñòğóìåíò: Ëèíèÿ";
	}

	private: System::Void btnEraser_Click(System::Object^ sender, System::EventArgs^ e)
	{
		tool = 4;
		UpdateToolDisplay();
		toolLabel->Text = L"Òåêóùèé: Ëàñòèê";
		statusLabel->Text = L"Âûáğàí èíñòğóìåíò: Ëàñòèê";
	}

		   // Îáğàáîò÷èêè öâåòà
	private: System::Void öâåòToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (penColorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			btnPenColor->BackColor = penColorDialog->Color;
			int brightness = (int)(penColorDialog->Color.R * 0.299 + penColorDialog->Color.G * 0.587 + penColorDialog->Color.B * 0.114);
			btnPenColor->ForeColor = (brightness < 128) ? Color::White : Color::Black;
			statusLabel->Text = L"Âûáğàí öâåò ëèíèè";
		}
	}

	private: System::Void öâåòToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (brushColorDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			btnBrushColor->BackColor = brushColorDialog->Color;
			int brightness = (int)(brushColorDialog->Color.R * 0.299 + brushColorDialog->Color.G * 0.587 + brushColorDialog->Color.B * 0.114);
			btnBrushColor->ForeColor = (brightness < 128) ? Color::White : Color::Black;
			statusLabel->Text = L"Âûáğàí öâåò çàëèâêè";
		}
	}

		   // Ôèëüòğû
	private: System::Void ÷åğíîÁåëûéToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (pictureBox1->Image == nullptr) return;
		SaveState();

		Bitmap^ bmp = gcnew Bitmap(pictureBox1->Image);
		for (int y = 0; y < bmp->Height; y++)
		{
			for (int x = 0; x < bmp->Width; x++)
			{
				Color pixel = bmp->GetPixel(x, y);
				int gray = (pixel.R + pixel.G + pixel.B) / 3;
				bmp->SetPixel(x, y, Color::FromArgb(gray, gray, gray));
			}
		}
		delete pictureBox1->Image;
		pictureBox1->Image = bmp;
		pictureBox1->Invalidate();
		statusLabel->Text = L"Ïğèìåíåí ÷åğíî-áåëûé ôèëüòğ";
	}

	private: System::Void èíâåğòèğîâàòüToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (pictureBox1->Image == nullptr) return;
		SaveState();

		Bitmap^ bmp = gcnew Bitmap(pictureBox1->Image);
		for (int y = 0; y < bmp->Height; y++)
		{
			for (int x = 0; x < bmp->Width; x++)
			{
				Color pixel = bmp->GetPixel(x, y);
				bmp->SetPixel(x, y, Color::FromArgb(255 - pixel.R, 255 - pixel.G, 255 - pixel.B));
			}
		}
		delete pictureBox1->Image;
		pictureBox1->Image = bmp;
		pictureBox1->Invalidate();
		statusLabel->Text = L"Öâåòà èíâåğòèğîâàíû";
	}

		   // Undo/Redo
	private: System::Void btnUndo_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (undoStack->Count > 0)
		{
			if (pictureBox1->Image != nullptr)
			{
				Bitmap^ current = gcnew Bitmap(pictureBox1->Image);
				redoStack->Push(current);
			}

			pictureBox1->Image = undoStack->Pop();
			pictureBox1->Invalidate();
			statusLabel->Text = L"Îòìåíà äåéñòâèÿ";
		}
		else
		{
			statusLabel->Text = L"Íåò äåéñòâèé äëÿ îòìåíû";
		}
	}

	private: System::Void btnRedo_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (redoStack->Count > 0)
		{
			if (pictureBox1->Image != nullptr)
			{
				Bitmap^ current = gcnew Bitmap(pictureBox1->Image);
				undoStack->Push(current);
			}

			pictureBox1->Image = redoStack->Pop();
			pictureBox1->Invalidate();
			statusLabel->Text = L"Ïîâòîğ äåéñòâèÿ";
		}
		else
		{
			statusLabel->Text = L"Íåò äåéñòâèé äëÿ ïîâòîğà";
		}
	}

		   // Çóì
	private: System::Void zoomTrackBar_Scroll(System::Object^ sender, System::EventArgs^ e)
	{
		zoomFactor = zoomTrackBar->Value / 100.0f;
		zoomLabel->Text = String::Format(L"{0}%", zoomTrackBar->Value);

		if (zoomFactor != 1.0f)
		{
			int newWidth = (int)(pictureBox1->Image->Width * zoomFactor);
			int newHeight = (int)(pictureBox1->Image->Height * zoomFactor);
			pictureBox1->Size = System::Drawing::Size(newWidth, newHeight);
		}
		else
		{
			pictureBox1->SizeMode = PictureBoxSizeMode::Zoom;
		}
		statusLabel->Text = String::Format(L"Ìàñøòàá: {0}%", zoomTrackBar->Value);
	}

		   // Ãîğÿ÷èå êëàâèøè
	private: System::Void MyForm_KeyDown(Object^ sender, KeyEventArgs^ e)
	{
		if (e->Control && e->KeyCode == Keys::Z)
		{
			btnUndo_Click(nullptr, nullptr);
			e->Handled = true;
		}
		else if (e->Control && e->KeyCode == Keys::Y)
		{
			btnRedo_Click(nullptr, nullptr);
			e->Handled = true;
		}
		else if (e->Control && e->KeyCode == Keys::S)
		{
			ñîõğàíèòüÊàêToolStripMenuItem_Click(nullptr, nullptr);
			e->Handled = true;
		}
		else if (e->Control && e->KeyCode == Keys::O)
		{
			îòêğûòüToolStripMenuItem_Click(nullptr, nullptr);
			e->Handled = true;
		}
		else if (e->Control && e->KeyCode == Keys::N)
		{
			ñîçäàòüToolStripMenuItem_Click(nullptr, nullptr);
			e->Handled = true;
		}
		else if (e->KeyCode == Keys::L)
		{
			btnLine_Click(nullptr, nullptr);
			e->Handled = true;
		}
		else if (e->KeyCode == Keys::E)
		{
			btnEllipse_Click(nullptr, nullptr);
			e->Handled = true;
		}
		else if (e->KeyCode == Keys::R)
		{
			btnRect_Click(nullptr, nullptr);
			e->Handled = true;
		}
		else if (e->KeyCode == Keys::X)
		{
			btnEraser_Click(nullptr, nullptr);
			e->Handled = true;
		}
		else if (e->KeyCode == Keys::Escape)
		{
			isDrawing = false;
			pictureBox1->Invalidate();
			statusLabel->Text = L"Ğèñîâàíèå îòìåíåíî";
			e->Handled = true;
		}

		isShiftPressed = e->Shift;
	}

		   // Îáğàáîò÷èêè ìûøè äëÿ ğèñîâàíèÿ
	private: System::Void pictureBox1_MouseDown(System::Object^ sender, MouseEventArgs^ e)
	{
		if (pictureBox1->Image == nullptr) return;
		if (e->Button == System::Windows::Forms::MouseButtons::Left)
		{
			SaveState();
			startX = e->X;
			startY = e->Y;
			prevX = e->X;
			prevY = e->Y;
			currentPoint = Point(e->X, e->Y);
			isDrawing = true;
			statusLabel->Text = L"Ğèñîâàíèå...";
		}
	}

	private: System::Void pictureBox1_MouseMove(System::Object^ sender, MouseEventArgs^ e)
	{
		positionLabel->Text = String::Format(L"Ïîçèöèÿ: {0},{1}", e->X, e->Y);

		if (!isDrawing) return;

		currentPoint = Point(e->X, e->Y);

		if (tool == 4) // Ëàñòèê
		{
			Graphics^ g = Graphics::FromImage(pictureBox1->Image);
			g->FillRectangle(gcnew SolidBrush(Color::White), e->X - 5, e->Y - 5, 10, 10);
			delete g;
			pictureBox1->Invalidate();
		}
		else if (tool == 3) // Ëèíèÿ
		{
			previewRect = Rectangle(0, 0, 0, 0);
			pictureBox1->Invalidate();
		}
		else // İëëèïñ èëè ïğÿìîóãîëüíèê
		{
			int width = Math::Abs(e->X - startX);
			int height = Math::Abs(e->Y - startY);

			if (isShiftPressed)
			{
				int size = Math::Max(width, height);
				width = size;
				height = size;
			}

			previewRect = Rectangle(
				Math::Min(startX, startX + (e->X > startX ? width : -width)),
				Math::Min(startY, startY + (e->Y > startY ? height : -height)),
				width, height
			);
			pictureBox1->Invalidate();
		}
	}

	private: System::Void pictureBox1_MouseUp(System::Object^ sender, MouseEventArgs^ e)
	{
		if (pictureBox1->Image == nullptr || !isDrawing) return;

		Graphics^ g = Graphics::FromImage(pictureBox1->Image);
		g->SmoothingMode = SmoothingMode::AntiAlias;

		float thickness = (float)safe_cast<int>(thicknessCombo->SelectedItem);
		Pen^ pen = gcnew Pen(penColorDialog->Color, thickness);
		SolidBrush^ brush = gcnew SolidBrush(brushColorDialog->Color);

		int nx = Math::Min(startX, e->X);
		int ny = Math::Min(startY, e->Y);
		int nw = Math::Abs(e->X - startX);
		int nh = Math::Abs(e->Y - startY);

		if (isShiftPressed && tool != 3)
		{
			int size = Math::Max(nw, nh);
			nw = size;
			nh = size;
			if (e->X < startX) nx = startX - size;
			if (e->Y < startY) ny = startY - size;
		}

		try
		{
			switch (tool)
			{
			case 1: // İëëèïñ
				if (nw > 0 && nh > 0)
				{
					if (chkFill->Checked) g->FillEllipse(brush, nx, ny, nw, nh);
					g->DrawEllipse(pen, nx, ny, nw, nh);
				}
				break;

			case 2: // Ïğÿìîóãîëüíèê
				if (nw > 0 && nh > 0)
				{
					if (chkFill->Checked) g->FillRectangle(brush, nx, ny, nw, nh);
					g->DrawRectangle(pen, nx, ny, nw, nh);
				}
				break;

			case 3: // Ëèíèÿ
				g->DrawLine(pen, startX, startY, e->X, e->Y);
				break;
			}

			statusLabel->Text = String::Format(L"Íàğèñîâàí {0}", currentTool->ToLower());
		}
		finally
		{
			delete pen;
			delete brush;
			delete g;
		}

		isDrawing = false;
		previewRect = Rectangle(0, 0, 0, 0);
		pictureBox1->Invalidate();
	}

	private: System::Void pictureBox1_Paint(System::Object^ sender, PaintEventArgs^ e)
	{
		if (!isDrawing || tool == 4) return;

		e->Graphics->SmoothingMode = SmoothingMode::AntiAlias;
		float thickness = (float)safe_cast<int>(thicknessCombo->SelectedItem);

		if (tool == 3) // Ëèíèÿ
		{
			Pen^ pPreview = gcnew Pen(penColorDialog->Color, thickness);
			pPreview->DashStyle = DashStyle::Dash;
			e->Graphics->DrawLine(pPreview, startX, startY, currentPoint.X, currentPoint.Y);
			delete pPreview;
		}
		else if (previewRect.Width > 0 && previewRect.Height > 0) // İëëèïñ èëè ïğÿìîóãîëüíèê
		{
			Pen^ pPreview = gcnew Pen(penColorDialog->Color, thickness);
			pPreview->DashStyle = DashStyle::Dash;

			if (chkFill->Checked)
			{
				SolidBrush^ bPreview = gcnew SolidBrush(Color::FromArgb(100, brushColorDialog->Color));

				if (tool == 1) e->Graphics->FillEllipse(bPreview, previewRect);
				else if (tool == 2) e->Graphics->FillRectangle(bPreview, previewRect);

				delete bPreview;
			}

			if (tool == 1) e->Graphics->DrawEllipse(pPreview, previewRect);
			else if (tool == 2) e->Graphics->DrawRectangle(pPreview, previewRect);

			delete pPreview;
		}
	}
	};
}