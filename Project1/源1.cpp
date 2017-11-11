#include"tinyxml2.h"
int main
{
tinyxml2::XMLDocument doc; int res = doc.LoadFile("blueSheet"); if (!res) MessageBox(NULL, "Error Load Xml", "Error", MB_OK);
XMLElement* root = doc.RootElement();
if (root == NULL) MessageBox(NULL, "Error Get root", "Error", MB_OK);
XMLElement* node = root->FirstChildElement();
while (node->Attribute("name") != "0") node = node->NextSiblingElement(); }