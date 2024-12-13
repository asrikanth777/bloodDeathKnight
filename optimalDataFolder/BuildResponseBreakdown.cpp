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

    item(const string& body, const string& name, const string& loc) : 
        gearType(body), itemName(name), itemDropLoc(loc) {}
};

ostream& operator << (ostream& os, const item& itm) {
    os << "Gear Type: " << itm.gearType << endl
       << "Item Name: " << itm.itemName << endl
       << "Item Drop Location: " << itm.itemDropLoc << endl;
       return os;
}

/* sample html search data

<p>This list contains the Best in Slot Gear from any source in Season 1 of The War
Within. It is there as a reference to what is currently the highest performing gear
available to players.</p>

<table>
<tr>
<th>Slot</th>
<th>Item</th>
<th>Source/Note</th>
</tr>
<tr>
<td>Weapon</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_axe_2h_nerubianraid_d_01.jpg" alt="Anub'arash's Colossal Mandible Icon" /> <span data-wowhead="item=212407&amp;bonus=10389:1540" class="q4">Anub'arash's Colossal Mandible</span></span> (639)</td>
<td><a href="//www.icy-veins.com/wow/the-silken-court-raid-guide-in-nerub-ar-palace">Silken Court</a> in Mythic <a href="//www.icy-veins.com/wow/nerubar-palace-raid-guide">Nerub-ar Palace</a></td>
</tr>
<tr>
<td>Helm</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_helm_plate_earthendungeon_c_01.jpg" alt="Soaring Behemoth's Greathelm Icon" /> <span data-wowhead="item=221146&amp;bonus=657:10358:5982:7981" class="q4">Soaring Behemoth's Greathelm</span></span> (639)</td>
<td><a href="//www.icy-veins.com/wow/the-dawnbreaker-dungeon-guide">The Dawnbreaker</a></td>
</tr>
<tr>
<td>Neck</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_11_0_nerubian_necklace_02_color5.jpg" alt="Silken Advisor's Favor Icon" /> <span data-wowhead="item=225575&amp;bonus=10389:1540" class="q4">Silken Advisor's Favor</span></span> (639)</td>
<td><a href="//www.icy-veins.com/wow/the-silken-court-raid-guide-in-nerub-ar-palace">Silken Court</a> in Mythic <a href="//www.icy-veins.com/wow/nerubar-palace-raid-guide">Nerub-ar Palace</a></td>
</tr>
<tr>
<td>Shoulder</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_shoulder_raiddeathknightnerubian_d_01.jpg" alt="Exhumed Centurion's Spikes Icon" /> <span data-wowhead="item=212000" class="q4">Exhumed Centurion's Spikes</span></span> (639)</td>
<td>Tier Set: Catalyst / Vault / Raid</td>
</tr>
<tr>
<td>Cloak</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_leather_raiddemonhunternerubian_d_01_cape.jpg" alt="Wings of Shattered Sorrow Icon" /> <span data-wowhead="item=225574&amp;bonus=10389:1540" class="q4">Wings of Shattered Sorrow</span></span> (639)</td>
<td><a href="//www.icy-veins.com/wow/rasha-nan-raid-guide-in-nerub-ar-palace">Rasha'nan</a> in Mythic <a href="//www.icy-veins.com/wow/nerubar-palace-raid-guide">Nerub-ar Palace</a></td>
</tr>
<tr>
<td>Chest</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_chest_raiddeathknightnerubian_d_01.jpg" alt="Exhumed Centurion's Breastplate Icon" /> <span data-wowhead="item=212005" class="q4">Exhumed Centurion's Breastplate</span></span> (639)</td>
<td>Tier Set: Catalyst / Vault / Raid</td>
</tr>
<tr>
<td>Bracers</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_plate_outdoorarathor_d_01_bracer.jpg" alt="Everforged Vambraces Icon" /> <span data-wowhead="item=222435&amp;bonus=10222:1515" class="q4">Everforged Vambraces</span></span> (636)</td>
<td>Crafted</td>
</tr>
<tr>
<td>Gloves</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_glove_raiddeathknightnerubian_d_01.jpg" alt="Exhumed Centurion's Gauntlets Icon" /> <span data-wowhead="item=212003" class="q4">Exhumed Centurion's Gauntlets</span></span> (639)</td>
<td>Tier Set: Catalyst / Vault / Raid</td>
</tr>
<tr>
<td>Belt</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_plate_outdoorarathor_d_01_belt.jpg" alt="Everforged Greatbelt Icon" /> <span data-wowhead="item=222431&amp;bonus=10222:1515" class="q4">Everforged Greatbelt</span></span> (636)</td>
<td>Crafted</td>
</tr>
<tr>
<td>Legs</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_pants_raiddeathknightnerubian_d_01.jpg" alt="Exhumed Centurion's Chausses Icon" /> <span data-wowhead="item=212001" class="q4">Exhumed Centurion's Chausses</span></span> (639)</td>
<td>Tier Set: Catalyst / Vault / Raid</td>
</tr>
<tr>
<td>Boots</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_plate_raidpaladinnerubian_d_01_boot.jpg" alt="Shattershell Greaves Icon" /> <span data-wowhead="item=212443&amp;bonus=10389:1540" class="q4">Shattershell Greaves</span></span> (639)</td>
<td><a href="//www.icy-veins.com/wow/the-silken-court-raid-guide-in-nerub-ar-palace">Silken Court</a> in Mythic <a href="//www.icy-veins.com/wow/nerubar-palace-raid-guide">Nerub-ar Palace</a></td>
</tr>
<tr>
<td>Ring #1</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_nerubian_ring_01_color3.jpg" alt="Seal of the Poisoned Pact Icon" /> <span data-wowhead="item=225578&amp;bonus=10389:1540" class="q4">Seal of the Poisoned Pact</span></span> (639)</td>
<td><a href="//www.icy-veins.com/wow/queen-ansurek-raid-guide-in-nerub-ar-palace">Queen Ansurek</a> in Mythic <a href="//www.icy-veins.com/wow/nerubar-palace-raid-guide">Nerub-ar Palace</a></td>
</tr>
<tr>
<td>Ring #2</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_ring_revendreth_01_brown.jpg" alt="Ritual Commander's Ring Icon" /> <span data-wowhead="item=178781&amp;bonus=657:10358:5982:7981" class="q4">Ritual Commander's Ring</span></span> (639)</td>
<td><a href="//www.icy-veins.com/wow/the-necrotic-wake-dungeon-guide">The Necrotic Wake</a></td>
</tr>
<tr>
<td>Trinket #1</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_raid_mercurialegg_red.jpg" alt="Ara-Kara Sacbrood Icon" /> <span data-wowhead="item=219314&amp;bonus=657:10358:5982:7981" class="q4">Ara-Kara Sacbrood</span></span> (639)</td>
<td><a href="//www.icy-veins.com/wow/ara-kara-city-of-echoes-dungeon-guide">Ara-Kara, City of Echoes</a></td>
</tr>
<tr>
<td>Trinket #2</td>
<td><span class="spell_icon_span"><img class="spell_icon" src="//static.icy-veins.com/images/wow/large_icons/inv_archaeology_70_tauren_moosebonefishhook.jpg" alt="Spare Meat Hook Icon" /> <span data-wowhead="item=178751&amp;bonus=657:10358:5982:7981" class="q4">Spare Meat Hook</span></span> (639)</td>
<td><a href="//www.icy-veins.com/wow/the-necrotic-wake-dungeon-guide">The Necrotic Wake</a></td>
</tr>
</table>

</div>
<div class="image_block_content" id="area_3">
*/



