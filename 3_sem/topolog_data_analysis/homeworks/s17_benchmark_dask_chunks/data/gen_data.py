import pandas as pd

data_URL = "https://raw.githubusercontent.com/keitazoumana/Experimentation-Data/main/diabetes.csv"

original_data = pd.read_csv(data_URL)

# Duplicate each row 100000 times
benchmarking_df = original_data.loc[original_data.index.repeat(100000*4)]

rows_10k_benchmarking_df = benchmarking_df[:10000]

rows_100k_benchmarking_df = benchmarking_df[:100000]

rows_1M_benchmarking_df = benchmarking_df[:1000000]

rows_50M_benchmarking_df = benchmarking_df[:50000000]

# Save the result as a CSV file for future use.
file_name = "full_benchmarking_data.csv"
benchmarking_df.to_csv(file_name, index=False)

file_name = "10k_benchmarking_data.csv"
rows_10k_benchmarking_df.to_csv(file_name, index=False)

file_name = "100k_benchmarking_data.csv"
rows_100k_benchmarking_df.to_csv(file_name, index=False)

file_name = "1M_benchmarking_data.csv"
rows_1M_benchmarking_df.to_csv(file_name, index=False)

file_name = "50M_benchmarking_data.csv"
rows_50M_benchmarking_df.to_csv(file_name, index=False)
