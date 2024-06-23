from fastapi import APIRouter

from config.conn import execQuery

router = APIRouter()

@router.get('/getAlerts')
def get_alerts():
    alerts = execQuery(
        "SELECT * FROM alerts ORDER BY date, time DESC LIMIT 5", []
    )

    res_alerts = [];    

    for row in alerts: 
        al = {
            "date": row[0],
            "time": row[1],
            "expected_traffic": row[2],
            "found_traffic": row[3]
        };
        res_alerts.append(al)
 
    return {"lastAlerts":res_alerts} 
