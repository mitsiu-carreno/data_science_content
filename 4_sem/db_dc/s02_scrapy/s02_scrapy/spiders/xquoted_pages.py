import scrapy

class QuotedSpider(scrapy.Spider):
    name = "xquoted_pages"
    start_urls = [
        "https://quotes.toscrape.com/page/1/"
    ]

    def parse(self, response):
        for quote in response.xpath("/html/body/div[1]/div[2]/div[1]/div"):
            yield {
                "text": quote.xpath(".//span[1]/text()").get(),
                "author": quote.xpath(".//small[@class='author']/text()").get(),
                    # filtrar por atributo en lugar de posición
                "tags": quote.xpath("(.//div)/a/text()").getall(), 
            }
        next = response.xpath("/html/body/div[@class='container']/div[@class='row']/div[@class='col-md-8']/nav/ul/li[@class='next']/a/@href").get()

        if next is not None:
            yield response.follow(next, callback=self.parse)
            # reconoce rutas absolutas y relativas
