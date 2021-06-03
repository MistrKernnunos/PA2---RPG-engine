//
// Created by machavi on 5/21/21.
//
#pragma once
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <cstdio>
#include <string>

class CFileLoaderIt;

class CFileLoader {
 public:
  CFileLoader() = default;
  ~CFileLoader();
  bool loadXmlFile(const std::string filePath);
  void printXML(xmlNode* a_Node);
  CFileLoaderIt GetNode(const std::string& name);

 private:
  xmlNode* getNode(const char* name, xmlNode* node);
  //  xmlChar* stringToXmlChar(const std::string& toEncode);
  //  std::string xmlCharToString(xmlChar* toEncode);
  xmlDocPtr doc = nullptr;
};
