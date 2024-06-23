import datetime
import time
import numpy as np
from typing import Union, Annotated
import pandas.io.sql as sqlio
from fastapi import APIRouter, Path, Query, BackgroundTasks

from config.conn import execQuery, insertAlert



router = APIRouter()

@router.get('/serverLoad')
def estim_load(
    req_date: datetime.date, 
    req_hour: Annotated[Union[int, None], Query(ge=0, le=24)]=None
):
    weekday = req_date.weekday() + 1

    q_sel = "SELECT COUNT(*) FROM logs"
    q_cond = "WHERE weekday = %s "
    q_agg = "GROUP BY date"
    params = [weekday]
    
    if req_hour :
        q_cond += " AND TRUNC(fabstime) = %s "
        params.append(req_hour)
    
    query = [q_sel, q_cond, q_agg];

    '''
    print("#"*12)
    print(" ".join(query))
    print(params)
    print("-"*12)
    '''

    #data = sqlio.read_sql_query(" ".join(query), getConn(), params=params)

    #sample_data = data.to_numpy().flatten()
    
    data = execQuery(" ".join(query), params)

    sample_data = np.array(data).flatten()
    
    num_samples = 1000  

    bootstrap_means = []

    for _ in range(num_samples):
        bootstrap_sample = np.random.choice(
            sample_data, 
            size=len(sample_data), 
            replace=True
        )
    
        bootstrap_means.append(np.mean(bootstrap_sample))

    confidence_interval = np.percentile(bootstrap_means, [25, 75])
    
    return {"min":confidence_interval[0], "max":confidence_interval[1]}
    #return {"confidence_interval":confidence_interval.tolist()}


def monitor():
    while True :
        currentDate = datetime.date.today()
        currentFabstime = datetime.datetime.now().time().hour
        range = estim_load(currentDate, currentFabstime); 
       
        #print(currentDate)
        #print(currentFabstime) 
        #print("-"*30)

        current = execQuery(
            "SELECT COUNT(*) FROM logs WHERE date = %s AND TRUNC(fabstime) = %s", 
            [currentDate, currentFabstime]
        )

        current = current[0][0]
       
        #print(current)
        #print(range["max"]) 
        if current > int(range["max"]) :
            insertAlert(
                {
                    "date":currentDate, 
                    "time":datetime.datetime.now().strftime('%H:%M:%S'),
                    "expected_traffic": int(range["max"]),
                    "found_traffic": current
                }
            )
        time.sleep(60)

@router.get('/startMonitor')
async def start_monitor(background_tasks: BackgroundTasks):
    background_tasks.add_task(monitor)
    return {"started_at": datetime.datetime.now().strftime('%H:%M:%S') }
