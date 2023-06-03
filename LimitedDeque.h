#pragma once

#include <deque>
#include <string>

//////////////////////////
struct SLimitedQueueItem {// ������� ������� TLimitedDeque
//////////////////////////
  std::string ssPathWoName;// ���� ��� ����� �����
  std::string ssFileName;// ������ ��� ����� ��� ����

  SLimitedQueueItem(){}
  SLimitedQueueItem(std::string ssPathWoName,std::string ssFileName): ssPathWoName(ssPathWoName), ssFileName(ssFileName){}
};

/////////////////////////////////////////////////////////
// ������������ ������������ ������� ����� std::string //
/////////////////////////////////////////////////////////
class TLimitedDeque {
protected:
//  std::deque<std::string> deqEVals;// ���������� �������
  std::deque<SLimitedQueueItem> deqEVals;// ���������� �������
  int iEMaxLen=0;// ������������ ����� �������

  void EDelItems(int iDelta)
  // ����������� �� ������� iDelta ����� ������ ���������.
  {
    for (int i=0; i<iDelta; i++)
      deqEVals.pop_front();
  }

public:
// default-�����������:
  TLimitedDeque(){}

  TLimitedDeque(int iMaxLen)
  // ��������������� �����������.
  {
    iEMaxLen = iMaxLen;
  }

  int GetMaxLen()
  // ������ ������������ ����� �������.
  {
    return iEMaxLen;
  }

  void SetMaxLen(int iMaxLen)
  // ��������� ���������� ����� ������������ ����� �������.
  {
  // ���� ������ ����� ������� ������ �����, �� ������� ������ ��������:
    if (iEMaxLen > iMaxLen) EDelItems(iEMaxLen-iMaxLen);

    iEMaxLen = iMaxLen;
  }
  
  int size()
  // ������ ������� ������ �������.
  {
    return (int)deqEVals.size();
  }

  SLimitedQueueItem GetItem(int iIdx)
  // ������ ������� ������������ ������� � ��������� ��������.
  {
    if (iIdx >= (int)deqEVals.size()) throw 0;
    return deqEVals[iIdx];
  }

  std::string GetPath(int iIdx)
  // ������ ����, ������ �� �������� ������������ ������� � ��������� ��������.
  {
    if (iIdx >= (int)deqEVals.size()) throw 0;
    SLimitedQueueItem Item = deqEVals[iIdx];
    return Item.ssPathWoName+Item.ssFileName;
  }

  SLimitedQueueItem GetLastItem()
  // ������ ��������� ������� ������������ �������.
  {
    if (!deqEVals.size()) throw 0;
    return deqEVals[deqEVals.size()-1];
  }

  std::string GetLastPath()
  // ������ ����, ������ �� ���������� �������� ������������ �������.
  {
    if (!deqEVals.size()) throw 0;
    SLimitedQueueItem Item = deqEVals[deqEVals.size()-1];
    return Item.ssPathWoName+Item.ssFileName;
  }

  void InitDeque(SLimitedQueueItem Item)
  // �������� ������ ������� � �������.
  {
    deqEVals.push_back(Item);
  }

  std::string push_back(SLimitedQueueItem Item,bool & wasDelFile)
  // �������� ������� � ����� �������. ���� ��� �������� ����������� �������, ������� ������ �������.
  // ���� ������ ������� ��� ������, ������ ��� � ���� wasDelFile = true.
  {
    wasDelFile = false; SLimitedQueueItem Result;
  // ���� ��������� ���������� ������, ������� ������ ������� � ������ �������:
    if (deqEVals.size() >= iEMaxLen){
      wasDelFile = true;// ���� ��������� ��� ���� ������� ����, ������ ��� �� ���������
      Result = deqEVals.front();// �������� �������� ������� �������� �������
      deqEVals.pop_front();// �������� ������� �������� �������
    }
  // �������� ����� ������� � ����� �������:
    deqEVals.push_back(Item);
    return Result.ssPathWoName+Result.ssFileName;
  }


};// class TLimitedDeque