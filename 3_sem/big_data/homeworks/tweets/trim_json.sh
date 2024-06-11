year=2021
input_json_path="./4_json/"
output_json_path="./test/din_test.json"


grep -PrnH "country_code\":\"MX\"" ${input_json_path} | grep -Po '(^.+?[^:]+:[^:]+|\"created_at\":\"[^\"]*'${year}'.*?(?:(?<!\\)")|\"place_type\":\".*?(?:(?<!\\)")|\"full_name\":\".*?(?:(?<!\\)"))' | awk -F ':' 'END {print "}"} { if ($1 ~ /^"/ ) {printf(", %s:%s", $1, substr($0, index($0,$2)))} else {  if(first == "not"){ printf("}\n") } printf("{\"file\":\"%s\", \"line\":\"%s\"", $1, $2 )} first = "not"; }' > ${output_json_path}
