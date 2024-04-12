import json
import socket
import threading
from coreFiles.User_Login import User_Judge
from GUIFiles.MyGUI import Draw_Data
from coreFiles.students_Infos import students_info_count as s_info

class TCPServer:
    def __init__(self, host='localhost', port=12345):
        self.host = host
        self.port = port
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.bind((self.host, self.port))
        self.server_socket.listen(2)
        #直方图
        #self.s_dict = s_info.get_stuDict()
        self.dd = None
        self.ds = None
        print(f"服务器启动\nServer is listening on {self.host}:{self.port}")

    def check_oper(self,data,client_socket):
        if data.startswith("login_UI::on_pb_randPasswd_clicked()"):
            rand_passwd = User_Judge.generate_password()
            client_socket.send((data + rand_passwd).encode('utf-8'))
            return
        
        if data.endswith(",map"):
            userInfos = data.replace(",map","")
            print(userInfos)
            #格式化处理并写入文件
            User_Judge.format_write_infos_to_file(userInfos)
            return
        
        if data.startswith("send_infos"):
            userInfos = User_Judge.send_theFormat_infos()
            #self.send_data(userInfos)
            client_socket.send((userInfos).encode('utf-8'))
            return
        #输出信息
        if(data == "first_connected"):
            client_socket.send("_Tips_连 接 服务器 成功!".encode('utf-8'))
            return
        #绘制直方图
        if data == "Enable_histogram":
            self.show_histogram()
            return
        if data == "Turn_off_histogram":
            self.close_histogram()
            return
         #绘制茎叶
        if data == "Enable_leaf":
            self.draw_stem_leaf(client_socket)
            return
        if data == "Turn_off_leaf":
            self.close_leaf()
            return


    def show_histogram(self):
        # 在子线程中显示直方图
        self.close_leaf()
        threading.Thread(target=self.draw_histogram).start()
        
    def draw_histogram(self):
        # 创建直方图实例
        if not self.dd:
            self.s_dict = s_info.get_stuDict()  # 获取学生信息字典
            self.dd = Draw_Data(self.s_dict)  # 初始化直方图对象
            # 显示直方图
        self.dd.show_histogram()

    def draw_stem_leaf(self,client_socket):
        if not self.ds:
            self.s_dict = s_info.get_stuDict()  # 获取学生信息字典
            self.ds = Draw_Data(self.s_dict)  # 初始化直方图对象
            # 显示直方图
            s  = self.ds.show_stem_leaf()
            client_socket.send(s.encode('utf-8'))
        

    def close_histogram(self):
        # 关闭直方图
        if self.dd:
            self.dd.close_histogram()
            self.dd = None

    def close_leaf(self):
        if self.ds:
            self.ds = None

    def handle_client(self, client_socket, client_address):
        print(f"Client Received connection from {client_address}")
        # 构造要发送给客户端的数据
        while True:
            try:
                data = client_socket.recv(4096).decode('utf-8')
                if not data: # 检查是否为空
                    break

                print(f"Received data from {client_address}: {data}")
                #更具我发送的指令既字符串判断要执行的逻辑操作
                self.check_oper(data,client_socket)
                ##############逻辑实现    
                
            except Exception as e:
                print(f"Error: {e}")
                break

        print(f"Connection with {client_address} closed.")
        client_socket.close()


    def start(self):
        print("服务器等待连接:... ...")
        while True:
            client_socket, client_address = self.server_socket.accept()
            client_thread = threading.Thread(target=self.handle_client, args=(client_socket, client_address))
            client_thread.start()
            