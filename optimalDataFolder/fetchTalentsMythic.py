import requests
from bs4 import BeautifulSoup

talentURL = "https://www.wowhead.com/guide/classes/death-knight/blood/talent-builds-pve-tank"

response = requests.get(talentURL)

if response.status_code == 200:
    print("Page fetched successfully")
    htmlContent = response.text
else:
    print(f"Failed to fetch page, status code: {response.status_code}")
    exit()

soupTalentPage = BeautifulSoup(htmlContent, 'html.parser') 
