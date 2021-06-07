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
  bool operator==(const CFileLoaderIt& lval);
  bool Next();
  bool Next(size_t cnt);
  bool Parent();
  bool Child();
  bool Prev();
  bool Empty();
  void Print();
  bool Valid();

  std::list<std::pair<std::string, std::string>> GetProperties();
  std::string GetName();
  std::string GetContent();
  std::string GetContent(const std::string& nodeName);

  bool CreateNewChildNode(const std::string& name);
  bool CreateNewTextChildNode(const std::string& name, const std::string text);
  bool AddProperties(const std::list<std::pair<std::string, std::string>>& props);

 private:
  void print(xmlNode* node);

  mutable xmlNode* curr = nullptr;
  mutable xmlNode* prev = nullptr;
  xmlDocPtr doc = nullptr;
};