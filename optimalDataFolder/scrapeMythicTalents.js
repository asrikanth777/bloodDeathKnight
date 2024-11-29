const { chromium } = require('playwright');
// uses Chromium to handle our web access request, since its a headless browser

(async () => {
    const browser = await chromium.launch(); //"browser opens"
    const page = await browser.newPage(); //it creates a tab in that browser

    // Go to the Wowhead page for Blood Death Knight talent builds (PvE Tank)
    await page.goto('https://www.wowhead.com/guide/classes/death-knight/blood/talent-builds-pve-tank');
    // the said page goes to the website above

    /* Now this part I have to work on, which is 
    - waiting on what element of the page to load
    - finding and inspecting the talent tree
    - storing the data in tree
    - returning it
    */



  // Close the browser
  await browser.close();
})();
