from flask import Blueprint, request, jsonify, url_for
from bson.json_util import dumps
from db import mongo
from werkzeug.utils import secure_filename
import os

issues_bp = Blueprint('issues', __name__)

# Define the uploads folder relative to this file (assuming this file is in "routes" and static is one level up)
UPLOAD_FOLDER = os.path.join(os.path.dirname(__file__), "..", "static/uploads")

# Define allowed file extensions for images
ALLOWED_EXTENSIONS = {"png", "jpg", "jpeg", "gif"}

def allowed_file(filename):
    return '.' in filename and filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

# POST /issues/report
@issues_bp.route('/report', methods=['POST'])
def report_issue():
    # Get form data as a dictionary
    data = request.form.to_dict()
    
    # Initialize an empty list for image URLs
    images = []
    
    # Check if an image file was uploaded under the key "image"
    if 'image' in request.files:
        file = request.files['image']
        if file and allowed_file(file.filename):
            filename = secure_filename(file.filename)
            file_path = os.path.join(UPLOAD_FOLDER, filename)
            file.save(file_path)
            # Build an external URL for the uploaded image
            image_url = url_for('static', filename='uploads/' + filename, _external=True)
            images.append(image_url)
    
    # Add the images list to our data dictionary
    data["images"] = images

    # Insert the document into MongoDB
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
    issues = mongo.db.issues.find().sort("created_at", -1).limit(10)
    return dumps(issues), 200, {'Content-Type': 'application/json'}
