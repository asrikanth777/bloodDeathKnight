#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <gumbo.h>



using namespace std;

struct item {
    string gearType;
    string itemName;
    string itemDropLoc;
};

void searchForItems(GumboNode* node, vector<item>& itemList) {
    // node = current HTML node in traversal
    // reference to where item objects are stored
    if (node->type != GUMBO_NODE_ELEMENT) return;
    // ensures only element nodes are processed

    GumboAttribute* classAttr;
    if ((classAttr = gumbo_get_attribute(&node->v.element.attributes, "class"))) {
        // gets class attribute of current element
        //gumbo_get... searches for specific attribute in node's attributes list
        string className = classAttr->value;

        if (className == "item-category") {
            string gearType;
            string itemName;
            string itemDropLoc;

            if (node->v.element.children.length > 0) {
                GumboNode* child = static_cast<GumboNode*>(node->v.element.children.data[0]);
                if (child->type == GUMBO_NODE_TEXT) {
                    category = child->v.text.text;
                }
            }

            if (!gearType.empty() && !itemName.empty() && !itemDropLoc.empty()) {
                itemList.emplace_back(gearType, itemName, itemDropLoc);
            } 

        }

    }


}