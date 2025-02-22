from flask import Blueprint, request, jsonify
from bson.json_util import dumps
from db import mongo

issues_bp = Blueprint('issues', __name__)

# POST /issues/report
@issues_bp.route('/report', methods=['POST'])
def report_issue():
    data = request.get_json()
    if not data:
        return jsonify({"error": "No data provided"}), 400

    result = mongo.db.issues.insert_one(data)
    new_issue = mongo.db.issues.find_one({"_id": result.inserted_id})
    return dumps(new_issue), 201, {'Content-Type': 'application/json'}

# GET /issues
@issues_bp.route('', methods=['GET'])
def get_issues():
    issues = mongo.db.issues.find()
    return dumps(issues), 200, {'Content-Type': 'application/json'}

# GET /issues/recent
@issues_bp.route('/recent', methods=['GET'])
def get_recent_issues():
    # Assuming "created_at" is stored in a format that allows sorting.
    # Sorting descending (newest first) and limiting to 10 results.
    issues = mongo.db.issues.find().sort("created_at", -1).limit(10)
    return dumps(issues), 200, {'Content-Type': 'application/json'}
