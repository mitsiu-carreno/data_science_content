from fastapi import FastAPI
from pydantic import BaseModel

from credit import * 
from house import * 
import json 

app = FastAPI()

class CreditHouse(BaseModel):
    salary: float
    credit_status: str

@app.get("/getCriteria")
async def data():
    criteria = get_criteria()
    print(criteria)
    return criteria

@app.post("/creditHouse")
async def credit_house(credit_house: CreditHouse):
    review = house_review(credit_house)
    print(review)
    return review

