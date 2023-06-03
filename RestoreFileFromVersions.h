#pragma once

#include <string>
#include <vector>
#include <msclr/marshal_cppstd.h>

#include "Utils.h"
#include "FileCtrlStore.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

using namespace utils;
using namespace std;

extern TFileCtrlStore * pFileCtrlStore;

extern std::vector<std::string> vectRestoredFiles;

namespace LabWork01CLR {
	public ref class RestoreFileFromVersions : public System::Windows::Forms::Form
	{
	protected:
    int iEHandle = 0;
  private: System::Windows::Forms::Button^  butClose;
  protected:
  private: System::Windows::Forms::Button^  butCancel;
         String^ sERestoreDir = nullptr;

  public:
		RestoreFileFromVersions(void)
		{
			InitializeComponent();
		}

  void SetHandle(int iHandle)
  {
    iEHandle = iHandle;
  }

  void SetRestoreDir(String^ sRestoreDir)
  {
    sERestoreDir = sRestoreDir;
  }

	protected:
		~RestoreFileFromVersions()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::Panel^  panel1;
  private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanelFileVersions;
  private: System::Windows::Forms::Panel^  panel2;
  private: System::Windows::Forms::Button^  butRestore;
  protected:


	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
      this->panel1 = (gcnew System::Windows::Forms::Panel());
      this->tableLayoutPanelFileVersions = (gcnew System::Windows::Forms::TableLayoutPanel());
      this->panel2 = (gcnew System::Windows::Forms::Panel());
      this->butClose = (gcnew System::Windows::Forms::Button());
      this->butCancel = (gcnew System::Windows::Forms::Button());
      this->butRestore = (gcnew System::Windows::Forms::Button());
      this->panel1->SuspendLayout();
      this->panel2->SuspendLayout();
      this->SuspendLayout();
      // 
      // panel1
      // 
      this->panel1->Controls->Add(this->tableLayoutPanelFileVersions);
      this->panel1->Location = System::Drawing::Point(1,3);
      this->panel1->Name = L"panel1";
      this->panel1->Size = System::Drawing::Size(545,468);
      this->panel1->TabIndex = 0;
      // 
      // tableLayoutPanelFileVersions
      // 
      this->tableLayoutPanelFileVersions->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
      this->tableLayoutPanelFileVersions->ColumnCount = 2;
      this->tableLayoutPanelFileVersions->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
        10)));
      this->tableLayoutPanelFileVersions->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
        90)));
      this->tableLayoutPanelFileVersions->Location = System::Drawing::Point(11,9);
      this->tableLayoutPanelFileVersions->Name = L"tableLayoutPanelFileVersions";
      this->tableLayoutPanelFileVersions->RowCount = 2;
      this->tableLayoutPanelFileVersions->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
        50)));
      this->tableLayoutPanelFileVersions->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,
        50)));
      this->tableLayoutPanelFileVersions->Size = System::Drawing::Size(523,456);
      this->tableLayoutPanelFileVersions->TabIndex = 0;
      // 
      // panel2
      // 
      this->panel2->Controls->Add(this->butClose);
      this->panel2->Controls->Add(this->butCancel);
      this->panel2->Controls->Add(this->butRestore);
      this->panel2->Location = System::Drawing::Point(1,474);
      this->panel2->Name = L"panel2";
      this->panel2->Size = System::Drawing::Size(545,73);
      this->panel2->TabIndex = 1;
      // 
      // butClose
      // 
      this->butClose->Location = System::Drawing::Point(378,12);
      this->butClose->Name = L"butClose";
      this->butClose->Size = System::Drawing::Size(120,51);
      this->butClose->TabIndex = 2;
      this->butClose->Text = L"Close";
      this->butClose->UseVisualStyleBackColor = true;
      this->butClose->Click += gcnew System::EventHandler(this,&RestoreFileFromVersions::butClose_Click);
      // 
      // butCancel
      // 
      this->butCancel->Location = System::Drawing::Point(213,12);
      this->butCancel->Name = L"butCancel";
      this->butCancel->Size = System::Drawing::Size(120,51);
      this->butCancel->TabIndex = 1;
      this->butCancel->Text = L"Cancel";
      this->butCancel->UseVisualStyleBackColor = true;
      this->butCancel->Click += gcnew System::EventHandler(this,&RestoreFileFromVersions::butCancel_Click);
      // 
      // butRestore
      // 
      this->butRestore->Location = System::Drawing::Point(49,12);
      this->butRestore->Name = L"butRestore";
      this->butRestore->Size = System::Drawing::Size(120,51);
      this->butRestore->TabIndex = 0;
      this->butRestore->Text = L"Restore";
      this->butRestore->UseVisualStyleBackColor = true;
      this->butRestore->Click += gcnew System::EventHandler(this,&RestoreFileFromVersions::butRestore_Click);
      // 
      // RestoreFileFromVersions
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6,13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(547,549);
      this->Controls->Add(this->panel2);
      this->Controls->Add(this->panel1);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
      this->MaximizeBox = false;
      this->Name = L"RestoreFileFromVersions";
      this->Text = L"RestoreFileFromVersions";
      this->Load += gcnew System::EventHandler(this,&RestoreFileFromVersions::RestoreFileFromVersions_Load);
      this->panel1->ResumeLayout(false);
      this->panel2->ResumeLayout(false);
      this->ResumeLayout(false);

    }
