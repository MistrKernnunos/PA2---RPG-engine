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

  /**
   * returns property of node
   * @return list of pairs first name, second value
   */
  std::list<std::pair<std::string, std::string>> GetProperties();
  /**
   * returns name of the node
   * @return string
   */
  std::string GetName();
  /**
   * returns content of the node
   * @return string
   */
  std::string GetContent();
  /**
   * gets content with checking the node name
   * @param nodeName name of the node
   * @return empty string if name is not correct
   */
  std::string GetContent(const std::string& nodeName);

  /**
   * creates child node of curr node
   * @param name name if the node
   * @return true if successful
   */
  bool CreateNewChildNode(const std::string& name);
  /**
   * creates child node of curr node with content
   * @param name of the node
   * @param text content
   * @return true if successful
   */
  bool CreateNewTextChildNode(const std::string& name, const std::string text);
  /**
   * adds properties to curr node
   * @param props which properties to add
   * @return true if successful
   */
  bool AddProperties(const std::list<std::pair<std::string, std::string>>& props);

 private:
  void print(xmlNode* node);

  mutable xmlNode* curr = nullptr;
  mutable xmlNode* prev = nullptr;
  xmlDocPtr doc = nullptr;
};