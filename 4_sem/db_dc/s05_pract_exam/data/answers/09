declare namespace message="http://www.sdmx.org/resources/sdmxml/schemas/v2_1/message";
declare namespace ss="http://www.sdmx.org/resources/sdmxml/schemas/v2_1/data/structurespecific";

for $data in distinct-values(doc('/home/kincaid/Downloads/drive-download-20240914T222313Z-001/comtrade_sdmx.xml')//message:StructureSpecificData/message:DataSet/Series/Obs/@TIME_PERIOD)
return $data
