from flask import Flask
from flask_pymongo import PyMongo

app = Flask(__name__)
app.config["MONGO_URI"] = "mongodb://localhost:27017/bobr_db"  # Adjust DB name if needed
mongo = PyMongo(app)

# Collections
issues_collection = mongo.db.issues

