from flask import Flask, send_from_directory
from db import mongo
from routes.issues import issues_bp
from routes.upvotes import upvotes_bp
from routes.microbit import microbit_bp
import os

app = Flask(__name__)

# MongoDB configuration (include your database name)
app.config["MONGO_URI"] = "mongodb+srv://austink2109:tvUmNdoJn4wIeUeV@cluster0.l7van.mongodb.net/CommunityReports?retryWrites=true&w=majority"
# Set the upload folder (absolute path)
app.config["UPLOAD_FOLDER"] = os.path.abspath(os.path.join(os.path.dirname(__file__), "static", "uploads"))

# Initialize PyMongo
mongo.init_app(app)

# Register blueprints with proper URL prefixes
app.register_blueprint(issues_bp, url_prefix="/issues")
app.register_blueprint(upvotes_bp, url_prefix="/issues")
app.register_blueprint(microbit_bp, url_prefix="/microbit")

# Route for serving uploaded files
@app.route('/uploads/<path:filename>')
def serve_uploaded_file(filename):
    return send_from_directory(app.config["UPLOAD_FOLDER"], filename)

if __name__ == '__main__':
    app.run(debug=True)
