#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <windows.h>
//#include <thread>
#include <filesystem>
#include <fstream>

#include "Globals.h"
#include "LimitedDeque.h"

//using namespace std;

// ������ ����������� �������:
//1.	���������� ����� �� ����������� ��������������(�� ���� �������� ���� �� �����, �� ����� ������������ �������������)
//2.	������ ������������ ����� �� ��������������. �� ���� �������� �������������, �� ����� ���� �� �����.
//3.	�������� ����� �� �������������� (�� ���� �������� �������������, �� ����� ������)
//4.	��������� �������������� ������������ ����� (�� ���� ��� ��������������, �� ����� ������)
//5.	��������� ������ ������ �� ���������� ��������������� (�� ���� ������ ���������������, �� ����� ������ �� ����� �� ������)
//6.	��������� ������ ���� ������ (�� ���� ������, �� ������ ������ �� ����� �� ������ � �� ���������������)
//7.	����� ����������� ������ ��� � 24 ���� � ������������ ��������� ������� ����� ������� � ���������������� �������
//8.	����������� �������������� � ������� ������. �������� ����������� ������ �������������� �� ������, ���� ���-�� ������ �� ���
//9.	�������� ��������� ��� ������ � ����������� � ���� GUI ��� CLI ��� ������� ������ ������������

// BYTE - ����������� ������������ ����� [0..255]
// WORD = 2 BYTE - ����������� ����������� ����� [0..65535]
// DWORD = 2 WORD = 4 BYTE - ����������� ��������������� ����� [0..4294967295]

const int ciDequeLimit = 3;// ���������� ����� ������� ����������� ������

// �������� ������������ �����, ���� ��������� �� ���� ����:
//////////////////
class TFileCtrl {// ���� "���-����� -- ����������"
//////////////////
protected:
  int iEHandle=0;// ����������
// ��� std::string ������������� ���������������� ���:
  std::string ssEFileDirSrc;// �������� ����������, � ������� ����� ����
  std::string ssEFileName;// ��� �����
  TLimitedDeque dequeELimited;// ������� �������������� ������� ��� ��������� ����������� ������ �����

public:
// ���� ����������� ���������� ����� ��������� ������ ���� ��������� � �� �������� ������� ���������(�������� ������ ��������)
//  TFileCtrl(){}// default constructor ����������� �� ���������

  TFileCtrl(int iHandle,std::string ssFileDirSrc,std::string ssFileName,std::string ssSaveDir,int iDequeLimit=ciDequeLimit)
  // ��������������� �����������; �� ����� ���� �����, �� � ������� �������� ������� ����������.
  {
  // this ��������� �� ������ ����� ������
    this->iEHandle = iHandle; this->ssEFileDirSrc = ssFileDirSrc; this->ssEFileName = ssFileName;
    dequeELimited.SetMaxLen(iDequeLimit);
    dequeELimited.InitDeque(SLimitedQueueItem(ssSaveDir,ssFileName));
  }

  int GetHandle()
  {
    return iEHandle;
  }

  void SetHandle(int iHandle)
  {
    iEHandle = iHandle;
  }

  std::string GetFileDir()
  {
    return ssEFileDirSrc;
  }

  std::string GetFileName()
  {
    return ssEFileName;
  }

