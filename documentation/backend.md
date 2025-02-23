## backend

The routes folder serves as the backbone of the application's API, encapsulating all the logic for managing issue data and integrating external services. 

It contains 3 components:
- issues.py
- microbit.py
- upvotes.py

## issues.py

This defines endpoints for reporting issues, retrieving lists of unresolved or recent issues, marking issues as resolved, and fetching a random issue from the MongoDB database. 

## microbit.py

This contains functionality for integrating with the microbit where we monitor the most upvoted issues and communicates to display alerts while updating the issue's status. The user of microbit device can press either A to confirm an issue was fixed or B to reject it.

## upvotes.py
The upvotes.py file defines a Flask blueprint for handling operations related to saving and voting on issues. It provides endpoints that allow clients to mark an issue as saved, retrieve all saved issues, cast a vote for an issue by incrementing its upvotes, and fetch the top ten trending issues sorted by upvotes. Each endpoint interacts with the MongoDB database, returning JSON responses that include the updated issue data or an error message if the issue isn't found.

## app.py
This initializes the Flask application by configuring the MongoDB connection and registering blueprints for issues and upvotes under the /issues prefix. It also starts a background thread that runs the bobr_alert function for continuous issue monitoring, and then runs the app in debug mode.

