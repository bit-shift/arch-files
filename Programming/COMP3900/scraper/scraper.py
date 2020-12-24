# import libraries
from urllib.request import urlopen
from bs4 import BeautifulSoup

# specify the url
# quote_page = "https://au.finance.yahoo.com/quote/ANZ.AX?p=ANZ.AX&.tsrc=fin-srch"
quote_page = "https://www.bloomberg.com/quote/AAPL:US"

# query the website and return the html to the variable 'page'
page = urlopen(quote_page)

# parse the html using beautiful soup and store in variable 'soup'
soup = BeautifulSoup(page, 'html.parser')
print(soup)


# Take out the <div> of name and get its value
# name_box = soup.find('h1', attrs={"class": "D(ib) Fz(16px) Lh(18px)"})
# price_box = soup.find('span', attrs={"class": "Trsdu(0.3s) Trsdu(0.3s) Fw(b) Fz(36px) Mb(-4px) D(b)"})

# strip() is used to remove starting and trailing
# name = name_box.text.strip()
# price = price_box.text.strip()

# print(name)
# print(price)

# get the index price
price_box = soup.find('span', attrs={'class': 'price__1853e8a5'})
price = price_box.text
print(price)
