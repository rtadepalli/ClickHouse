#pragma once

#include <Poco/SharedPtr.h>

#include <DB/Core/Names.h>
#include <DB/Core/Block.h>
#include <DB/Core/ColumnNumbers.h>
#include <DB/DataTypes/IDataType.h>


namespace DB
{

/** Интерфейс для обычных функций.
  * Обычные функции - это функции, которые не меняют количество строк в таблице,
  *  и результат работы которых для каждой строчки не зависит от других строк.
  *
  * Функция может принимать произвольное количество аргументов и возвращать произвольное количество значений.
  * Типы и количество значений результата зависят от типов и количества аргументов.
  *
  * Функция диспетчеризуется для целого блока. Это позволяет производить всевозможные проверки редко,
  *  и делать основную работу в виде эффективного цикла.
  *
  * Функция применяется к одному или нескольким столбцам блока, и записывает свой результат,
  *  добавляя новые столбцы к блоку. Функция не модифицирует свои агрументы.
  */
class IFunction
{
public:
	/// Получить основное имя функции.
	virtual String getName() const = 0;

	/// Получить тип результата по типам аргументов. Если функция неприменима для данных аргументов - кинуть исключение.
	virtual DataTypePtr getReturnType(const DataTypes & arguments) const = 0;

	/// Выполнить функцию над блоком.
	virtual void execute(Block & block, const ColumnNumbers & arguments, size_t result) = 0;
};


using Poco::SharedPtr;

typedef SharedPtr<IFunction> FunctionPtr;


}
