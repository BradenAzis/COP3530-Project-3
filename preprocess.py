import pandas as pd

input_file = "cleaned-anime-dataset.csv"
output_file = "formatted-anime-dataset.csv"

df = pd.read_csv(input_file)

# Keep only the relevant columns
columns_to_keep = ["Name", "Genres", "Type", "Episodes", "Aired", "Members", "Score"]
df = df[columns_to_keep]

# Ensure variables are in the correct format (numeric), otherwise default to 0
df["Episodes"] = pd.to_numeric(df["Episodes"], errors="coerce").fillna(0).astype(int)
df["Members"] = pd.to_numeric(df["Members"], errors="coerce").fillna(0).astype(int)
df["Score"] = pd.to_numeric(df["Score"], errors="coerce").fillna(0.0).astype(float)

df.to_csv(output_file, index=False)

print(f"Formatted dataset saved to {output_file}")
