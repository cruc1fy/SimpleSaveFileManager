#pragma once

namespace LabWork01CLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class ChangeHandle : public System::Windows::Forms::Form
	{
  protected:
    int iENewHandle = 0;

    void ESetNewHandle(int iNewHandle)
    {
      iENewHandle = iNewHandle;
    }

	public:
		ChangeHandle(int iOldHandle)
		{
			InitializeComponent();
      textBoxOldHandle->Text = iOldHandle.ToString();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ChangeHandle()
		{
			if (components)
			{
				delete components;
			}
		}
    private: System::Windows::Forms::Panel^  panel1;
  private: System::Windows::Forms::TextBox^  textBoxOldHandle;

    private: System::Windows::Forms::Label^  label1;
    private: System::Windows::Forms::Panel^  panel2;
  private: System::Windows::Forms::TextBox^  textBoxNewHandle;

    private: System::Windows::Forms::Label^  label2;
  private: System::Windows::Forms::Panel^  panel3;
  private: System::Windows::Forms::Button^  button1;
  private: System::Windows::Forms::Button^  button2;
  protected:

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
      this->panel1 = (gcnew System::Windows::Forms::Panel());
      this->panel3 = (gcnew System::Windows::Forms::Panel());
      this->textBoxOldHandle = (gcnew System::Windows::Forms::TextBox());
      this->label1 = (gcnew System::Windows::Forms::Label());
      this->panel2 = (gcnew System::Windows::Forms::Panel());
      this->textBoxNewHandle = (gcnew System::Windows::Forms::TextBox());
      this->label2 = (gcnew System::Windows::Forms::Label());
      this->button1 = (gcnew System::Windows::Forms::Button());
      this->button2 = (gcnew System::Windows::Forms::Button());
      this->panel1->SuspendLayout();
      this->panel2->SuspendLayout();
      this->SuspendLayout();
      // 
      // panel1
      // 
      this->panel1->Controls->Add(this->panel3);
      this->panel1->Controls->Add(this->textBoxOldHandle);
      this->panel1->Controls->Add(this->label1);
      this->panel1->Location = System::Drawing::Point(3,12);
      this->panel1->Name = L"panel1";
      this->panel1->Size = System::Drawing::Size(217,38);
      this->panel1->TabIndex = 0;
      // 
      // panel3
      // 
      this->panel3->Location = System::Drawing::Point(0,81);
      this->panel3->Name = L"panel3";
      this->panel3->Size = System::Drawing::Size(217,46);
      this->panel3->TabIndex = 2;
      // 
      // textBoxOldHandle
      // 
      this->textBoxOldHandle->Location = System::Drawing::Point(75,11);
      this->textBoxOldHandle->Name = L"textBoxOldHandle";
      this->textBoxOldHandle->ReadOnly = true;
      this->textBoxOldHandle->Size = System::Drawing::Size(136,20);
      this->textBoxOldHandle->TabIndex = 1;
      // 
      // label1
      // 
      this->label1->AutoSize = true;
      this->label1->Location = System::Drawing::Point(9,11);
      this->label1->Name = L"label1";
      this->label1->Size = System::Drawing::Size(60,13);
      this->label1->TabIndex = 0;
      this->label1->Text = L"Old Handle";
      // 
      // panel2
      // 
      this->panel2->Controls->Add(this->textBoxNewHandle);
      this->panel2->Controls->Add(this->label2);
      this->panel2->Location = System::Drawing::Point(3,56);
      this->panel2->Name = L"panel2";
      this->panel2->Size = System::Drawing::Size(217,38);
      this->panel2->TabIndex = 1;
      // 
      // textBoxNewHandle
      // 
      this->textBoxNewHandle->Location = System::Drawing::Point(75,11);
      this->textBoxNewHandle->Name = L"textBoxNewHandle";
      this->textBoxNewHandle->Size = System::Drawing::Size(136,20);
      this->textBoxNewHandle->TabIndex = 1;
      // 
      // label2
      // 
      this->label2->AutoSize = true;
      this->label2->Location = System::Drawing::Point(3,11);
      this->label2->Name = L"label2";
      this->label2->Size = System::Drawing::Size(66,13);
      this->label2->TabIndex = 0;
      this->label2->Text = L"New Handle";
      // 
      // button1
      // 
      this->button1->Location = System::Drawing::Point(3,96);
      this->button1->Name = L"button1";
      this->button1->Size = System::Drawing::Size(106,40);
      this->button1->TabIndex = 2;
      this->button1->Text = L"OK";
      this->button1->UseVisualStyleBackColor = true;
      this->button1->Click += gcnew System::EventHandler(this,&ChangeHandle::button1_Click);
      // 
      // button2
      // 
      this->button2->Location = System::Drawing::Point(115,96);
      this->button2->Name = L"button2";
      this->button2->Size = System::Drawing::Size(106,40);
      this->button2->TabIndex = 3;
      this->button2->Text = L"Cancel";
      this->button2->UseVisualStyleBackColor = true;
      this->button2->Click += gcnew System::EventHandler(this,&ChangeHandle::button2_Click);
      // 
      // ChangeHandle
      // 
      this->AutoScaleDimensions = System::Drawing::SizeF(6,13);
      this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
      this->ClientSize = System::Drawing::Size(226,140);
      this->Controls->Add(this->button2);
      this->Controls->Add(this->button1);
      this->Controls->Add(this->panel2);
      this->Controls->Add(this->panel1);
      this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
      this->Name = L"ChangeHandle";
      this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
      this->Text = L"ChangeHandle";
      this->panel1->ResumeLayout(false);
      this->panel1->PerformLayout();
      this->panel2->ResumeLayout(false);
      this->panel2->PerformLayout();
      this->ResumeLayout(false);

    }

  public:
    int GetNewHandle()
    {
      return iENewHandle;
    }

#pragma endregion
    private: System::Void button1_Click(System::Object^  sender,System::EventArgs^  e)
    // Реакция кнопки на нажатие.
    {
      try {
        ESetNewHandle(Int32::Parse(textBoxNewHandle->Text));
      } catch(...){
        ESetNewHandle(-1);
      }
      Close();
    }
  
    private: System::Void button2_Click(System::Object^  sender,System::EventArgs^  e) 
    // Реакция кнопки на нажатие.
    {
      ESetNewHandle(-1);
      Close();
    }
};// public ref class ChangeHandle
}// namespace LabWork01CLR
