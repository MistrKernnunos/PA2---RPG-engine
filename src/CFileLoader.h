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

  /**
   * loads and parses xml file
   * @param filePath path to the file
   * @return true if successful
   */
  bool LoadXmlFile(const std::string filePath);
  /**
   * creates new blank document
   * @param rootName name of the root node
   * @return iterator to root node
   */
  CFileLoaderIt NewDoc(const std::string rootName);
  /**
   * saves xml file version 1.0 in utf-8 encoding
   * @param filePath path where to save the file
   * @return true if successful
   */
  bool SaveFile(const std::string filePath);
  /**
   * returns node with name
   * @param name which node to find
   * @return not null node if successful, null node if not
   */
  CFileLoaderIt GetNode(const std::string& name);
  /**
   * returns root node
   * @return iterator to root node
   */
  CFileLoaderIt GetTopNode();

 private:
  xmlNode* getNode(const char* name, xmlNode* node);
  xmlDocPtr doc = nullptr;
};
