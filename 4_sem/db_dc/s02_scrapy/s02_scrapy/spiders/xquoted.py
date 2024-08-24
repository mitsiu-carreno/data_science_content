import scrapy

class QuotedSpider(scrapy.Spider):
    name = "xquoted"
    start_urls = [
        "https://quotes.toscrape.com/page/1/",
        "https://quotes.toscrape.com/page/2/"
    ]

    def parse(self, response):
        for quote in response.xpath("/html/body/div[1]/div[2]/div[1]/div"):
            yield {
                "text": quote.xpath(".//span[1]/text()").get(),
                "author": quote.xpath(".//small[@class='author']/text()").get(),
                    # filtrar por atributo en lugar de posición
                "tags": quote.xpath("(.//div)/a/text()").getall(), 
            }
