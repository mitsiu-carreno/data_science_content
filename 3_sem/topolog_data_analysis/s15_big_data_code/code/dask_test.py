import dask.dataframe as dd

df = dd.read_csv("benchmarking_data.csv")

print(df) # native dask dataframe

df = df.compute()

print(df)