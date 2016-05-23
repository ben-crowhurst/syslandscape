#ifndef SYSLANDSCAPE_TMPL_DATA
#define SYSLANDSCAPE_TMPL_DATA

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "DataType.h"

namespace syslandscape {
namespace tmpl {

class Data
{
public:
  
  Data();
  Data(DataType);
  Data(const std::string &);
  Data(const char *);
  Data(int);

  virtual ~Data();
  
  DataType getType() const;

  bool isObject() const;
  bool isList() const;
  bool isString() const;
  bool isInt() const;

  size_t size() const noexcept;
  bool hasMember(const std::string &) const;
  std::string asString() const;
  int asInt() const;

  Data& operator[](const std::string &key);
  const Data& operator[](const std::string &key) const;  
  Data& operator[](int index);
  const Data& operator[](int index) const;

  void operator=(const char *);
  void operator=(const std::string &);
  void operator=(int);
  Data& operator=(Data &d);

  Data* find(const std::string &);

  void append(const Data &value);

private:

  DataType _type;

  std::map<std::string, Data *> *_object;
  std::vector<Data *> *_list;  
  std::string *_string;
  int *_int;

  Data(const Data &);
  
  static std::string toString(DataType);

  void copy(const Data &);

  /**
   * Deletes all allocated Data objects and clears _object map.
   */
  void releaseObject();
  /**
   * Deletes all allocated Data objects and clears _list vector.
   */  
  void releaseList();

  void initValue(DataType);

}; // class Data


inline DataType Data::getType() const
{
  return _type;
}

inline bool Data::isObject() const
{
  return DataType::OBJECT == _type;
}

inline bool Data::isList() const
{
  return DataType::LIST == _type;
}

inline bool Data::isString() const
{
  return DataType::STRING == _type;
}

inline bool Data::isInt() const
{
  return DataType::INT == _type;
}


} /* namespace tmpl */
} /* namespace syslandscape  */

#endif /* SYSLANDSCAPE_TMPL_DATA */
