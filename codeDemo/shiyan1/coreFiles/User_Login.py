#User_Login.py
import random
import string
from classFiles.ManageFiles import Manage_file

class User_Judge:
    @staticmethod
    def generate_password():
        # 大写字母
        uppercase = random.choice(string.ascii_uppercase)
        # 小写字母
        lowercase = random.choice(string.ascii_lowercase)
        # 特殊符号
        special_char = random.choice('!@#$%^&*?')
        # 六位数字
        digits = ''.join(random.choices(string.digits, k=6))
        # 将所有字符放在一起并随机排列
        all_chars = uppercase + lowercase + special_char + digits
        password = ''.join(random.sample(all_chars, len(all_chars)))
        #将序列中的每个字符串连接起来形成一个新的字符串。
        return password
    
    @staticmethod
    def format_write_infos_to_file(infos):
        userInfos = Manage_file("C:\\Users\\17255\\Desktop\\python\\codeDemo\\userInfos.ini")
        data = ""
        data = infos.replace(':','\t').replace(',','\n')
        userInfos.write_file(data)

    @staticmethod
    def send_theFormat_infos()->str:
        userInfos = Manage_file("C:\\Users\\17255\\Desktop\\python\\codeDemo\\userInfos.ini")
        data = userInfos.read_allFile().replace('\n','\t')
        return "userInfos:"+data