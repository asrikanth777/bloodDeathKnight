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

void parseTableElements(GumboNode* node) {
    item itemData;
    const GumboVector* trChildren = &node->v.element.children;
    cout << trChildren->length << endl;
    vector<GumboNode*> tdBlocks;
    for (int x = 0; x < trChildren->length; ++x) {
        GumboNode* trChild = static_cast<GumboNode*>(trChildren->data[x]);
        if (trChild->type == GUMBO_NODE_ELEMENT && trChild->v.element.tag == GUMBO_TAG_TD) {
            tdBlocks.push_back(trChild);
            cout << tdBlocks.size() << endl;
            continue;
        }

    }

    if (tdBlocks.size() == 3) {
        GumboNode* slotNode = tdBlocks[0];
        if (slotNode->type == GUMBO_NODE_ELEMENT && slotNode->v.element.tag == GUMBO_TAG_TD) {
            const GumboVector* slotChildren = &slotNode->v.element.children;
            
        }


        GumboNode* nameNode = tdBlocks[1];

        GumboNode* locNode = tdBlocks[2];
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
        cout << "found table" << endl;
        const GumboVector* tableChildren = &node->v.element.children;
        for (int a = 0; a < tableChildren->length; ++a) {
            GumboNode* tabChild = static_cast<GumboNode*>(tableChildren->data[a]);
            if (tabChild->type == GUMBO_NODE_ELEMENT && tabChild->v.element.tag == GUMBO_TAG_TBODY) {
                cout << "found tbody" << endl;
                const GumboVector* tbodyChildren = &tabChild->v.element.children;
                for (int b = 0; b < tbodyChildren->length; ++b) {
                    GumboNode* tbodyChild = static_cast<GumboNode*>(tbodyChildren->data[b]);
                    if (tbodyChild->type == GUMBO_NODE_ELEMENT && tbodyChild->v.element.tag == GUMBO_TAG_TR) {
                        cout << "found tr" << endl;
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