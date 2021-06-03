//
// Created by machavi on 5/21/21.
//
#include "CFileLoader.h"

#include "CFileLoaderIterator.h"
CFileLoader::~CFileLoader() {
  xmlFreeDoc(doc);
  xmlCleanupParser();
}

bool CFileLoader::loadXmlFile(const std::string filePath) {
  doc = xmlReadFile(filePath.c_str(), nullptr, 0);
  if (doc == nullptr) {
    return false;
  }
  return true;
}

void CFileLoader::printXML(xmlNode* a_node) {
  xmlNode* cur_node = nullptr;
  xmlChar* key = nullptr;
  for (cur_node = a_node; cur_node; cur_node = cur_node->next) {
    if (cur_node->type == XML_ELEMENT_NODE) {
      printf("node type: Element, name: %s", cur_node->name);
      if (xmlStrcmp(cur_node->name, (const xmlChar*)"X1") == 0) {
        key = xmlNodeListGetString(doc, cur_node->children, 1);
        printf(" value: %s", key);
        xmlFree(key);
      }
      printf("\n");
    }
    printXML(cur_node->children);
  }
}

xmlNode* CFileLoader::getNode(const char* name, xmlNode* node) {
  xmlNode* currNode = nullptr;
  for (currNode = node; currNode; currNode = currNode->next) {
    if (currNode->type == XML_ELEMENT_NODE) {
      if (xmlStrcmp(currNode->name, (const xmlChar*)name) == 0) {
        return currNode;  // node found
      }
    }
    xmlNode* res = getNode(name, currNode->children);
    if (res) {
      return res;
    }
  }
  return nullptr;  // not found
}

CFileLoaderIt CFileLoader::GetNode(const std::string& name) {
  xmlNode* res = getNode(name.c_str(), xmlDocGetRootElement(doc));
  CFileLoaderIt resIt(res, doc);
  return resIt;
}