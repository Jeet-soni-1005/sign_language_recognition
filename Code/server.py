from flask import Flask, request, jsonify
import numpy as np

app = Flask(__name__)

all_data = []
i = 0

# POST endpoint to receive data
@app.route('/feed', methods=['POST'])
def feed_data():
    data = request.get_json()  # Expecting JSON payload
    if not data:
        return jsonify({"error": "No data provided"}), 400
    all_data.append(data)
    global i
    i += 1
    if i == 10:
        np.save('data.npy', np.array(all_data).astype(np.float32))
        i = 0
    return jsonify({"message": "Data received successfully"}), 200

# GET endpoint to retrieve data
@app.route('/data', methods=['GET'])
def get_data():
    return jsonify(all_data), 200

if __name__ == '__main__':
    app.run(host='192.168.201.151', port=5000, debug=True)
