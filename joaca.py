import json
fisier = open('./date.json', 'r') # practic stream catre fisier deschis
date = fisier.read() # citesc ce e in el in date
r = json.loads(date) # parsez si construiesc OBIECT


def searchBooks(searchedTerm):
    for book in r['data']:
        titlu = book['attributes']['title']
        author = book['attributes']['author']
        dedication = book['attributes']['dedication']
        summary = book['attributes']['summary']
        
        if searchedTerm in titlu or  searchedTerm in summary or searchedTerm in dedication or  searchedTerm in author: 
            del book['relationships']
            del book['links']
            print(json.dumps(book['attributes'], indent=4))



def test():
    arr = {
        'vector': [1,2,3,4],
        'vector2': [5,6,7,8],
        '   attributes': {
            'carti': [
                {
                    'titlu': 'Salut'
                }, 
                {
                    'titlu': 'Salut 2'
                }
            ]
        }
    }

    output = open('./output.json', 'w')
    output.write(json.dumps(arr))
    output.close()
    print(arr['attributes']['carti'][1]['titlu']) 


searchBooks('Dumbledore')
