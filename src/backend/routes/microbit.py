from flask import Blueprint, request, jsonify
from bson.json_util import dumps
from db import mongo
import requests

# microbit_bp = Blueprint('microbit', __name__)
microbit_url = 'http://localhost:8080/api/new-bobr'
# POST /microbit/bobr_alert
# @microbit_bp.route('/bobr_alert', methods=['POST'])
def bobr_alert():
    print("check")
    issues = list(mongo.db.issues.find(
        {"status": {"$nin": ["resolved", "rejected"]},
         "upvotes": {"$gt": 22}}
    ).sort("upvotes", -1).limit(10) )
    # make sure not already resolved
    # reflash microbit
    # allow to press b to reject
    if not issues:
        return
    title = issues[0]['title']
    issue_id = issues[0].get('_id')
    print(issue_id)
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
            return
        elif response.status_code == 204:
            result = mongo.db.issues.update_one(
                filter,
                {"$set": {"status": "rejected"}}
            )
            return
        else:
            return

    except requests.exceptions.RequestException as e:
        return



