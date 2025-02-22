from flask import Blueprint, request, jsonify
from bson.objectid import ObjectId
from db import issues_collection
from sockets import socketio

issues_bp = Blueprint('issues', __name__)

# 🔹 Report a new issue
@issues_bp.route('/api/issues', methods=['POST'])
def create_issue():
    data = request.json
    new_issue = {
        "title": data["title"],
        "description": data["description"],
        "location": data["location"],
        "upvotes": 0,
        "nickname": data.get("nickname", "Anonymous")  # Store nickname
    }
    result = issues_collection.insert_one(new_issue)

    issue_id = str(result.inserted_id)
    new_issue["_id"] = issue_id

    # 🔹 Send real-time update
    socketio.emit('new_issue', new_issue)

    return jsonify({"message": "Issue created!", "id": issue_id}), 201

# 🔹 Get all issues
@issues_bp.route('/api/issues', methods=['GET'])
def get_issues():
    issues = list(issues_collection.find({}, {"_id": 1, "title": 1, "description": 1, "upvotes": 1, "nickname": 1}))
    for issue in issues:
        issue["_id"] = str(issue["_id"])  # Convert ObjectId to string
    return jsonify(issues)
