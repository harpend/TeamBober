from flask import Blueprint, request, jsonify
from bson.json_util import dumps
from db import mongo
import requests
import time 

# microbit_bp = Blueprint('microbit', __name__)
microbit_url = 'http://localhost:8080/api/new-bobr'
# POST /microbit/bobr_alert
# @microbit_bp.route('/bobr_alert', methods=['POST'])
def bobr_alert():
    while True:
        issues = list(mongo.db.issues.find(
            {"status": {"$nin": ["resolved", "rejected"]},
            "upvotes": {"$gt": 22}}
        ).sort("upvotes", -1).limit(10) )
        # make sure not already resolved
        # reflash microbit
        # allow to press b to reject
        if not issues:
            time.sleep(5)
            continue
        title = issues[0]['title']
        issue_id = issues[0].get('_id')
        data = {
            "Text": title
        }

        try:
            response = requests.post(microbit_url, json=data) 
            filter = {"_id": issue_id}
            if response.status_code == 200:
                result = mongo.db.issues.update_one(
                    filter,
                    {"$set": {"status": "resolved"}}
                )
                time.sleep(5)
                continue
            elif response.status_code == 204:
                result = mongo.db.issues.update_one(
                    filter,
                    {"$set": {"status": "rejected"}}
                )
                time.sleep(5)
                continue
            else:
                time.sleep(5)
                continue

        except requests.exceptions.RequestException as e:
            time.sleep(5)
            continue



