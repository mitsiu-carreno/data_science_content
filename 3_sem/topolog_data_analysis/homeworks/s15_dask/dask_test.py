import dask.dataframe as dd

df = dd.read_parquet("./full2.parquet")

print(df.shape)

print(df["date"].unique())
