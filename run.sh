export FLASK_APP=server/server
SERVICE_ACCOUNT_FILE="creds/keys.json" \
flask run --host 0.0.0.0 --port 8000