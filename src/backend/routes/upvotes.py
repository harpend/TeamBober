from flask import Blueprint, request, jsonify
from bson.json_util import dumps
from db import mongo

upvotes_bp = Blueprint('upvotes', __name__)

# POST /issues/<issue_id>/save
@upvotes_bp.route('/<issue_id>/save', methods=['POST'])
def save_issue(issue_id):
    result = mongo.db.issues.update_one({"issue_id": issue_id}, {"$set": {"saved": True}})
    if result.matched_count:
        issue = mongo.db.issues.find_one({"issue_id": issue_id})
        return dumps(issue), 200, {'Content-Type': 'application/json'}
    else:
        return jsonify({"error": "Issue not found"}), 404

# GET /issues/saved
@upvotes_bp.route('/saved', methods=['GET'])
def get_saved_issues():
    saved_issues = mongo.db.issues.find({"saved": True})
    return dumps(saved_issues), 200, {'Content-Type': 'application/json'}

# POST /issues/<issue_id>/vote
@upvotes_bp.route('/<issue_id>/vote', methods=['POST'])
def vote_issue(issue_id):
    result = mongo.db.issues.update_one({"issue_id": issue_id}, {"$inc": {"upvotes": 1}})
    if result.matched_count:
        issue = mongo.db.issues.find_one({"issue_id": issue_id})
        return dumps(issue), 200, {'Content-Type': 'application/json'}
    else:
        return jsonify({"error": "Issue not found"}), 404

# GET /issues/trending
@upvotes_bp.route('/trending', methods=['GET'])
def get_trending_issues():
    issues = mongo.db.issues.find().sort("upvotes", -1).limit(10)
    return dumps(issues), 200, {'Content-Type': 'application/json'}

__all__ = ["upvotes_bp"]