  bool BackupFile(std::string ssSaveDir)
  // ������� ����� �����.
  {
    std::string ssTimeStamp = GetTimeStamp();// �������� ����� ������� ���� � ������� � ���� ������
	// �������� ������� find_last_of ��� ������ ����� ����� ssEFileName;
	// find_last_of('.') ���� ������ ���������� ��������� ����� � ����� �����:
    std::string::size_type const iPointPos(ssEFileName.find_last_of('.'));
	// ������� substr(0, iPointPos) ������ ��������� ssEFileName ������� � ������� ������� �� ������� iPointPos:
    std::string ssFileNameWoExt = ssEFileName.substr(0, iPointPos);
	// ������� ������ ���������� ����� ssEFileName �� ������� ��������� �� ������ �� ����� �����:
    std::string ssFileExt = ssEFileName.substr(iPointPos+1,ssEFileName.length());

    std::string ssSrcFilePath = ssEFileDirSrc+"\\"+ssEFileName;
    std::string ssFileName = ssFileNameWoExt+"."+ssTimeStamp+"."+ssFileExt;
	// �������� ���� ����������� ���� �� �������� ���������� � ����� ����� � ����������� ������ ���� � �������:
    std::string ssBackupFilePath = ssSaveDir+ssFileNameWoExt+"."+ssTimeStamp+"."+ssFileExt;
//    if (!std::filesystem::copy_file(ssEFileName,ssBackupFileName,std::filesystem::copy_options::overwrite_existing)) return;
    try {
      if (!std::filesystem::copy_file(ssSrcFilePath,ssBackupFilePath)) return false;
    } catch(std::exception e){
      return false;
    } catch(...){
      return false;
    }
  // ���� ���� ������� ����������, �������� ��� � ������ ��������� ������:
    bool wasDelFile = false;
	// �������� � ������� ����� ���� ssBackUpFilePath, ���� ������� ��� ���������, ������ ���� wasDelFile = true
	// � ���� ����� ������� ���� ������� ssFile2DeletePath:
    std::string ssFile2DeletePath = dequeELimited.push_back(SLimitedQueueItem(ssSaveDir,ssFileName),wasDelFile);
//    std::string ssFile2DeletePath = dequeELimited.push_back(ssFileName,wasDelFile);
    try {
      if (wasDelFile) std::filesystem::remove(ssFile2DeletePath);
    } catch(...){
      return false;
    }
    return true;
  }

  std::vector<std::string> GetLimitedDequePaths()
  {
    std::vector<std::string> ssFileVersions;
    for (int i=0; i < dequeELimited.size(); i++)
      ssFileVersions.push_back(dequeELimited.GetPath(i));
    return ssFileVersions;
  }

  std::vector<SLimitedQueueItem> GetLimitedDequeItems()
  {
    std::vector<SLimitedQueueItem> vectFileVersions;
    for (int i=0; i < dequeELimited.size(); i++)
      vectFileVersions.push_back(dequeELimited.GetItem(i));
    return vectFileVersions;
  }

  std::string GetLastPath()
  {
    return dequeELimited.GetLastPath();
  }

  SLimitedQueueItem GetLastItem()
  {
    return dequeELimited.GetLastItem();
  }

};// class TFileCtrl

//////////////////////
class TFileCtrlStore {// ����� "���������, ����������� �������"
//////////////////////
protected:
  std::string ssESaveDir;// ���������� ��� ���������� ������
  std::vector<TFileCtrl *> vectEFiles;// ������ ���������� �� ���������, ����������� ����������� ����� - ������������ ������

