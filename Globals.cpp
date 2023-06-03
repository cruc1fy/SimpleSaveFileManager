#include "Globals.h"
#include "FileCtrlStore.h"

void CurrentDate2DateComponents(int & iYear,int & iMonth,int & iDayOfMonth,int & iHour,int & iMin,int & iSec)
// ������������� ������� ������ � ���������� ���� � �������.
{
  auto now = std::chrono::system_clock::now();// �������� ������� ������
  time_t timeNow = std::chrono::system_clock::to_time_t(now);// ������������� � �����

  struct tm curTime;// �������� ���������� ���� � �������
  localtime_s(&curTime,&timeNow);

  iSec = curTime.tm_sec;
  iMin = curTime.tm_min;
  iHour = curTime.tm_hour;
  iDayOfMonth = curTime.tm_mday;// ���� ������
  iMonth = curTime.tm_mon+1;// ����� ������� � 0
  iYear = curTime.tm_year+1900;// ��� ������� � 1900
}

std::string GetTimeStamp()
// ������ ����� ���� � ������� � ���� ������.
{
  int iYear,iMonth,iDayOfMonth,iHour,iMin,iSec;
// �������� ���� ������� ��� ��������� ��������� ������� ���� � �������:
  CurrentDate2DateComponents(iYear,iMonth,iDayOfMonth,iHour,iMin,iSec);
// ������������ ����� ���� � �������; std::to_string ����������� ����� ����� � ������ std::string:
  std::string ssDateTimeStamp = "["+std::to_string(iDayOfMonth)+"."+std::to_string(iMonth)+"."+std::to_string(iYear)+"+"+
    std::to_string(iHour)+"."+std::to_string(iMin)+"."+std::to_string(iSec)+"]";
  return ssDateTimeStamp;
}
