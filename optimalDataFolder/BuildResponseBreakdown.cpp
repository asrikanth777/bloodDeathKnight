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
    // node = current HTML node in traversal
    // reference to where item objects are stored
    if (node->type != GUMBO_NODE_ELEMENT) return;
    // ensures only element nodes are processed

    if (node->v.element.tag == GUMBO_TAG_TR) {
        // looks for the tag TR, which has our contents
        const GumboVector* children = &node->v.element.children;

        if (children->length == 3) {
            // for our TR element, there are exactly three categories we are looking for
            // one that has title ("trinket 1"), one that has item name, and one that has drop location
            // if it has 3 categories, we initialize our variables to "contain" the data later
            string gearTypeHTML, itemNameHTML, itemDropLocHTML;

            GumboNode* slotNode = static_cast<GumboNode*>(children->data[0]);
            // this is for slot, like which part of body it goes to ("head")
            if (slotNode->type == GUMBO_NODE_ELEMENT && slotNode->v.element.children.length > 0) {
                // makes sure its an html element and not empty
                GumboNode* textNode = static_cast<GumboNode*>(slotNode->v.element.children.data[0]);
                // then it encapsulates the data inside the first category
                if (textNode->type == GUMBO_NODE_TEXT) {
                    // if it is text, it saves it to gearTypeHTML, our 1st catch variable
                    gearTypeHTML = textNode->v.text.text;
                }
            }

            GumboNode* itemNode = static_cast<GumboNode*>(children->data[1]);
            // proceeds to second category, which should be item name
            // this line has a lot of data, so it takes more steps to parse through it
            if (itemNode->type == GUMBO_NODE_ELEMENT) {
                for (unsigned int i = 0; i < itemNode->v.element.children.length; ++i) {
                    //iterrates through the stuff in the item name section, since it has a lot of data 
                    GumboNode* child = static_cast<GumboNode*>(itemNode->v.element.children.data[i]);
                    if (child->type == GUMBO_NODE_ELEMENT && gumbo_get_attribute(&child->v.element.attributes, "class") &&
                    string(gumbo_get_attribute(&child->v.element.attributes, "class")->value) == "q4") {
                        // if the element has a "class" with the name "q4", we look here
                        GumboNode* textNode = static_cast<GumboNode*>(child->v.element.children.data[0]);
                        // encapsulates this segment of our line and double checks to see if it is a text form
                        if (textNode->type == GUMBO_NODE_TEXT) {
                            itemNameHTML = textNode->v.text.text;
                        }
                    }
                }
            }

            GumboNode* locNode = static_cast<GumboNode*>(children->data[2]);
            // goes through third category, which has our location
            if (locNode->type == GUMBO_NODE_ELEMENT && locNode->v.element.children.length > 0) {
                // same as before, checks to see if it is an element and has data in it
                for (unsigned int i = 0; i < locNode->v.element.children.length; ++i) {
                    // iterrates through elements, since there is more than just text to this part
                    GumboNode* child = static_cast<GumboNode*>(locNode->v.element.children.data[i]);
                    if (child-> type == GUMBO_NODE_ELEMENT &&  child->v.element.tag == GUMBO_TAG_A) {
                        // our loc data is encased around a "a" tag, so we are looking for it
                        GumboNode* textNode = static_cast<GumboNode*>(child->v.element.children.data[0]);
                        // captures data and checks to see if it has text
                        if (textNode->type == GUMBO_NODE_TEXT) {
                            itemDropLocHTML = textNode->v.text.text;
                        }
                    }
                }
            }

            if (!gearTypeHTML.empty() && !itemNameHTML.empty() && !itemDropLocHTML.empty()) {
                // checks to see if any of these are not empty, and will add them to vector set accordingly
                itemList.emplace_back(gearTypeHTML, itemNameHTML, itemDropLocHTML);
            }
        }

    }

    // recursive transversal
    const GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        searchForItems(static_cast<GumboNode*>(children->data[i]) , itemList);
    }

}