
import json
import os
import pandas as pd
import sys

print(f"Name of the script      : {sys.argv[0]=}")

print(f"Output parquet path: {sys.argv[1:]=}")


USAGE = f"Usage: python {sys.argv[0]} [path_to_json]"

args = sys.argv[1:]
if not args:
    raise SystemExit(USAGE)

input_file = sys.argv[1];
output_file = input_file.replace(".json", ".parquet")

err_logger_1 = []
err_logger_2 = []
data = []


with open(input_file) as f:
    for line in f:
        try:
            data.append(json.loads(fr'''{line}'''))
        except Exception as e:
            err_template = "An exception of type {0} occurred. Arguments:\n{1!r}"
            err_message = err_template.format(type(e).__name__, e.args)
            err_logger_1.append({"operation":"Load json", "detail":input_file, "err":err_message})


try:
    print("gen_file")
    # Json to dataframe
    df = pd.json_normalize(data)

    # Guardar dataframe completo
    df.to_parquet(output_file, engine='auto', compression='snappy')


    data = []
except Exception as e:
    err_template = "An exception of type {0} occurred. Arguments:\n{1!r}"
    err_message = err_template.format(type(e).__name__, e.args)
    err_logger_2.append({"operation":"Dataframe & parquet", "detail":output_file, "err":err_message})

print(err_logger_1)
print("-"*12)
print(err_logger_2)


print("-"*5, "Validating", "-"*5)

import pandas as pd
import pyarrow.parquet as pq

df = pd.read_parquet(output_file)
print(df.shape)

print(df.head())

print(df["place_type"].unique())

