#pragma once

#include <deque>
#include <string>

//////////////////////////
struct SLimitedQueueItem {// Элемент очереди TLimitedDeque
//////////////////////////
  std::string ssPathWoName;// Путь без имени файла
  std::string ssFileName;// Только имя файла без пути

  SLimitedQueueItem(){}
  SLimitedQueueItem(std::string ssPathWoName,std::string ssFileName): ssPathWoName(ssPathWoName), ssFileName(ssFileName){}
};

/////////////////////////////////////////////////////////
// Ограниченная двусторонняя очередь строк std::string //
/////////////////////////////////////////////////////////
class TLimitedDeque {
protected:
//  std::deque<std::string> deqEVals;// Собственно очередь
  std::deque<SLimitedQueueItem> deqEVals;// Собственно очередь
  int iEMaxLen=0;// Максимальная длина очереди

  void EDelItems(int iDelta)
  // Выталкивает из очереди iDelta самых старых элементов.
  {
    for (int i=0; i<iDelta; i++)
      deqEVals.pop_front();
  }

public:
// default-конструктор:
  TLimitedDeque(){}

  TLimitedDeque(int iMaxLen)
  // Параметрический конструктор.
  {
    iEMaxLen = iMaxLen;
  }

  int GetMaxLen()
  // Вернет максимальную длину очереди.
  {
    return iEMaxLen;
  }

  void SetMaxLen(int iMaxLen)
  // Позволяет установить новую максимальную длину очереди.
  {
  // Если старая длина очереди больше новой, то удаляет лишние элементы:
    if (iEMaxLen > iMaxLen) EDelItems(iEMaxLen-iMaxLen);

    iEMaxLen = iMaxLen;
  }
  
  int size()
  // Вернет текущий размер очереди.
  {
    return (int)deqEVals.size();
  }

  SLimitedQueueItem GetItem(int iIdx)
  // Вернет элемент ограниченной очереди с указанным индексом.
  {
    if (iIdx >= (int)deqEVals.size()) throw 0;
    return deqEVals[iIdx];
  }

  std::string GetPath(int iIdx)
  // Вернет путь, взятый из элемента ограниченной очереди с указанным индексом.
  {
    if (iIdx >= (int)deqEVals.size()) throw 0;
    SLimitedQueueItem Item = deqEVals[iIdx];
    return Item.ssPathWoName+Item.ssFileName;
  }

  SLimitedQueueItem GetLastItem()
  // Вернет последний элемент ограниченной очереди.
  {
    if (!deqEVals.size()) throw 0;
    return deqEVals[deqEVals.size()-1];
  }

  std::string GetLastPath()
  // Вернет путь, взятый из последнего элемента ограниченной очереди.
  {
    if (!deqEVals.size()) throw 0;
    SLimitedQueueItem Item = deqEVals[deqEVals.size()-1];
    return Item.ssPathWoName+Item.ssFileName;
  }

  void InitDeque(SLimitedQueueItem Item)
  // Добавить первый элемент в очередь.
  {
    deqEVals.push_back(Item);
  }

  std::string push_back(SLimitedQueueItem Item,bool & wasDelFile)
  // Добавить элемент в хвост очереди. Если она достигла предельного размера, удалить первый элемент.
  // Если первый элемент был удален, вернет его и флаг wasDelFile = true.
  {
    wasDelFile = false; SLimitedQueueItem Result;
  // Если достигнут предельный размер, удалить первый элемент в голове очереди:
    if (deqEVals.size() >= iEMaxLen){
      wasDelFile = true;// Флаг говорящий что надо удалить файл, вернем его из программы
      Result = deqEVals.front();// Получить значение первого элемента очереди
      deqEVals.pop_front();// Удаление первого элемента очереди
    }
  // Добавить новый элемент в хвост очереди:
    deqEVals.push_back(Item);
    return Result.ssPathWoName+Result.ssFileName;
  }


};// class TLimitedDeque