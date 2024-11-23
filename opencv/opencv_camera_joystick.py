import cv2
import numpy as np
import pyautogui

camera = cv2.VideoCapture(0)
if not camera.isOpened():
    print("Cannot open camera")
    exit()

targetBGR = (67, 53, 143)
targetHSV = (234, 99, 80)

maxDiff = 20

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

def draw_axes_circle(frame, deadzone, zone1, zone2, zone3):
    height, width, _ = frame.shape
    y_center = height // 2
    x_center = width // 2

    cv2.line(frame, (x_center, 0), (x_center, height), (255, 255, 255), 1)
    cv2.line(frame, (0, y_center), (width, y_center), (255, 255, 255), 1)

    cv2.circle(frame, (x_center, y_center), int(deadzone), (255, 255, 255), 1)
    cv2.circle(frame, (x_center, y_center), int(zone1), (255, 255, 255), 1)
    cv2.circle(frame, (x_center, y_center), int(zone2), (255, 255, 255), 1)
    cv2.circle(frame, (x_center, y_center), int(zone3), (255, 255, 255), 1)
    return frame

def get_angle(x, y, cx, cy):
    angle = np.degrees(np.arctan2(y - cy, x - cx))  
    if angle < 0:
        angle += 360  
    return angle

def move(x, y, center_x, center_y, senisitivity):
    angle = get_angle(x, y, center_x, center_y)

    angles = [0, 20, 70, 110, 160, 200, 250, 290, 350, 0]
    decisions = (
        (sensitivity, 0), #dreapta
        (sensitivity, sensitivity), #dreapta sus
        (0, sensitivity), #sus
        (-sensitivity, sensitivity), #stanga sus
        (-sensitivity, 0), #stanga
        (-sensitivity, -sensitivity), #stanga jos
        (0, -sensitivity), # jos 
        (sensitivity, -sensitivity),  #dreapta jos 
        (sensitivity, 0), #dreapta
    )
    for i in range(len(angles) - 1):
        if angle > angles[i] and angle <= angles[i+1]:
            pyautogui.move(decisions[i])

def get_sensitivity(x, y, center_x, center_y, deadzone, zone1, zone2, zone3):
    distance = np.sqrt((x - center_x)**2 + (y - center_y)**2)
    sensitivity1 = 10
    sensitivity2 = 20
    sensitivity3 = 30
    sensitivity4 = 50

    if distance <= deadzone:
        return 0
    elif distance <= zone1:
        return sensitivity1
    elif distance <= zone2:
        return sensitivity2
    elif distance <= zone3:
        return sensitivity3
    else:
        return sensitivity4


previousBiggestContour = None
while True:
    ret, frame = camera.read()
    if not ret:
        print("Can't receive frame (stream end?). Exiting ...")
        break

    height, width, _ = frame.shape

    lower = getLowerBGR(targetBGR)
    upper = getUpperBGR(targetBGR)

    mask = cv2.inRange(frame, lower, upper)
    contours, hierarchy = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    
    frame = draw_axes_circle(frame, 80, 170, 300, 400)
    biggestContour = None
    maxArea = 0

    for cnt in contours:
        area = cv2.contourArea(cnt)
        if area > maxArea:
            maxArea = area
            biggestContour = cnt

    if biggestContour is not None:
        cv2.drawContours(frame, contours, -1, (0, 255, 0), 2)

        x, y, w, h = cv2.boundingRect(biggestContour)
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 0, 255), 4)

        M = cv2.moments(biggestContour)
        if M['m00'] != 0:
            cx = int(M['m10']/M['m00'])
            cy = int(M['m01']/M['m00'])
            cv2.circle(frame, (cx, cy), 7, (255, 0, 0), -1)
            cv2.putText(frame, "center", (cx - 20, cy - 20),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 2)

            sensitivity = get_sensitivity(cx, cy, width // 2, height // 2,  80, 200, 350, 550)
            move(cx, cy, width // 2, height // 2, sensitivity)
        previousBiggestContour = biggestContour

    cv2.imshow('frame', frame)
    if cv2.waitKey(1) == ord('q'):
        break

camera.release()
cv2.destroyAllWindows()