declare namespace message="http://www.sdmx.org/resources/sdmxml/schemas/v2_1/message";
declare namespace ss="http://www.sdmx.org/resources/sdmxml/schemas/v2_1/data/structurespecific";

let $data := doc('/home/kincaid/Downloads/drive-download-20240914T222313Z-001/comtrade_sdmx.xml')//message:StructureSpecificData/message:DataSet/Series[@TRADE_FLOW = "M" and  @TRANSPORT_MODE_BORDER = "T_2" and @COUNTERPART_AREA_1 = "US"]
return 
<country id="US">
{
  for $product in $data
  return 
    <product id="{$product/@COMMODITY_1}">{$product/data(Obs/@OBS_VALUE)}</product>
}
</country>
