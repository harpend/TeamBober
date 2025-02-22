from flask import Blueprint, request, jsonify
from bson.json_util import dumps
from db import mongo
import requests

microbit_bp = Blueprint('microbit', __name__)
microbit_url = 'insert endpoint/api/bobr_alert'
# POST /microbit/bobr_alert
@microbit_bp.route('/bobr_alert', methods=['POST'])
def bobr_alert():
    issues = mongo.db.issues.find().sort("upvotes", -1).limit(10)
    title = issues[0]['title']
    data = {
        "Text": title
    }

    try:
        response = requests.post(microbit_url, json=data) 
        if response.status_code == 200:
            ret = {
                "Value": response.text
            }
            return ret, 201, {'Content-Type': 'application/json'}
        elif response.status_code == 400:
            ret = {
                "Value": response.text
            }
            return ret, 201, {'Content-Type': 'application/json'}
        else:
            return None, 500, {'Content-Type': 'application/json'}

    except requests.exceptions.RequestException as e:
        return None, 500, {'Content-Type': 'application/json'}



