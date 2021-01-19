import paho.mqtt.client as mqtt
import numpy as np
import pandas as pd
import mysql.connector
from mysql.connector import Error
from mysql.connector import errorcode
from sklearn import preprocessing
from sklearn.svm import SVC
from sklearn.preprocessing import StandardScaler


def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("acc/#")


def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload, 'UTF8'))
    datas =str(msg.payload, 'UTF8').split(';')
    new = np.array([[float(datas[0]),float(datas[1]),float(datas[2])]])
    if(msg.topic == 'acc/1'):
    	filepath = r'C:\mpudataset.csv'
    	data = pd.read_csv(filepath)

    	ley = preprocessing.LabelEncoder()
    	X = data.drop(columns=['Label'])
    	y = data['Label'].values
    	y = ley.fit_transform(y)

    	scaler = StandardScaler()
    	X = scaler.fit_transform(X)
    	clf = SVC(gamma=0.01, C=10)

    	clf.fit(X,y)

    	new = scaler.transform(new)
    	res = clf.predict(new)
    	print(ley.inverse_transform(res)[0])
    	try:
    		connection = mysql.connector.connect(host='localhost',
		                                 database='id12730345_yusril',
		                                 user='id12730345_iottest',
		                                 password='b4TCh#JXdEry*[3g')
    		cursor = connection.cursor()
    		mySql_insert_query = """INSERT INTO iot (Ax, Ay, Az, Label) VALUES (%s, %s, %s, %s) """
    		recordTuple = (float(datas[0]), float(datas[1]), float(datas[2]), ley.inverse_transform(res)[0])
    		cursor.execute(mySql_insert_query, recordTuple)
    		connection.commit()
    		print("Record inserted successfully into mpu6050 table")
    	except mysql.connector.Error as error:
    		print("Failed to insert into mpu6050 table {}".format(error))
    	finally:
    		if (connection.is_connected()):
    			cursor.close()
    			connection.close()
    			print("MySQL connection is closed")

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

#blank part should be IP address of client
client.connect("blank", 1883, 60)

client.loop_forever()