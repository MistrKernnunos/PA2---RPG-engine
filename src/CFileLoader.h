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
  bool LoadXmlFile(const std::string filePath);
  CFileLoaderIt NewDoc(const std::string rootName);
  bool SaveFile(const std::string filePath);
  void printXML(xmlNode* a_Node);
  CFileLoaderIt GetNode(const std::string& name);
  CFileLoaderIt GetTopNode();

 private:
  xmlNode* getNode(const char* name, xmlNode* node);
  xmlDocPtr doc = nullptr;
};
