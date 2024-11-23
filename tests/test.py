# import cv2 as cv
# import numpy as np

# vid = cv.VideoCapture(0)

# while True:
#     ret, frame = vid.read()

#     # Convert BGR to HSV
#     hsv = cv.cvtColor(frame, cv.COLOR_BGR2HSV)
 
#     # define range of blue color in HSV
#     lower_blue = np.array([110,50,50])
#     upper_blue = np.array([130,255,255])
 
#     # Threshold the HSV image to get only blue colors
#     mask = cv.inRange(hsv, lower_blue, upper_blue)
 
#     # Bitwise-AND mask and original image
#     res = cv.bitwise_and(frame,frame, mask= mask)
 
#     cv.imshow('frame',frame)
#     cv.imshow('mask',mask)
#     cv.imshow('res',res)


#     if cv.waitKey(1) & 0xFF == ord('q'):
#         break

# vid.release()
# cv.destroyAllWindows()


import requests

# Funcție pentru a căuta termenul în fiecare rezultat dintr-o listă
def search_in_data(data, query):
    results = []
    for item in data:
        # Verificăm dacă termenul apare în oricare dintre valorile dicționarului
        if any(query.lower() in str(value).lower() for value in item.values()):
            results.append(item)
    return results

# Funcție principală
def main():
    # Citim termenul de căutare de la tastatură
    searched_query = input("Enter the search term: ")

    # Lista endpoint-urilor din API
    endpoints = ['characters', 'houses', 'spells', 'books']

    # Iterăm prin fiecare endpoint și căutăm termenul
    for endpoint in endpoints:
        url = f'https://api.potterdb.com/v1/{endpoint}'
        response = requests.get(url)
        data = response.json().get('data', [])
        # Căutăm termenul în datele obținute
        matching_results = search_in_data(data, searched_query)
        if matching_results:
            print(f"\nResults found in {endpoint}:")
            for result in matching_results:
                print(result)

if __name__ == "__main__":
    main()