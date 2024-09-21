declare namespace message="http://www.sdmx.org/resources/sdmxml/schemas/v2_1/message";
declare namespace ss="http://www.sdmx.org/resources/sdmxml/schemas/v2_1/data/structurespecific";

for $country in distinct-values(doc('/home/kincaid/Downloads/drive-download-20240914T222313Z-001/comtrade_sdmx.xml')//message:StructureSpecificData/message:DataSet/Series[@TRADE_FLOW = "M"]/@COUNTERPART_AREA_1)

let $products := distinct-values(doc('/home/kincaid/Downloads/drive-download-20240914T222313Z-001/comtrade_sdmx.xml')//message:StructureSpecificData/message:DataSet/Series[@COUNTERPART_AREA_1 = $country]/@COMMODITY_1)
return 
<country id="{$country}">
{
  for $product in $products
  return <product id="{$product}"></product>
}
</country>

