export FLASK_APP=server/server
SERVICE_ACCOUNT_FILE="creds/keys.json" \
flask run
# * Running on http://127.0.0.1:5000/``
# curl "http://127.0.0.1:5000/update-sheet?avg=7&max=2"