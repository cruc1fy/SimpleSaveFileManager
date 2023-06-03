#pragma once

#include <string>
#include <vector>
#include <filesystem>
#include <msclr/marshal_cppstd.h>

#include "ChangeHandle.h"
#include "FileListByHandle.h"
#include "RestoreFileFromVersions.h"
#include "Utils.h"
#include "FileCtrlStore.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

using namespace std;

using namespace utils;

extern TFileCtrlStore * pFileCtrlStore;// Не определение переменной, а только ее заголовок

namespace LabWork01CLR {

  const int ciBegMainFormCount = 50;
    
//  const string cssRootFolder = "C:\\";
    
  const int ciVerticalScrollBarWidth = 17;

  string ssCurSaveDir = "";
  int iTimeDeltaHours=24, iTimeDeltaMinutes=0, iTimeDeltaSeconds=0;

	public ref class MainForm : public System::Windows::Forms::Form {
  protected:
    String^ cssBegSaveDir = L"C:\\SAVE_DIR\\";
    String^ cssBegRestoreDir = L"C:\\RESTORE_DIR\\";
    String^ cssBegWorkDir = L"C:\\WORK_DIR\\";

    RestoreFileFromVersions^ formRestoreFileFromVersions = nullptr;

  private: System::Windows::Forms::GroupBox^  groupBox1;
  protected:
  private: System::Windows::Forms::Button^  butChangeRestoreDir;
  private: System::Windows::Forms::Timer^  timerBackup;
  private: System::Windows::Forms::GroupBox^  groupBox2;
  private: System::Windows::Forms::Button^  buttonChangeWorkDir;

  private: System::Windows::Forms::TextBox^  textBoxWorkDir;


  private: System::Windows::Forms::TextBox^  textBoxRestoreDir;
         
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
    ~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
  private: System::Windows::Forms::GroupBox^  groupBoxSaveDir;
  protected:
  private: System::Windows::Forms::Button^  buttonChangeSaveDir;
  private: System::Windows::Forms::TextBox^  textBoxSaveDir;
  private: System::Windows::Forms::GroupBox^  groupBoxTimeDelta;
  private: System::Windows::Forms::Button^  buttonSetTimePeriod;

  private: System::Windows::Forms::MaskedTextBox^  maskedTextBoxMinutes;
  private: System::Windows::Forms::MaskedTextBox^  maskedTextBoxHours;
  private: System::Windows::Forms::Panel^  panelMain;
  private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanelMain;
  private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
  private: System::Windows::Forms::Button^  buttonAdd;
  private: System::Windows::Forms::Button^  buttonRestore;
  private: System::Windows::Forms::Button^  buttonChange;
  private: System::Windows::Forms::Button^  buttonClose;
  private: System::Windows::Forms::OpenFileDialog^  openFileDialogAdd;
  private: System::ComponentModel::IContainer^  components;


	private:


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
      this->components = (gcnew System::ComponentModel::Container());
      this->groupBoxSaveDir = (gcnew System::Windows::Forms::GroupBox());
      this->buttonChangeSaveDir = (gcnew System::Windows::Forms::Button());
      this->textBoxSaveDir = (gcnew System::Windows::Forms::TextBox());
      this->groupBoxTimeDelta = (gcnew System::Windows::Forms::GroupBox());
      this->buttonSetTimePeriod = (gcnew System::Windows::Forms::Button());
      this->maskedTextBoxMinutes = (gcnew System::Windows::Forms::MaskedTextBox());
      this->maskedTextBoxHours = (gcnew System::Windows::Forms::MaskedTextBox());
      this->panelMain = (gcnew System::Windows::Forms::Panel());
      this->tableLayoutPanelMain = (gcnew System::Windows::Forms::TableLayoutPanel());
      this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
      this->buttonAdd = (gcnew System::Windows::Forms::Button());
      this->buttonRestore = (gcnew System::Windows::Forms::Button());
      this->buttonChange = (gcnew System::Windows::Forms::Button());
      this->buttonClose = (gcnew System::Windows::Forms::Button());
      this->openFileDialogAdd = (gcnew System::Windows::Forms::OpenFileDialog());
      this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
      this->butChangeRestoreDir = (gcnew System::Windows::Forms::Button());
      this->textBoxRestoreDir = (gcnew System::Windows::Forms::TextBox());
      this->timerBackup = (gcnew System::Windows::Forms::Timer(this->components));
      this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
      this->buttonChangeWorkDir = (gcnew System::Windows::Forms::Button());
      this->textBoxWorkDir = (gcnew System::Windows::Forms::TextBox());
      this->groupBoxSaveDir->SuspendLayout();
      this->groupBoxTimeDelta->SuspendLayout();
      this->panelMain->SuspendLayout();
      this->tableLayoutPanel1->SuspendLayout();
      this->groupBox1->SuspendLayout();
      this->groupBox2->SuspendLayout();
      this->SuspendLayout();
      // 
      // groupBoxSaveDir
      // 
      this->groupBoxSaveDir->Controls->Add(this->buttonChangeSaveDir);
      this->groupBoxSaveDir->Controls->Add(this->textBoxSaveDir);
      this->groupBoxSaveDir->Location = System::Drawing::Point(4,4);
      this->groupBoxSaveDir->Name = L"groupBoxSaveDir";
      this->groupBoxSaveDir->Size = System::Drawing::Size(266,51);
      this->groupBoxSaveDir->TabIndex = 0;
      this->groupBoxSaveDir->TabStop = false;
      this->groupBoxSaveDir->Text = L"Directory to save files";
      // 
      // buttonChangeSaveDir
      // 
      this->buttonChangeSaveDir->Location = System::Drawing::Point(190,17);
      this->buttonChangeSaveDir->Name = L"buttonChangeSaveDir";
      this->buttonChangeSaveDir->Size = System::Drawing::Size(72,22);
      this->buttonChangeSaveDir->TabIndex = 1;
      this->buttonChangeSaveDir->Text = L"Change";
      this->buttonChangeSaveDir->UseVisualStyleBackColor = true;
      this->buttonChangeSaveDir->Click += gcnew System::EventHandler(this,&MainForm::buttonChangeSaveDir_Click);
      // 
      // textBoxSaveDir
      // 
      this->textBoxSaveDir->Location = System::Drawing::Point(4,18);
      this->textBoxSaveDir->Name = L"textBoxSaveDir";
      this->textBoxSaveDir->ReadOnly = true;
      this->textBoxSaveDir->Size = System::Drawing::Size(180,20);
      this->textBoxSaveDir->TabIndex = 0;
      // 
      // groupBoxTimeDelta
      // 
      this->groupBoxTimeDelta->Controls->Add(this->buttonSetTimePeriod);
      this->groupBoxTimeDelta->Controls->Add(this->maskedTextBoxMinutes);
      this->groupBoxTimeDelta->Controls->Add(this->maskedTextBoxHours);
      this->groupBoxTimeDelta->Location = System::Drawing::Point(838,4);
      this->groupBoxTimeDelta->Name = L"groupBoxTimeDelta";
      this->groupBoxTimeDelta->Size = System::Drawing::Size(160,51);
      this->groupBoxTimeDelta->TabIndex = 2;
      this->groupBoxTimeDelta->TabStop = false;
      this->groupBoxTimeDelta->Text = L"Time period: HH:MM";
      // 
      // buttonSetTimePeriod
      // 
      this->buttonSetTimePeriod->Location = System::Drawing::Point(78,18);
      this->buttonSetTimePeriod->Name = L"buttonSetTimePeriod";
      this->buttonSetTimePeriod->Size = System::Drawing::Size(75,23);
      this->buttonSetTimePeriod->TabIndex = 3;
      this->buttonSetTimePeriod->Text = L"Set";
      this->buttonSetTimePeriod->UseVisualStyleBackColor = true;
      this->buttonSetTimePeriod->Click += gcnew System::EventHandler(this,&MainForm::buttonSetTimePeriod_Click);
      // 
      // maskedTextBoxMinutes
      // 
      this->maskedTextBoxMinutes->Location = System::Drawing::Point(47,19);
      this->maskedTextBoxMinutes->Mask = L"00";
      this->maskedTextBoxMinutes->Name = L"maskedTextBoxMinutes";
      this->maskedTextBoxMinutes->Size = System::Drawing::Size(25,20);
      this->maskedTextBoxMinutes->TabIndex = 1;
      this->maskedTextBoxMinutes->Text = L"0";
      this->maskedTextBoxMinutes->Validating += gcnew System::ComponentModel::CancelEventHandler(this,&MainForm::maskedTextBoxMinutes_Validating);
      // 
      // maskedTextBoxHours
      // 
      this->maskedTextBoxHours->Location = System::Drawing::Point(6,19);
      this->maskedTextBoxHours->Mask = L"0000";
      this->maskedTextBoxHours->Name = L"maskedTextBoxHours";
      this->maskedTextBoxHours->Size = System::Drawing::Size(35,20);
      this->maskedTextBoxHours->TabIndex = 0;
      this->maskedTextBoxHours->Text = L"24";
      this->maskedTextBoxHours->Validating += gcnew System::ComponentModel::CancelEventHandler(this,&MainForm::maskedTextBoxHours_Validating);
      // 
      // panelMain
      // 
      this->panelMain->Controls->Add(this->tableLayoutPanelMain);
      this->panelMain->Location = System::Drawing::Point(4,63);
      this->panelMain->Name = L"panelMain";
      this->panelMain->Size = System::Drawing::Size(1007,535);
      this->panelMain->TabIndex = 4;
      // 
      // tableLayoutPanelMain
      // 
      this->tableLayoutPanelMain->AutoScroll = true;
      this->tableLayoutPanelMain->AutoSize = true;
      this->tableLayoutPanelMain->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
      this->tableLayoutPanelMain->ColumnCount = 5;
      this->tableLayoutPanelMain->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
        5)));
      this->tableLayoutPanelMain->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
        80)));
      this->tableLayoutPanelMain->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
        5)));
      this->tableLayoutPanelMain->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
        5)));
      this->tableLayoutPanelMain->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
        5)));
      this->tableLayoutPanelMain->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute,
        20)));
      this->tableLayoutPanelMain->Location = System::Drawing::Point(4,4);
      this->tableLayoutPanelMain->Name = L"tableLayoutPanelMain";
      this->tableLayoutPanelMain->RowCount = 3;
      this->tableLayoutPanelMain->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
        20)));
      this->tableLayoutPanelMain->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
        20)));
      this->tableLayoutPanelMain->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute,
        20)));
      this->tableLayoutPanelMain->Size = System::Drawing::Size(1000,477);
      this->tableLayoutPanelMain->TabIndex = 1;
      // 
      // tableLayoutPanel1
      // 
      this->tableLayoutPanel1->ColumnCount = 4;
      this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
        25)));
      this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
        25)));
      this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
        25)));
      this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
        25)));
      this->tableLayoutPanel1->Controls->Add(this->buttonAdd,0,0);
      this->tableLayoutPanel1->Controls->Add(this->buttonRestore,1,0);
      this->tableLayoutPanel1->Controls->Add(this->buttonChange,2,0);
      this->tableLayoutPanel1->Controls->Add(this->buttonClose,3,0);
      this->tableLayoutPanel1->Location = System::Drawing::Point(1,604);
      this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
      this->tableLayoutPanel1->RowCount = 1;
      this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,100)));
      this->tableLayoutPanel1->Size = System::Drawing::Size(1010,56);
      this->tableLayoutPanel1->TabIndex = 5;
      // 
      // buttonAdd
      // 
      this->buttonAdd->Location = System::Drawing::Point(3,3);
      this->buttonAdd->Name = L"buttonAdd";
      this->buttonAdd->Size = System::Drawing::Size(246,50);
      this->buttonAdd->TabIndex = 0;
      this->buttonAdd->Text = L"Add";
      this->buttonAdd->UseVisualStyleBackColor = true;
      this->buttonAdd->Click += gcnew System::EventHandler(this,&MainForm::buttonAdd_Click);
      // 
      // buttonRestore
      // 
      this->buttonRestore->Enabled = false;
      this->buttonRestore->Location = System::Drawing::Point(255,3);
      this->buttonRestore->Name = L"buttonRestore";
      this->buttonRestore->Size = System::Drawing::Size(246,50);
      this->buttonRestore->TabIndex = 1;
      this->buttonRestore->Text = L"Restore";
      this->buttonRestore->UseVisualStyleBackColor = true;
      this->buttonRestore->Click += gcnew System::EventHandler(this,&MainForm::buttonRestore_Click);
      // 
      // buttonChange
      // 
      this->buttonChange->Enabled = false;
      this->buttonChange->Location = System::Drawing::Point(507,3);
      this->buttonChange->Name = L"buttonChange";
      this->buttonChange->Size = System::Drawing::Size(246,50);
      this->buttonChange->TabIndex = 2;
      this->buttonChange->Text = L"File List";
      this->buttonChange->UseVisualStyleBackColor = true;
      this->buttonChange->Click += gcnew System::EventHandler(this,&MainForm::buttonChange_Click);
      // 
      // buttonClose
      // 
      this->buttonClose->Location = System::Drawing::Point(759,3);
      this->buttonClose->Name = L"buttonClose";
      this->buttonClose->Size = System::Drawing::Size(248,50);
      this->buttonClose->TabIndex = 3;
      this->buttonClose->Text = L"Close";
      this->buttonClose->UseVisualStyleBackColor = true;
      this->buttonClose->Click += gcnew System::EventHandler(this,&MainForm::buttonClose_Click);
      // 
      // openFileDialogAdd
      // 
      this->openFileDialogAdd->Filter = L"All files(*.*)|*.*";
      this->openFileDialogAdd->InitialDirectory = L"C:\\WORK_DIR";
      this->openFileDialogAdd->Multiselect = true;
      this->openFileDialogAdd->RestoreDirectory = true;
      // 
      // groupBox1
      // 
      this->groupBox1->Controls->Add(this->butChangeRestoreDir);
      this->groupBox1->Controls->Add(this->textBoxRestoreDir);
      this->groupBox1->Location = System::Drawing::Point(276,4);
      this->groupBox1->Name = L"groupBox1";
      this->groupBox1->Size = System::Drawing::Size(277,51);
      this->groupBox1->TabIndex = 6;
      this->groupBox1->TabStop = false;
      this->groupBox1->Text = L"Directory to restore files";
      // 
      // butChangeRestoreDir
      // 
      this->butChangeRestoreDir->Location = System::Drawing::Point(199,16);
      this->butChangeRestoreDir->Name = L"butChangeRestoreDir";
      this->butChangeRestoreDir->Size = System::Drawing::Size(72,22);
      this->butChangeRestoreDir->TabIndex = 1;
      this->butChangeRestoreDir->Text = L"Change";
      this->butChangeRestoreDir->UseVisualStyleBackColor = true;
      this->butChangeRestoreDir->Click += gcnew System::EventHandler(this,&MainForm::butChangeRestoreDir_Click);
      // 
      // textBoxRestoreDir
      // 
      this->textBoxRestoreDir->Location = System::Drawing::Point(6,19);
      this->textBoxRestoreDir->Name = L"textBoxRestoreDir";
      this->textBoxRestoreDir->ReadOnly = true;
      this->textBoxRestoreDir->Size = System::Drawing::Size(180,20);
      this->textBoxRestoreDir->TabIndex = 0;
      // 
      // timerBackup
      // 
      this->timerBackup->Tick += gcnew System::EventHandler(this,&MainForm::timerBackup_Tick);
      // 
      // groupBox2
      // 
      this->groupBox2->Controls->Add(this->buttonChangeWorkDir);
      this->groupBox2->Controls->Add(this->textBoxWorkDir);
      this->groupBox2->Location = System::Drawing::Point(559,4);
      this->groupBox2->Name = L"groupBox2";
      this->groupBox2->Size = System::Drawing::Size(273,51);
      this->groupBox2->TabIndex = 7;
      this->groupBox2->TabStop = false;
      this->groupBox2->Text = L"Directory for work files";
      // 
      // buttonChangeWorkDir
      // 
      this->buttonChangeWorkDir->Location = System::Drawing::Point(192,17);
      this->buttonChangeWorkDir->Name = L"buttonChangeWorkDir";
      this->buttonChangeWorkDir->Size = System::Drawing::Size(72,22);
      this->buttonChangeWorkDir->TabIndex = 1;
      this->buttonChangeWorkDir->Text = L"Change";
      this->buttonChangeWorkDir->UseVisualStyleBackColor = true;
      this->buttonChangeWorkDir->Click += gcnew System::EventHandler(this,&MainForm::button1_Click);
      // 
      // textBoxWorkDir
      // 
      this->textBoxWorkDir->Location = System::Drawing::Point(6,19);
      this->textBoxWorkDir->Name = L"textBoxWorkDir";
      this->textBoxWorkDir->ReadOnly = true;
      this->textBoxWorkDir->Size = System::Drawing::Size(180,20);
      this->textBoxWorkDir->TabIndex = 0;
      // 
      // MainForm
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6,13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(1013,663);
      this->Controls->Add(this->groupBox2);
      this->Controls->Add(this->groupBox1);
      this->Controls->Add(this->tableLayoutPanel1);
      this->Controls->Add(this->panelMain);
      this->Controls->Add(this->groupBoxTimeDelta);
      this->Controls->Add(this->groupBoxSaveDir);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
      this->MaximizeBox = false;
      this->Name = L"MainForm";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
      this->Text = L"SaveFileManager";
      this->Load += gcnew System::EventHandler(this,&MainForm::MainForm_Load);
      this->groupBoxSaveDir->ResumeLayout(false);
      this->groupBoxSaveDir->PerformLayout();
      this->groupBoxTimeDelta->ResumeLayout(false);
      this->groupBoxTimeDelta->PerformLayout();
      this->panelMain->ResumeLayout(false);
      this->panelMain->PerformLayout();
      this->tableLayoutPanel1->ResumeLayout(false);
      this->groupBox1->ResumeLayout(false);
      this->groupBox1->PerformLayout();
      this->groupBox2->ResumeLayout(false);
      this->groupBox2->PerformLayout();
      this->ResumeLayout(false);

    }// InitializeComponent
