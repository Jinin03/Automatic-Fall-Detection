import pdb
import requests
fl = open('/home/root/Vitis-AI/vitis_ai_library/samples/Automatic_Fall_Detection/Single_Camera_Video/test_sms.txt','r').readlines()
flag = False
while(flag == False):
    if(len(fl)>1):
        if(fl[1] == "Fall detected\n"):
            flag = True
            url = "https://www.fast2sms.com/dev/bulk/"
            payload = "sender_id=FSTSMS&message=fall%20detected&language=english&route=p&numbers=9915617946,8160190561"
            headers = {'authorization': "PhF002aSHBWyR0ud5NBEJlEzfZ4t6G6ozUdUSVLdrAlnfIAJWbtndmLSNyMZ",'Content-Type': "application/x-www-form-urlencoded",'Cache-Control': "no-cache",}
            response = requests.request("POST", url, data=payload, headers=headers)
            print(response.text)
    else:
        fl = open('/home/root/Vitis-AI/vitis_ai_library/samples/yolov3/test_sms.txt','r').readlines()