void searchForItems(GumboNode* node, vector<item>& itemList) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }
    

    if (node->v.element.tag == GUMBO_TAG_TABLE) {
        cout << "found table!" << endl;
        const GumboVector* table_children = &node->v.element.children;

        for (int i = 0; i < table_children->length; ++i) {
            GumboNode* child = static_cast<GumboNode*>(table_children->data[i]);

            // write in space for tbody
            if(child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_TR) {
                cout << "found tr" << endl;
                vector<string> row_data;
                const GumboVector* row_children = &child->v.element.children;
                for(int j = 0; j < row_children->length; ++j) {
                    GumboNode* cell = static_cast<GumboNode*>(row_children->data[j]);
                    if (cell->type == GUMBO_NODE_ELEMENT &&
                    cell -> v.element.tag == GUMBO_TAG_TD) {
                        const GumboVector* cell_children = &cell->v.element.children;
                        for (int k = 0; k < cell_children->length; ++k) {
                            GumboNode* text_node = static_cast<GumboNode*>(cell_children->data[k]);
                            if(text_node->type == GUMBO_NODE_TEXT) {
                                row_data.push_back(std::string(text_node->v.text.text));
                            }
                        }
                    }
                }

                if (row_data.size() == 3) {
                    itemList.emplace_back(row_data[0], row_data[1], row_data[2]);
                }
            }
        }
    }

    const GumboVector* children = &node->v.element.children;
    for (int i = 0; i < children->length; ++i) {
        searchForItems(static_cast<GumboNode*>(children->data[i]), itemList);
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
    searchForItems(output->root, finalItems);
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