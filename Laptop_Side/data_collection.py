from flask import Flask, request
from data_storage import insert_data, fill, output_data, update_robot_position, insert_target
from math import cos, sin

app = Flask(__name__)

# orientation = 0

@app.route('/process', methods=['POST'])
def process():
    
    data = request.form['data']
    print(f"Received data: {data}")

    # data = data.split(',')

    # if data[0] == "Scan":
    #     for i in range(1, 360):
    #         if data[i] != -1:
    #             insert_data(i-1, data[i])

    #     fill()
    #     process_data = output_data("Scan")
    #     return str(process_data)
    
    # elif data[0] == "Target":
    #     insert_target(data[1], data[2])

    #     process_data = output_data("Target")
    #     return str(process_data)

    # elif data[0] == "Received":
    #     process_data = output_data("Received")
    #     return str(process_data)
    # else:
    #     process_data = "ERROR"
    #     return str(process_data)
    return str("works")

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)