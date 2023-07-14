from flask import Flask, request
# import pandas as pd
import numpy as np


all_data = []
i = 0

app = Flask(__name__)

@app.route('/feed', methods=['POST'])
def get_data():
    data = request.data.decode('ascii')
    print(data)
    return 'OK'

# @app.route('/feed', methods=['POST'])
# def get_data():
#     global all_data, i
#     i += 1
#     data = request.data.decode('ascii')
#     # print(request.data)
#     all_data.append(data.split(","))
#     if i == 10:
#         np.save('data.npy', np.array(all_data).astype(np.float32))
#         print("Saved")
#         i = 0
#     return 'OK'

if __name__ == '__main__':
    app.run(host='192.168.201.151', port=5000, debug=True)
