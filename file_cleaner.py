import pandas as pd

input_file = "anime-dataset-2023.csv"
output_file = "cleaned-anime-dataset.csv"

df = pd.read_csv(input_file)

# Inspect the first few rows to identify the column with Japanese characters
print(df.head())

# Drop the column with Japanese characters (replace 'Other name' with the actual column name)
if 'Other name' in df.columns:
    df = df.drop(columns=['Other name'])

df.to_csv(output_file, index=False)

print(f"Cleaned dataset saved to {output_file}")