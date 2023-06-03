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

// Список реализуемых функций:
//1.	Сохранение файла по уникальному идентификатору(на вход подается путь до файла, на выход возвращается идентификатор)
//2.	Выдача сохраненного файла по идентификатору. На вход подается идентификатор, на выход путь до файла.
//3.	Удаление файла по идентификатору (на вход подается идентификатор, на выход ничего)
//4.	Изменение идентификатора сохраненного файла (на вход два идентификатора, на выход ничего)
//5.	Получение списка файлов по нескольким идентификаторам (на вход список идентификаторов, на выход список из путей до файлов)
//6.	Получение списка всех файлов (на вход ничего, на выходе список из путей до файлов и их идентификаторов)
//7.	Бэкап сохраненных файлов раз в 24 часа с возможностью изменения времени этого времени и версионированием бэкапов
//8.	Возможность восстановиться с помощью бэкапа. Добавить возможность отмены восстановления на случай, если что-то пойдет не так
//9.	Добавить интерфейс для работы с приложением в виде GUI или CLI для удобной работы пользователя

// BYTE - беззнаковое однобайтовое число [0..255]
// WORD = 2 BYTE - беззнаковое двубайтовое число [0..65535]
// DWORD = 2 WORD = 4 BYTE - беззнаковое четырехбайтовое число [0..4294967295]

const int ciDequeLimit = 3;// Предельная длина очереди сохраненных файлов

// Описание сохраняемого файла, одна структура на один файл:
//////////////////
class TFileCtrl {// Пара "имя-файла -- дескриптор"
//////////////////
protected:
  int iEHandle=0;// Дескриптор
// Тип std::string автоматически инициализируется сам:
  std::string ssEFileDirSrc;// Исходная директория, в которой лежал файл
  std::string ssEFileName;// Имя файла
  TLimitedDeque dequeELimited;// Очередь фиксированного размера для последних сохраненных версий файла

public:
// этот конструктор вызывается когда создается объект этой структуры и не задаются никакие параметры(например массив структур)
//  TFileCtrl(){}// default constructor конструктор по умолчанию

