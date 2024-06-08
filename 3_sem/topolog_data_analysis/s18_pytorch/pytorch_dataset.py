import torch
from torch.utils.data import Dataset, DataLoader
import csv

class CSVDataset(Dataset):
    def __init__(self, file_path, transform=None):
        self.file_path = file_path
        self.transform = transform
        self.data = []
        with open(file_path, 'r') as file:
            reader = csv.reader(file)
            self.header = next(reader)  # Skip the header
            for line in reader:
                self.data.append(line)
                
    def __len__(self):
        return len(self.data)
    
    def __getitem__(self, idx):
        row = self.data[idx]
        if self.transform:
            row = self.transform(row)
        return torch.tensor(row, dtype=torch.float32)    

def transform(row):
    # Example transformation: Convert all elements to float
    return [float(element) for element in row]


file_path = 'benchmarking_data.csv'
dataset = CSVDataset(file_path, transform=transform)
dataloader = DataLoader(dataset, batch_size=32, shuffle=True)

for batch in dataloader:
    # Process your batch here
    print(batch)