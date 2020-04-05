#pragma once
#include <string>

class File
{
public:

	std::string name;			// имя файла
	std::string magic;			// набор магических байт/сигнатруа
	std::string chsum;			// контрольтная сумма заголовка/файла
	std::string os;				// целевая ос
	std::string time_stamp;		// отметка времени (время создания/время модификации)
	std::string format;			// формат файла
	std::string type;			// тип файла
	std::string compression;	// метод/алгоритм сжатия
	std::string extension;		// расширение файла
	std::string arch;			// архитектура целевой системы
	int network;				// наличие сетевыз возможнойстей (0 - есть, 1 - нет)
	int filesInside;			// количество файлов внутри (акутально для архивов)
	unsigned long long size;	// размер файла
	int magic_offset;			// смещение до сигнатуры
	int magic_offset_size;		// длина сигнатуры

	
	File();																// пустой конструктор. нужен для создания массива File* formatObjects[]
	File(std::string format, std::string magic);						// конструктор.принимает парметры: формат файла, набор магических байт файла
																		 
	int formatToInt();													// {
	int compressionToInt();												// методы для измнения значений 
	int typeToInt();													// для более удобной записи в БД
	int osToInt();														// }

	void getNameAndExt(std::string filePath);							// метод, определяющий имя и расширение файла. Записывает значения в поля file.name, file.extension
	void getInfo();														// метод для вывода значений полей экземпляра file

	std::string convertTime(std::string unixTime);						// метод конвертирует время формате ubixTime в обычный формат: часы:минуты:секунды число:месяц:год
	std::string convertBigEndian(std::string bigEndian, int bytes);		// метод изменяет порядок байт little Endian в big Endian. работает либо для 2 байт либо для 4
	std::string convertHexToDec(std::string hexInString);				// метод переыодит из 16 СС в 10 СС

	virtual void parseFile(std::string fileInBytes, File* file);		// метод отвечает за парсинг файла. Каждый производный класс переопределяет данный метод
	virtual std::string getFormat();									// метод возвращает формат файла
	virtual std::string getMagic();										// метод возыращает сигнатуру файла
	virtual int getMagicOffset();										// метод возвращает смещение до сигнатуры
	virtual int getMagicOffsetSize();									// метод возвращает длину сигнатуры

};
