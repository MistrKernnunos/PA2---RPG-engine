//
// Created by machavi on 5/23/21.
//

#pragma once
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <list>

class CFileLoaderIt {
 public:
  CFileLoaderIt(xmlNode* ptr, xmlDocPtr doc) : curr(ptr), doc(doc){};
  CFileLoaderIt(const CFileLoaderIt& other) : curr(other.curr), prev(other.prev), doc(other.doc){};
  const CFileLoaderIt& operator=(const CFileLoaderIt& other);
  bool operator==(const CFileLoaderIt& lval) const;
  bool Next() const;
  bool Parent() const;
  bool Child() const;
  bool Prev() const;
  bool Empty() const;
  void Print() const;
  bool Valid() const;

  std::list<std::pair<std::string, std::string>> GetProperties() const;
  std::string GetName() const;
  std::string GetContent() const;

 private:
  void print(xmlNode* node) const;

  mutable xmlNode* curr = nullptr;
  mutable xmlNode* prev = nullptr;
  xmlDocPtr doc = nullptr;
};

bool CFileLoaderIt::Next() const {
  prev = curr;
  if (curr) {
    curr = curr->next;
  }
  return curr;
}
bool CFileLoaderIt::Child() const {
  prev = curr;
  if (curr) {
    curr = curr->children;
  }
  return curr;
}
bool CFileLoaderIt::Parent() const {
  prev = curr;
  if (curr) {
    curr = curr->parent;
  }
  return curr;
}

bool CFileLoaderIt::Prev() const {
  xmlNode* tmp = curr;
  curr = prev;
  prev = tmp;
  return curr;
}

std::string CFileLoaderIt::GetName() const {
  std::string name((const char*)curr->name);
  return name;
}
std::list<std::pair<std::string, std::string>> CFileLoaderIt::GetProperties() const {
  std::list<std::pair<std::string, std::string>> res;
  for (xmlAttr* attribute = curr->properties; attribute; attribute = attribute->next) {
    res.emplace_back(std::string((const char*)attribute->name),
                     std::string((const char*)xmlGetProp(curr, attribute->name)));
  }
  return res;
}
std::string CFileLoaderIt::GetContent() const {
  xmlChar* content = xmlNodeListGetString(doc, curr->children, 1);
  std::string res((const char*)content);
  xmlFree(content);
  return res;
}

const CFileLoaderIt& CFileLoaderIt::operator=(const CFileLoaderIt& other) {
  if (*this == other) {
    return other;
  }
  curr = other.curr;
  prev = other.prev;
  return *this;
}

bool CFileLoaderIt::operator==(const CFileLoaderIt& lval) const { return curr == lval.curr && prev == lval.prev; }

bool CFileLoaderIt::Empty() const { return curr; }

void CFileLoaderIt::Print() const { print(curr->children); }

bool CFileLoaderIt::Valid() const { return curr; }

void CFileLoaderIt::print(xmlNode* node) const {
  xmlNode* cur_node = nullptr;
  xmlChar* key = nullptr;
  for (cur_node = node; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      printf("node type: Element, name: %s", cur_node->name);
      if (xmlStrcmp(cur_node->name, (const xmlChar*)"X1") == 0) {
        key = xmlNodeListGetString(doc, cur_node->children, 1);
        printf(" value: %s", key);
        xmlFree(key);
      }
      printf("\n");
    }
    print(cur_node->children);
  }
}