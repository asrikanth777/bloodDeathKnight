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

    if (node->v.element.tag == GUMBO_TAG_TR) {
        const GumboVector* children = &node->v.element.children;

        if (children->length == 3) {
            string gearTypeHTML, itemNameHTML, itemDropLocHTML;

            GumboNode* slotNode = static_cast<GumboNode*>(children->data[0]);
            if (slotNode->type == GUMBO_NODE_ELEMENT && slotNode->v.element.children.length > 0) {
                GumboNode* textNode = static_cast<GumboNode*>(slotNode->v.element.children.data[0]);
                if (textNode->type == GUMBO_NODE_TEXT) {
                    gearTypeHTML = textNode->v.text.text;
                }
            }

            GumboNode* itemNode = static_cast<GumboNode*>*(children->data[1]);
            if (itemNode->type == GUMBO_NODE_ELEMENT) {
                for (unsigned int i = 0; i < itemNode->v.element.children.length; ++i) {
                    GumboNode* child = static_cast<GumboNode*>(itemNode->v.element.children.data[i]);
                    if (child->type == GUMBO_NODE_ELEMENT && gumbo_get_attribute(&child->v.element.attributes, "class") &&
                    string(gumbo_get_attribute(&child->v.element.attributes, "class")->value) == "q4") {
                        GumboNode* textNode = static_cast<GumboNode*>(child->v.element.children.data[0]);
                        if (textNode->type == GUMBO_NODE_TEXT) {
                            itemNameHTML = textNode->v.text.text;
                        }
                    }
                }
            }
        }


    }

}