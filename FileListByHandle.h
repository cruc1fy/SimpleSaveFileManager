#pragma once

#include <vector>
#include <string>
#include <msclr/marshal_cppstd.h>
#include <cliext/vector>

#include "FileCtrlStore.h"

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

extern TFileCtrlStore * pFileCtrlStore;

//std::vector<int> vectFileHandles;

namespace LabWork01CLR {

	public ref class FileListByHandle : public System::Windows::Forms::Form {
  private:
    cliext::vector<int> vectHandles;

	public:
		FileListByHandle(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FileListByHandle()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::TextBox^  textBoxListOfHandles;
    protected:
    private: System::Windows::Forms::Panel^  panel1;
    private: System::Windows::Forms::Button^  buttonAddHandle;
    private: System::Windows::Forms::MaskedTextBox^  maskedTextBoxHandle;
    private: System::Windows::Forms::Label^  label2;
    private: System::Windows::Forms::Label^  label1;
  private: System::Windows::Forms::Panel^  panel2;
  private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;

  private: System::Windows::Forms::Button^  buttonShow;
  private: System::Windows::Forms::Panel^  panel4;
  private: System::Windows::Forms::Button^  buttonClose;
  private: System::Windows::Forms::Button^  butClear;
  private: System::Windows::Forms::Button^  butShowFiles2;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
      this->textBoxListOfHandles = (gcnew System::Windows::Forms::TextBox());
      this->panel1 = (gcnew System::Windows::Forms::Panel());
      this->buttonAddHandle = (gcnew System::Windows::Forms::Button());
      this->maskedTextBoxHandle = (gcnew System::Windows::Forms::MaskedTextBox());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->panel2 = (gcnew System::Windows::Forms::Panel());
      this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
      this->buttonShow = (gcnew System::Windows::Forms::Button());
      this->panel4 = (gcnew System::Windows::Forms::Panel());
      this->butShowFiles2 = (gcnew System::Windows::Forms::Button());
      this->butClear = (gcnew System::Windows::Forms::Button());
      this->buttonClose = (gcnew System::Windows::Forms::Button());
      this->panel1->SuspendLayout();
      this->panel2->SuspendLayout();
      this->panel4->SuspendLayout();
      this->SuspendLayout();
      // 
      // textBoxListOfHandles
      // 
      this->textBoxListOfHandles->Location = System::Drawing::Point(97,9);
      this->textBoxListOfHandles->Name = L"textBoxListOfHandles";
      this->textBoxListOfHandles->ReadOnly = true;
      this->textBoxListOfHandles->Size = System::Drawing::Size(159,20);
      this->textBoxListOfHandles->TabIndex = 0;
      // 
      // panel1
      // 
      this->panel1->Controls->Add(this->buttonAddHandle);
      this->panel1->Controls->Add(this->maskedTextBoxHandle);
      this->panel1->Controls->Add(this->label2);
      this->panel1->Controls->Add(this->label1);
      this->panel1->Controls->Add(this->textBoxListOfHandles);
      this->panel1->Location = System::Drawing::Point(87,12);
      this->panel1->Name = L"panel1";
      this->panel1->Size = System::Drawing::Size(262,66);
      this->panel1->TabIndex = 1;
      // 
      // buttonAddHandle
      // 
      this->buttonAddHandle->Location = System::Drawing::Point(163,35);
      this->buttonAddHandle->Name = L"buttonAddHandle";
      this->buttonAddHandle->Size = System::Drawing::Size(93,23);
      this->buttonAddHandle->TabIndex = 4;
      this->buttonAddHandle->Text = L"Add Handle";
      this->buttonAddHandle->UseVisualStyleBackColor = true;
      this->buttonAddHandle->Click += gcnew System::EventHandler(this,&FileListByHandle::buttonAddHandle_Click);
      // 
      // maskedTextBoxHandle
      // 
      this->maskedTextBoxHandle->Location = System::Drawing::Point(112,35);
      this->maskedTextBoxHandle->Mask = L"000000";
      this->maskedTextBoxHandle->Name = L"maskedTextBoxHandle";
      this->maskedTextBoxHandle->Size = System::Drawing::Size(45,20);
      this->maskedTextBoxHandle->TabIndex = 3;
      this->maskedTextBoxHandle->ValidatingType = System::Int32::typeid;
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Location = System::Drawing::Point(13,39);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(93,13);
      this->label2->TabIndex = 2;
      this->label2->Text = L"Enter new handle:";
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Location = System::Drawing::Point(13,12);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(78,13);
      this->label1->TabIndex = 0;
      this->label1->Text = L"List of handles:";
      // 
      // panel2
      // 
      this->panel2->Controls->Add(this->tableLayoutPanel1);
      this->panel2->Location = System::Drawing::Point(12,84);
      this->panel2->Name = L"panel2";
      this->panel2->Size = System::Drawing::Size(425,536);
      this->panel2->TabIndex = 2;
      // 
      // tableLayoutPanel1
      // 
      this->tableLayoutPanel1->CellBorderStyle = System::Windows::Forms::TableLayoutPanelCellBorderStyle::Single;
      this->tableLayoutPanel1->ColumnCount = 2;
      this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
        10)));
      this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
        90)));
      this->tableLayoutPanel1->Location = System::Drawing::Point(3,3);
      this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
      this->tableLayoutPanel1->RowCount = 2;
      this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,50)));
      this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent,50)));
      this->tableLayoutPanel1->Size = System::Drawing::Size(419,530);
      this->tableLayoutPanel1->TabIndex = 0;
      // 
      // buttonShow
      // 
      this->buttonShow->Location = System::Drawing::Point(8,6);
      this->buttonShow->Name = L"buttonShow";
      this->buttonShow->Size = System::Drawing::Size(98,41);
      this->buttonShow->TabIndex = 0;
      this->buttonShow->Text = L"NameByHandle";
      this->buttonShow->UseVisualStyleBackColor = true;
      this->buttonShow->Click += gcnew System::EventHandler(this,&FileListByHandle::buttonShow_Click);
      // 
      // panel4
      // 
      this->panel4->Controls->Add(this->buttonShow);
      this->panel4->Controls->Add(this->butShowFiles2);
      this->panel4->Controls->Add(this->butClear);
      this->panel4->Controls->Add(this->buttonClose);
      this->panel4->Location = System::Drawing::Point(12,623);
      this->panel4->Name = L"panel4";
      this->panel4->Size = System::Drawing::Size(425,56);
      this->panel4->TabIndex = 4;
      // 
      // butShowFiles2
      // 
      this->butShowFiles2->Location = System::Drawing::Point(112,6);
      this->butShowFiles2->Name = L"butShowFiles2";
      this->butShowFiles2->Size = System::Drawing::Size(98,41);
      this->butShowFiles2->TabIndex = 2;
      this->butShowFiles2->Text = L"NamesByHandleList";
      this->butShowFiles2->UseVisualStyleBackColor = true;
      this->butShowFiles2->Click += gcnew System::EventHandler(this,&FileListByHandle::butShowFiles2_Click);
      // 
      // butClear
      // 
      this->butClear->Location = System::Drawing::Point(216,6);
      this->butClear->Name = L"butClear";
      this->butClear->Size = System::Drawing::Size(98,41);
      this->butClear->TabIndex = 1;
      this->butClear->Text = L"Clear";
      this->butClear->UseVisualStyleBackColor = true;
      this->butClear->Click += gcnew System::EventHandler(this,&FileListByHandle::butClear_Click);
      // 
      // buttonClose
      // 
      this->buttonClose->Location = System::Drawing::Point(320,6);
      this->buttonClose->Name = L"buttonClose";
      this->buttonClose->Size = System::Drawing::Size(98,41);
      this->buttonClose->TabIndex = 0;
      this->buttonClose->Text = L"Close";
      this->buttonClose->UseVisualStyleBackColor = true;
      this->buttonClose->Click += gcnew System::EventHandler(this,&FileListByHandle::buttonClose_Click);
      // 
      // FileListByHandle
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6,13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(449,679);
      this->Controls->Add(this->panel4);
      this->Controls->Add(this->panel2);
      this->Controls->Add(this->panel1);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
      this->MaximizeBox = false;
      this->Name = L"FileListByHandle";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"FileListByHandle";
      this->Load += gcnew System::EventHandler(this,&FileListByHandle::FileListByHandle_Load);
      this->panel1->ResumeLayout(false);
      this->panel1->PerformLayout();
      this->panel2->ResumeLayout(false);
      this->panel4->ResumeLayout(false);
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
      textBoxListOfHandles->Text = "";
    }

    Control^ FCreateNewItem(String^ sText)
    // Создает новый элемент CLR для добавления в TableLayoutPanel.
    {
      System::Windows::Forms::Label^ textNew = gcnew System::Windows::Forms::Label();
      textNew->AutoSize = true;
      textNew->Text = sText;
      return textNew;
    }

    void FShowFiles()
    // 5. Иллюстрирует вызов TFileCtrlStore::GetNameByHandle.
    {
      if (!pFileCtrlStore) return;

      tableLayoutPanel1->SuspendLayout();
      tableLayoutPanel1->Controls->Clear();
      tableLayoutPanel1->RowCount = 0;

      for (int i=0; i<vectHandles.size(); i++){
        tableLayoutPanel1->RowCount++;
        tableLayoutPanel1->RowStyles->Add(gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize));

        int iHandle = vectHandles[i];
        std::string ssHandle = std::to_string(iHandle);
    		String^ sHandle = msclr::interop::marshal_as<String^>(ssHandle);

        std::string ssFilePath = pFileCtrlStore->GetNameByHandle(iHandle);
    		String^ sFilePath = msclr::interop::marshal_as<String^>(ssFilePath);

        tableLayoutPanel1->Controls->Add(FCreateNewItem(sHandle), 0, tableLayoutPanel1->RowCount);
        tableLayoutPanel1->Controls->Add(FCreateNewItem(sFilePath), 1, tableLayoutPanel1->RowCount);
      }

      tableLayoutPanel1->AutoScroll = true;
      tableLayoutPanel1->ResumeLayout();
    }

    void FShowFiles2()
    // 5. Иллюстрирует вызов TFileCtrlStore::GetFileListByHandleList.
    {
      if (!pFileCtrlStore) return;

      std::vector<int> vectHandles2;
      for (int i=0; i<vectHandles.size(); i++)
        vectHandles2.push_back(vectHandles[i]);

      std::vector<std::string> vectFileNames = pFileCtrlStore->GetFileListByHandleList(vectHandles2);

      tableLayoutPanel1->SuspendLayout();
      tableLayoutPanel1->Controls->Clear();
      tableLayoutPanel1->RowCount = 0;

      for (int i=0; i<vectFileNames.size(); i++){
        tableLayoutPanel1->RowCount++;
        tableLayoutPanel1->RowStyles->Add(gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::AutoSize));

        int iHandle = vectHandles[i];
        std::string ssHandle = std::to_string(iHandle);
    		String^ sHandle = msclr::interop::marshal_as<String^>(ssHandle);

//    		String^ sIndex = msclr::interop::marshal_as<String^>(std::to_string(i));
    		String^ sFilePath = msclr::interop::marshal_as<String^>(vectFileNames[i]);

        tableLayoutPanel1->Controls->Add(FCreateNewItem(sHandle), 0, tableLayoutPanel1->RowCount);
        tableLayoutPanel1->Controls->Add(FCreateNewItem(sFilePath), 1, tableLayoutPanel1->RowCount);
      }

      tableLayoutPanel1->AutoScroll = true;
      tableLayoutPanel1->ResumeLayout();
    }
 
    bool FHasHandle(int iHandle)
    // Вернет true, если такой дескриптор уже есть в списке дескрипторов.
    {
      for (int i=0; i<vectHandles.size(); i++)
        if (iHandle == vectHandles[i]) return true;
      return false;
    }

    private: System::Void buttonAddHandle_Click(System::Object^  sender,System::EventArgs^  e) 
    // Реакция кнопки Add Handle на нажатие: добавить дескриптор в список дескрипторов.
    {
      if (!pFileCtrlStore) return;
      int iNewHandle = -1;
      try {
        iNewHandle = Int32::Parse(maskedTextBoxHandle->Text);
      } catch(...){
      }
    // Проверяем, что дескриптор еще не содержится в окне "List of handles" и при этом имеется в списке pFileCtrlStore:
      if (iNewHandle == -1 || FHasHandle(iNewHandle) || !pFileCtrlStore->HasNameByHandle(iNewHandle)) return;
      vectHandles.push_back(iNewHandle);
      if (textBoxListOfHandles->Text->Length > 0) textBoxListOfHandles->Text += ",";
      textBoxListOfHandles->Text += maskedTextBoxHandle->Text;
      maskedTextBoxHandle->Text = "";
    }
    
    private: System::Void buttonClose_Click(System::Object^  sender,System::EventArgs^  e) 
    // Реакция кнопки Close на нажатие: закрыть окно.
    {
      Close();
    }


    private: System::Void FileListByHandle_Load(System::Object^  sender,System::EventArgs^  e) 
    // Вызывается в момент загрузки окна.
    {
      FInitMainPanelFill(tableLayoutPanel1);
    }

    private: System::Void buttonShow_Click(System::Object^  sender,System::EventArgs^  e) 
    // Реакция кнопки NameByHandle на нажатие.
    {
      FShowFiles();
    }
    
    private: System::Void butClear_Click(System::Object^  sender,System::EventArgs^  e) 
    {
      textBoxListOfHandles->Text = "";
      vectHandles.clear();
      FShowFiles();
    }
    
    private: System::Void butShowFiles2_Click(System::Object^  sender,System::EventArgs^  e) 
    // Реакция кнопки NamesByHandleList на нажатие.
    {
      FShowFiles2();
    }
};
}

