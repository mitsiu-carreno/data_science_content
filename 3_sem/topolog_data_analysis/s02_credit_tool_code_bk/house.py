import csv


def house_review(credit_house):
    # read csv file to a list of dictionaries
    with open('realStateCleaned.csv', 'r') as file:
        csv_reader = csv.DictReader(file)
        data = [row for row in csv_reader]

    # credit criteria will be based on this link : https://www.investopedia.com/articles/pf/05/030905.asp
    # good credit can get a house over 2.5 x anual salary
    # standard credit can get a house over 2 x anual salary
    # bad credit canget a house over 1.5 x anual salary  

    credit_limit = 0 
    
    if credit_house.credit_status.lower() == 'good':
        credit_limit = credit_house.salary * 2.5

    if credit_house.credit_status.lower() == 'standard':
        credit_limit = credit_house.salary * 2
    
    if credit_house.credit_status.lower() == 'bad':
        credit_limit = credit_house.salary * 1.5

    house_options = []
    
    for element in data:
        opt = {}
        if int(element['SalePrice']) < credit_limit:
            opt['SalePrice'] = element['SalePrice']
            opt['StreetNameAndWay'] = element['StreetNameAndWay']
            opt['OwnerFirstName'] = element['OwnerFirstName']
            opt['OwnerLastName'] = element['OwnerLastName']
            house_options.append(opt)


    return house_options