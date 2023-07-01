# import datetime
# from ultralytics import YOLO
# import cv2
# import rclpy
# from std_msgs.msg import Int32MultiArray
# import threading

# CONFIDENCE_THRESHOLD = 0.35
# GREEN = (0, 255, 0)

# video_cap = cv2.VideoCapture("/home/cchoirun/Documents/yolov8/sampel.webm")
# model = YOLO("/home/cchoirun/Documents/yolov8/best.pt")
# model.predict(half=True)

# titikRed = [1, 2]
# titikGreen = [3, 4]

# def publish_data():
#     node = rclpy.create_node("simple_publisher")
#     publisher = node.create_publisher(Int32MultiArray, "titik_data", 10)
#     msg = Int32MultiArray()

#     while True:
#         msg.data = [titikRed[0], titikRed[1], titikGreen[0], titikGreen[1]]
#         publisher.publish(msg)
#         rclpy.spin_once(node)

# def main():
#     rclpy.init()

#     # publish_thread = threading.Thread(target=publish_data)
#     # publish_thread.start()

#     maxFPS = -1
#     minFPS = 1003
#     totalFPS = 0
#     FPSCount = 0

#     while True:
#         start = datetime.datetime.now()
#         ret, frame = video_cap.read()

#         if not ret:
#             break

#         detections = model(frame)[0]
#         print(detections)

#         for data in detections.boxes.data.tolist():
#             xmin, ymin, xmax, ymax = int(data[0]), int(data[1]), int(data[2]), int(data[3])
#             class_id = data[5]
#             COLOR = (255, 255, 255)

#             class_name = "none"

#             if (xmax - xmin <= 5 or ymax - ymin <= 5):
#                 continue

#             if class_id == 1:
#                 class_name = "red_ball"
#                 COLOR = (0, 0, 255)
#             elif class_id == 0:
#                 class_name = "green_ball"
#                 COLOR = (0, 255, 0)

#             cv2.rectangle(frame, (xmin, ymin), (xmax, ymax), COLOR, 1)
#             if class_name == "red_ball":
#                 titikRed = [abs(xmax + xmin) / 2, abs(ymax + ymin) / 2]
#             elif class_name == "green_ball":
#                 titikGreen = [abs(xmax + xmin) / 2, abs(ymax + ymin) / 2]
#             cv2.putText(frame, class_name, (xmin - 10, ymin - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, COLOR, 1)

#         end = datetime.datetime.now()
#         total = (end - start).total_seconds()

#         fps = f"FPS: {1 / total:.2f}"
#         FPS = 1 / total
#         maxFPS = max(maxFPS, FPS)
#         minFPS = min(minFPS, FPS)
#         totalFPS += FPS
#         FPSCount += 1

#         print(f"Hijau titik : {titikGreen}")
#         print(f"Red titik : {titikRed}")
#         publish_thread = threading.Thread(target=publish_data)
#         publish_thread.start()
#         cv2.putText(frame, fps, (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 0), 7)
#         cv2.imshow("Frame", frame)
#         if cv2.waitKey(1) == ord("q"):
#             break

#     # publish_thread.join()

#     # print(f"Maximum FPS Rate: {maxFPS}")
#     # print(f"Minimum FPS Rate: {minFPS}")
#     # print(f"Average FPS Rate: {totalFPS / FPSCount}")

#     video_cap.release()
#     cv2.destroyAllWindows()

#     rclpy.shutdown()

# if __name__ == "__main__":
#     main()



import datetime
from ultralytics import YOLO
import cv2
import rclpy
from std_msgs.msg import Float32MultiArray
import threading

CONFIDENCE_THRESHOLD = 0.35
GREEN = (0, 255, 0)

video_cap = cv2.VideoCapture("/home/cchoirun/Documents/yolov8/sampel.webm")
model = YOLO("/home/cchoirun/Documents/yolov8/best.pt")
model.predict(half=True)

titikRed = [1, 2]
titikGreen = [3, 4]

def publish_data(node, hijau, merah):
    publisher = node.create_publisher(Float32MultiArray, "titik_data", 10)
    msg = Float32MultiArray()

    
    msg.data = [hijau[0], hijau[1], merah[0], merah[1]]
    publisher.publish(msg)
    # rclpy.spin_once(node)

def main():
    rclpy.init()

    node = rclpy.create_node("simple_publisher")
    

    maxFPS = -1
    minFPS = 1003
    totalFPS = 0
    FPSCount = 0

    while True:
        start = datetime.datetime.now()
        ret, frame = video_cap.read()

        if not ret:
            break

        detections = model(frame)[0]
        print(detections)

        for data in detections.boxes.data.tolist():
            xmin, ymin, xmax, ymax = int(data[0]), int(data[1]), int(data[2]), int(data[3])
            class_id = data[5]
            COLOR = (255, 255, 255)

            class_name = "none"

            if (xmax - xmin <= 5 or ymax - ymin <= 5):
                continue

            if class_id == 1:
                class_name = "red_ball"
                COLOR = (0, 0, 255)
            elif class_id == 0:
                class_name = "green_ball"
                COLOR = (0, 255, 0)

            cv2.rectangle(frame, (xmin, ymin), (xmax, ymax), COLOR, 1)
            if class_name == "red_ball":
                titikRed = [abs(xmax + xmin) / 2, abs(ymax + ymin) / 2]
            elif class_name == "green_ball":
                titikGreen = [abs(xmax + xmin) / 2, abs(ymax + ymin) / 2]
            cv2.putText(frame, class_name, (xmin - 10, ymin - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, COLOR, 1)

        end = datetime.datetime.now()
        total = (end - start).total_seconds()

        fps = f"FPS: {1 / total:.2f}"
        FPS = 1 / total
        maxFPS = max(maxFPS, FPS)
        minFPS = min(minFPS, FPS)
        totalFPS += FPS
        FPSCount += 1

        hijau = titikGreen
        merah = titikRed
        print(f"Hijau titik : {titikGreen}")
        print(f"Red titik : {titikRed}")
        publish_data(node, hijau, merah)
        # publish_thread = threading.Thread(target=publish_data, args=(node,hijau, merah))
        
        cv2.putText(frame, fps, (50, 50), cv2.FONT_HERSHEY_SIMPLEX, 2, (0, 0, 0), 7)
        cv2.imshow("Frame", frame)
        if cv2.waitKey(1) == ord("q"):
            break


    # print(f"Maximum FPS Rate: {maxFPS}")
    # print(f"Minimum FPS Rate: {minFPS}")
    # print(f"Average FPS Rate: {totalFPS / FPSCount}")

    video_cap.release()
    cv2.destroyAllWindows()

    rclpy.shutdown()

if __name__ == "__main__":
    main()