#pragma endregion

    void FInitMainPanelFill(TableLayoutPanel^ panel)
    // Инициализирует TableLayoutPanel при открытии окна.
    {
      panel->SuspendLayout();
      panel->RowCount = 0;
      panel->RowStyles->Clear();
      panel->Padding = System::Windows::Forms::Padding(0, 0, ciVerticalScrollBarWidth, 0);
//      panel->MaximumSize = new Size(panel.Width, panel.Height);
      panel->MaximumSize = System::Drawing::Size(panel->Width, panel->Height);
      panel->ResumeLayout();
    }

    Control^ FCreateNewItem(String^ sText)
    // Создает новый элемент CLR для добавления в TableLayoutPanel.
    {
      System::Windows::Forms::Label^ textNew = gcnew System::Windows::Forms::Label();
      textNew->AutoSize = true;
      textNew->Text = sText;
      return textNew;
    }

    void TreatError(String^ sText)
    // Вывести окно и затем выбросить исключение.
    {
      MessageBox::Show(sText);
      throw 0;
    }

    void ButtonRestoreOnClick(Object^ sender, EventArgs^ eventArgs)
    // Функция 2: выдача сохраненного файла по идентификатору. На вход подается идентификатор, на выход путь до файла.
    {
      if (!pFileCtrlStore) TreatError("FileCtrlStore doesn't exist");

      ButtonWithVal^ pButton = (ButtonWithVal^)sender;
      if (!pButton) return;

      int iHandle = pButton->GetVal();
  		string ssRestoreDir = msclr::interop::marshal_as<string>(textBoxRestoreDir->Text);// Получить директорию, в которую будем восстанавливать файл

      if (!ssRestoreDir.length()){
        MessageBox::Show("Set restore directory"); return;
      }

//      auto formRestoreFileFromVersions = gcnew RestoreFileFromVersions();
      formRestoreFileFromVersions = gcnew RestoreFileFromVersions();
      formRestoreFileFromVersions->SetHandle(iHandle);
      formRestoreFileFromVersions->SetRestoreDir(textBoxRestoreDir->Text);
      formRestoreFileFromVersions->ShowDialog();
    }

    void ButtonDeleteOnClick(Object^ sender, EventArgs^ eventArgs)
    // Функция 3: удаление файла по идентификатору (на вход подается идентификатор, на выход ничего).
    // Также удаляется файл из списка и соответствующая строка из панели.
    {
      if (!pFileCtrlStore) TreatError("FileCtrlStore doesn't exist");

      ButtonWithVal^ pButton = (ButtonWithVal^)sender;
      if (!pButton) return;

      int iHandle = pButton->GetVal();
      pFileCtrlStore->DeleteFileByHandle(iHandle);

      FRewritePanel();
      ChangeButStatus();
    }

    void ButtonChangeOnClick(Object^ sender, EventArgs^ eventArgs)
    // Изменить дескриптор для файла из указанной строки.
    // Функция 4: изменение идентификатора сохраненного файла (на вход два идентификатора, на выход ничего).
    {
      if (!pFileCtrlStore) TreatError("FileCtrlStore doesn't exist");

      ButtonWithVal^ pButton = (ButtonWithVal^)sender;
      if (!pButton) return;

      int iOldHandle = pButton->GetVal();

//      int iRow = pButton->GetVal();
      auto ButPos = tableLayoutPanelMain->GetPositionFromControl(pButton);
//      auto Val2 = tableLayoutPanelMain->GetCellPosition(pButton);
      int iRow = ButPos.Row;
      Control^ control = tableLayoutPanelMain->GetControlFromPosition(0, iRow);
//      int iOldHandle = Int32::Parse(control->Text);

      auto formChangeHandle = gcnew ChangeHandle(iOldHandle);
      formChangeHandle->ShowDialog();
//      this->Hide();

      int iNewHandle = formChangeHandle->GetNewHandle();
      if (iNewHandle == -1) return;

      control->Text = iNewHandle.ToString();

    //Функция 4: изменение идентификатора сохраненного файла (на вход два идентификатора, на выход ничего):
      pFileCtrlStore->ChangeFileHandle(iOldHandle,iNewHandle);

      delete formChangeHandle;

      FRewritePanel();
    }
    
    void FAddRowToPanel(TableLayoutPanel^ panel, String^ sFileName, int iHandle)
    // Добавляет строку в TableLayoutPanel.
    {
      panel->RowCount++;
      panel->RowStyles->Add(gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize));

