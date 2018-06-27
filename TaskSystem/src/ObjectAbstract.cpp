#include "ObjectAbstract.h"

ObjectAbstract::ObjectAbstract(std::shared_ptr<DataAbstract> data):
	data(data){}

const std::shared_ptr<DataAbstract>& ObjectAbstract::GetData()
{
	return data;
}