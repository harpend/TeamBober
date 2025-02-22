from flask import Flask
from flask_jwt_extended import JWTManager
from flask_cors import CORS
from sockets import socketio
from db import app
from routes.issues import issues_bp
from routes.auth import auth_bp
from routes.upvotes import upvotes_bp

app.config["JWT_SECRET_KEY"] = "supersecret"  # Change this in production
jwt = JWTManager(app)
CORS(app)

# Register routes
app.register_blueprint(issues_bp)
app.register_blueprint(auth_bp)
app.register_blueprint(upvotes_bp)

if __name__ == "__main__":
    socketio.init_app(app, cors_allowed_origins="*")
    socketio.run(app, debug=True)
