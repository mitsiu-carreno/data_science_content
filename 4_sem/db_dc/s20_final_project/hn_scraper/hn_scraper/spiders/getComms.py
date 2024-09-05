import scrapy


class GetcommsSpider(scrapy.Spider):
    name = "getComms"
    allowed_domains = ["hnrss.org"]
    start_urls = ["https://hnrss.org/replies"]

    def parse(self, response):
        pass
