import csv
import numpy as np


def get_criteria():
    # read csv file to a list of dictionaries
    with open('testCleaned.csv', 'r') as file:
        csv_reader = csv.DictReader(file)
        data = [row for row in csv_reader]

    # types of credit risk : Good, Standard, Bad 
    # metrics to be used to decide metrics : 
    # min number of Num_of_Delayed_Payment , max number of Num_of_Delayed_Payment, media 
    # min number of Num_of_Loan , max Num_of_Loan, media 
    statistic_data = {
        "Good" : {
            "min_Num_of_Delayed_Payment" : 0,
            "max_Num_of_Delayed_Payment" : 0,
            "mean_Num_of_Delayed_Payment" : 0,
        },
        "Bad" : {
            "min_Num_of_Delayed_Payment" : 0,
            "max_Num_of_Delayed_Payment" : 0,
            "mean_Num_of_Delayed_Payment" : 0,
        },
        "Standard" : {
                "min_Num_of_Delayed_Payment" : 0,
                "max_Num_of_Delayed_Payment" : 0,
                "mean_Num_of_Delayed_Payment" : 0,
            }
    }

    good_delayed_payment = []
    bad_delayed_payment = []
    standard_delayed_payment = []

    for element in data:
        parse_num_delayed_payment = int(element['Num_of_Delayed_Payment'])

        if (element['Credit_Mix'] == 'Good'):
            good_delayed_payment.append(parse_num_delayed_payment)

            if (len(good_delayed_payment) == 1):
                statistic_data['Good']['min_Num_of_Delayed_Payment'] = parse_num_delayed_payment

            if parse_num_delayed_payment < statistic_data['Good']['min_Num_of_Delayed_Payment']:
                statistic_data['Good']['min_Num_of_Delayed_Payment'] = parse_num_delayed_payment
            
            if parse_num_delayed_payment > statistic_data['Good']['max_Num_of_Delayed_Payment']:
                statistic_data['Good']['max_Num_of_Delayed_Payment'] = parse_num_delayed_payment
            
        
        if (element['Credit_Mix'] == 'Bad'):
            bad_delayed_payment.append(parse_num_delayed_payment)
            if (len(bad_delayed_payment) == 1):
                statistic_data['Bad']['min_Num_of_Delayed_Payment'] = parse_num_delayed_payment
            
            if parse_num_delayed_payment < statistic_data['Bad']['min_Num_of_Delayed_Payment']:
                statistic_data['Bad']['min_Num_of_Delayed_Payment'] = parse_num_delayed_payment
            
            if parse_num_delayed_payment > statistic_data['Bad']['max_Num_of_Delayed_Payment']:
                statistic_data['Bad']['max_Num_of_Delayed_Payment'] = parse_num_delayed_payment
        
        if (element['Credit_Mix'] == 'Standard'):
            standard_delayed_payment.append(parse_num_delayed_payment)

            if (len(standard_delayed_payment) == 1):
                statistic_data['Standard']['min_Num_of_Delayed_Payment'] = parse_num_delayed_payment
            
            if parse_num_delayed_payment < statistic_data['Standard']['min_Num_of_Delayed_Payment']:
                statistic_data['Standard']['min_Num_of_Delayed_Payment'] = parse_num_delayed_payment
            
            if parse_num_delayed_payment > statistic_data['Standard']['max_Num_of_Delayed_Payment']:
                statistic_data['Standard']['max_Num_of_Delayed_Payment'] = parse_num_delayed_payment

    statistic_data['Good']['mean_Num_of_Delayed_Payment'] = np.mean(good_delayed_payment)
    statistic_data['Bad']['mean_Num_of_Delayed_Payment'] = np.mean(bad_delayed_payment)
    statistic_data['Standard']['mean_Num_of_Delayed_Payment'] = np.mean(standard_delayed_payment)



    return statistic_data