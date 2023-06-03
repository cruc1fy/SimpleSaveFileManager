#pragma once

using namespace System;
using namespace System::Windows::Forms;

namespace utils {

public ref class ButtonWithVal : public System::Windows::Forms::Button {
protected: 
  int iEVal = -1;

public:
// после двоеточия список инициализации iEVal(iVal) => iEVal = iVal
  ButtonWithVal(int iVal): iEVal(iVal){}

  int GetVal()
  { 
    return iEVal;
  } 
  
  void SetVal(int iVal)
  {
    iEVal = iVal;
  } 
};

public ref class CheckBoxWithVal: public System::Windows::Forms::CheckBox {
protected: 
  int iEVal = -1;

public:
// после двоеточия список инициализации iEVal(iVal) => iEVal = iVal
  CheckBoxWithVal(int iVal): iEVal(iVal){}

  int GetVal()
  { 
    return iEVal;
  } 
  
  void SetVal(int iVal)
  {
    iEVal = iVal;
  } 
};
};