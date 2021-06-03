//
// Created by machavi on 6/2/21.
//
#pragma once
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <list>
#include <stdexcept>
#include <string>

class CFileLoaderIt {
 public:
  CFileLoaderIt(xmlNode* ptr, xmlDocPtr doc) : curr(ptr), doc(doc){};
  CFileLoaderIt(const CFileLoaderIt& other) : curr(other.curr), prev(other.prev), doc(other.doc){};
  CFileLoaderIt& operator=(const CFileLoaderIt& other);
  bool operator==(const CFileLoaderIt& lval) const;
  bool Next() const;
  bool Next(size_t cnt) const;
  bool Parent() const;
  bool Child() const;
  bool Prev() const;
  bool Empty() const;
  void Print() const;
  bool Valid() const;

  std::__cxx11::list<std::pair<std::string, std::string>> GetProperties() const;
  std::string GetName() const;
  std::string GetContent() const;
  std::string GetContent(const std::string& nodeName) const;

 private:
  void print(xmlNode* node) const;

  mutable xmlNode* curr = nullptr;
  mutable xmlNode* prev = nullptr;
  xmlDocPtr doc = nullptr;
};