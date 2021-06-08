//
// Created by machavi on 5/21/21.
//
#include "CFileLoader.h"

#include "CFileLoaderIterator.h"
CFileLoader::~CFileLoader() {
  xmlFreeDoc(doc);
  xmlCleanupParser();
}

bool CFileLoader::LoadXmlFile(const std::string filePath) {
  doc = xmlReadFile(filePath.c_str(), nullptr, 0);
  if (doc == nullptr) {
    return false;
  }
  return true;
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
CFileLoaderIt CFileLoader::GetTopNode() {
  xmlNode* node = xmlDocGetRootElement(doc);
  CFileLoaderIt it(node, doc);
  return it;
}
CFileLoaderIt CFileLoader::NewDoc(const std::string rootName) {
  doc = xmlNewDoc((xmlChar*)"1.0");
  xmlNodePtr rootNode = xmlNewNode(NULL, (xmlChar*)rootName.c_str());
  xmlDocSetRootElement(doc, rootNode);
  return GetTopNode();
}
bool CFileLoader::SaveFile(const std::string filePath) {
  if (xmlSaveFormatFileEnc(filePath.c_str(), doc, "utf-8", 1) == -1) return false;
  return true;
}
