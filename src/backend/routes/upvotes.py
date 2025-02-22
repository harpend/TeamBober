from flask import Blueprint, request, jsonify
from bson.objectid import ObjectId
from db import issues_collection
from sockets import socketio

upvotes_bp = Blueprint('upvotes', __name__)

# 🔹 Upvote an issue
@upvotes_bp.route('/api/issues/<id>/upvote', methods=['POST'])
def upvote_issue(id):
    data = request.json
    nickname = data.get("nickname", "Anonymous")

    issue = issues_collection.find_one({"_id": ObjectId(id)})
    if issue:
        new_upvote_count = issue["upvotes"] + 1
        issues_collection.update_one({"_id": ObjectId(id)}, {"$set": {"upvotes": new_upvote_count}})

        # 🔹 Send real-time update
        socketio.emit('issue_upvoted', {"id": id, "upvotes": new_upvote_count, "nickname": nickname})

        return jsonify({"message": "Issue upvoted!", "upvotes": new_upvote_count, "nickname": nickname}), 200

    return jsonify({"error": "Issue not found"}), 404
