#include "Data.h"
#include "TemplateException.h"

using std::string;
using std::map;
using std::vector;

namespace syslandscape {
namespace tmpl {


Data::Data() : _type(DataType::NONE), _object(nullptr), _list(nullptr), _string(nullptr), _int(nullptr) { }
Data::Data(DataType type) : _type(type),  _object(nullptr), _list(nullptr), _string(nullptr), _int(nullptr) {
  initValue(type);
}
Data::Data(const Data &v) : _type(DataType::NONE), _object(nullptr), _list(nullptr), _string(nullptr), _int(nullptr) {
  copy(v);
}
Data::Data(const string &value) : _type(DataType::NONE), _object(nullptr), _list(nullptr), _string(nullptr), _int(nullptr) {
  initValue(DataType::STRING);
  operator=(value);
}
Data::Data(const char *value) : _type(DataType::NONE), _object(nullptr), _list(nullptr), _string(nullptr), _int(nullptr) {
  initValue(DataType::STRING);
  operator=(string(value));
}

Data::Data(int value) : _type(DataType::NONE), _object(nullptr), _list(nullptr), _string(nullptr), _int(nullptr) {
  initValue(DataType::INT);
  operator=(value);
}

Data::~Data()
{
  if (nullptr != _string)
    {
      delete _string;
    }
  if (nullptr != _int)
    {
      delete _int;
    }
  if (nullptr !=  _object)
    {
      releaseObject();
    }
  if (nullptr != _list)
    {
      releaseList();
    }
}

size_t Data::size() const noexcept
{
  if (isObject()) return _object->size();
  if (isList()) return _list->size();
  if (isString()) return _string->size();
  throw TemplateException("Data type " + toString(_type) + " doesn't have size.");
}

bool Data::hasMember(const string &key) const
{
  if (!isObject() || _object == nullptr) return false;
  return _object->find(key) != _object->end();
}

string Data::asString() const
{
  if (!isString()) throw TemplateException("Not a " + toString(DataType::STRING) + " data.");
  return *_string;
}

int Data::asInt() const
{
  if (!isInt()) throw TemplateException("Not a " + toString(DataType::INT) + " data.");
  return *_int;
}

/**
 * Returns object's property.
 * 
 * If value type is NONE, then type is changed to object.
 */
Data& Data::operator[](const string &key)
{
  if (_type == DataType::NONE) initValue(DataType::OBJECT);
  if (!isObject()) throw TemplateException("Error with key " + key +  ". Data type " + toString(getType()) + " is not object.");
  if (!hasMember(key)) {
    _object->insert(std::pair<string, Data *>(key, new Data()));
  }
  return *_object->at(key);
}

const Data & Data::operator[](const string &key) const
{
  if (!isObject()) throw TemplateException("Error with key " + key +  ". Data type " + toString(getType()) + " is not object.");
  if (!hasMember(key)) throw TemplateException(toString(_type) +  " has no key " + key +  ".");
  
  return *_object->at(key);
}

/**
 * Returns object's array index.
 * 
 * If value type is NONE, then type is changed to array.
 */
Data& Data::operator[](int index)
{
  if (_type == DataType::NONE) initValue(DataType::LIST);
  if (!isList()) throw TemplateException("Error with index " + std::to_string(index) +  ". Data type " + toString(getType()) + " is not array.");
  return *_list->at(index);
}

const Data& Data::operator[](int index) const
{
  if (!isList()) throw TemplateException("Error with index " + std::to_string(index) +  ". Data type " + toString(getType()) + " is not array.");
  
  return *_list->at(index);
}

void Data::operator=(const char *value)
{
  if (_type == DataType::NONE) initValue(DataType::STRING);
  if (!isString()) throw TemplateException("Can't assign " + string(value) + " to non " + toString(_type) + " data.");
  _string->assign(value);
}

void Data::operator=(const string &value)
{
  if (_type == DataType::NONE) initValue(DataType::STRING);
  if (!isString()) throw TemplateException("Can't assign " + value + " to non " + toString(_type) + " data.");
  _string->assign(value);
}

void Data::operator=(int value)
{
  if (_type == DataType::NONE) initValue(DataType::INT);
  if (!isInt()) throw TemplateException("Can't assign " + std::to_string(value) + " to non " + toString(_type) + " data.");
  *_int = value;
}

Data& Data::operator=(Data &d) {
  if (isObject()) { releaseObject(); initValue(DataType::OBJECT); }
  if (isList()) { releaseList(); initValue(DataType::LIST); }
  
  copy(d);
  
  return *this;
}


Data* Data::find(const string &key)
{
  if (DataType::OBJECT != _type && DataType::LIST != _type)
    {
      return nullptr;
    }
  if (key[0] == '\"')
    {
      return nullptr;
    }

  size_t index = key.find(".");
  if (index == std::string::npos)
    {
      if (!hasMember(key))
        {
          return nullptr;
        }
      return &operator[](key);
    }

  string property = key.substr(0, index) ;
  if (!hasMember(property))
    {
      return nullptr;
    }
  return operator [](property).find(key.substr(index+1));
}

void Data::append(const Data &d)
{
  if (_type == DataType::NONE) initValue(DataType::LIST);
  if (!isList()) throw TemplateException("Can't append value to " + toString(_type));

  _list->push_back(new Data(d));  
}

void Data::copy(const Data &v)
{
  if (DataType::NONE != _type && _type != v._type) throw TemplateException("Can't assign " + toString(v._type) + " to " + toString(_type));
  if (DataType::NONE == _type) initValue(v._type);

  if (DataType::STRING == _type) this->operator=(*v._string);
  if (DataType::INT == _type) this->operator=(*v._int);
  
  if (DataType::OBJECT == _type) {
    for (auto pair: *v._object)
      _object->insert(std::pair<string, Data *>(pair.first, new Data(*pair.second)));
  }
  if (DataType::LIST == _type) {
    for (auto item: *v._list) {
      _list->push_back(new Data(*item));
    }
  }
}

void Data::initValue(DataType type)
{
  _type = type;
  if (DataType::STRING == _type) _string = new string();
  if (DataType::INT == _type)  _int = new int(0);
  if (DataType::OBJECT == _type)  _object = new map<string, Data *>();
  if (DataType::LIST == _type)  _list = new vector<Data *>();  
}

void Data::releaseObject()
{
  if (nullptr == _object) return;
  for (auto pair: *_object) delete pair.second;
  _object->clear();
  delete _object;
}

void Data::releaseList()
{
  if (nullptr == _list) return;
  for (auto item: *_list) delete item;
  _list->clear();
  delete _list;
}

string Data::toString(DataType type)
{
  switch(type) {
  case DataType::NONE: return "none"; break;
  case DataType::STRING: return "string"; break;
  case DataType::OBJECT: return "object"; break;
  case DataType::LIST: return "list"; break;
  case DataType::DOUBLE : return "double"; break;
  case DataType::INT: return "int"; break;
  }
  return "unknown";
}

} /* namespace tmpl */
} /* namespace syslandscape  */
