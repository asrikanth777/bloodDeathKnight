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

    item() : gearType("slot"), itemName("item"), itemDropLoc("source/note") {}

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

item parseTableElements(GumboNode* node) {


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

        item itemData;
        

        string slotText;
        string nameText;
        string locText;

        GumboNode* slotNode = tdBlocks[0];
        if (slotNode->type == GUMBO_NODE_ELEMENT && slotNode->v.element.tag == GUMBO_TAG_TD) {
            const GumboVector* slotChildren = &slotNode->v.element.children;
            for (int slot = 0; slot < slotChildren->length; ++slot) {
                GumboNode* slotChild = static_cast<GumboNode*>(slotChildren->data[slot]);
                if (slotChild->type == GUMBO_NODE_TEXT) {
                    slotText = string(slotChild->v.text.text);

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
        }




        item completeItem = item(slotText, nameText, locText);
        return completeItem;


    }
    
    return item();

    
}
bool startsWith(string& text, string& prefix) {
    if (text.size() < prefix.size()) {
        return false;
    }
    return equal(prefix.begin(), prefix.end(), text.begin(), 
        [](char a, char b) {return tolower(a) == tolower(b);});
}


void searchForBuildDescriptions(GumboNode* node, vector<string>& buildDes) {
    string prefix = "This List";
    string emptyagain = "";
    const GumboVector* pChildren = &node->v.element.children;
    for (int p = 0; p < pChildren->length; ++p) {
        GumboNode* pChild = static_cast<GumboNode*>(pChildren->data[p]);
        if (pChild->type == GUMBO_NODE_TEXT) {
            string text(pChild->v.text.text);
            if (startsWith(text, prefix)) {
                cout << "found it!" << endl;
                buildDes.push_back(text);
            } 
        }
    }
    
}


void searchForTableElements(GumboNode* node, vector<item>& itemList, vector<string>& buildDes) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }


    if (node->v.element.tag == GUMBO_TAG_P) {
        searchForBuildDescriptions(node, buildDes);
        
    }

    if (node->v.element.tag == GUMBO_TAG_TABLE) {
        
        const GumboVector* tableChildren = &node->v.element.children;
        for (int a = 0; a < tableChildren->length; ++a) {
            GumboNode* tabChild = static_cast<GumboNode*>(tableChildren->data[a]);
            if (tabChild->type == GUMBO_NODE_ELEMENT && tabChild->v.element.tag == GUMBO_TAG_TBODY) {
                
                const GumboVector* tbodyChildren = &tabChild->v.element.children;
                for (int b = 0; b < tbodyChildren->length; ++b) {
                    GumboNode* tbodyChild = static_cast<GumboNode*>(tbodyChildren->data[b]);
                    if (tbodyChild->type == GUMBO_NODE_ELEMENT && tbodyChild->v.element.tag == GUMBO_TAG_TR) {
                        
                        item compItem = parseTableElements(tbodyChild);
                        itemList.push_back(compItem);
                    }
                }
            }
        }
    }

    const GumboVector* children = &node->v.element.children;
    for (int i = 0; i < children->length; ++i) {
        searchForTableElements(static_cast<GumboNode*>(children->data[i]), itemList, buildDes);
    }
}


int main() {
    string buildHTMLstring;
    ifstream buildHTMLfile("optimalBuild.html");
    vector<item> finalItems;
    vector<string> buildDesc;

    if (buildHTMLfile.is_open()) {
        buildHTMLstring.assign(istreambuf_iterator<char>(buildHTMLfile),
        istreambuf_iterator<char>());
        buildHTMLfile.close();
    } else {
        cerr << "Error: could not open file optimalbuild.html" << endl;
        return -1;
    }

    

    GumboOutput* output = gumbo_parse(buildHTMLstring.c_str());
    searchForTableElements(output->root, finalItems, buildDesc);
    
    gumbo_destroy_output(&kGumboDefaultOptions, output);

    ofstream bestBuildsSheet("bestBuilds.txt");
    cout << "in main file" << endl;
    cout << buildDesc.size() << endl;
    int itemTextCount = 0;
    if (bestBuildsSheet.is_open()) {
        bestBuildsSheet << "updated builds (rough draft needs improvement later)" << endl;
        bestBuildsSheet << "+++++++++" << endl;
        bestBuildsSheet << buildDesc[0] << endl;
        bestBuildsSheet << "+++++++++" << endl;
        for (const item& itm: finalItems) {
            bestBuildsSheet << "---------" << endl;
            bestBuildsSheet << itm << endl;
            bestBuildsSheet << "---------" << endl;
            itemTextCount++;
            if (itemTextCount % 16 == 0) {
                bestBuildsSheet << "===========" << endl;
                bestBuildsSheet << buildDesc[itemTextCount/16] << endl;
            }
        }
        bestBuildsSheet.close();
    } else {
        cerr << "Error: could not open file bestbuilds.txt" << endl;
    }

    return 0;



}