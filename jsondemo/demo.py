import json

data = {}
data['foo'] = 7
data['more'] = {}
data['more']['less'] = [ 1, 2, 3, 4]

print(json.dumps(data))



request = { 
    "requests": [
        {
            "addChart": {

            }
        }
    ]
}


print(json.dumps(request))