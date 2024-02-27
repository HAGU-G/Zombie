#include "pch.h"
#include "StringTable.h"
#include "rapidcsv.h"

StringTable::StringTable(Types t)
	:DataTable(t)
{
}

StringTable::~StringTable()
{
}

bool StringTable::Load()
{
	Load(currLang);

	return true;
}

bool StringTable::Load(Languages lang)
{
	table.clear();
	static std::vector<std::string> filePathArray =
	{
		"data/StringTable_KR.csv",
		"data/StringTable_EN.csv"
	};
	currLang = lang;

	rapidcsv::Document doc(filePathArray[(int)lang], rapidcsv::LabelParams(0, -1));
	//std::vector<std::string> keys = doc.GetColumn<std::string>(0);
	//std::vector<std::string> values = doc.GetColumn<std::string>(1);

	for (int i = 0; i < doc.GetRowCount(); ++i)
	{
		std::vector<std::string> pair = doc.GetRow<std::string>(i);
		table.insert({ pair[0], pair[1] });
	}

	return true;
}

void StringTable::Release()
{
}

const std::string& StringTable::Get(const std::string& id)
{
	auto find = table.find(id);
	if (find == table.end())
		return "Undefined ID";
	return find->second;
}