  TFileCtrl(int iHandle,std::string ssFileDirSrc,std::string ssFileName,std::string ssSaveDir,int iDequeLimit=ciDequeLimit)
  // Параметрический конструктор; их может быть много, но с разными списками входных параметров.
  {
  // this указывает на объект этого класса
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
  // Сделать копию файла.
  {
    std::string ssTimeStamp = GetTimeStamp();// Получить метку текущих даты и времени в виде строки
	// Вызываем функцию find_last_of для нашего имени файла ssEFileName;
	// find_last_of('.') дает индекс последнего вхождения точки в имени файла:
    std::string::size_type const iPointPos(ssEFileName.find_last_of('.'));
	// Функция substr(0, iPointPos) вернет подстроку ssEFileName начиная с нулевой позиции до позиции iPointPos:
    std::string ssFileNameWoExt = ssEFileName.substr(0, iPointPos);
	// Находим только расширение файла ssEFileName от позиции следующей за точкой до конца имени:
    std::string ssFileExt = ssEFileName.substr(iPointPos+1,ssEFileName.length());

    std::string ssSrcFilePath = ssEFileDirSrc+"\\"+ssEFileName;
    std::string ssFileName = ssFileNameWoExt+"."+ssTimeStamp+"."+ssFileExt;
	// Собираем путь копирования куда из заданной директории и имени файла с добавленной меткой даты и времени:
    std::string ssBackupFilePath = ssSaveDir+ssFileNameWoExt+"."+ssTimeStamp+"."+ssFileExt;
//    if (!std::filesystem::copy_file(ssEFileName,ssBackupFileName,std::filesystem::copy_options::overwrite_existing)) return;
    try {
      if (!std::filesystem::copy_file(ssSrcFilePath,ssBackupFilePath)) return false;
    } catch(std::exception e){
      return false;
    } catch(...){
      return false;
    }
  // Если файл успешно скопирован, добавить его в список последних версий:
    bool wasDelFile = false;
	// Добавить в очередь новый файл ssBackUpFilePath, если очередь уже заполнена, вернет флаг wasDelFile = true
	// и путь файла который надо удалить ssFile2DeletePath:
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
class TFileCtrlStore {// Класс "хранилище, управляющее файлами"
//////////////////////
protected:
  std::string ssESaveDir;// Директория для сохранения файлов
  std::vector<TFileCtrl *> vectEFiles;// Вектор указателей на структуру, описывающих сохраняемые файлы - динамический массив

  bool ECreateDir(std::string ssDir)
  // Создать рабочую директорию программы.
  {
		// из объекта ssDir класса std::string извлекаем строку в стиле старого C (ASCIIZ) = const char*, нуль терминированная строка
		// сначала преобразуем строку типа std::string в ASCIIZ при помощи функции c_str
		// потом приводим строку типа ASCIIZ к типу LPCSTR(необязательно)
		// LPCSTR sSaveDir = (LPCSTR)ssDir.c_str(); // LPCSTR - const CHAR*

		// ANSI - вариант функции CreateDirectory, 1 символ - 1 байт, подходит для английского языка
		// Есть также Unicode вариант он называется CreateDirectoryW, 1 символ - 2 байта, подходит для любых языков

		// BOOL boolRes = CreateDirectoryA(sSaveDir, NULL); // создать директорию windows 
		// DWORD dwError = GetLastError();
		// сначала вызывается CreateDirectoryA если она создала директорию, сразу выходим из функции и вернем true 
		// если директория уже существует, то CreateDirectoryA вернет false и в этом случае вызывается функция GetLastError
		// GetLastError - вернет последнюю ошибку в функции windows
		// ERROR_ALREADY_EXISTS - ошибка "уже существует"
		// если ERROR_ALREADY_EXISTS то функция вернет true иначе вернет false
		// CreateDirectoryA - системная функция windows, GetLastError также системная функция
    return (CreateDirectoryA((LPCSTR)ssDir.c_str(), NULL) || GetLastError() == ERROR_ALREADY_EXISTS);//183 = 0xB7
  }

  bool ECopyFile(std::string ssSrc,std::string ssDst)
  // Функция защищенного (try..catch) копирования файлов, ssSrc - путь откуда, ssDst - путь куда.
  {
    bool boolRes = false;
	// try - catch - единый оператор, в котором исполняются какие то функции, 
	// если в этих функциях происходит сбой(exception), то управление передается в catch(фильтр обработки)
	// таких фильтров может быть много, программа пробует их один за другим, в поисках правильного обработчика
		try { // Защищаемый блок - исполнение любых операторов и защита программы от ошибок в этих операторах
	  // Если в операторе copy_file будет ошибка, мы ее перехватим
      boolRes = std::filesystem::copy_file(ssSrc,ssDst,std::filesystem::copy_options::overwrite_existing);
    }
    catch(...){// Обработчик всех не перехваченных раньше исключений, общий обработчик
      return false;
    }
    return boolRes;
  }

  bool ESaveFile(std::string ssDirSrc,std::string ssFileName)
  // Скопировать сохраняемый файл в рабочую директорию.
	// ssDirSrc - директория откуда копируются файлы; ssFileName - файл который копируется.
  {
	// \" - воспринимается компилятором как управляющая последовательность, например: \n - конец строки, \t - табуляция
	// \ - признак начала управляющей последовательности, \\ = \ 
    std::string ssSrcFileName = ssDirSrc+"\\"+ssFileName;// Путь откуда - место откуда копируются файлы
    std::string ssBackupFileName = ssESaveDir+ssFileName;// Путь куда - место сохранения файлов
    return ECopyFile(ssSrcFileName,ssBackupFileName);
  }

  std::string ERestoreFile(std::string ssFileName,std::string ssRestoreDir,bool & boolRes)
  // Скопировать ранее сохраненный файл обратно в заданную директорию.
	// Эта функция вернет два параметра, первый std::string а второй bool&
	// bool boolResult - локальная переменная которая будет потеряна при выходе из функции
	// bool &boolResult - переменная которая возвращается по ссылке, результат будет передан из функции
	// ссылка(reference) - адрес переменной, почти указатель, но к указателю обращаются через стрелочку и он может быть равен 0, а ссылка никогда не равна нулю
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
    return (boolRes) ? ssRestoreFileName : "";// То же самое что предыдущие 6 строк
  }

  bool EDeleteFiles(std::vector<std::string> vectFile2Delete)
  // Удалить файлы, имена которых заданы в векторе vectFile2Delete.
  {
    bool boolRes = true;

    for (std::string ssFileName2Del: vectFile2Delete)
      boolRes &= DeleteFile(ssFileName2Del);
     
    return boolRes;
  }


public:
  TFileCtrlStore()
  // Default-конструктор.
  {
  }

  TFileCtrlStore(std::string ssSaveDir)
  // Параметрический конструктор.
  {
    ssESaveDir = ssSaveDir;// Слева - куда, справа - откуда; например: X=10
	// Если ECreateDir вернет false, то сразу выходим из конструктора, чтобы его дальнейшая часть не выполнялась
	// Обычно вместо return используется опретор throw - выбросить исключение: try..catch
    if (!ECreateDir(ssESaveDir)) return;
  }

  ~TFileCtrlStore()
  // Деструктор.
  {
	// Пройти по всем элементам вектора и освободить их, потому что эти элементы - указатели, они не освобождаются автоматически:
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur) continue;
      delete pFileCur; pFileCur = nullptr;
    }
  }

