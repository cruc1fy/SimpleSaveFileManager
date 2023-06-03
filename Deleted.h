    void ButtonDeleteOnClick(Object^ sender, EventArgs^ eventArgs)
    // Удалить файл из списка и соответствующую строку из панели.
    {
      ButtonWithVal^ pButton = (ButtonWithVal^)sender;
      if (!pButton) return;
    //  std::string ssText = "DeleteBut#"+std::to_string(pButton->GetVal());
  		//String^ sText = msclr::interop::marshal_as<String^>(ssText);
    //  MessageBox::Show(sText);
//      int iRow = pButton->GetVal();
      //auto ButPos = tableLayoutPanelMain->GetPositionFromControl(pButton);
      //int iRow = ButPos.Row;
//      Control^ control = tableLayoutPanelMain->GetControlFromPosition(0, iRow);
//      int iHandle = Int32::Parse(control->Text);

      int iHandle = pButton->GetVal();
      if (!pFileCtrlStore) TreatError("FileCtrlStore doesn't exist");
      pFileCtrlStore->DeleteFileByHandle(iHandle);

      int iRow = pButton->GetVal();

      for(int i = 0; i < tableLayoutPanelMain->ColumnCount; i++){
        Control^ Control = tableLayoutPanelMain->GetControlFromPosition(i, iRow);
        tableLayoutPanelMain->Controls->Remove(Control);
      }

      //for (int i = iRow + 1; i < tableLayoutPanelMain->RowCount; i++){// move up row controls that comes after row we want to remove
      //    for (int j = 0; j < tableLayoutPanelMain->ColumnCount; j++){
      //        auto control = tableLayoutPanelMain->GetControlFromPosition(j, i);
      //        if (control) tableLayoutPanelMain->SetRow(control, i - 1);
      //    }
      //}

      tableLayoutPanelMain->RowStyles->RemoveAt(iRow);
      if (tableLayoutPanelMain->RowCount > 1) tableLayoutPanelMain->RowCount--; else {
        tableLayoutPanelMain->Controls->Clear();
        tableLayoutPanelMain->RowCount = 0;
      }
      DelButFromList(iRow-1);

      //for(int i = 0; i < tableLayoutPanelMain->ColumnCount; i++){
      //  Control^ Control = tableLayoutPanelMain->GetControlFromPosition(i, iRow);
      //  tableLayoutPanelMain->Controls->Remove(Control);
      //}
      //for (int i = iRow; i < tableLayoutPanelMain->RowCount-1; i++ ){
      //  Control^ ctlNext = tableLayoutPanelMain->GetControlFromPosition(0, i + 1);
      //  tableLayoutPanelMain->SetCellPosition(ctlNext, gcnew TableLayoutPanelCellPosition(0, i));
      //}
      // 
      // 
      //table.RowStyles.RemoveAt(table.RowCount - 1);
      //table.RowCount = table.RowCount - 1;
      //tableLayoutPanelMain->RowStyles->RemoveAt(iRow);

//tableLayoutPanel1.SuspendLayout();
//tableLayoutPanel1.Controls.Remove(item);
//tableLayoutPanel1.RowStyles.RemoveAt(0);
//tableLayoutPanel1.RowCount--;
//tableLayoutPanel1.ResumeLayout();
    }

//tableLayoutPanel1.Controls.Clear();
//tableLayoutPanel1.RowCount = 0;

// Problem: when I remove and all controls are visible, vertical scroll is visible

//when you remove the dynamic controls, you need to remove the extra rows that was inserted during the addition and re-size the table layout panel height to smaller than scroll container height.
//During the addition the table layout panel height would have increased, which handled by the scroll container; but when you remove the controls, the table layout panel height doesn't reduce it's height to fit the scroll container.
//One way to do this is to give fixed height to the rows and set the table layout panel seize set to "Auto".

//One of the easiest and funniest solution is to just disable and enable tableLayoutPanel1.AutoScroll
//In your Deleting procedure code add at the end these codes :
//    tableLayoutPanel1.AutoScroll = False
//    tableLayoutPanel1.AutoScroll = True
    
//I counted the number of rows in my TableLayoutPanel to see how many would fit. Below the amount that fit I set AutoScroll = false for the add and delete methods. The scroll will appear for large sets and disappear on small sets.
//if (tableLayoutPanel.RowCount < 15) panel1.AutoScroll = false; else
//     panel1.AutoScroll = true;

//public static void RemoveArbitraryRow(TableLayoutPanel panel, int rowIndex)
//    {
//        for (int i = 0; i < panel.ColumnCount; i++){// delete all controls of row that we want to delete
//            var control = panel.GetControlFromPosition(i, rowIndex);
//            panel.Controls.Remove(control);
//        }
//        for (int i = rowIndex + 1; i < panel.RowCount; i++){// move up row controls that comes after row we want to remove
//            for (int j = 0; j < panel.ColumnCount; j++){
//                var control = panel.GetControlFromPosition(j, i);
//                if (control != null) panel.SetRow(control, i - 1);
//            }
//        }
//        var removeStyle = panel.RowCount - 1;
//        if (panel.RowStyles.Count > removeStyle) panel.RowStyles.RemoveAt(removeStyle);
//        panel.RowCount--;
//    }
