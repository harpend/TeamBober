from flask import Flask
from db import mongo
from routes.issues import issues_bp
from routes.upvotes import upvotes_bp
import os
from routes.microbit import microbit_bp

app = Flask(__name__)
# Be sure to include your database name in the URI (e.g., "CommunityReports")
app.config["MONGO_URI"] = "mongodb+srv://austink2109:tvUmNdoJn4wIeUeV@cluster0.l7van.mongodb.net/CommunityReports?retryWrites=true&w=majority"

# Initialize PyMongo with the Flask app
mongo.init_app(app)

# Register blueprints
app.register_blueprint(issues_bp, url_prefix="/issues")
app.register_blueprint(upvotes_bp, url_prefix="/issues")
app.register_blueprint(microbit_bp, url_prefix="/microbit")

if __name__ == '__main__':
    app.run(debug=True)
