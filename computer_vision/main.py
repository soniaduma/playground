import cv2
import pyautogui


'''
todo:
- ori recalibrat ori folosit card meu
- pyautogui: sa testam daca merge pe python sa misti mouseul; daca nu, sa cautam o librarie pe pip echivalenta care sa miste mouseul
- ! in loc sa se msite mouseul cu cati pixeli s-a mutat boxul, poate are mai mult sens sa reimplementam logica unde box-ul e un joysticK:
    daca box-ul e in sus-dreapta, mutam mouseul cate un pixel * sensitivity la fiecare frame in sus-dreapta
    daca box-ul e in jos-dreapta, mutam mouseul cate un pixel * sensitivity la fiecare frame in jos-dreapta
    similar cu toate restul pozitiilor

- de gandit un mecanism in care sa poti sa dai CLICK STANGA din camera (poate daca aducem un alt cartonas de alta culoare si il detectam in ecran, atunci sa dam click?)
- nu cred ca functia de find contours e ideala, dar poate gasim un alt mecanism de a ne prinde de media centrala a boxului;

'''
camera = cv2.VideoCapture(0)
if not camera.isOpened():
    print("Cannot open camera")
    exit()


targetBGR = (67, 53, 143)
targetHSV = (234, 99, 80)

maxDiff = 30

def aproape(pixela, pixelb):
    for i in range(len(pixela)):
        if abs(pixela[i] - pixelb[i]) > maxDiff:
            return False
    return True

def getUpperBGR(pixel):
    return (min(pixel[0] + maxDiff, 255), min(pixel[1] + maxDiff, 255), min(pixel[2] + maxDiff, 255))

def getLowerBGR(pixel):
    return (max(pixel[0] - maxDiff, 0), max(pixel[1] - maxDiff, 0), max(pixel[2] - maxDiff, 0))

def getUpperHSV(pixel):
    return (min(pixel[0] + 10, 255), min(pixel[1] + 30, 255), 245)

def getLowerHSV(pixel):
    return (max(pixel[0] - 10, 0), max(pixel[1] - 30, 0), 10)


sensitivity = 5
previousBiggestContour = None
while True:
    # camerature frame-by-frame
    ret, frame = camera.read()

    height, width, _ = frame.shape

    lower = getLowerBGR(targetBGR)
    upper = getUpperBGR(targetBGR)

    # hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    mask = cv2.inRange(frame, lower, upper)

    contours, hierarchy = cv2.findContours(mask, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)

    contours=[cv2.boundingRect(cnt) for cnt in contours]

    biggestContour = (0,0,0,0)
    for cnt in contours:
        x,y,w,h=cnt
        cv2.rectangle(frame,(x,y),(x+w,y+h),(0,255,0),2)
        if (w+h > biggestContour[3] + biggestContour[2]):
            biggestContour = cnt
    
    if (previousBiggestContour):
        diffX = biggestContour[0] - previousBiggestContour[0]
        diffY = biggestContour[1] - previousBiggestContour[1]
        pyautogui.moveRel(diffX * sensitivity, diffY * sensitivity)
    previousBiggestContour = biggestContour
    cv2.rectangle(frame,(biggestContour[0], biggestContour[1]),(biggestContour[0]+biggestContour[2],biggestContour[1] + biggestContour[3]),(0,0,255),4)
    # if frame is read correctly ret is True
    if not ret:
        print("Can't receive frame (stream end?). Exiting ...")
        break
    

    # Display the resulting frame
    cv2.imshow('frame', frame)
    cv2.imshow('mask', mask)
    if cv2.waitKey(1) == ord('q'):
        break
 
# When everything done, release the camerature
camera.release()
cv2.destroyAllWindows()