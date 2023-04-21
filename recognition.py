import mysql.connector
import face_recognition
import numpy as np
import cv2

img = face_recognition.load_image_file('imageBasics/Bill_gates.jpg')
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

encode = face_recognition.face_encodings(img)[0]

# print(encode)

mydb = mysql.connector.connect(
  host = "localhost",
  user = "root",
  password = "",
  database = "technothon"
)

# print(mydb)

mycursor = mydb.cursor()

mycursor.execute("SELECT * FROM patientdetails")

myresult = mycursor.fetchall()

# for x in myresult:
# #   print(x)
# print(float('-4.39940542e-02'))

# var = myresult[0][1]
# print(var)
# z = np.array(list(var[1:-1]), dtype=np.float)
# print(z)
print(encode)
# x = var[s:-1].split(" ")
# print(x)
# y = [float(i) for i in x]
# print(var)
# print(type(encode))

# print(encode)


# results = face_recognition.compare_faces(var, encode)

# print(results)

# ar = np.array(x)
# print(type(ar))
# test = ar.astype('float64')
# print(test)