declare namespace message="http://www.sdmx.org/resources/sdmxml/schemas/v2_1/message";
declare namespace ss="http://www.sdmx.org/resources/sdmxml/schemas/v2_1/data/structurespecific";

for $data in doc('/home/kincaid/Downloads/drive-download-20240914T222313Z-001/comtrade_sdmx.xml')//message:StructureSpecificData/message:DataSet/Series[@TRADE_FLOW = "X" and @COMMODITY_1 = "HS17_03"]/Obs[@OBS_VALUE != "_X"]
return $data
