from flask import Blueprint, request, jsonify
from bson.json_util import dumps
from db import mongo
import requests

microbit_bp = Blueprint('microbit', __name__)
microbit_url = 'http://localhost:8080/api/new-bobr'
# POST /microbit/bobr_alert
@microbit_bp.route('/bobr_alert', methods=['POST'])
def bobr_alert():
    issues = mongo.db.issues.find().sort("upvotes", -1).limit(10)
    title = issues[0]['title']
    issue_id = issues[0].get('_id')
    print(issue_id)
    data = {
        "Text": title
    }

    try:
        response = requests.post(microbit_url, json=data) 
        if response.status_code == 200:
            filter = {"_id": issue_id}
            result = mongo.db.issues.update_one(
                filter,
                {"$set": {"status": "resolved"}}
            )
            return jsonify({"Value": response.text}), 201
        elif response.status_code == 400:
            ret = {
                "Value": response.text
            }
            return jsonify({"error": "Unexpected response"}), 500
        else:
            return jsonify({"error": "Unexpected response"}), 500

    except requests.exceptions.RequestException as e:
        return jsonify({"error": "Unexpected response"}), 500



