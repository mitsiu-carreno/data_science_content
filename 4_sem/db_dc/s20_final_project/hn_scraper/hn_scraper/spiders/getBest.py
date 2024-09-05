# scrapy crawl getBest -o data/best.xml
import scrapy


class GetbestSpider(scrapy.Spider):
    name = "getBest"
    allowed_domains = ["hnrss.org"]
    start_urls = ["https://hnrss.org/best"]

    def parse(self, response):
        for entry in response.xpath("/rss/channel/item"):
            comments_id = entry.xpath(".//comments/text()").re(r".+item\?id=([\d]+)")[0]
            getComments = scrapy.Request(
                f"https://hnrss.org/replies?id={comments_id}",
                callback=self.parseComment, 
                cb_kwargs=dict(title=entry.xpath(".//title/text()").get())
            )
            yield getComments

    def parseComment(self, response, title):
        comments = []
        for comment in response.xpath("/rss/channel/item"):
            comments.append({
                "title": comment.xpath(".//title/text()").get()
            })
        yield {
            "title": title,
            "comments": comments
        }
