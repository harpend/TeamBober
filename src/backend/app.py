from flask import Flask, send_from_directory
from db import mongo
from routes.issues import issues_bp
from routes.upvotes import upvotes_bp
from routes.microbit import bobr_alert
import os
import threading
from dotenv import load_dotenv

# Load .env variables
load_dotenv()

app = Flask(__name__)

# Use environment variables
app.config["MONGO_URI"] = os.environ.get("MONGO_URI")
app.config["UPLOAD_FOLDER"] = os.path.abspath(os.path.join(os.path.dirname(__file__), os.environ.get("UPLOAD_FOLDER", "static/uploads")))

# Initialize PyMongo
mongo.init_app(app)

# Register blueprints with proper URL prefixes
app.register_blueprint(issues_bp, url_prefix="/issues")
app.register_blueprint(upvotes_bp, url_prefix="/issues")
# app.register_blueprint(microbit_bp, url_prefix="/microbit")

# Route for serving uploaded files
@app.route('/uploads/<path:filename>')
def serve_uploaded_file(filename):
    return send_from_directory(app.config["UPLOAD_FOLDER"], filename)

if __name__ == '__main__':
    thread = threading.Thread(target=bobr_alert, daemon=True)
    thread.start()
    app.run(debug=True)