  bool ECreateDir(std::string ssDir)
  // ������� ������� ���������� ���������.
  {
		// �� ������� ssDir ������ std::string ��������� ������ � ����� ������� C (ASCIIZ) = const char*, ���� ��������������� ������
		// ������� ����������� ������ ���� std::string � ASCIIZ ��� ������ ������� c_str
		// ����� �������� ������ ���� ASCIIZ � ���� LPCSTR(�������������)
		// LPCSTR sSaveDir = (LPCSTR)ssDir.c_str(); // LPCSTR - const CHAR*

		// ANSI - ������� ������� CreateDirectory, 1 ������ - 1 ����, �������� ��� ����������� �����
		// ���� ����� Unicode ������� �� ���������� CreateDirectoryW, 1 ������ - 2 �����, �������� ��� ����� ������

		// BOOL boolRes = CreateDirectoryA(sSaveDir, NULL); // ������� ���������� windows 
		// DWORD dwError = GetLastError();
		// ������� ���������� CreateDirectoryA ���� ��� ������� ����������, ����� ������� �� ������� � ������ true 
		// ���� ���������� ��� ����������, �� CreateDirectoryA ������ false � � ���� ������ ���������� ������� GetLastError
		// GetLastError - ������ ��������� ������ � ������� windows
		// ERROR_ALREADY_EXISTS - ������ "��� ����������"
		// ���� ERROR_ALREADY_EXISTS �� ������� ������ true ����� ������ false
		// CreateDirectoryA - ��������� ������� windows, GetLastError ����� ��������� �������
    return (CreateDirectoryA((LPCSTR)ssDir.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS);//183 = 0xB7
  }

  bool ECopyFile(std::string ssSrc,std::string ssDst)
  // ������� ����������� (try..catch) ����������� ������, ssSrc - ���� ������, ssDst - ���� ����.
  {
    bool boolRes = false;
	// try - catch - ������ ��������, � ������� ����������� ����� �� �������, 
	// ���� � ���� �������� ���������� ����(exception), �� ���������� ���������� � catch(������ ���������)
	// ����� �������� ����� ���� �����, ��������� ������� �� ���� �� ������, � ������� ����������� �����������
		try { // ���������� ���� - ���������� ����� ���������� � ������ ��������� �� ������ � ���� ����������
	  // ���� � ��������� copy_file ����� ������, �� �� ����������
      boolRes = std::filesystem::copy_file(ssSrc,ssDst,std::filesystem::copy_options::overwrite_existing);
    }
    catch(...){// ���������� ���� �� ������������� ������ ����������, ����� ����������
      return false;
    }
    return boolRes;
  }

  bool ESaveFile(std::string ssDirSrc,std::string ssFileName)
  // ����������� ����������� ���� � ������� ����������.
	// ssDirSrc - ���������� ������ ���������� �����; ssFileName - ���� ������� ����������.
  {
	// \" - �������������� ������������ ��� ����������� ������������������, ��������: \n - ����� ������, \t - ���������
	// \ - ������� ������ ����������� ������������������, \\ = \ 
    std::string ssSrcFileName = ssDirSrc+"\\"+ssFileName;// ���� ������ - ����� ������ ���������� �����
    std::string ssBackupFileName = ssESaveDir+ssFileName;// ���� ���� - ����� ���������� ������
    return ECopyFile(ssSrcFileName,ssBackupFileName);
  }

  std::string ERestoreFile(std::string ssFileName,std::string ssRestoreDir,bool & boolRes)
  // ����������� ����� ����������� ���� ������� � �������� ����������.
	// ��� ������� ������ ��� ���������, ������ std::string � ������ bool&
	// bool boolResult - ��������� ���������� ������� ����� �������� ��� ������ �� �������
	// bool &boolResult - ���������� ������� ������������ �� ������, ��������� ����� ������� �� �������
	// ������(reference) - ����� ����������, ����� ���������, �� � ��������� ���������� ����� ��������� � �� ����� ���� ����� 0, � ������ ������� �� ����� ����
  {
    std::string ssBackupFileName = ssESaveDir+ssFileName;
    std::string ssRestoreFileName = ssRestoreDir+ssFileName;
    boolRes = ECopyFile(ssBackupFileName,ssRestoreFileName);
		//if (boolRes == true) {
		//	return ssRestoreFileName;
		//}
		//else {
		//	return "";
		//}
    return (boolRes) ? ssRestoreFileName : "";// �� �� ����� ��� ���������� 6 �����
  }

  bool EDeleteFiles(std::vector<std::string> vectFile2Delete)
  // ������� �����, ����� ������� ������ � ������� vectFile2Delete.
  {
    bool boolRes = true;

    for (std::string ssFileName2Del: vectFile2Delete)
      boolRes &= DeleteFile(ssFileName2Del);
     
    return boolRes;
  }


public:
  TFileCtrlStore()
  // Default-�����������.
  {
  }

  TFileCtrlStore(std::string ssSaveDir)
  // ��������������� �����������.
  {
    ssESaveDir = ssSaveDir;// ����� - ����, ������ - ������; ��������: X=10
	// ���� ECreateDir ������ false, �� ����� ������� �� ������������, ����� ��� ���������� ����� �� �����������
	// ������ ������ return ������������ ������� throw - ��������� ����������: try..catch
    if (!ECreateDir(ssESaveDir)) return;
  }

  ~TFileCtrlStore()
  // ����������.
  {
	// ������ �� ���� ��������� ������� � ���������� ��, ������ ��� ��� �������� - ���������, ��� �� ������������� �������������:
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur) continue;
      delete pFileCur; pFileCur = nullptr;
    }
  }

  bool SetSaveDir(std::string ssSaveDir)
  // ���������� ���������� ��� ���������� ������.
  {
    ssESaveDir = ssSaveDir;
    return ECreateDir(ssESaveDir);
  }

  int GetCount()
  // ������ ���������� ��������� � ������� ����������� ������ vectEFiles.
  {
    return (int)vectEFiles.size();
  }

  int GetFileHandleByName(std::string ssDirSrc,std::string ssFileName)
  // �� ���� �������� ���� �� �����, �� ����� ������������ �������������.
  {
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur) continue;
      if (pFileCur->GetFileDir() == ssDirSrc && pFileCur->GetFileName() == ssFileName) 
        return pFileCur->GetHandle();
    }
    return -1;
  }

  std::string GetNameByHandle(int iHandle)
  // ������ �� ����������� ���� � �����.
  {
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur || pFileCur->GetHandle() != iHandle) continue;
      std::string ssResult = pFileCur->GetFileDir() + "\\" + pFileCur->GetFileName();
      return ssResult;
    }
    return "";
  }

  bool HasNameByHandle(int iHandle)
  // ������ true, ���� ��� ������� ����������� � ������ ����������� ������ ������� ���.
  {
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur || pFileCur->GetHandle() != iHandle) continue;
      std::string ssResult = pFileCur->GetFileDir() + "\\" + pFileCur->GetFileName();
      return true;
    }
    return false;
  }

  std::vector<std::string> GetLimitedDequePaths(int iHandle)
  // ���� ���� � ����� iHandle �� ������ - ������ ������ ������.
  {
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur || pFileCur->GetHandle() != iHandle) continue;
      return pFileCur->GetLimitedDequePaths();
    }
    return std::vector<std::string>();
  }

  std::vector<SLimitedQueueItem> GetLimitedDequeItems(int iHandle)
  // ���� ���� � ����� iHandle �� ������ - ������ ������ ������.
  {
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur || pFileCur->GetHandle() != iHandle) continue;
      return pFileCur->GetLimitedDequeItems();
    }
    return std::vector<SLimitedQueueItem>();
  }

  bool DeleteFile(std::string ssDeleteFileName)
  // ������� ������� ����, ��� ���� ������������� ��������� ������.
  {
    try {
      std::filesystem::remove(ssDeleteFileName);
    } catch(...){
      return false;
    }
    return true;
  }

  int AddFile(std::string ssDirSrc,std::string ssFileName)
  // ������� 1: ���������� ����� �� ����������� ��������������(�� ���� �������� ���� �� �����, �� ����� ������������ �������������)
  // ���������� ����� ����� �� ���������� �������.
	// �� ���������� ssDirSrc ����� ���� ssFileName � ����������� ��� � ���������� ssESaveDir, ��������� ��� � ����� ���������� ����������(vectEFiles)
	// Src = source - ��������, sources - �������� ������
	// �������� ���� ssFileName � ����� ���������� ����������. ������ ���� ���������� �����, ���� -1 ���� ������
  {

	// ������� ��������� ���� ssFileName � ����� ������� ���������� ssESaveDir:
    if (!ESaveFile(ssDirSrc,ssFileName)) return -1;
	// ���� �� ����� �� ������� ESaveFile ���������� �������

  // ��������� ����� ��������� � ������� �� ���������� (�������� ���������) �����:
    int iNextHandle = (int)vectEFiles.size();// size_t - ����������� �����, int - �������� �����, iNextHandle - ��������� ���������� ������� AddFile

	// TFileControl FileControl; // ������ ��������� TFileControl ��������� � �������� ������ - ����� ������ ��� ������ �� ���� �������
	// �������� ������� ���� TFileControl � ���� - ����� ������������ ���� �� ��������� delete pFileControl, ���� �� ����� ������ ���������
	// TFileControl *pFileControl = new TFileControl; // ���������� ����������� ��� ���������� �. �. ���������
	// ������� ����������� � ����� �����������, ����� iNextNandle � ssFileName - ����������� ���������

	// ������ ��������� � ����, �� ���� ���������� ������ � ���� ��� ������� ���� ��������� �� TFileCtrl:
    vectEFiles.push_back(new TFileCtrl(iNextHandle,ssDirSrc,ssFileName,ssESaveDir));
    return iNextHandle;
  }

  std::string RestoreFileByHandle(int iHandle,std::string ssRestoreDir,bool & boolRes)
  // ������� 2:	������ ������������ ����� �� ��������������. �� ���� �������� �������������, �� ����� ���� �� �����.
  // boolRes = true, ���� ������� ����������� �������.

  // int iHandle, std::string ssRestoreDir, bool& boolRes - ��������� �������
	// ������ ������������ ����� �� ��������������
	// bool& - ��������� ��� ��� ����������� ��������� boolRes �� �������
	// ���� ���� �� ������ bool boolRes � ��������� �������, �� ��� ��� �� ��������� ��������
	// bool& boolRes ��� �������� ��������� ������ �� ������� �� ������(�� ������)
  {
    boolRes = false;// ������������� boolRes ������ ��� ����� ��������� �� ������� ��������, ����� ����� ������������ ��������� ����� ����������� ��������
    if (!ECreateDir(ssRestoreDir)) return "";// ������� ���������� RestoreDir, ���� �� ��� ���
  // ����������� ���� ���� forall, ������� ����� ���������� ��� �������� � ���������� vectEFiles, FileCur - ������� ����������
    for (TFileCtrl * pFileCur: vectEFiles){
		// if (!pFileCur) throw 0; // �������� ��� ��������� �� �������, ���� �� ������� �� ���������� ����������(0)
		// ���� throw �� ����� ���������� ���������� ���� �� �����, �� ����� ��������� ���������� ���������
      if (!pFileCur) continue;
		// ��������� � ���� iHandle ��������� pFileCur:
      if (pFileCur->GetHandle() == iHandle)
        return ERestoreFile(pFileCur->GetFileName(),ssRestoreDir,boolRes);
    }
    return "";
  }

  std::string RestoreLastFileByHandle(int iHandle,std::string ssRestoreDir,bool & boolRes)
  // ������� 2:	������ ���������� ������������ ����� �� ��������������. �� ���� �������� �������������, �� ����� ���� �� �����.
  // boolRes = true, ���� ������� ����������� �������.
  {
    boolRes = false;
    if (!ECreateDir(ssRestoreDir)) return "";
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur) continue;
      if (pFileCur->GetHandle() == iHandle){
        SLimitedQueueItem LastItem = pFileCur->GetLastItem();
        return ERestoreFile(LastItem.ssFileName,ssRestoreDir,boolRes);
      }
    }
    return "";
  }

  bool DeleteFileByHandle(int iHandle)
  // ������� 3:	�������� ����� �� �������������� (�� ���� �������� �������������, �� ����� ������)
  {
    bool boolRes = false;
    for (int iIdx=0; iIdx < (int)vectEFiles.size(); iIdx++){
      TFileCtrl * pFileCur = vectEFiles[iIdx];
		// if (!pFileCur) throw 0; ����������� ����������, ����� ������� ������� ���������
		// if (!pFileCur) break; � ���� ������ ���� �����������, ������� ��������� �������� ���������
      if (!pFileCur) continue;// ������� � ��������� �������� �����, ������ ��������� 
      if (pFileCur->GetHandle() == iHandle){
			// erase - 2 ��������� - ���������, ������ ��������� �� ��������� ��������� ������� � ������ ��������� �� ������� �� ��������� ���������
			// begin() - ������ �������� ����������� �� ������ �������
			// end() - ������ �������� ����������� �� ������ ������� �� ������ �������
        vectEFiles.erase(vectEFiles.begin()+iIdx,vectEFiles.begin()+iIdx+1);// ������� ������� � �������� i
        std::string ssDeleteFileName = ssESaveDir+pFileCur->GetFileName();// ������������ ���� �� ����� ������� ����� �������
        std::vector<std::string> vectFile2Delete = pFileCur->GetLimitedDequePaths();
        boolRes = EDeleteFiles(vectFile2Delete);// ������� �������� ����� �� ����� ����
//        return DeleteFile(ssDeleteFileName);
        delete pFileCur;// ���������� ������� � ����
      }
    }
    return boolRes;
  }

  void ChangeFileHandle(int iHandleOld,int iHandleNew)
  // ������� 4:	��������� �������������� ������������ ����� (�� ���� ��� ��������������, �� ����� ������)
  {
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur) continue;
      if (pFileCur->GetHandle() == iHandleOld){
        pFileCur->SetHandle(iHandleNew); return;
      }
    }
  }

  std::vector<std::string> GetFileListByHandleList(std::vector<int> vectHandles)
  // ������� 5:	��������� ������ ������ �� ���������� ��������������� (�� ���� ������ ���������������, �� ����� ������ �� ����� �� ������).
  // ����������� ������ �� ������������.
  {
    std::vector<std::string> vectFileList;// ������ ���������� ������������ �� �������
    for (int iHandle: vectHandles)
      vectFileList.push_back(GetNameByHandle(iHandle));
    return vectFileList;
  }

  std::vector<TFileCtrl *> GetAllFileCtrlList()
  // ������� 6:	��������� ������ ���� ������ (�� ���� ������, �� ������ ������ �� ����� �� ������ � �� ���������������)
  {
    return vectEFiles;
  }

  bool BackupAllFiles()
  // ������� 7:	����� ����������� ������ ��� � 24 ���� � ������������ ��������� ������� ����� ������� � ���������������� �������
  {
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur) continue;
      if (!pFileCur->BackupFile(ssESaveDir)) return false;
    }
    return true;
  }

  std::vector<std::string> RestoreFilesList(int iHandle,std::string ssRestoreDir,std::vector<int> vectFiles2Restore,bool & isSuccess)
  // ������� 8: ����������� �������������� � ������� ������. �������� ����������� ������ �������������� �� ������, ���� ���-�� ������ �� ���.
  // ������������ ���� � ������ ssFileName � ���������� ssRestoreDir.
  // ������������ ����� � ���������� ssRestoreDir. ������ vectFiles2Restore �������� ������� ������, ���������� ��������������, � ������� TLimitedDeque dequeELimited.
  {
    bool boolResTrue = false; isSuccess = true;
    std::vector<std::string> vectRestoredFiles;
//    std::vector<std::string> dequeLimited = GetLimitedDequePaths(iHandle);
    std::vector<SLimitedQueueItem> dequeLimited = GetLimitedDequeItems(iHandle);

    for (int i=0; i < (int)vectFiles2Restore.size(); i++){
      int iIdx = vectFiles2Restore[i];
      std::string ssFileName = dequeLimited[iIdx].ssFileName;
      std::string ssRestoredFilePath = ERestoreFile(ssFileName,ssRestoreDir,boolResTrue);
      isSuccess &= boolResTrue;// ���� ���� � ����� ������ boolResTrue ����� ����� false, �� isSuccess �� ������ �� ������� ���� ����� ����� false
      vectRestoredFiles.push_back(ssRestoredFilePath);
    }
    return vectRestoredFiles;
  }

};// class TFileCtrlStore

// ������� 9:	�������� ��������� ��� ������ � ����������� � ���� GUI ��� CLI ��� ������� ������ ������������

