import datetime
import numpy as np
from typing import Union, Annotated
import pandas.io.sql as sqlio
from fastapi import APIRouter, Path, Query

from config.conn import getConn



router = APIRouter()

@router.get('/serverLoad')
def estim_load(
    date: datetime.date, 
    hour: Annotated[Union[int, None], Query(ge=0, le=24)]=None
):
    weekday = date.weekday() + 1

    q_sel = "SELECT COUNT(*) FROM logs"
    q_cond = "WHERE weekday = %s "
    q_agg = "GROUP BY date"
    params = [weekday]
    
    if hour :
        q_cond += " AND TRUNC(fabstime) = %s "
        params.append(hour)
    
    query = [q_sel, q_cond, q_agg];

    '''
    print("#"*12)
    print(" ".join(query))
    print(params)
    print("-"*12)
    '''

    data = sqlio.read_sql_query(" ".join(query), getConn(), params=params)

    sample_data = data.to_numpy().flatten()

    
    num_samples = 1000  

    bootstrap_means = []

    for _ in range(num_samples):
        bootstrap_sample = np.random.choice(
            sample_data, 
            size=len(sample_data), 
            replace=True
        )
    
        bootstrap_means.append(np.mean(bootstrap_sample))

    confidence_interval = np.percentile(bootstrap_means, [2.5, 97.5])
    
    return {"min":confidence_interval[0], "max":confidence_interval[1]}
    #return {"confidence_interval":confidence_interval.tolist()}
