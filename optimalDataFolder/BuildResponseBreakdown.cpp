#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <utility>
#include <gumbo.h>
#include <cstring>


using namespace std;

struct item {
    string gearType;
    string itemName;
    string itemDropLoc;

    item() : gearType(""), itemName(""), itemDropLoc("") {}

    item(const string& body, const string& name, const string& loc) : 
        gearType(body), itemName(name), itemDropLoc(loc) {}
};

ostream& operator << (ostream& os, const item& itm) {
    os << "Gear Type: " << itm.gearType << endl
       << "Item Name: " << itm.itemName << endl
       << "Item Drop Location: " << itm.itemDropLoc << endl;
       return os;
}

int itemCounter = 0;

void parseTableElements(GumboNode* node) {
    item itemData;

    string slotText;
    string nameText;
    string locText;

    const GumboVector* trChildren = &node->v.element.children;
    
    vector<GumboNode*> tdBlocks;
    for (int x = 0; x < trChildren->length; ++x) {
        GumboNode* trChild = static_cast<GumboNode*>(trChildren->data[x]);
        if (trChild->type == GUMBO_NODE_ELEMENT && trChild->v.element.tag == GUMBO_TAG_TD) {
            tdBlocks.push_back(trChild);
            continue;
        }

    }

    if (tdBlocks.size() == 3) {
        GumboNode* slotNode = tdBlocks[0];
        if (slotNode->type == GUMBO_NODE_ELEMENT && slotNode->v.element.tag == GUMBO_TAG_TD) {
            const GumboVector* slotChildren = &slotNode->v.element.children;
            for (int slot = 0; slot < slotChildren->length; ++slot) {
                GumboNode* slotChild = static_cast<GumboNode*>(slotChildren->data[slot]);
                if (slotChild->type == GUMBO_NODE_TEXT) {
                    slotText = string(slotChild->v.text.text);
                    cout << slotText << endl;
                    itemCounter++;
                }
            }
            
        }


        GumboNode* nameNode = tdBlocks[1];
        if (nameNode->type == GUMBO_NODE_ELEMENT && nameNode->v.element.tag == GUMBO_TAG_TD) {
            const GumboVector* nameChildren = &nameNode->v.element.children;
            for (int name = 0; name < nameChildren->length; ++name) {
                GumboNode* nameChild = static_cast<GumboNode*>(nameChildren->data[name]);
                if (nameChild->type == GUMBO_NODE_ELEMENT && nameChild->v.element.tag == GUMBO_TAG_SPAN) {
                    
                    const GumboVector* firstSpanChildren = &nameChild->v.element.children;
                    for (int span = 0; span < firstSpanChildren->length; ++span) {
                        GumboNode* spanChild = static_cast<GumboNode*>(firstSpanChildren->data[span]);
                        const GumboAttribute* classAttr = gumbo_get_attribute(&spanChild->v.element.attributes, "class");
                        if (spanChild->type == GUMBO_NODE_ELEMENT && string(classAttr->value) == "q4"){
                            
                            GumboNode* nameTextNode = static_cast<GumboNode*>(spanChild->v.element.children.data[0]);
                            if (nameTextNode->type == GUMBO_NODE_TEXT) {
                                nameText = nameTextNode->v.text.text;
                                cout << nameText << endl;
                            }
                        }

                    }
                }
            }
        }

        GumboNode* locNode = tdBlocks[2];
        if (locNode->type == GUMBO_NODE_ELEMENT && nameNode->v.element.tag == GUMBO_TAG_TD) {
            const GumboVector* locChildren = &locNode->v.element.children;
            for (int loc = 0; loc < locChildren->length; ++loc) {
                GumboNode* locChild = static_cast<GumboNode*>(locChildren->data[loc]);
                if (locChild->type == GUMBO_NODE_TEXT) {
                    locText +=  string(locChild->v.text.text) + " ";
                } else if (locChild->type == GUMBO_NODE_ELEMENT && locChild->v.element.tag == GUMBO_TAG_A) {
                    const GumboVector* aChildren = &locChild->v.element.children;
                    for (int atag = 0; atag < aChildren->length; ++atag) {
                        GumboNode* aChild = static_cast<GumboNode*>(aChildren->data[atag]);
                        if (aChild->type == GUMBO_NODE_TEXT) {
                            locText += string(aChild->v.text.text) + " ";
                        }
                    }
                }
                
                
            }
            cout << locText << endl;
        }

    cout << "------------------------" << endl;

    }

    if (itemCounter % 15 == 0) {
        cout << "==============" << endl;
    }
}

void searchForTableElements(GumboNode* node, vector<item>& itemList) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }

/* the structure for content we want goes as 
<html lang="en">
    <body class = "iv_body">
        <div id = "main" class = "design_new_toc">
            div id="content" class = "background">
                <div id = "center" class = "backgrond">
                    <table>
                        <tbody>
                            <tr>
                                <td> <- stuff we want 
*/

    if (node->v.element.tag == GUMBO_TAG_TABLE) {
        
        const GumboVector* tableChildren = &node->v.element.children;
        for (int a = 0; a < tableChildren->length; ++a) {
            GumboNode* tabChild = static_cast<GumboNode*>(tableChildren->data[a]);
            if (tabChild->type == GUMBO_NODE_ELEMENT && tabChild->v.element.tag == GUMBO_TAG_TBODY) {
                
                const GumboVector* tbodyChildren = &tabChild->v.element.children;
                for (int b = 0; b < tbodyChildren->length; ++b) {
                    GumboNode* tbodyChild = static_cast<GumboNode*>(tbodyChildren->data[b]);
                    if (tbodyChild->type == GUMBO_NODE_ELEMENT && tbodyChild->v.element.tag == GUMBO_TAG_TR) {
                        
                        parseTableElements(tbodyChild);
                    }
                }
            }
        }
    }
    const GumboVector* children = &node->v.element.children;
    for (int i = 0; i < children->length; ++i) {
        searchForTableElements(static_cast<GumboNode*>(children->data[i]), itemList);
    }
}


int main() {
    string buildHTMLstring;
    ifstream buildHTMLfile("optimalBuild.html");
    vector<item> finalItems;

    if (buildHTMLfile.is_open()) {
        buildHTMLstring.assign(istreambuf_iterator<char>(buildHTMLfile),
        istreambuf_iterator<char>());
        buildHTMLfile.close();
    } else {
        cerr << "Error: could not open file optimalbuild.html" << endl;
        return -1;
    }

    

    GumboOutput* output = gumbo_parse(buildHTMLstring.c_str());
    searchForTableElements(output->root, finalItems);
    gumbo_destroy_output(&kGumboDefaultOptions, output);

    ofstream bestBuildsSheet("bestBuilds.txt");
    if (bestBuildsSheet.is_open()) {
        bestBuildsSheet << "updated builds (rough draft needs improvement later)" << endl;
        for (const item& itm: finalItems) {
            bestBuildsSheet << itm << endl;
        }
        bestBuildsSheet.close();
    } else {
        cerr << "Error: could not open file bestbuilds.txt" << endl;
    }

    return 0;



}