//      std::string ssRowCount = std::to_string(panel->RowCount);
      std::string ssHandle = std::to_string(iHandle);
  		String^ sHandle = msclr::interop::marshal_as<String^>(ssHandle);

      panel->Controls->Add(FCreateNewItem(sHandle), 0, panel->RowCount);

      panel->Controls->Add(FCreateNewItem(sFileName), 1, panel->RowCount);

//      ButtonWithVal^ butDel = gcnew ButtonWithVal(panel->RowCount);
      ButtonWithVal^ butDel = gcnew ButtonWithVal(iHandle);
      butDel->Text = "X";
      butDel->Click += gcnew EventHandler(this, &MainForm::ButtonDeleteOnClick);
      panel->Controls->Add(butDel, 2, panel->RowCount);

//      ButtonWithVal^ butChange = gcnew ButtonWithVal(panel->RowCount);
      ButtonWithVal^ butChange = gcnew ButtonWithVal(iHandle);
      butChange->Text = "...";
      butChange->Click += gcnew EventHandler(this, &MainForm::ButtonChangeOnClick);
      panel->Controls->Add(butChange, 3, panel->RowCount);

//      ButtonWithVal^ butRestore = gcnew ButtonWithVal(panel->RowCount);
      ButtonWithVal^ butRestore = gcnew ButtonWithVal(iHandle);
      butRestore->Text = "R";
      butRestore->Click += gcnew EventHandler(this, &MainForm::ButtonRestoreOnClick);
      panel->Controls->Add(butRestore, 4, panel->RowCount);
    }

    void FRewritePanel()
    // Перерисовать главную панель заново.
    {
      tableLayoutPanelMain->SuspendLayout();
      tableLayoutPanelMain->Controls->Clear();
      tableLayoutPanelMain->RowCount = 0;

//      cli::array< String^ >^ arrWork = gcnew cli::array< String^ >(2);

      if (!pFileCtrlStore) return;
    //6. Получение списка всех файлов (на вход ничего, на выходе список из путей до файлов и их идентификаторов):
      std::vector<TFileCtrl *> vectFiles = pFileCtrlStore->GetAllFileCtrlList();

      for (TFileCtrl * pFileCtrl: vectFiles){
        if (!pFileCtrl) continue;
        int iHandle = pFileCtrl->GetHandle();
        std::string ssFileDir = pFileCtrl->GetFileDir();
        std::string ssFileName = pFileCtrl->GetFileName();
        std::string ssFilePath = ssFileDir+"\\"+ssFileName;

        String^ sFilePath = msclr::interop::marshal_as<String^>(ssFilePath);
        FAddRowToPanel(tableLayoutPanelMain, sFilePath,iHandle);
      }
      tableLayoutPanelMain->AutoScroll = true;
      tableLayoutPanelMain->ResumeLayout();
    }

    void FAddMainPanelRows(TableLayoutPanel^ panel,cli::array<String^,1>^ arrFileNames)
    // Вариант для rowElements из двух элементов: sFileName + sTime для каждого файла.
    {
      panel->SuspendLayout();
  		string ssSaveDir = msclr::interop::marshal_as<string>(textBoxSaveDir->Text);// Получить директорию, в которую будем сохранять файл
//      if (!pFileCtrlStore) pFileCtrlStore = new TFileCtrlStoreTimed(ssSaveDir,GetTimeDeltaInMinutes());// Создать объект TFileCtrlStoreTimed, если он еще не создан
      if (!pFileCtrlStore) pFileCtrlStore = new TFileCtrlStore(ssSaveDir);// Создать объект TFileCtrlStoreTimed, если он еще не создан

//      for each(auto FileName in arrFileNames)
      for (int i = 0; i < arrFileNames->Length; i++){
        String^ sFileName = arrFileNames[i];

        std::filesystem::path Path = msclr::interop::marshal_as<string>(sFileName);
        std::string ssDirSrc = (Path.parent_path()).string();
        std::string ssFileName = (Path.filename()).string();
      // Если файл с таким путем уже существует в списке - не будем добавлять его второй раз:
        if (pFileCtrlStore->GetFileHandleByName(ssDirSrc,ssFileName) != -1) continue;

        std::string ssFilePath = Path.string();

    		String^ sPath = msclr::interop::marshal_as<String^>(ssFilePath);
    		sFileName = msclr::interop::marshal_as<String^>(ssFileName);
//    		sDirSrc = msclr::interop::marshal_as<String^>(ssDirSrc);

      // Функция 1: Сохранить файл:
        int iHandle = pFileCtrlStore->AddFile(ssDirSrc,ssFileName);// Добавить файл к списку сохраненных файлов

//        FAddRowToPanel(tableLayoutPanelMain,sPath,iHandle);
        FAddRowToPanel(panel,sPath,iHandle);

      }
      panel->AutoScroll = true;
      panel->ResumeLayout();
    }

    void CheckForBegDirs()
    {
      std::string ssSaveDir = msclr::interop::marshal_as<std::string>(textBoxSaveDir->Text);// Получить директорию, в которую будем восстанавливать файл
      CreateDirectoryA((LPCSTR)ssSaveDir.c_str(),NULL);
      std::string ssRestoreDir = msclr::interop::marshal_as<std::string>(textBoxRestoreDir->Text);// Получить директорию, в которую будем восстанавливать файл
      CreateDirectoryA((LPCSTR)ssRestoreDir.c_str(),NULL);
      std::string ssWorkDir = msclr::interop::marshal_as<std::string>(textBoxWorkDir->Text);// Получить директорию, в которую будем восстанавливать файл
      CreateDirectoryA((LPCSTR)ssWorkDir.c_str(),NULL);
    }

    System::Void MainForm_Load(Object^ sender,EventArgs^ e)
    // Начальная загрузка окна.
    {
//      this.tableLayoutPanelMain.CellPaint += new TableLayoutCellPaintEventHandler(tableLayoutPanelMain_CellPaint);
      textBoxSaveDir->Text = cssBegSaveDir;
      textBoxRestoreDir->Text = cssBegRestoreDir;
      textBoxWorkDir->Text = cssBegWorkDir;

//      FInitMainPanelFill2(tableLayoutPanelMain, ciFBegMainFormCount);
      FInitMainPanelFill(tableLayoutPanelMain);
//      int gpFileStore = LoadFileStore(csFBegSaveDir);
      timerBackup->Interval = GetTimeDeltaInMillisecs();// Интервал таймера clr в миллисекундах
      timerBackup->Enabled = true;// Запускаем таймер
      
      CheckForBegDirs();
    }

    System::Void buttonAdd_Click(System::Object^  sender,System::EventArgs^  e) 
  	// По этой кнопке добавляются файлы, которые мы будем отслеживать.
    {
//	  	String^ sBegWorkDir = msclr::interop::marshal_as<String^>(cssBegWorkDir);
      openFileDialogAdd->InitialDirectory = textBoxWorkDir->Text;
//      sfd->Filter = "Text Files|*.txt|All Files|*.*";
      if (openFileDialogAdd->ShowDialog() == System::Windows::Forms::DialogResult::Cancel) return;
      FAddMainPanelRows(tableLayoutPanelMain,openFileDialogAdd->FileNames);
      ChangeButStatus();
      SetTime();
    }

    void ChangeButStatus()
    // Изменяет состояние кнопок, делая из серыми или нажимаемыми, если имеются загруженные в программу файлы.
    {
      buttonRestore->Enabled = false; buttonChange->Enabled = false;
      if (pFileCtrlStore && pFileCtrlStore->GetCount() > 0){
        buttonRestore->Enabled = true; buttonChange->Enabled = true;
      }
    }

    void ValidateHours()
    // Валидатор поля "часы" - проверяет, что значение является Int32.
    {
      iTimeDeltaHours = Int32::Parse(maskedTextBoxHours->Text);
//      auto Number1 = Double::Parse(maskedTextBoxHours->Text);
    }

    void ValidateMinutes()
    // Валидатор поля "минуты" - проверяет, что значение является Int32.
    {
      iTimeDeltaMinutes = Int32::Parse(maskedTextBoxMinutes->Text);
      if (iTimeDeltaMinutes >= 60){
        iTimeDeltaMinutes = 59; maskedTextBoxMinutes->Text = iTimeDeltaMinutes.ToString();
      }
    }
    
    int GetTimeDeltaInMinutes()
		// Переводим интервал таймера в миллисекунды.
    {
      return iTimeDeltaHours*60 + iTimeDeltaMinutes;
    }

    int GetTimeDeltaInMillisecs()
		// Переводим интервал таймера в миллисекунды.
    {
      return (iTimeDeltaHours*3600 + iTimeDeltaMinutes*60)*1000;
    }

    System::Void maskedTextBoxHours_Validating(System::Object^  sender,System::ComponentModel::CancelEventArgs^  e) 
    // Валидатор поля "часы" - вызывает ValidateHours.
    {
      ValidateHours();
    }
    
    System::Void maskedTextBoxMinutes_Validating(System::Object^  sender,System::ComponentModel::CancelEventArgs^  e) 
    // Валидатор поля "минуты" - вызывает ValidateMinutes.
    {
      ValidateMinutes();
    }
    
    void ShowMessageInt(std::string ssText,int iVal,std::string ssText2)
    // Вывести окно с указанным текстом и числом iVal.
    {
   		String^ sText = msclr::interop::marshal_as<String^>(ssText+std::to_string(iVal)+ssText2);
      MessageBox::Show(sText);
    }

    void SetTime()
    // Установить время для бэкапа.
    {
      ValidateHours();
      ValidateMinutes();
      int iNewTimeDelta = GetTimeDeltaInMillisecs();
      if (iNewTimeDelta <= 0){
        ShowMessageInt("Invalid delta time ",iNewTimeDelta,""); return;
      }
      timerBackup->Interval = iNewTimeDelta;
      ShowMessageInt("New delta time ",GetTimeDeltaInMinutes()," min was set");
    // DEBUG ONLY:
      //timerBackup->Interval = 60000;// Отладочный интервал таймера = 5 секунд
      //ShowMessageInt("New delta time ",iNewTimeDelta," ms was set");
    }

    System::Void buttonSetTimePeriod_Click(System::Object^  sender,System::EventArgs^  e) 
    // Реакция кнопки Set для времени.
    {
      SetTime();
    }
    
    System::Void buttonClose_Click(System::Object^  sender,System::EventArgs^  e) 
    // Реакция общей кнопки Close: закрыть приложение.
    {
      Close();
    }

    System::Void buttonRestore_Click(System::Object^  sender,System::EventArgs^  e)
    // Восстановить все сохраненные файлы.
    {
      if (!pFileCtrlStore) TreatError("FileCtrlStore doesn't exist");
  		string ssRestoreDir = msclr::interop::marshal_as<string>(textBoxRestoreDir->Text);// Получить директорию, в которую будем восстанавливать файл

    //6. Получение списка всех файлов (на вход ничего, на выходе список из путей до файлов и их идентификаторов):
      std::vector<TFileCtrl *> vectFiles = pFileCtrlStore->GetAllFileCtrlList(); bool boolRes = false, boolAllFilesRestored = true;

      for (TFileCtrl * pFileCtrl: vectFiles){
        if (!pFileCtrl) continue;
        int iHandle = pFileCtrl->GetHandle();
      // 2. Выдача сохраненного файла по идентификатору. На вход подается идентификатор, на выход путь до файла.
        std::string ssRestoredFile = pFileCtrlStore->RestoreLastFileByHandle(iHandle,ssRestoreDir,boolRes);
        boolAllFilesRestored &= boolRes;
        if (!boolRes){
          std::string ssText = "File "+ssRestoredFile+" wasn't restored";
      		String^ sText = msclr::interop::marshal_as<String^>(ssText);
          MessageBox::Show(sText);
        }
      }
      if (boolAllFilesRestored) MessageBox::Show("All files restored successfully");
    }

    System::Void buttonChangeSaveDir_Click(System::Object^  sender,System::EventArgs^  e) 
	  // Вызываем системный диалог для выбора папки для сохранения файлов.
    {
      //string[] files = Directory.GetFiles(fbd.SelectedPath);
    // gcnew - аналог new native c++, но для clr:
      FolderBrowserDialog^ folderBrowserDialog = gcnew System::Windows::Forms::FolderBrowserDialog;
  	// ShowDialog вызывает показ диалогового окна для выбора папки:
      System::Windows::Forms::DialogResult result = folderBrowserDialog->ShowDialog();
  	// После закрытия окна переменная result содержит результат; если была нажата кнопка ОК - результат будет Dialogresult::OK:
      if (result == ::DialogResult::OK){
		  // SelectedPath - это переменная объекта folderBrowserDialog, она содержит выбранную папку:
         String^ sFolderName = folderBrowserDialog->SelectedPath;
      //    if (!Directory.Exists(sFCurSaveDir)) Directory.CreateDirectory(sFCurSaveDir);
  		// Выведем выбранную папку на экран в редакторе textBoxSaveDir:
         textBoxSaveDir->Text = sFolderName;
      	 std::string ssSaveDir = msclr::interop::marshal_as<std::string>(textBoxSaveDir->Text);// Получить директорию, в которую будем восстанавливать файл
         CreateDirectoryA((LPCSTR)ssSaveDir.c_str(),NULL);
      }
    }

    private: System::Void butChangeRestoreDir_Click(System::Object^  sender,System::EventArgs^  e) 
	  // Вызываем системный диалог для выбора папки для восстановления файлов.
    {
      //string[] files = Directory.GetFiles(fbd.SelectedPath);
    // gcnew - аналог new native c++, но для clr:
      FolderBrowserDialog^ folderBrowserDialog = gcnew System::Windows::Forms::FolderBrowserDialog;
  	// ShowDialog вызывает показ диалогового окна для выбора папки:
      System::Windows::Forms::DialogResult result = folderBrowserDialog->ShowDialog();
  	// После закрытия окна переменная result содержит результат; если была нажата кнопка ОК - результат будет Dialogresult::OK:
      if (result == ::DialogResult::OK){
		  // SelectedPath - это переменная объекта folderBrowserDialog, она содержит выбранную папку:
         String^ sFolderName = folderBrowserDialog->SelectedPath;
  		// Выведем выбранную папку на экран в редакторе textBoxSaveDir:
         textBoxRestoreDir->Text = sFolderName;
      	 std::string ssRestoreDir = msclr::interop::marshal_as<std::string>(textBoxRestoreDir->Text);// Получить директорию, в которую будем восстанавливать файл
         CreateDirectoryA((LPCSTR)ssRestoreDir.c_str(),NULL);
      }
    }

    private: System::Void button1_Click(System::Object^  sender,System::EventArgs^  e) 
	  // Вызываем системный диалог для выбора папки для рабочих файлов.
    {
      FolderBrowserDialog^ folderBrowserDialog = gcnew System::Windows::Forms::FolderBrowserDialog;
  	// ShowDialog вызывает показ диалогового окна для выбора папки:
      System::Windows::Forms::DialogResult result = folderBrowserDialog->ShowDialog();
  	// После закрытия окна переменная result содержит результат; если была нажата кнопка ОК - результат будет Dialogresult::OK:
      if (result == ::DialogResult::OK){
		  // SelectedPath - это переменная объекта folderBrowserDialog, она содержит выбранную папку:
         String^ sFolderName = folderBrowserDialog->SelectedPath;
  		// Выведем выбранную папку на экран в редакторе textBoxSaveDir:
         textBoxWorkDir->Text = sFolderName;
      	 std::string ssWorkDir = msclr::interop::marshal_as<std::string>(textBoxWorkDir->Text);// Получить директорию, в которую будем восстанавливать файл
         CreateDirectoryA((LPCSTR)ssWorkDir.c_str(),NULL);
      }
    }

    private: System::Void buttonChange_Click(System::Object^  sender,System::EventArgs^  e) 
    // 5. Получение списка файлов по нескольким идентификаторам (на вход список идентификаторов, на выход список из путей до файлов).
    {
      auto formFileListByHandle = gcnew FileListByHandle();
      formFileListByHandle->ShowDialog();
    }

    private: System::Void timerBackup_Tick(System::Object^  sender,System::EventArgs^  e) 
    // Обоаботчик одного такта таймера, срабатывает с заданным интервалом.
    {
      if (pFileCtrlStore){
        if (formRestoreFileFromVersions) formRestoreFileFromVersions->ReDrawFiles();
        if (!pFileCtrlStore->BackupAllFiles())
          MessageBox::Show("There was error during files backup");
      }
    }
};// public ref class MainForm
}