  bool SetSaveDir(std::string ssSaveDir)
  // Установить директорию для сохранения файлов.
  {
    ssESaveDir = ssSaveDir;
    return ECreateDir(ssESaveDir);
  }

  int GetCount()
  // Вернет количество элементов в векторе сохраненных файлов vectEFiles.
  {
    return (int)vectEFiles.size();
  }

  int GetFileHandleByName(std::string ssDirSrc,std::string ssFileName)
  // На вход подается путь до файла, на выход возвращается идентификатор.
  {
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur) continue;
      if (pFileCur->GetFileDir() == ssDirSrc && pFileCur->GetFileName() == ssFileName) 
        return pFileCur->GetHandle();
    }
    return -1;
  }

  std::string GetNameByHandle(int iHandle)
  // Вернет по дескриптору путь к файлу.
  {
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur || pFileCur->GetHandle() != iHandle) continue;
      std::string ssResult = pFileCur->GetFileDir() + "\\" + pFileCur->GetFileName();
      return ssResult;
    }
    return "";
  }

  bool HasNameByHandle(int iHandle)
  // Вернет true, если для данного дестриптора в списке сохраненных файлов имеется имя.
  {
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur || pFileCur->GetHandle() != iHandle) continue;
      std::string ssResult = pFileCur->GetFileDir() + "\\" + pFileCur->GetFileName();
      return true;
    }
    return false;
  }

  std::vector<std::string> GetLimitedDequePaths(int iHandle)
  // Если файл с таким iHandle не найден - вернем пустой вектор.
  {
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur || pFileCur->GetHandle() != iHandle) continue;
      return pFileCur->GetLimitedDequePaths();
    }
    return std::vector<std::string>();
  }

  std::vector<SLimitedQueueItem> GetLimitedDequeItems(int iHandle)
  // Если файл с таким iHandle не найден - вернем пустой вектор.
  {
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur || pFileCur->GetHandle() != iHandle) continue;
      return pFileCur->GetLimitedDequeItems();
    }
    return std::vector<SLimitedQueueItem>();
  }

  bool DeleteFile(std::string ssDeleteFileName)
  // Функция удаляет файл, при этом перехватывает возможные ошибки.
  {
    try {
      std::filesystem::remove(ssDeleteFileName);
    } catch(...){
      return false;
    }
    return true;
  }

  int AddFile(std::string ssDirSrc,std::string ssFileName)
  // Функция 1: сохранение файла по уникальному идентификатору(на вход подается путь до файла, на выход возвращается идентификатор)
  // Сохранение имени файла во внутреннем векторе.
	// из директории ssDirSrc взять файл ssFileName и скопировать его в директорию ssESaveDir, сохранить его в наших внутренних структурах(vectEFiles)
	// Src = source - источник, sources - исходные тексты
	// добавить файл ssFileName к нашим внутренним структурам. Вернет либо дескриптор файла, либо -1 если ошибка
  {

	// Попытка сохранить файл ssFileName в нашей рабочей директории ssESaveDir:
    if (!ESaveFile(ssDirSrc,ssFileName)) return -1;
	// Если мы здесь то функция ESaveFile отработала успешно

  // Принимаем число элементов в векторе за дескриптор (числовой описатель) файла:
    int iNextHandle = (int)vectEFiles.size();// size_t - беззнаковое целое, int - знаковое целое, iNextHandle - локальная переменная функции AddFile

	// TFileControl FileControl; // объект структуры TFileControl созданной в стековой памяти - будет удален при выходе из этой функции
	// создание объекта типа TFileControl в куче - будет существовать либо до оператора delete pFileControl, либо до конца работы программы
	// TFileControl *pFileControl = new TFileControl; // вызывается конструктор без параметров т. е. дефолтный
	// вызывем конструктор с двумя аргументами, здесь iNextNandle и ssFileName - фактические параметры

	// Объект создается в куче, то есть выделяется память в куче для объекта типа указатель на TFileCtrl:
    vectEFiles.push_back(new TFileCtrl(iNextHandle,ssDirSrc,ssFileName,ssESaveDir));
    return iNextHandle;
  }

  std::string RestoreFileByHandle(int iHandle,std::string ssRestoreDir,bool & boolRes)
  // Функция 2:	выдача сохраненного файла по идентификатору. На вход подается идентификатор, на выход путь до файла.
  // boolRes = true, если функция завершилась успешно.

  // int iHandle, std::string ssRestoreDir, bool& boolRes - параметры функции
	// выдача сохраненного файла по идентификатору
	// bool& - ссылочный тип для возвращения параметра boolRes из функции
	// если было бы просто bool boolRes в заголовке функции, то это был бы локальный параметр
	// bool& boolRes это передача параметра наружу из функции по ссылке(по адресу)
  {
    boolRes = false;// Инициализация boolRes потому что можем вернуться из функции досрочно, нужно чтобы возвращаемые параметры имели осмысленное значение
    if (!ECreateDir(ssRestoreDir)) return "";// Создать директорию RestoreDir, если ее еще нет
  // Современный цикл типа forall, который будет перебирать все элементы в контейнере vectEFiles, FileCur - текущая переменная
    for (TFileCtrl * pFileCur: vectEFiles){
		// if (!pFileCur) throw 0; // Проверка что указатель не нулевой, если он нулевой то выбросится исключение(0)
		// если throw не будет обработана программой выше по стеку, то будет аварийное завершение программы
      if (!pFileCur) continue;
		// Обращение к полю iHandle структуры pFileCur:
      if (pFileCur->GetHandle() == iHandle)
        return ERestoreFile(pFileCur->GetFileName(),ssRestoreDir,boolRes);
    }
    return "";
  }

  std::string RestoreLastFileByHandle(int iHandle,std::string ssRestoreDir,bool & boolRes)
  // Функция 2:	выдача последнего сохраненного файла по идентификатору. На вход подается идентификатор, на выход путь до файла.
  // boolRes = true, если функция завершилась успешно.
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
  // Функция 3:	удаление файла по идентификатору (на вход подается идентификатор, на выход ничего)
  {
    bool boolRes = false;
    for (int iIdx=0; iIdx < (int)vectEFiles.size(); iIdx++){
      TFileCtrl * pFileCur = vectEFiles[iIdx];
		// if (!pFileCur) throw 0; выбрасываем исключение, самый жесткий вариант обработки
		// if (!pFileCur) break; в этом случае цикл завершается, жесткая обработка нулевого указателя
      if (!pFileCur) continue;// Переход к следующей итерации цикла, мягкая обработка 
      if (pFileCur->GetHandle() == iHandle){
			// erase - 2 аргумента - итератора, первый указывает на начальный стираемый элемент а второй указывает на элемент за последним стираемым
			// begin() - вернет итератор указывающий на начало вектора
			// end() - вернет итератор указывающий на первый элемент за концом вектора
        vectEFiles.erase(vectEFiles.begin()+iIdx,vectEFiles.begin()+iIdx+1);// Стирает элемент с индексом i
        std::string ssDeleteFileName = ssESaveDir+pFileCur->GetFileName();// Формирование путь до файла который нужно стереть
        std::vector<std::string> vectFile2Delete = pFileCur->GetLimitedDequePaths();
        boolRes = EDeleteFiles(vectFile2Delete);// Команда удаления файла по этому пути
//        return DeleteFile(ssDeleteFileName);
        delete pFileCur;// Освободить элемент в куче
      }
    }
    return boolRes;
  }

  void ChangeFileHandle(int iHandleOld,int iHandleNew)
  // Функция 4:	изменение идентификатора сохраненного файла (на вход два идентификатора, на выход ничего)
  {
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur) continue;
      if (pFileCur->GetHandle() == iHandleOld){
        pFileCur->SetHandle(iHandleNew); return;
      }
    }
  }

  std::vector<std::string> GetFileListByHandleList(std::vector<int> vectHandles)
  // Функция 5:	получение списка файлов по нескольким идентификаторам (на вход список идентификаторов, на выход список из путей до файлов).
  // Копирование файлов не производится.
  {
    std::vector<std::string> vectFileList;// Задаем переменную возвращаемую из функции
    for (int iHandle: vectHandles)
      vectFileList.push_back(GetNameByHandle(iHandle));
    return vectFileList;
  }

  std::vector<TFileCtrl *> GetAllFileCtrlList()
  // Функция 6:	получение списка всех файлов (на вход ничего, на выходе список из путей до файлов и их идентификаторов)
  {
    return vectEFiles;
  }

  bool BackupAllFiles()
  // Функция 7:	бэкап сохраненных файлов раз в 24 часа с возможностью изменения времени этого времени и версионированием бэкапов
  {
    for (TFileCtrl * pFileCur: vectEFiles){
      if (!pFileCur) continue;
      if (!pFileCur->BackupFile(ssESaveDir)) return false;
    }
    return true;
  }

  std::vector<std::string> RestoreFilesList(int iHandle,std::string ssRestoreDir,std::vector<int> vectFiles2Restore,bool & isSuccess)
  // Функция 8: возможность восстановиться с помощью бэкапа. Добавить возможность отмены восстановления на случай, если что-то пойдет не так.
  // Восстановить файл с именем ssFileName в директорию ssRestoreDir.
  // Восстановить файлы в директорию ssRestoreDir. Список vectFiles2Restore содержит индексы файлов, подлежащих восстановлению, в очереди TLimitedDeque dequeELimited.
  {
    bool boolResTrue = false; isSuccess = true;
    std::vector<std::string> vectRestoredFiles;
//    std::vector<std::string> dequeLimited = GetLimitedDequePaths(iHandle);
    std::vector<SLimitedQueueItem> dequeLimited = GetLimitedDequeItems(iHandle);

    for (int i=0; i < (int)vectFiles2Restore.size(); i++){
      int iIdx = vectFiles2Restore[i];
      std::string ssFileName = dequeLimited[iIdx].ssFileName;
      std::string ssRestoredFilePath = ERestoreFile(ssFileName,ssRestoreDir,boolResTrue);
      isSuccess &= boolResTrue;// Если хоть в одном вызове boolResTrue будет равно false, то isSuccess на выходе из функции тоже будет равно false
      vectRestoredFiles.push_back(ssRestoredFilePath);
    }
    return vectRestoredFiles;
  }

};// class TFileCtrlStore

// Функция 9:	добавить интерфейс для работы с приложением в виде GUI или CLI для удобной работы пользователя

