#include "Globals.h"
#include "FileCtrlStore.h"

void CurrentDate2DateComponents(int & iYear,int & iMonth,int & iDayOfMonth,int & iHour,int & iMin,int & iSec)
// Преобразовать текущий момент в компоненты даты и времени.
{
  auto now = std::chrono::system_clock::now();// Получить текущий момент
  time_t timeNow = std::chrono::system_clock::to_time_t(now);// Преобразовать в число

  struct tm curTime;// Получить компоненты даты и времени
  localtime_s(&curTime,&timeNow);

  iSec = curTime.tm_sec;
  iMin = curTime.tm_min;
  iHour = curTime.tm_hour;
  iDayOfMonth = curTime.tm_mday;// День месяца
  iMonth = curTime.tm_mon+1;// Месяц начиная с 0
  iYear = curTime.tm_year+1900;// Год начиная с 1900
}

std::string GetTimeStamp()
// Вернет метку даты и времени в виде строки.
{
  int iYear,iMonth,iDayOfMonth,iHour,iMin,iSec;
// Вызываем нашу функцию для получения компонент текущих даты и времени:
  CurrentDate2DateComponents(iYear,iMonth,iDayOfMonth,iHour,iMin,iSec);
// Сформировать метку даты и времени; std::to_string преобразует целое число в формат std::string:
  std::string ssDateTimeStamp = "["+std::to_string(iDayOfMonth)+"."+std::to_string(iMonth)+"."+std::to_string(iYear)+"+"+
    std::to_string(iHour)+"."+std::to_string(iMin)+"."+std::to_string(iSec)+"]";
  return ssDateTimeStamp;
}