#pragma endregion

    void FInitMainPanelFill(TableLayoutPanel^ panel)
    // Инициализирует TableLayoutPanel при открытии окна.
    {
      const int ciVerticalScrollBarWidth = 17;
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

    void FAddRowToPanel(TableLayoutPanel^ panel, String^ sFileName, int iHandle)
    // Добавляет строку в TableLayoutPanel.
    {
      panel->RowCount++;
      panel->RowStyles->Add(gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize));

      System::Windows::Forms::CheckBox^ checkBox = gcnew System::Windows::Forms::CheckBox();
      panel->Controls->Add(checkBox, 0, panel->RowCount);

      panel->Controls->Add(FCreateNewItem(sFileName), 1, panel->RowCount);
    }

    void FShowFiles()
    // Перерисовать главную панель заново.
    {
      tableLayoutPanelFileVersions->SuspendLayout();
      tableLayoutPanelFileVersions->Controls->Clear();
      tableLayoutPanelFileVersions->RowCount = 0;

      if (!pFileCtrlStore) return;
      std::vector<std::string> vectFiles = pFileCtrlStore->GetLimitedDequePaths(iEHandle);

      for (int i=0; i < (int)vectFiles.size(); i++){
        std::string ssFilePath = vectFiles[i];
        String^ sFilePath = msclr::interop::marshal_as<String^>(ssFilePath);
        FAddRowToPanel(tableLayoutPanelFileVersions, sFilePath,i+1);
      }
      tableLayoutPanelFileVersions->AutoScroll = true;
      tableLayoutPanelFileVersions->ResumeLayout();
    }

    public: void ReDrawFiles()
    {
      FShowFiles();
    }

    void Undo(std::vector<std::string> vectRestoredFiles)
    // Откат восстановления файлов из списка vectRestoredFiles.
    {
      if (!pFileCtrlStore) return;
      for (std::string ssFileName: vectRestoredFiles)
        pFileCtrlStore->DeleteFile(ssFileName);
    }

    private: System::Void RestoreFileFromVersions_Load(System::Object^  sender,System::EventArgs^  e)
    // Реакция на нажатие кнопки Restore, находящейся в строке для данного файла: открыть окно с сохраненними версиями этого файла.
    {
      vectRestoredFiles.clear();
      FInitMainPanelFill(tableLayoutPanelFileVersions);
      FShowFiles();
    }

    private: System::Void butRestore_Click(System::Object^  sender,System::EventArgs^  e) 
    // Реакция на нажатие общей кнопки Restore: восстановить последние версии всех файлов.
    {
      CheckBox^ pCheckBox = nullptr;
      std::vector<int> vectFiles2Restore;

      for (int i=0; i < tableLayoutPanelFileVersions->RowCount; i++){
        pCheckBox = (CheckBox^)tableLayoutPanelFileVersions->GetControlFromPosition(0, i+1);
        if (pCheckBox->Checked) vectFiles2Restore.push_back(i);
      }

      String^ sRestoreDir = sERestoreDir;
  		string ssRestoreDir = msclr::interop::marshal_as<string>(sRestoreDir);// Получить директорию, в которую будем восстанавливать файл

      bool isSuccess = false;
      if (!pFileCtrlStore) return;
      vectRestoredFiles.clear();
      vectRestoredFiles = pFileCtrlStore->RestoreFilesList(iEHandle,ssRestoreDir,vectFiles2Restore,isSuccess);

      if (!isSuccess) Undo(vectRestoredFiles);

      MessageBox::Show("All files were successfully restored.");
    }

    private: System::Void butCancel_Click(System::Object^  sender,System::EventArgs^  e) 
    // Реакция на нажатие общей кнопки Cancel: откат восстановления файлов.
    {
       if (MessageBox::Show("This operation will delete restored files!", "Attention",MessageBoxButtons::OKCancel, MessageBoxIcon::Information) == System::Windows::Forms::DialogResult::Cancel) return;
       Undo(vectRestoredFiles);
    }

    private: System::Void butClose_Click(System::Object^  sender,System::EventArgs^  e) 
    // Реакция на нажатие общей кнопки Close: закрыть окно.
    {
      Close();
    }
};
}
