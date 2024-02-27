#include "pch.h"
#include "DataTableMgr.h"
#include "StringTable.h"

DataTableMgr::DataTableMgr()
{
}

DataTableMgr::~DataTableMgr()
{
	Release();
}

void DataTableMgr::Init()
{
	Release();

	//StringTable
	DataTable* table = new StringTable(DataTable::Types::String);
	table->Load();
	tables.insert({ DataTable::Types::String, table });


}

void DataTableMgr::Release()
{
	for (auto pair : tables)
	{
		delete pair.second;
	}
	tables.clear();
}