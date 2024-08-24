import scrapy

class QuotedSpider(scrapy.Spider):
    name = "worldometer"
    start_urls = [
        "https://www.worldometers.info/world-population/population-by-country/"
    ]

    def parse(self, response):
        for country in response.xpath("/html/body/div[@class='container']/div[@class='row']/div[@class='col-md-12']/div[@class='content-inner']/div[@class='table-responsive']/table/tbody/tr"):
            yield {
                "id": country.xpath(".//td[1]/text()").get(),
                "country": country.xpath(".//td[2]/a/text()").get(),
                "population-2024": country.xpath(".//td[3]/text()").get(),
                "yearly-change": country.xpath(".//td[4]/text()").get(),
                "net-change": country.xpath(".//td[5]/text()").get(),
                "density": country.xpath(".//td[6]/text()").get(),
                "land-area": country.xpath(".//td[7]/text()").get(),
                "migrants": country.xpath(".//td[8]/text()").get(),
                "fert-rate": country.xpath(".//td[9]/text()").get(),
                "med-age": country.xpath(".//td[10]/text()").get(),
                "urban-pop": country.xpath(".//td[11]/text()").get(),
                "world-share": country.xpath(".//td[12]/text()").get(),
            }
        """
        next = response.xpath("/html/body/div[@class='container']/div[@class='row']/div[@class='col-md-8']/nav/ul/li[@class='next']/a/@href").get()

        if next is not None:
            yield response.follow(next, callback=self.parse)
            # reconoce rutas absolutas y relativas
        """
