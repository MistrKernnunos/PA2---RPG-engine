//
// Created by machavi on 5/23/21.
//
#include "CFileLoaderIterator.h"

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
  if (!curr) {
    throw std::invalid_argument("node is null");
    return "";
  }
  std::string name((const char*)curr->name);
  return name;
}
std::list<std::pair<std::string, std::string>> CFileLoaderIt::GetProperties() const {
  std::list<std::pair<std::string, std::string>> res;
  if (!curr) {
    throw std::invalid_argument("node is null");
    return res;
  }
  for (xmlAttr* attribute = curr->properties; attribute; attribute = attribute->next) {
    xmlChar* prop = xmlGetProp(curr, attribute->name);
    res.emplace_back(std::string((const char*)attribute->name), std::string((const char*)prop));
    xmlFree(prop);
  }
  return res;
}
std::string CFileLoaderIt::GetContent() const {
  if (!curr) {
    throw std::invalid_argument("node is null");
    return "";
  }
  xmlChar* content = xmlNodeListGetString(doc, curr->children, 1);
  std::string res((const char*)content);
  xmlFree(content);
  return res;
}

CFileLoaderIt& CFileLoaderIt::operator=(const CFileLoaderIt& other) {
  if (*this == other) {
    return *this;
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
std::string CFileLoaderIt::GetContent(const std::string& nodeName) const {
  std::string res;
  if (GetName() != nodeName) {
    throw std::invalid_argument("wrong property name name");
    return res;
  }
  res = GetContent();
  return res;
}
bool CFileLoaderIt::Next(size_t cnt) const {
  for (size_t i = 0; i < cnt; ++i) {
    if (!Next()) {
      return false;
    }
  }
  return true;
}
