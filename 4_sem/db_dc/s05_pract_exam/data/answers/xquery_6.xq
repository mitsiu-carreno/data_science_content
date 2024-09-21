declare namespace message="http://www.sdmx.org/resources/sdmxml/schemas/v2_1/message";
declare namespace ss="http://www.sdmx.org/resources/sdmxml/schemas/v2_1/data/structurespecific";

for $data in doc('/home/kincaid/Downloads/drive-download-20240914T222313Z-001/comtrade_sdmx.xml')//message:StructureSpecificData/message:DataSet/Series[@TRADE_FLOW = "M" and @TRANSPORT_MODE_BORDER = "T_1"]/@COMMODITY_1
return $data

