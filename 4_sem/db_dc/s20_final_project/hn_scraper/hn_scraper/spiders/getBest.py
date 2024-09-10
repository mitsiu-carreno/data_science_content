# scrapy crawl getBest -o data/best.xml
import scrapy


class GetbestSpider(scrapy.Spider):
    name = "getBest"
    allowed_domains = ["hnrss.org"]
    start_urls = ["https://hnrss.org/best"]

    def parse(self, response):
        for entry in response.xpath("/rss/channel/item"):
            entry_id = entry.xpath(".//guid/text()").re(r".+item\?id=([\d]+)")[0]
            getComments = scrapy.Request(
                f"https://hnrss.org/replies?id={entry_id}",
                callback=self.parseComment, 
                cb_kwargs=dict(
                    id=entry_id,
                    title=entry.xpath(".//title/text()").get(),
                    description=entry.xpath(".//description/text()").get(),
                    pubDate=entry.xpath(".//pubDate/text()").get(),
                    link=entry.xpath(".//link/text()").get(),
                    dc_creator=entry.xpath(".//*[name()='dc:creator']/text()").get(),
                    guid=entry.xpath(".//guid/text()").get()
                )
            )
            yield getComments

    def parseComment(self, response, id, title, description, pubDate, link, dc_creator, guid):
        comments = []
        for comment in response.xpath("/rss/channel/item"):
            comment_id = comment.xpath(".//guid/text()").re(r".+item\?id=([\d]+)")[0]
            comments.append({
                "id": comment_id,
                "title": comment.xpath(".//title/text()").get(),
                "description": comment.xpath(".//description/text()").get(),
                "pubDate": comment.xpath(".//pubDate/text()").get(),
                "link": comment.xpath(".//link/text()").get(),
                "dc_creator": comment.xpath(".//*[name()='dc:creator']/text()").get(),
                "guid": comment.xpath(".//guid/text()").get()
            })
        yield {
            "id":id,
            "title": title,
            "description": description,
            "pubDate": pubDate,
            "link": link,
            "dc_creator": dc_creator,
            "comments": comments,
            "guid": guid
        }
